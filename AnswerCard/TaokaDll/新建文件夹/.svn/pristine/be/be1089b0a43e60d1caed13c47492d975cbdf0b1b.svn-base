#include "stdafx.h"
#include "ACStructs.h"
#include "MarkAC.h"
#include "DetectPerAC.h"
#include "TranStruct.h"
#include <highgui.h>



//答题卡识别接口
int MarkAnswerCard(uchar* img,cv::Size size, int actype,int acinfoAddress,AC_RST **pResult,AcArgs acargs)
{
	//Result result;
	//void * acinfoData;
	Result result;
	*pResult=new AC_RST;
	Mat acimg(size, CV_8UC1, img, Mat::AUTO_STEP);
	int returnValue=0;
	if (actype==1||actype==2)
	{
		AC_info *acinfo=(AC_info *)acinfoAddress;
		if(acinfo->ac_type==1||acinfo->ac_type==2)
			returnValue=MarkAnswerCard(acimg,*acinfo,result,acargs);
		else 
			return ACTYPE_NOT_MATCH;
	}else if (actype==3||actype==4)
	{
//		ac_info3point=(AC_info3 *)acinfoAddress;
		AC_info3 *acinfo3=(AC_info3 *)acinfoAddress;
		if(acinfo3->ac_type==3)
			returnValue=MarkAnswerCard(acimg,*acinfo3,result,acargs);
		else
			return ACTYPE_NOT_MATCH;
	} 
	else
	{
		return ACTYPE_NOT_MATCH;
	}
	Result2AC_RST(result,**pResult);
	return returnValue;

}

//套卡识别 单张图片
int MarkTaokaSinglePage(uchar* img,cv::Size imgSize, int actype,int tkinfoAddress,AC_RST ** pResult,AcArgs acargs)
{
	Mat acimg(imgSize, CV_8UC1, img,Mat::AUTO_STEP);
	int returnValue=0;
	Result result;
	*pResult=new AC_RST;
	if (actype==3||actype==4)
	{
		TK_info3 *tkinfo3=(TK_info3 *)tkinfoAddress;
		for (int i=tkinfo3->tkinfo.size()-1;i>=0;i--)
		{
			returnValue=MarkAnswerCard(acimg,tkinfo3->tkinfo[i].acinfo[0],result,acargs);
			if(returnValue!=0&&returnValue<YMARKERS_ERR_BASE+2)
				continue;
			else
			{
				result.pageId=tkinfo3->tkinfo[i].pageId;
				break;
			}
		}
	} 
	else
	{
		TK_info *tkinfo=(TK_info *)tkinfoAddress;
		
		for (int i=tkinfo->tkinfo.size()-1;i>=0;i--)
		{
			returnValue=MarkAnswerCard(acimg,tkinfo->tkinfo[i].acinfo[0],result,acargs);
			if(returnValue!=0&&returnValue<YMARKERS_ERR_BASE+2)
				continue;
			else
			{
				result.tkId=tkinfo->tkinfo[i].tkId;
				result.pageId=tkinfo->tkinfo[i].pageId;
				break;
			}
		}
	}
	
	Result2AC_RST(result,**pResult);
	
	return returnValue;
}
//套卡识别 正反面
int MarkTaokaDoublePage(uchar* frontImg,cv::Size fImgSize, uchar* rearImg,cv::Size rImgSize,int actype,int tkinfoAddress,AC_RST ** pFrontResult,AC_RST ** pRearResult,AcArgs acargs)
{
	Mat fImg(fImgSize, CV_8UC1, frontImg, Mat::AUTO_STEP);
	Mat rImg(rImgSize, CV_8UC1, rearImg, Mat::AUTO_STEP);
	Result fResult,rResult;
	*pFrontResult=new AC_RST;
	*pRearResult=new AC_RST;
	int returnValue=0;
	if (actype==3||actype==4)
	{
		TK_info3 *tkinfo3=(TK_info3 *)tkinfoAddress;
		for (int i=tkinfo3->tkinfo.size()-1;i>=0;i--)
		{
			if(tkinfo3->tkinfo[i].acinfo[0].isFront==true)
				returnValue=MarkAnswerCard(fImg,tkinfo3->tkinfo[i].acinfo[0],fResult,acargs);
			else if(tkinfo3->tkinfo[i].acinfo.size()==2&&tkinfo3->tkinfo[i].acinfo[1].isFront==true)
				returnValue=MarkAnswerCard(fImg,tkinfo3->tkinfo[i].acinfo[1],fResult,acargs);
			if(returnValue!=0&&returnValue<PAGEMAKER_ERR+2)
				continue;
			else
			{
				rResult.pageId=fResult.pageId=tkinfo3->tkinfo[i].pageId;	
				if(tkinfo3->tkinfo[i].acinfo[0].isFront==false)
					returnValue+=MarkAnswerCard(rImg,tkinfo3->tkinfo[i].acinfo[0],rResult,acargs);
				else if(tkinfo3->tkinfo[i].acinfo.size()==2&&tkinfo3->tkinfo[i].acinfo[1].isFront==false)
					returnValue+=MarkAnswerCard(rImg,tkinfo3->tkinfo[i].acinfo[1],rResult,acargs);
				break;
			}
		}
		
	} 
	else
	{
		TK_info *tkinfo=(TK_info *)tkinfoAddress;
		for (int i=tkinfo->tkinfo.size()-1;i>=0;i--)
		{
			if(tkinfo->tkinfo[i].acinfo[0].isFront==true)
				returnValue=MarkAnswerCard(fImg,tkinfo->tkinfo[i].acinfo[0],fResult,acargs);
			else if(tkinfo->tkinfo[i].acinfo.size()==2&&tkinfo->tkinfo[i].acinfo[1].isFront==true)
				returnValue=MarkAnswerCard(fImg,tkinfo->tkinfo[i].acinfo[1],fResult,acargs);
			if(returnValue!=0&&returnValue<YMARKERS_ERR_BASE+2&&returnValue!=REFPOINT_ERROR)
				continue;
			else
			{
				rResult.tkId=fResult.tkId=tkinfo->tkinfo[i].tkId;
				rResult.pageId=fResult.pageId=tkinfo->tkinfo[i].pageId;	
				if(tkinfo->tkinfo[i].acinfo[0].isFront==false)
					returnValue+=MarkAnswerCard(rImg,tkinfo->tkinfo[i].acinfo[0],rResult,acargs);
				else if(tkinfo->tkinfo[i].acinfo.size()==2&&tkinfo->tkinfo[i].acinfo[1].isFront==false)
					returnValue+=MarkAnswerCard(rImg,tkinfo->tkinfo[i].acinfo[1],rResult,acargs);
				break;
			}
		}
	}
	Result2AC_RST(fResult,**pFrontResult);
	Result2AC_RST(rResult,**pRearResult);
	return returnValue;
}
int MarkTaokaSPage(const char *imgPath, int actype,int tkinfoAddress,AC_RST * *pResult,AcArgs acargs)
{
	Mat img=imread(imgPath);
	if (!img.data)
	{
		return -3;
	}
	if (img.channels()==3)
	{
		cvtColor(img,img,CV_RGB2GRAY);
	}
	int returnValue = MarkTaokaSinglePage(img.data,img.size(),actype,tkinfoAddress,pResult,acargs);
	return returnValue;
}
//套卡识别 两张图片 正反面
int MarkTaokaDPage(const char* frontImgPath, const char* rearImgPath,int actype,int tkinfoAddress,AC_RST ** pFrontResult,AC_RST ** pRearResult,AcArgs acargs)
{
	Mat fGray = imread(frontImgPath);		//读取文件
	Mat rGray = imread(rearImgPath);		//读取文件
	if ((!fGray.data)&&(!rGray.data))
	{
		return -3;
	}
	if (fGray.channels()==3)
	{
		cvtColor(fGray,fGray,CV_RGB2GRAY);
	}
	if(rGray.channels()==3)
		cvtColor(rGray,rGray,CV_RGB2GRAY);
	int returnValue = MarkTaokaDoublePage(fGray.data,fGray.size(),rGray.data,rGray.size(),actype,tkinfoAddress,pFrontResult,pRearResult,acargs);
	return returnValue;
}

int GetCum_TkInfo(int tkinfoAddress,Cum_TK_info **cum_tkinfo)
{
	TK_info *tkinfo=(TK_info *)tkinfoAddress;
	*cum_tkinfo=new Cum_TK_info;
	TransTkinfo(*tkinfo,**cum_tkinfo);
	return 0;
}

int GetCum_TkInfo3(int tkinfoAddress,Cum_TK_info3 **cum_tkinfo)
{
	TK_info3 *tkinfo=(TK_info3 *)tkinfoAddress;
	*cum_tkinfo=new Cum_TK_info3;
	TransTkinfo3(*tkinfo,**cum_tkinfo);
	return 0;
}

void freeCumTkInfo(Cum_TK_info *tkinfo)
{
	for (int i=tkinfo->tkInfoCount-1;i>=0;i--)
	{
		for (int j=tkinfo->tkInfo[i].acInfoCount-1;j>=0;j--)
		{
			delete []tkinfo->tkInfo[i].acInfo[j].anchorPointInfo.anchorPt;
			delete []tkinfo->tkInfo[i].acInfo[j].idPoint;
			delete []tkinfo->tkInfo[i].acInfo[j].barGroup;
			for (int k=tkinfo->tkInfo[i].acInfo[j].fillingPointGroupCount-1;k>=0;k--)
			{
				delete [] tkinfo->tkInfo[i].acInfo[j].fillingPointGroup[k].name;
				delete [] tkinfo->tkInfo[i].acInfo[j].fillingPointGroup[k].fillingPoints;
			}
			delete []tkinfo->tkInfo[i].acInfo[j].fillingPointGroup;
			delete []tkinfo->tkInfo[i].acInfo[j].questionInfo;
			for (int k=tkinfo->tkInfo[i].acInfo[j].cropAreaInfoCount-1;k>=0;k--)
			{
				delete []tkinfo->tkInfo[i].acInfo[j].cropAreaInfo[k].name;
			}
			delete []tkinfo->tkInfo[i].acInfo[j].cropAreaInfo;
			delete []tkinfo->tkInfo[i].acInfo[j].refPoint;
			delete []tkinfo->tkInfo[i].acInfo[j].xMarker;
			delete []tkinfo->tkInfo[i].acInfo[j].yMarker;
		}
		delete []tkinfo->tkInfo[i].acInfo;
		
	}
	delete []tkinfo->tkInfo;
	delete tkinfo;
}

void freeCumTkInfo3(Cum_TK_info3 *tkinfo)
{
	for (int i=tkinfo->tkInfoCount-1;i>=0;i--)
	{
		for (int k=tkinfo->tkInfo[i].acInfoCount-1;k>=0;k--)
		{
			delete [] tkinfo->tkInfo[i].acinfo[k].ac_id;
			delete [] tkinfo->tkInfo[i].acinfo[k].anchorPointInfo.anchorPt;
			delete [] tkinfo->tkInfo[i].acinfo[k].pageMarker;
			for (int j= tkinfo->tkInfo[i].acinfo[k].markInfoCunt-1;j>=0;j--)
			{
				delete []  tkinfo->tkInfo[i].acinfo[k].markerInfo[j].xMarker;
				delete []  tkinfo->tkInfo[i].acinfo[k].markerInfo[j].yMarker;
			}
			delete [] tkinfo->tkInfo[i].acinfo[k].markerInfo;
			delete [] tkinfo->tkInfo[i].acinfo[k].barGroup;
			for (int j=tkinfo->tkInfo[i].acinfo[k].fillingPointGroupCount-1;j>=0;j--)
			{
				delete [] tkinfo->tkInfo[i].acinfo[k].fillingPointGroup[j].name;
				for (int l=tkinfo->tkInfo[i].acinfo[k].fillingPointGroup[j].fillingPointsCount-1;l>=0;l--)
				{
					delete [] tkinfo->tkInfo[i].acinfo[k].fillingPointGroup[j].fillingPoints[l].pos;
				}
				delete [] tkinfo->tkInfo[i].acinfo[k].fillingPointGroup[j].fillingPoints;
			}
			delete [] tkinfo->tkInfo[i].acinfo[k].fillingPointGroup;
			delete [] tkinfo->tkInfo[i].acinfo[k].questionInfo;
			for (int j=tkinfo->tkInfo[i].acinfo[k].cropAreaInfoCount-1;j>=0;j--)
			{
				delete [] tkinfo->tkInfo[i].acinfo[k].cropAreaInfo[j].name;
			}
			delete [] tkinfo->tkInfo[i].acinfo[k].cropAreaInfo;
			delete [] tkinfo->tkInfo[i].acinfo[k].refPoint;

		}
		delete []tkinfo->tkInfo[i].acinfo;
	}
	delete []tkinfo->tkInfo;
	delete tkinfo;
}

//释放AC_RST结构体
void freeResult(AC_RST * result)
{
	delete []result->img;
	//删除客观题答案结构体
	for (int i=result->answerResult.answerCount-1;i>=0;i--)
	{
		delete[] result->answerResult.answer[i].answerPos;
	}
	delete []result->answerResult.answer;
	//删除条码识别结果结构体
	for (int i=result->barResultCount-1;i>=0;i--)
	{
		delete []result->barResult[i].bar;
	}
	delete [] result->barResult;
	//删除裁切区域结果
	for (int i=result->cropAreaResultCount-1;i>=0;i--)
	{
		delete []result->cropAreaResult[i].name;
	}
	delete []result->cropAreaResult;
	//删除预定义填涂点识别结果
	for (int i=result->cfpResultCount-1;i>=0;i--)
	{
		delete []result->cfpResult[i].name;
		for (int j=result->cfpResult[i].fillingResultCount-1;j>=0;j--)
		{
			delete []result->cfpResult[i].fillingResult[j].resultPos;
		}
		delete []result->cfpResult[i].fillingResult;
	}
	delete []result->cfpResult;
	delete result;
	
}

