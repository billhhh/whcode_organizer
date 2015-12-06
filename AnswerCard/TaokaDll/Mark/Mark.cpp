// Mark.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TraversingFile/TraversingFile.h"
#include <cv.h>
#include <string>
#include <highgui.h>
#include "TimeCounter.h"
#include "../Taoka/MarkAC.h"
#include "../XmlIO/XmlIO.h"
#include "../Taoka/ACStructs.h"
#include <fstream>
#include <bitset>
#include <iomanip>
//#include <atltrace.h>
using namespace std;
using namespace cv;
#pragma comment(lib,"../debug/Taoka.lib")
#pragma comment(lib,"../debug/XmlIO.lib")


int SaveResultToFile(Result rt,string path,string filename);
int CustomSaveResultToFile(Result rt,string path,string filename);
void DrawAnswerToImgFile(Mat img,string filename,Result result,Size rectSize,Rect barPos);
void SaveCropArea(vector<CropAreaResult> car,string path,string filename);

//转换result格式
void AC_RST2Result(Result &result,const AC_RST &acrst)
{
	result.angle=acrst.angle;
	result.errFlag=acrst.errFlag;
	//转换客观题答案结构体
	result.answerResult.suspectFlag=acrst.answerResult.suspectFlag;
	for (int i=acrst.answerResult.answerCount-1;i>=0;i--)
	{
		PerquestionResult pqrst;
		pqrst.questionId=acrst.answerResult.answer[i].questionId;
		string tmp=string(acrst.answerResult.answer[i].answer,acrst.answerResult.answer[i].answer+4);
		//pqrst.answer=HexString2Int(tmp);
				pqrst.answer=acrst.answerResult.answer[i].answer;
		pqrst.suspectFlag=acrst.answerResult.answer[i].suspectFlag;
		for (int j=acrst.answerResult.answer[i].answerPosCount-1;j>=0;j--)
		{
			pqrst.answerPos.push_back(acrst.answerResult.answer[i].answerPos[j]);
		}
		result.answerResult.answer.push_back(pqrst);
	}
	//转换条码识别结果结构体
	for (int i=acrst.barResultCount-1;i>=0;i--)
	{
		BarResult brst;
		brst.errflag=acrst.barResult[i].errflag;
		brst.barType=acrst.barResult[i].barType;
		brst.bar=acrst.barResult[i].bar;
		result.barResult.push_back(brst);
	}
	//转换裁切区域结果
	for (int i=acrst.cropAreaResultCount-1;i>=0;i--)
	{
		CropAreaResult crst;
		crst.groupNum=acrst.cropAreaResult[i].groupNum;
		crst.isSecret=acrst.cropAreaResult[i].isSecret;
		crst.rect=acrst.cropAreaResult[i].cropRect;
		crst.name=acrst.cropAreaResult[i].name;
		result.cropAreaResult.push_back(crst);
	}
	//转换预定义填涂点识别结果
	for (int i=acrst.cfpResultCount-1;i>=0;i--)
	{
		FillingPointsResult fprst;
		fprst.name=acrst.cfpResult[i].name;
		fprst.type=acrst.cfpResult[i].fPType;
		fprst.suspectFlag=acrst.cfpResult[i].suspectFlag;
		for (int j=acrst.cfpResult[i].fillingResultCount-1;j>=0;j--)
		{
			PerFPResult pfprst;
			pfprst.result=acrst.cfpResult[i].fillingResult[j].result;
			pfprst.suspectFlag=acrst.cfpResult[i].fillingResult[j].suspectFlag;
			for (int k=acrst.cfpResult[i].fillingResult[j].resultPosCount-1;k>=0;k--)
			{
				pfprst.resultPos.push_back(acrst.cfpResult[i].fillingResult[j].resultPos[k]);
			}
			fprst.fillingResult.push_back(pfprst);

		}
		result.cfpResult.push_back(fprst);
	}

}


int _tmain(int argc, char* argv[])
{

	if (argc<3)
	{
		cout<<"//////////////////////////////////////////////////////////////////////////////"<<endl<<"参数说明"<<endl
			<<"参数一：卡格式描述文件路径"<<endl<<"参数二：扫描图像(jpg格式)所在文件夹"<<endl<<"参数三：是否是正反面模式"<<endl<<"参数四：标记点宽度范围阈值（可为空）"<<endl
			<<"参数五：标记点高度范围阈值（可为空）"<<endl
			<<"//////////////////////////////////////////////////////////////////////////////"<<endl;
		getchar();
		return -1;
	}
	char *xmlFilepath = argv[1];
	string path = string(argv[2]);
	
	//unsigned int a = 0x12345678;
	//printf("%x",*((unsigned char *)(&a)+1)+1);
	//char str[]="abcdefghijklmnopqrstuvwxyz";
	//char *pchar=str;
	//int * point=(int *)(str+4);
	//short int * pshort=(short int * )(str+3);
	//printf("%c%c%c",*(++pchar),*((char *)(++point)),*((char *)(++pshort)));

	//////////////////////////////////卡格式文件读取////////////////////////////////////////
//	char * xmlFilepath = "I:\\答题卡项目\\新数据\\类型四\\卡格式\\dl.xml";
//	char * xmlFilepath = "I:\\答题卡项目\\新数据\\维护期\\参考点识别异常\\5.xml";
//	char * xmlFilepath = "I:\\答题卡项目\\新数据\\error\\6.xml";
//	char * xmlFilepath = "I:\\答题卡项目\\新数据\\维护期\\5.xml";
//	char * xmlFilepath = "I:\\答题卡项目\\新数据\\广外新算法识别有误_507\\6.xml";
	//char * xmlFilepath = "I:\\答题卡项目\\新数据\\蜀山图片\\1.xml";
	//xmlFilepath = "D:\\ACTest\\whtest2_F.xml";

	int acinfoaddress;
	int actype;
//	xmlFilepath="I:\\答题卡项目\\新数据\\类型三虚拟同步头报错\\17_1.xml";
	int returnValue=GetTKInfo(xmlFilepath,actype,acinfoaddress);
	
// 	Cum_TK_info3 *cumtkinfo;
// 	GetCum_TkInfo3(acinfoaddress,&cumtkinfo);
// 	freeCumTkInfo3(cumtkinfo);

	AcArgs acargs;
// 	TK_info3 acinfo;
// 	XmlIo xmlIo;
// 	int returnValue = xmlIo.Read(xmlFilepath,acinfo);
	if (returnValue)
	{
		cout<<"卡格式文件读取异常，异常代码："<<returnValue<<endl;
		getchar();
		return 1;
	}
	///////////////////////////////////遍历文件///////////////////////////////////////
	acargs.areaThreshold=acargs.sensibilityThresh=0;
	acargs.xRangeScale=3;
	acargs.yRangeScale=4;
	acargs.sensibilityThresh=0;
	acargs.areaThreshold=1.2;
	acargs.seSize=0.1;
// 	int (*n)[10];
// 	cout<<sizeof(n)<<endl;


	//待遍历文件夹
//	string path ="I:\\答题卡项目\\新数据\\参考点错误\\b\\";
//	string path ="I:\\答题卡项目\\新数据\\cet4\\错位\\";
//	string path ="I:\\答题卡项目\\新数据\\error\\";
//	string path ="I:\\答题卡项目\\新数据\\维护期\\参考点识别异常\\time.txt";
//	string path ="I:\\答题卡项目\\新数据\\类型四\\lxa\\";
//	string path ="I:\\答题卡项目\\新数据\\江西中考识别报错\\江西中考地生格式未找到\\";
	//string path ="I:\\答题卡项目\\新数据\\蜀山图片\\";
	//path ="D:\\ACTest\\";

	int flag=1;


	bool isSingle=true;
	//if(argc>=4)
	//	isSingle = argv[3];
//	AcArgs acargs;

// 	for (unsigned int i=0;i<path.size();i++)
// 	{
// 		if (path[i] == '/')
// 		{
// 			path[i] = '\\';
// 		}		
// 	}
	
	string filename;
	string rFilename;
	string fFilename;
	
	////////////////////////////////////计时器//////////////////////////////////////
	LARGE_INTEGER startCount;
	LARGE_INTEGER endCount;
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	/////////////////////////////////////清空文件///////////////////////////////////////
	ofstream clear(path+"result.txt",ios::trunc);	
	clear.close();
	clear.open(path+"error.txt",ios::trunc);
	clear.close();
	clear.open(path+"time.txt",ios::trunc);
	clear.close();
// 	clear.open(path+"barerr.txt",ios::trunc);
// 	clear.close();
	int count=0;
	//////////////////////////////////////////////////////////////////////////
	int pos=path.find(".txt",path.length()-4);
	int tpos=path.rfind('\\',path.length()-1);
	string tpath=path.substr(0,tpos+1);
	if (pos!=path.npos)
	{
		fstream imgread(path,ios::in);
		if (!imgread)
		{
			cout<<"txt文件读取异常！"<<endl;
			getchar();
			imgread.close();
			exit(0);
		}
		if (isSingle) //是否单面
		{
			while(getline(imgread,fFilename))
			{
				count++;
				cout<<"\n第"<<count<<"个文件"<<endl;
				cout<<fFilename<<endl;			//输出文件名
				string fffilename;
				int fffpos=fFilename.rfind("jpg");
				fFilename=fFilename.substr(0,fffpos+3);

				Mat fRaw = imread(fFilename);		//读取文件
				if ((!fRaw.data))
				{
					cout<<"第"<<count<<"行:"<<filename<<"图像文件读取异常"<<endl;
					cout<<"按任意键继续。。。"<<endl;
				//	getchar();
					continue;
				}
				Mat fGray;
				cvtColor(fRaw,fGray,CV_RGB2GRAY);
				string gpath=path+"time.txt";
				ofstream gout(gpath,ios::app);
				//计算结果
				AC_RST *fAC_rt;
				Result fRT;
				fRT.answerResult.answer.clear();

				fRT.errFlag=0;  //初始化，标记未出错
   			//计时开始		
				QueryPerformanceCounter(&startCount);
				//【核心函数】正式进入判别单面答题卡的函数
				//(uchar* img,cv::Size imgSize, int actype,int tkinfoAddress,AC_RST ** pResult,AcArgs acargs【用户可调参数集】)
				returnValue = MarkTaokaSinglePage(fGray.data,fGray.size(),actype,acinfoaddress,&fAC_rt,acargs);
				if (returnValue)
				{
					cout<<"识别出错:"<<returnValue<<endl;
					gout<<fFilename<<returnValue<<endl;
					gout.close();
					continue;
				}
				//计时结束
				QueryPerformanceCounter(&endCount);
				double elapsed = (double)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart*1000;  //计算的时间
				cout << "耗时：" << elapsed <<"ms"<< endl;
				/*gout<<filename<<","<<elapsed<<"ms"<< endl;
				gout.close();*/
				AC_RST2Result(fRT,*fAC_rt);

				//输出结果
				//SaveResultToFile(rt,path+"result.txt",filename);
				SaveResultToFile(fRT,path,fFilename);
				//保存含答案的图像

				unsigned found = fFilename.rfind('\\',fFilename.length()-1);
				string filePath;
				if (found==std::string::npos)
				{
					found = fFilename.rfind('\\',fFilename.length()-1);
					if (found==std::string::npos)
					{
						cout<<"filename error"<<endl;
						continue;
					}
				}
				filePath = fFilename.substr(0,found+1);
				char buf[10];
				sprintf(buf,"%d",count);
				string fname = string(buf)+fFilename.substr(found+1,fffpos+3);
				CreateDirectory((tpath+"识别结果\\").c_str(),NULL);
				if(flag)	
				{
					DrawAnswerToImgFile(fRaw,tpath+"识别结果\\"+fname,fRT,Size(28,16),Rect());

				}


				//保存裁切区域
				// 			if (fRT.cropAreaResult.size()>0)
				// 			{
				// 				CreateDirectory((filePath+"裁切区域\\").c_str(),NULL);
				// 				SaveCropArea(rt.cropAreaResult,filePath,name);
				// 			}
				if (returnValue)
				{
					//			ATLTRACE("%s\n",filename.c_str());
					cout<<"答题卡识别异常，异常代码"<<returnValue<<endl;
				}else
				{
					cout<<"答题卡识别正常"<<endl;
				}
				freeResult(fAC_rt);
			}
			imgread.close();
		}
		else
		{
			//双面
			while(getline(imgread,fFilename)&&getline(imgread,rFilename))
			{
				count++;
				cout<<"\n第"<<count<<"个文件"<<endl;
				cout<<fFilename<<endl;			//输出文件名
				string fffilename;
				int fffpos=fFilename.rfind("jpg");
				fFilename=fFilename.substr(0,fffpos+3);

				Mat fRaw = imread(fFilename);		//读取文件
				Mat rRaw = imread(rFilename);		//读取文件
				if ((!fRaw.data)&&(!rRaw.data))
				{
					cout<<"第"<<count<<"行:"<<filename<<"图像文件读取异常"<<endl;
					cout<<"按任意键继续。。。"<<endl;
					getchar();
					continue;
				}
				Mat fGray,rGray;
				cvtColor(fRaw,fGray,CV_RGB2GRAY);
				cvtColor(rRaw,rGray,CV_RGB2GRAY);
				string gpath=path+"time.txt";
				ofstream gout(gpath,ios::app);
				//计算结果
				AC_RST *fAC_rt,*rAC_rt;
				Result fRT,rRT;
				fRT.answerResult.answer.clear();
				fRT.errFlag=0;
				rRT.answerResult.answer.clear();
				rRT.errFlag=0;

				//计时开始		
				QueryPerformanceCounter(&startCount);
				returnValue = MarkTaokaDoublePage(fGray.data,fGray.size(),rGray.data,rGray.size(),actype,acinfoaddress,&fAC_rt,&rAC_rt,acargs);
				if (returnValue)
				{
					cout<<"识别出错:"<<returnValue<<endl;
					gout<<fFilename<<returnValue<<endl;
					gout<<rFilename<< endl;
					gout.close();
					continue;
				}
				//计时结束
				QueryPerformanceCounter(&endCount);
				double elapsed = (double)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart*1000;
				cout << "耗时：" << elapsed <<"ms"<< endl;
				/*gout<<filename<<","<<elapsed<<"ms"<< endl;
				gout.close();*/
				AC_RST2Result(fRT,*fAC_rt);
				AC_RST2Result(rRT,*rAC_rt);

				//输出结果
				//SaveResultToFile(rt,path+"result.txt",filename);
				SaveResultToFile(fRT,path,fFilename);
				SaveResultToFile(rRT,path,rFilename);
				//保存含答案的图像

				unsigned found = fFilename.rfind('\\',fFilename.length()-1);
				string filePath;
				if (found==std::string::npos)
				{
					found = fFilename.rfind('\\',fFilename.length()-1);
					if (found==std::string::npos)
					{
						cout<<"filename error"<<endl;
						continue;
					}
				}
				filePath = fFilename.substr(0,found+1);
				string fname = fFilename.substr(found+1,fffpos+3);
				string rname = rFilename.substr(found+1,rFilename.length());
				CreateDirectory((tpath+"识别结果\\").c_str(),NULL);
				if(flag)	
				{
					DrawAnswerToImgFile(fRaw,tpath+"识别结果\\"+fname,fRT,Size(28,16),Rect());
					DrawAnswerToImgFile(rRaw,tpath+"识别结果\\"+rname,rRT,Size(28,16),Rect());

				}


				//保存裁切区域
				// 			if (fRT.cropAreaResult.size()>0)
				// 			{
				// 				CreateDirectory((filePath+"裁切区域\\").c_str(),NULL);
				// 				SaveCropArea(rt.cropAreaResult,filePath,name);
				// 			}
				if (returnValue)
				{
					//			ATLTRACE("%s\n",filename.c_str());
					cout<<"答题卡识别异常，异常代码"<<returnValue<<endl;
				}else
				{
					cout<<"答题卡识别正常"<<endl;
				}
				freeResult(fAC_rt);
				freeResult(rAC_rt);
			}
			imgread.close();
		}
	}else
	{
		TraversingFile t;
		t.Init(path,"jpg");
		while (!t.GetFileName(filename))
		{
			cout<<"\n第"<<t.GetFileCounter()<<"个文件"<<endl;
			cout<<filename<<endl;			//输出文件名
			Mat raw = imread(filename);		//读取文件
			if (!raw.data)
			{
				cout<<filename<<"图像文件读取异常"<<endl;
				cout<<"按任意键继续。。。"<<endl;
				continue;
			}
			Mat gray;
			cvtColor(raw,gray,CV_RGB2GRAY);
			string gpath=path+"time.txt";
			ofstream gout(gpath,ios::app);
			//计算结果
			Result rt;
			AC_RST *ac_rt;
			rt.answerResult.answer.clear();
			rt.errFlag=0;
			//计时开始		
			QueryPerformanceCounter(&startCount);
			returnValue = MarkTaokaSinglePage(gray.data,gray.size(),actype,acinfoaddress,&ac_rt,acargs);
			//计时结束
			QueryPerformanceCounter(&endCount);
			double elapsed = (double)(endCount.QuadPart - startCount.QuadPart) / freq.QuadPart*1000;
			cout << "耗时：" << elapsed <<"ms"<< endl;
			count++;
			gout<<filename<<","<<elapsed<<" ms"<< endl;
			gout.close();

			//输出结果
			//SaveResultToFile(rt,path+"result.txt",filename);
			AC_RST2Result(rt,*ac_rt);
			CustomSaveResultToFile(rt,path,filename);
			//保存含答案的图像

			unsigned found = filename.rfind('\\',filename.length()-1);
			string filePath;
			if (found==std::string::npos)
			{
				found = filename.rfind('\\',filename.length()-1);
				if (found==std::string::npos)
				{
					cout<<"filename error"<<endl;
					continue;
				}
			}
			filePath = filename.substr(0,found+1);
			string name = filename.substr(found+1,filename.length());
			CreateDirectory((filePath+"识别结果\\").c_str(),NULL);
			if(flag)	
				DrawAnswerToImgFile(raw,filePath+"识别结果\\"+name,rt,Size(28,16),Rect());

			//保存裁切区域
// 			if (rt.cropAreaResult.size()>0)
// 			{
// 				CreateDirectory((filePath+"裁切区域\\").c_str(),NULL);
// 				SaveCropArea(rt.cropAreaResult,filePath,name);
// 			}
			if (returnValue)
			{
				//			ATLTRACE("%s\n",filename.c_str());
				cout<<"答题卡识别异常，异常代码"<<returnValue<<endl;
			}else
			{
				cout<<"答题卡识别正常"<<endl;
			}
			if(!returnValue)
				freeResult(ac_rt);
		}
	}
	
	cout<<endl<<"识别完成"<<endl;
	getchar();
	return 0;
}
//将答案加上标注保存
void DrawAnswerToImgFile(Mat img,string filename,Result result,Size rectSize,Rect barPos)
{
	Rect rect;
	rect.width = rectSize.width;
	rect.height = rectSize.height;
	Mat warp_mat = getRotationMatrix2D(cv::Point2d(img.cols>>1,img.rows>>1),result.angle,1);
	warpAffine( img, img, warp_mat, img.size());
	for (unsigned int i = 0;i<result.answerResult.answer.size();i++)
	{
		for (unsigned int j = 0;j<result.answerResult.answer[i].answerPos.size();j++)
		{
			rect.x = result.answerResult.answer[i].answerPos[j].x-(rect.width>>1);
			rect.y = result.answerResult.answer[i].answerPos[j].y-(rect.height>>1);
			if (result.answerResult.answer[i].suspectFlag==1)
			{
				rectangle(img,rect,Scalar(255,0,0),2);
			}else if (result.answerResult.answer[i].suspectFlag==2)
			{
				rectangle(img,rect,Scalar(0,0,255),2);
			}else
			rectangle(img,rect,Scalar(0,255,0),2);
		}		
	}
	for (unsigned int i = 0;i<result.cfpResult.size();i++)
	{
		for (unsigned int j = 0;j<result.cfpResult[i].fillingResult.size();j++)
		{
			for (unsigned int k = 0;k<result.cfpResult[i].fillingResult[j].resultPos.size();k++)
			{
				rect.x = result.cfpResult[i].fillingResult[j].resultPos[k].x-(rect.width>>1);
				rect.y = result.cfpResult[i].fillingResult[j].resultPos[k].y-(rect.height>>1);
				rectangle(img,rect,Scalar(0,255,0),2);
			}
			
		}		
	}
//	rectangle(img,barPos,Scalar(0,255,0),1);
	for (int i = result.barResult.size()-1;i>=0;i--)
	{
		cv::putText(img,result.barResult[i].bar,cv::Point2d(barPos.x,barPos.y),FONT_HERSHEY_COMPLEX,.6,Scalar(0,255,0),2);
	}

	imwrite(filename,img);
}
int CustomSaveResultToFile(Result rt,string path,string filename)
{
	string resultpath=path+"result.txt";
	string errorpath=path+"error.txt";
//	string barerrorpath=path+"barerr.txt";
	ofstream fout(resultpath,ios::app);
	ofstream eout(errorpath,ios::app);
//	ofstream bout(barerrorpath,ios::app);
	bool flag=true;
	
	if(rt.errFlag!=0)
	{
		eout<<filename<<"出错，异常代码:"<<rt.errFlag<<endl;
		eout.close();
		fout.close();
		return 0;
	}
	fout<<filename<<',';

	if (rt.barResult.size()>0)
	{
	//	fout<<"条形码识别结果"<<endl;
		for (int i=0;i<rt.barResult.size();i++)
		{
			if (rt.barResult[i].errflag)
			{
//				bout<<filename<<endl;
			}else
			fout<<rt.barResult[i].bar<<",";
		}
		//fout<<',';
	}

	if (rt.cfpResult.size()>0)
	{
		for (int i=0;i<rt.cfpResult.size();i++)
		{
			FillingPointsResult fpResult=rt.cfpResult[i];
			fout<<fpResult.name<<",";
			switch(fpResult.type)
			{
			case PaperType:
				{
					ushort tmpAnswer = fpResult.fillingResult[0].result;
					string strAnswer;
					for (int s = 0;s<15;s++)
					{
						ushort tmp = 1<<s;
						if (tmp&tmpAnswer)
						{
							strAnswer += '0'+s;
						}
					}
					fout<<strAnswer<<",";
					break;

				}

			case Absent:
				{
					fout<<fpResult.fillingResult[0].result<<",";
					break;
				}

			case Discipline:
				{
					fout<<fpResult.fillingResult[0].result<<",";
					break;
				}


			case OptionalQuestion:
				{
					for (int j=0;j<fpResult.fillingResult.size();j++)
					{
						ushort tmpAnswer = fpResult.fillingResult[j].result;
						string strAnswer;
						for (int s = 0;s<15;s++)
						{
							ushort tmp = 1<<s;
							if (tmp&tmpAnswer)
							{
								strAnswer += '0'+s;
							}
						}
						fout<<strAnswer;
					}
					fout<<",";
					break;
				}

			case CourseNumZeroFirst:
			case ExamHallNumZeroFirst:
			case FirstCandidateNumZeroFirst:
			case ExamRoomNumZeroFirst:
			case SeatNumZeroFirst:
			case TickerNumZeroFirst:
				{
					for (int j=0;j<fpResult.fillingResult.size();j++)
					{
						ushort tmpAnswer = fpResult.fillingResult[j].result;
						string strAnswer;
						for (int s = 0;s<15;s++)
						{
							ushort tmp = 1<<s;
							if (tmp&tmpAnswer)
							{
								strAnswer += '0'+s;
							}
						}
						fout<<strAnswer;
					}
					fout<<",";
					break;
				}
			default:
				{
					for (int j=0;j<fpResult.fillingResult.size();j++)
					{
						ushort tmpAnswer = fpResult.fillingResult[j].result;
						string strAnswer;
						for (int s = 0;s<9;s++)
						{
							ushort tmp = 1<<s;
							if (tmp&tmpAnswer)
							{
								strAnswer += '1'+s;
							}
						}
						ushort tmp = 1<<9;
						if(tmp&tmpAnswer)
							strAnswer +='0';
						fout<<strAnswer;
					}
					fout<<",";
					break;
				}

			}

		}
//		fout<<endl;
	}

	bool eoutflag=false;
	for (int i=0;i<rt.answerResult.answer.size();i++)
	{	
		if (rt.answerResult.answer[i].suspectFlag!=0)
		{
//			fout<<"####";
			fout<<"0000";
			if(flag)
			{
//				eout<<endl;
				eout<<filename<<',';
				flag=false;
				eoutflag=true;
			}
			eout<<"  题"<<rt.answerResult.answer[i].questionId<<"可疑";


		}else
		{
			ushort tmpAnswer = rt.answerResult.answer[i].answer;
			fout<<setw(4)<<setfill('0')<<hex<<rt.answerResult.answer[i].answer;
		}

	}
	if(eoutflag)
		eout<<endl;
	fout<<endl;
	fout.close();
	eout.close();
	return 0;
}



//保存答案到txt
int SaveResultToFile(Result rt,string path,string filename)
{
	string resultpath=path+"result.txt";
	string errorpath=path+"error.txt";
	ofstream fout(resultpath,ios::app);
	ofstream eout(errorpath,ios::app);
	bool flag=true;
	if(rt.errFlag!=0)
	{
		eout<<filename<<"出错，异常代码:"<<rt.errFlag<<endl;
		eout.close();
		fout.close();
		return 0;
	}
	fout<<filename<<endl;
	if (rt.barResult.size()>0)
	{
		fout<<"条形码识别结果"<<endl;
		for (int i=0;i<rt.barResult.size();i++)
		{
			switch(rt.barResult[i].barType)
			{
			case PaperTypeBar:
				fout<<"试卷类型: ";
				break;			
			case TickerNumBar:
				fout<<"准考证号: ";
				break;		
			case ExamRoomNumBar:
				fout<<"考室号: ";
				break;			
			case AbsentBar:
				fout<<"缺考: ";
				break;
			}
			fout<<rt.barResult[i].bar<<endl;
		}
	}
	
	if (rt.cfpResult.size()>0)
	{
		fout<<"预定义填涂点识别结果"<<endl;
		for (int i=0;i<rt.cfpResult.size();i++)
		{
			FillingPointsResult fpResult=rt.cfpResult[i];
			switch(fpResult.type)
			{
			case PaperType:
				{
					fout<<"试卷类型"<<"   ";
					ushort tmpAnswer = fpResult.fillingResult[0].result;
					string strAnswer;
					for (int s = 0;s<15;s++)
					{
						ushort tmp = 1<<s;
						if (tmp&tmpAnswer)
						{
							strAnswer += '0'+s;
						}
					}
					fout<<strAnswer;
					break;

				}
				
			case Absent:
				{
					fout<<"缺考：  ";
					fout<<fpResult.fillingResult[0].result<<endl;
					break;
				}
				
			case Discipline:
				{
					fout<<"违纪：  ";
					fout<<fpResult.fillingResult[0].result<<endl;
					break;
				}
				

			case OptionalQuestion:
				{
					fout<<fpResult.name<<":  ";
					for (int j=0;j<fpResult.fillingResult.size();j++)
					{
						ushort tmpAnswer = fpResult.fillingResult[j].result;
						string strAnswer;
						for (int s = 0;s<15;s++)
						{
							ushort tmp = 1<<s;
							if (tmp&tmpAnswer)
							{
								strAnswer += '0'+s;
							}
						}
						fout<<strAnswer;
					}
					fout<<endl;
					break;
				}
				
			case CourseNumZeroFirst:
			case ExamHallNumZeroFirst:
			case FirstCandidateNumZeroFirst:
			case ExamRoomNumZeroFirst:
			case SeatNumZeroFirst:
			case TickerNumZeroFirst:
				{
					fout<<fpResult.name<<":  ";
					for (int j=0;j<fpResult.fillingResult.size();j++)
					{
						ushort tmpAnswer = fpResult.fillingResult[j].result;
						string strAnswer;
						for (int s = 0;s<15;s++)
						{
							ushort tmp = 1<<s;
							if (tmp&tmpAnswer)
							{
								strAnswer += '0'+s;
							}
						}
					fout<<strAnswer;
					}
					fout<<endl;
					break;
				}
			default:
				{
					fout<<fpResult.name<<":  ";
					for (int j=0;j<fpResult.fillingResult.size();j++)
					{
						ushort tmpAnswer = fpResult.fillingResult[j].result;
						string strAnswer;
						for (int s = 0;s<9;s++)
						{
							ushort tmp = 1<<s;
							if (tmp&tmpAnswer)
							{
								strAnswer += '1'+s;
							}
						}
						ushort tmp = 1<<9;
						if(tmp&tmpAnswer)
							strAnswer +='0';
						fout<<strAnswer;
					}
					fout<<endl;
					break;
				}
				
			}
			
		}
	}

	for (int i=0;i<rt.answerResult.answer.size();i++)
	{	
		ushort tmpAnswer = rt.answerResult.answer[i].answer;
		string strAnswer;
		for (int j = 0;j<15;j++)
		{
			ushort tmp = 1<<j;
			if (tmp&tmpAnswer)
			{
				strAnswer += 'A'+j;
			}
		}
		if (strAnswer.length()==0)
		{
			strAnswer = "未作答";
		}
		fout<<"\t题"<<rt.answerResult.answer[i].questionId<<":"<<strAnswer;
		//fout<<setw(4)<<setfill('0')<<hex<<rt.answerResult.answer[i].answer;
		if (rt.answerResult.answer[i].suspectFlag!=0)
		{
//			fout<<"\t题"<<rt.answerResult.answer[i].questionId<<":可疑";
			fout<<"  :可疑  ";
			if(flag)
			{
				eout<<filename<<endl;
				flag=false;
			}
			eout<<"\t题"<<rt.answerResult.answer[i].questionId<<"可疑"<<endl;
			

		}
			
		
		
	}
	fout<<endl;
	fout.close();
	eout.close();
	return 0;
}
/*
//保存答案到txt
int SaveResultToFile(Result rt,string path,string filename)
{
	ofstream fout(path+"result.txt",ios::app);
	fout<<filename<<endl;
	fout<<"倾斜角度为："<<rt.angle<<endl;
 	fout<<"条形码识别结果"<<endl;
	for (int i=0;i<rt.barResult.size();i++)
	{
		switch(rt.barResult[i].barType)
		{
		case PaperTypeBar:
			fout<<"试卷类型: ";
			break;			
		case TickerNumBar:
			fout<<"准考证号: ";
			break;		
		case ExamRoomNumBar:
			fout<<"考室号: ";
			break;			
		case AbsentBar:
			fout<<"缺考: ";
			break;
		}
		fout<<rt.barResult[i].bar<<endl;
	}
	if (rt.cfpResult.size()>0)
	{
		fout<<"用户自定义填涂点识别结果(结果为二进制)"<<endl;
		for (int i=0;i<rt.cfpResult.size();i++)
		{
			fout<<rt.cfpResult[i].name<<":"<<bitset<sizeof(ushort)*8>(rt.cfpResult[i].fillingResult);
			if (rt.cfpResult[i].suspectFlag)
			{
				fout<<"可疑！"<<endl;
			}else
				fout<<endl;
		}
	}
	for (int i=0;i<rt.answerResult.answer.size();i++)
	{
		ushort tmpAnswer = rt.answerResult.answer[i].answer;
		string strAnswer;
		for (int j = 0;j<15;j++)
		{
			ushort tmp = 1<<j;
			if (tmp&tmpAnswer)
			{
				strAnswer += 'A'+j;
			}
		}
		if (strAnswer.length()==0)
		{
			strAnswer = "未作答";
		}
		fout<<"题"<<rt.answerResult.answer[i].questionId<<":\t"<<strAnswer;
		if (rt.answerResult.answer[i].suspectFlag!=0)
		{
			fout<<"\t可疑!"<<endl;
		}else
			fout<<endl;

	}
	fout<<endl;
	fout.close();
	return 0;
}
*/
void SaveCropArea(vector<CropAreaResult> car,string path,string filename)
{
	int idx = filename.rfind('.');
	string prefix = filename.substr(0,idx);
	string suffix = filename.substr(idx,filename.length()-1);
	for (unsigned int i=0;i<car.size();i++)
	{
//		imwrite(path+"裁切区域\\"+prefix+'_'+car[i].name+'_'+suffix,car[i].img);
	}
}