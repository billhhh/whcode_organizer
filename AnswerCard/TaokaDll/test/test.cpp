// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../Taoka/ACStructs.h"
//#include "../XmlIO/XmlIODLL.h"
#include "../Demo/debug_new.h"
#include "../Taoka/MarkAC.h"
#include <string>
using namespace std;
//#pragma comment(lib,"../debug/XmlIoDll.lib")
#pragma comment(lib,"../debug/Taoka.lib")
void Result2AC_RST(const Result &result,AC_RST &acrst)
{
	acrst.errFlag=result.errFlag;
	acrst.angle=result.angle;
	acrst.answerResult.suspectFlag=result.answerResult.suspectFlag;
	acrst.answerResult.answerCount=result.answerResult.answer.size();
	//转换客观题答案结构体
	Perquestion_RST *pqrst=new Perquestion_RST[acrst.answerResult.answerCount];
	acrst.answerResult.answer=pqrst;
	vector<PerquestionResult>::const_iterator iter;
	int i=0;
	for (iter=result.answerResult.answer.begin();iter!=result.answerResult.answer.end();iter++)
	{

		pqrst[i].questionId=iter->questionId;
		pqrst[i].suspectFlag=iter->suspectFlag;
		pqrst[i].answer=iter->answer;
		pqrst[i].answerPosCount=iter->answerPos.size();
		pqrst[i].answerPos=new cv::Point[iter->answerPos.size()];
		vector<cv::Point> ::const_iterator it;
		int j=0;
		for (it=iter->answerPos.begin();it!=iter->answerPos.end();it++)
		{

			pqrst[i].answerPos[j]=*it;
			j++;
		}
		i++;
	}
	//转换条码识别结果结构体
	acrst.barResultCount=result.barResult.size();
	Bar_RST * brst=new Bar_RST[acrst.barResultCount];
	acrst.barResult=brst;
	vector<BarResult>::const_iterator barIter;
	i=0;
	for (barIter=result.barResult.begin();barIter!=result.barResult.end();barIter++)
	{

		brst[i].barType=barIter->barType;
		brst[i].errflag=barIter->errflag;
		int slen=barIter->bar.length();
		char *bar=new char[slen+1];
		memcpy(bar,barIter->bar.c_str(),slen);
		bar[slen]='\0';
		brst[i].bar=bar;
		i++;
	}
	//转换裁切区域结果
	acrst.cropAreaResultCount=result.cropAreaResult.size();
	CropArea_RST *cropAreaRst=new CropArea_RST[acrst.cropAreaResultCount];
	acrst.cropAreaResult=cropAreaRst;
	vector<CropAreaResult>::const_iterator cariter;
	i=0;
	for (cariter=result.cropAreaResult.begin();cariter!=result.cropAreaResult.end();cariter++)
	{

		cropAreaRst[i].groupNum=cariter->groupNum;
		cropAreaRst[i].isSecret=cariter->isSecret;
		cropAreaRst[i].cropRect=cariter->rect;
		int cnamelen=cariter->name.length();
		char *name=new char[cnamelen+1];
		memcpy(name,cariter->name.c_str(),cnamelen);
		name[cnamelen]='\0';
		cropAreaRst[i].name=name;
		i++;
	}

	//转换预定义填涂点识别结果
	acrst.cfpResultCount=result.cfpResult.size();
	FillingPoints_RST *fpRst=new FillingPoints_RST[acrst.cfpResultCount];
	acrst.cfpResult=fpRst;
	vector<FillingPointsResult>::const_iterator fpiter;
	i=0;
	for (fpiter=result.cfpResult.begin();fpiter!=result.cfpResult.end();fpiter++)
	{

		fpRst[i].fPType=fpiter->type;
		fpRst[i].suspectFlag=fpiter->suspectFlag;
		int length=fpiter->name.length();
		char *fpname=new char[length+1];
		memcpy(fpname,fpiter->name.c_str(),length);
		fpname[length]='\0';
		fpRst[i].name=fpname;
		fpRst[i].fillingResultCount=fpiter->fillingResult.size();
		PerFP_RST *pfprst=new PerFP_RST[fpiter->fillingResult.size()];
		fpRst[i].fillingResult=pfprst;
		vector<PerFPResult>::const_iterator pfpiter;
		int j=0;
		for (pfpiter=fpiter->fillingResult.begin();pfpiter!=fpiter->fillingResult.end();pfpiter++)
		{

			pfprst[j].result=pfpiter->result;
			pfprst[j].suspectFlag=pfpiter->suspectFlag;
			pfprst[j].resultPosCount=pfpiter->resultPos.size();
			pfprst[j].resultPos=new cv::Point[pfpiter->resultPos.size()];
			vector<cv::Point> ::const_iterator it;
			int k=0;
			for (it=pfpiter->resultPos.begin();it!=pfpiter->resultPos.end();it++)
			{

				pfprst[j].resultPos[k]=*it;
				k++;
			}

			j++;
		}
		i++;
	}

}
//释放AC_RST结构体
// void freeResult(AC_RST * result)
// {
// 	//删除客观题答案结构体
// 	for (int i=result->answerResult.answerCount-1;i>=0;i--)
// 	{
// 		delete[] result->answerResult.answer[i].answerPos;
// 	}
// 	delete []result->answerResult.answer;
// 	//删除条码识别结果结构体
// 	for (int i=result->barResultCount-1;i>=0;i--)
// 	{
// 		delete []result->barResult[i].bar;
// 	}
// 	delete [] result->barResult;
// 	//删除裁切区域结果
// 	for (int i=result->cropAreaResultCount-1;i>=0;i--)
// 	{
// 		delete []result->cropAreaResult[i].name;
// 	}
// 	delete []result->cropAreaResult;
// 	//删除预定义填涂点识别结果
// 	for (int i=result->cfpResultCount-1;i>=0;i--)
// 	{
// 		delete []result->cfpResult[i].name;
// 		for (int j=result->cfpResult[i].fillingResultCount-1;j>=0;j--)
// 		{
// 			delete []result->cfpResult[i].fillingResult[j].resultPos;
// 		}
// 		delete []result->cfpResult[i].fillingResult;
// 	}
// 	delete []result->cfpResult;
// 	delete result;
// 
// }
void creatResult(Result &result)
{
	result.angle=1;
	result.errFlag=0;
	result.answerResult.suspectFlag=0;
	PerquestionResult pqst;
	for (int i=0;i<20;i++)
	{
		pqst.questionId=i;
		pqst.answer=i%4;
		pqst.suspectFlag=i%2;
		pqst.answerPos.push_back(Point(i,i+5));
		pqst.answerPos.push_back(Point(2,i+5));
		result.answerResult.answer.push_back(pqst);
	}
	for (int i=0;i<5;i++)
	{
		BarResult brst;
		brst.bar=TickerNumBar;
		brst.bar="adfd";
		brst.errflag=i%2;
		result.barResult.push_back(brst);
		CropAreaResult crst;
		crst.groupNum=i;
		crst.isSecret=i%2;
		crst.name="sdfl";


	}
	

}
int _tmain(int argc, _TCHAR* argv[])
{
// 	_CrtDumpMemoryLeaks();
// 	string xmlpath="C:\\Users\\luzif\\Desktop\\卡格式制作软件\\空白卡\\类型一\\Taoka.xml";
// 	XmlIo xml;
// 	TK_info tkinfo;
// 	xml.Read(xmlpath,tkinfo);
	Result result;
	AC_RST *acresult=new AC_RST;
	creatResult(result);
	Result2AC_RST(result,*acresult);
	freeResult(acresult);

	_CrtDumpMemoryLeaks();
	return 0;
}

