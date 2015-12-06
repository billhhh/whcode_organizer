#include "TranStruct.h"

//将AC_RST结构体转换成Result结构体
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

//将Result结构体转换成AC_RST结构体
void Result2AC_RST(const Result &result,AC_RST &acrst)
{
	acrst.tkId=result.tkId;
	acrst.pageId=result.pageId;
	acrst.errFlag=result.errFlag;
	acrst.angle=result.angle;
	acrst.blackLine=result.blackLine;
	acrst.whiteLine=result.whiteLine;
	cv::Size imgSize=result.img.size();
	acrst.imgSize=imgSize;
	int dataLength=imgSize.width*imgSize.height;
	uchar *data=new uchar[dataLength];
	memcpy(data,result.img.data,dataLength);
	acrst.img=data;
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
// 		stringstream sStream;
// 
// 		//将答案的输出由int改成十六进制的char[4]
// 		sStream<<setw(4)<<setfill('0')<<hex<<uppercase<<iter->answer;
// 		memcpy(&pqrst[i].answer,sStream.str().c_str(),4);
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

//十六进制的string转int
int HexString2Int(const string &hexStr)
{
	int len=hexStr.length();
	if(len>8) return 0;
	int res=0;
	for (int i=0;i<len;i++)
	{
		int tmp=0;
		if (hexStr[i]>='0'&&hexStr[i]<='9')
		{
			tmp=hexStr[i]-'0';
		}else if (hexStr[i]>='a'&&hexStr[i]<='f')
		{
			tmp=hexStr[i]-'a'+10;
		}else if (hexStr[i]>='A'&&hexStr[i]<='F')
		{
			tmp=hexStr[i]-'A'+10;
		}else
		{
			res=0;
			break;
		}
		tmp<<=((len-i-1)<<2);
		res |=tmp;
	}
	return res;
}

void TransTkinfo(const TK_info &tkInfo,Cum_TK_info &cumTkInfo)
{
	cumTkInfo.tkInfoCount=tkInfo.tkinfo.size();
	cumTkInfo.tkInfo=new Cum_PerAC_info[cumTkInfo.tkInfoCount];
	for (int i=0;i<cumTkInfo.tkInfoCount;i++)
	{
		cumTkInfo.tkInfo[i].tkId=tkInfo.tkinfo[i].tkId;
		cumTkInfo.tkInfo[i].pageId=tkInfo.tkinfo[i].pageId;
		int acinfoCunt=tkInfo.tkinfo[i].acinfo.size();
		cumTkInfo.tkInfo[i].acInfoCount=acinfoCunt;
		Cum_AC_info * cum_acinfo=new Cum_AC_info[acinfoCunt];
		cumTkInfo.tkInfo[i].acInfo=cum_acinfo;
		for(int j=0;j<acinfoCunt;j++)
		{
			transACInfo(tkInfo.tkinfo[i].acinfo[j],cum_acinfo[j]);
		}
	}
}
void TransTkinfo3(const TK_info3 &tkInfo,Cum_TK_info3 &cumTkInfo)
{
	//cumTkInfo.tkInfoCount=tkInfo.tkinfo.size();
	//cumTkInfo.tkInfo=new Cum_AC_info3[cumTkInfo.tkInfoCount];
	//for (int i=0;i<cumTkInfo.tkInfoCount;i++)
	//{
	//	transACInfo3(tkInfo.tkinfo[i],cumTkInfo.tkInfo[i]);
	//}
	cumTkInfo.tkInfoCount=tkInfo.tkinfo.size();
	cumTkInfo.tkInfo=new Cum_PerAC_info3[cumTkInfo.tkInfoCount];
	for (int i=0;i<cumTkInfo.tkInfoCount;i++)
	{
		cumTkInfo.tkInfo[i].pageId=tkInfo.tkinfo[i].pageId;
		int acinfoCunt=tkInfo.tkinfo[i].acinfo.size();
		cumTkInfo.tkInfo[i].acInfoCount=acinfoCunt;
		Cum_AC_info3 * cum_acinfo=new Cum_AC_info3[acinfoCunt];
		cumTkInfo.tkInfo[i].acinfo=cum_acinfo;
		for(int j=0;j<acinfoCunt;j++)
		{
			transACInfo3(tkInfo.tkinfo[i].acinfo[j],cum_acinfo[j]);
		}
	}
}

void transACInfo(const AC_info &acinfo,Cum_AC_info &cum_acinfo)
{
	cum_acinfo.ac_type=acinfo.ac_type;
	cum_acinfo.isFront=acinfo.isFront;
	cum_acinfo.imgSize=acinfo.imgSize;
	cum_acinfo.isAnchorPointExist=acinfo.isAnchorPointExist;
	cum_acinfo.blackLine=acinfo.blackLine;
	cum_acinfo.whiteLine=acinfo.whiteLine;
	//定位点
	cum_acinfo.anchorPointInfo.num=acinfo.anchorPointInfo.num;
	cum_acinfo.anchorPointInfo.anchorType=acinfo.anchorPointInfo.anchorType;
	int anchorPtCount=acinfo.anchorPointInfo.anchorPt.size();
	cum_acinfo.anchorPointInfo.anchorPtCount=anchorPtCount;
	Rect *anchorPt=new Rect[anchorPtCount];
	cum_acinfo.anchorPointInfo.anchorPt=anchorPt;
	for (int i=0;i<anchorPtCount;i++)
	{
		anchorPt[i]=acinfo.anchorPointInfo.anchorPt[i];
	}
	//同步头
	cum_acinfo.markerInfo.xNum=acinfo.markerInfo.xNum;
	cum_acinfo.markerInfo.xMarker=acinfo.markerInfo.xMarker;
	cum_acinfo.markerInfo.xSize=acinfo.markerInfo.xSize;
	cum_acinfo.markerInfo.yMarker=acinfo.markerInfo.yMarker;
	cum_acinfo.markerInfo.yNum=acinfo.markerInfo.yNum;
	cum_acinfo.markerInfo.ySize=acinfo.markerInfo.ySize;
	//ID点
	int idPointCount=acinfo.idPoint.size();
	cum_acinfo.idPointCount=idPointCount;
	Cum_ItemPos * idPoint=new Cum_ItemPos[idPointCount];
	cum_acinfo.idPoint=idPoint;
	transItemPos(acinfo.idPoint.begin(),acinfo.idPoint.end(),idPoint);
//	vector<ItemPos>::iterator iter=acinfo.idPoint.begin();
// 	for (;iter!=acinfo.idPoint.end();iter++,idPoint++)
// 	{
// 		idPoint->id=iter->id;
// 		idPoint->interval=iter->interval;
// 		idPoint->mark_id=iter->mark_id;
// 		idPoint->isCrosswise=iter->isCrosswise;
// 		idPoint->isSingleChoice=iter->isSingleChoice;
// 		idPoint->markerIdx[0]=iter->markerIdx[0];
// 		idPoint->markerIdx[1]=iter->markerIdx[1];
// 		idPoint->markerIdx[2]=iter->markerIdx[2];
// 	}
	//条形码组
	int barGroupCount=acinfo.barGroup.size();
	cum_acinfo.barGroupCount=barGroupCount;
	cum_acinfo.barGroup=new Cum_Bar_info[barGroupCount];
	for (int i=0;i<barGroupCount;i++)
	{
		cum_acinfo.barGroup[i].barType=acinfo.barGroup[i].barType;
		cum_acinfo.barGroup[i].pos=acinfo.barGroup[i].pos;
	}
	//预定义填涂点组
	int fpgCount=acinfo.fillingPointGroup.size();
	cum_acinfo.fillingPointGroupCount=fpgCount;
	Cum_FillingPoints_info * cum_fp=new Cum_FillingPoints_info[fpgCount];
	cum_acinfo.fillingPointGroup=cum_fp;
	vector<FillingPoints_info>::const_iterator fpiter=acinfo.fillingPointGroup.begin();
	for (;fpiter!=acinfo.fillingPointGroup.end();fpiter++,cum_fp++)
	{
		cum_fp->fptype=fpiter->type;
		int length=fpiter->name.length();
		char *fpname=new char[length+1];
		memcpy(fpname,fpiter->name.c_str(),length);
		fpname[length]='\0';
		cum_fp->name=fpname;
		int fillingPointsCount=fpiter->fillingPoints.size();
		cum_fp->fillingPointsCount=fillingPointsCount;
		Cum_ItemPos * fp=new Cum_ItemPos[fillingPointsCount];
		cum_fp->fillingPoints=fp;
		transItemPos(fpiter->fillingPoints.begin(),fpiter->fillingPoints.end(),fp);
	}
	//题目信息
	int qstCount=acinfo.questioninfo.size();
	cum_acinfo.questionInfoCount=qstCount;
	Cum_QustionItemPos * questionInfo=new Cum_QustionItemPos[qstCount];
	cum_acinfo.questionInfo=questionInfo;
	transItemPos(acinfo.questioninfo.begin(),acinfo.questioninfo.end(),questionInfo);
	//裁切区域信息
	int cropAreaInfoCount=acinfo.cropAreaInfo.size();
	cum_acinfo.cropAreaInfoCount=cropAreaInfoCount;
	Cum_CropArea_info * cropAreaInfo=new Cum_CropArea_info[cropAreaInfoCount];
	cum_acinfo.cropAreaInfo=cropAreaInfo;
	vector<CropArea_info>::const_iterator cropIter=acinfo.cropAreaInfo.begin();
	for (;cropIter!=acinfo.cropAreaInfo.end();cropIter++,cropAreaInfo++)
	{
		cropAreaInfo->groupNum=cropIter->groupNum;
		cropAreaInfo->isSecret =cropIter->isSecret;
		cropAreaInfo->pos=cropIter->pos;
		int length=cropIter->name.length();
		char *cropname=new char[length+1];
		memcpy(cropname,cropIter->name.c_str(),length);
		cropname[length]='\0';
		cropAreaInfo->name=cropname;
	}
	//识别参考点
	int refPointCount=acinfo.refPoint.size();
	cum_acinfo.refPointCount=refPointCount;
	Rect *refPoint=new Rect[refPointCount];
	cum_acinfo.refPoint=refPoint;
	for (int i=0;i<refPointCount;i++)
	{
		refPoint[i]=acinfo.refPoint[i];
	}
	//横向同步头
	int markerNum=acinfo.xMarker.size();
	cum_acinfo.xMarkerCount=markerNum;
	Cum_PerMarker_info * marker=new Cum_PerMarker_info[markerNum];
	cum_acinfo.xMarker=marker;
	transMarker(acinfo.xMarker.begin(),acinfo.xMarker.end(),marker);
	//纵向同步头
	markerNum=acinfo.yMarker.size();
	cum_acinfo.yMarkerCount=markerNum;
	marker=new Cum_PerMarker_info[markerNum];
	cum_acinfo.yMarker=marker;
	transMarker(acinfo.yMarker.begin(),acinfo.yMarker.end(),marker);


}
void transACInfo3(const AC_info3 &acinfo,Cum_AC_info3 &cum_acinfo)
{
	cum_acinfo.ac_type=acinfo.ac_type;
	int length=acinfo.ac_id.length();
	char *acId=new char[length+1];
	memcpy(acId,acinfo.ac_id.c_str(),length);
	acId[length]='\0';
	cum_acinfo.ac_id=acId;
	cum_acinfo.isFront=acinfo.isFront;
	cum_acinfo.imgSize=acinfo.imgSize;
	cum_acinfo.isAnchorPointExist=acinfo.isAnchorPointExist;
	cum_acinfo.isAnchorRectExist=acinfo.isAnchorRectExist;
	cum_acinfo.anchorRect=acinfo.anchorRect;
	cum_acinfo.blackLine=acinfo.blackLine;
	cum_acinfo.whiteLine=acinfo.whiteLine;
	//定位点
	cum_acinfo.anchorPointInfo.num=acinfo.anchorPointInfo.num;
	cum_acinfo.anchorPointInfo.anchorType=acinfo.anchorPointInfo.anchorType;
	int anchorPtCount=acinfo.anchorPointInfo.anchorPt.size();
	cum_acinfo.anchorPointInfo.anchorPtCount=anchorPtCount;
	Rect *anchorPt=new Rect[anchorPtCount];
	cum_acinfo.anchorPointInfo.anchorPt=anchorPt;
	for (int i=0;i<anchorPtCount;i++)
	{
		anchorPt[i]=acinfo.anchorPointInfo.anchorPt[i];
	}
	//页码标识块
	int pageMakerCount=acinfo.pageMarker.size();
	cum_acinfo.pageMarkerCount=pageMakerCount;
	Rect *pageMarker=new Rect[pageMakerCount];
	cum_acinfo.pageMarker=pageMarker;
	for (int i=0;i<pageMakerCount;i++)
	{
		pageMarker[i]=acinfo.pageMarker[i];
	}

	//虚拟同步头
	int markInfoCount=acinfo.markerInfo.size();
	cum_acinfo.markInfoCunt=markInfoCount;
	Cum_Marker_info3 *markinfo=new Cum_Marker_info3[markInfoCount];
	cum_acinfo.markerInfo=markinfo;
	vector<Marker_info3>::const_iterator markIter=acinfo.markerInfo.begin();
	for (;markIter!=acinfo.markerInfo.end();markIter++,markinfo++)
	{
		markinfo->id=markIter->id;
		int xmarkCount=markIter->xMarker.size();
		int ymarkCount=markIter->yMarker.size();
		markinfo->xMarkerCount=xmarkCount;
		markinfo->yMarkerCount=ymarkCount;
		markinfo->xMarker=new Rect[xmarkCount];
		markinfo->yMarker=new Rect[ymarkCount];
		for (int i=0;i<xmarkCount;i++)
		{
			markinfo->xMarker[i]=markIter->xMarker[i];
		}
		for (int i=0;i<ymarkCount;i++)
		{
			markinfo->yMarker[i]=markIter->yMarker[i];
		}
	}
	//条形码组
	int barGroupCount=acinfo.barGroup.size();
	cum_acinfo.barGroupCount=barGroupCount;
	cum_acinfo.barGroup=new Cum_Bar_info[barGroupCount];
	for (int i=0;i<barGroupCount;i++)
	{
		cum_acinfo.barGroup[i].barType=acinfo.barGroup[i].barType;
		cum_acinfo.barGroup[i].pos=acinfo.barGroup[i].pos;
	}
	//预定义填涂点组
	int fpgCount=acinfo.fillingPointGroup.size();
	cum_acinfo.fillingPointGroupCount=fpgCount;
	Cum_FillingPoints_info3 * cum_fp=new Cum_FillingPoints_info3[fpgCount];
	cum_acinfo.fillingPointGroup=cum_fp;
	vector<FillingPoints_info3>::const_iterator fpiter=acinfo.fillingPointGroup.begin();
	for (;fpiter!=acinfo.fillingPointGroup.end();fpiter++,cum_fp++)
	{
		cum_fp->fptype=fpiter->type;
		cum_fp->isCrosswise=fpiter->isCrosswise;
		int length=fpiter->name.length();
		char *fpname=new char[length+1];
		memcpy(fpname,fpiter->name.c_str(),length);
		fpname[length]='\0';
		cum_fp->name=fpname;
		int fpCount=fpiter->fillingPoints.size();
		cum_fp->fillingPointsCount=fpCount;
		Cum_FillingpointItemPos *fp=new Cum_FillingpointItemPos[fpCount];
		cum_fp->fillingPoints=fp;
		vector<FillingpointItemPos>::const_iterator fpPosIter=fpiter->fillingPoints.begin();
		for (;fpPosIter!=fpiter->fillingPoints.end();fpPosIter++,fp++)
		{
			fp->id=fpPosIter->id;
			fp->isSingleChoice=fpPosIter->isSingleChoice;
			int posCount=fpPosIter->pos.size();
			fp->posCount=posCount;
			fp->pos=new Rect[posCount];
			for (int i=0;i<posCount;i++)
			{
				fp->pos[i]=fpPosIter->pos[i];
			}
		}

	}
	//题目信息
	int qstCount=acinfo.questioninfo.size();
	cum_acinfo.questionInfoCount=qstCount;
	Cum_QustionItemPos * questionInfo=new Cum_QustionItemPos[qstCount];
	cum_acinfo.questionInfo=questionInfo;
	transItemPos(acinfo.questioninfo.begin(),acinfo.questioninfo.end(),questionInfo);
	//裁切区域信息
	int cropAreaInfoCount=acinfo.cropAreaInfo.size();
	cum_acinfo.cropAreaInfoCount=cropAreaInfoCount;
	Cum_CropArea_info * cropAreaInfo=new Cum_CropArea_info[cropAreaInfoCount];
	cum_acinfo.cropAreaInfo=cropAreaInfo;
	vector<CropArea_info>::const_iterator cropIter=acinfo.cropAreaInfo.begin();
	for (;cropIter!=acinfo.cropAreaInfo.end();cropIter++,cropAreaInfo++)
	{
		cropAreaInfo->groupNum=cropIter->groupNum;
		cropAreaInfo->isSecret =cropIter->isSecret;
		cropAreaInfo->pos=cropIter->pos;
		int length=cropIter->name.length();
		char *cropname=new char[length+1];
		memcpy(cropname,cropIter->name.c_str(),length);
		cropname[length]='\0';
		cropAreaInfo->name=cropname;
	}
	//识别参考点
	int refPointCount=acinfo.refPoint.size();
	cum_acinfo.refPointCount=refPointCount;
	Rect *refPoint=new Rect[refPointCount];
	cum_acinfo.refPoint=refPoint;
	for (int i=0;i<refPointCount;i++)
	{
		refPoint[i]=acinfo.refPoint[i];
	}

}

void transItemPos(vector<ItemPos>::const_iterator itemBegin,vector<ItemPos>::const_iterator itemEnd,Cum_ItemPos *itemPos)
{
	for (;itemBegin!=itemEnd;itemBegin++,itemPos++)
	{
		itemPos->id=itemBegin->id;
		itemPos->interval=itemBegin->interval;
		itemPos->mark_id=itemBegin->mark_id;
		itemPos->isCrosswise=itemBegin->isCrosswise;
		itemPos->isSingleChoice=itemBegin->isSingleChoice;
		itemPos->markerIdx[0]=itemBegin->markerIdx[0];
		itemPos->markerIdx[1]=itemBegin->markerIdx[1];
		itemPos->markerIdx[2]=itemBegin->markerIdx[2];
	}
}

void transMarker(vector<PerMarker_info>::const_iterator itemBegin,vector<PerMarker_info>::const_iterator itemEnd,Cum_PerMarker_info *perMarker)
{
	for (;itemBegin!=itemEnd;itemBegin++,perMarker++)
	{
		perMarker->id=itemBegin->id;
		perMarker->pos=itemBegin->pos;
	}
}