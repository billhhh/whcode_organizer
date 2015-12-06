#include "DetectPerAC.h"
#include "AnswerCardProcessing.h"
#include "DetectRefPoint.h"
#include "DetectMarkers.h"
#include "DetectAnswer.h"
#include "DetectBar.h"
#include "DetectFillingPoint.h"
#include "DetectAnchorPoint.h"
#include "CropAreas.h"
#include <atltrace.h>
#include <vector>
#include <algorithm>
#include <highgui.h>
//类型三识别
//获取识别结果，输入为待识别图像数据块，识别结果保存在result结构体中，返回值为识别结果状态信息，为0表示识别正常，不为0则返回出错状态。该函数需要先导入题卡描述信息。
int MarkAnswerCard(Mat img,AC_info3 acinfo,Result & result,AcArgs acargs)
{
	if (acinfo.ac_type==3||acinfo.ac_type==4)
		;
	else
		return ACTYPE_NOT_MATCH;

	result.errFlag = 0;
	result.answerResult.suspectFlag = 0;
	result.blackLine=acinfo.blackLine;
	result.whiteLine=acinfo.whiteLine;
	acargs.xRangeScale--;
	acargs.yRangeScale--;
	//定位点检测

	double xRangeScale=acargs.xRangeScale;
	double yRangeScale=acargs.yRangeScale;
	int returnValue = 0;
	cv::Point originalPoint(0,0);
	if (acinfo.isAnchorPointExist)
	{
		//定位点
		vector<cv::Rect> anchorPos(acinfo.anchorPointInfo.anchorPt);
		returnValue=DetectAnchorPoint(img,anchorPos,acinfo.anchorPointInfo.anchorType,xRangeScale,yRangeScale);
		if (returnValue)
		{
			ATLTRACE("定位点检测异常，异常代码：%d\n",returnValue);
			result.errFlag=ANCHOR_POINT_ERR_BASE+returnValue;
			return ANCHOR_POINT_ERR_BASE+returnValue;
		}
		//倾斜校正
		//	imshow("test1",img);
		returnValue = TiltCorrection(img,img,anchorPos,acinfo.anchorPointInfo.anchorType,result.angle);
		originalPoint.x=anchorPos[0].x;
		originalPoint.y=anchorPos[0].y;
		if (returnValue)
		{
			result.errFlag=TILTCORRECTION_ERR_BASE+returnValue;
			ATLTRACE("倾斜校正异常，异常代码：%d\n",returnValue);
			return TILTCORRECTION_ERR_BASE+returnValue;
		}

	}else if (acinfo.isAnchorRectExist)
	{
		Rect rect=acinfo.anchorRect;
		/*Rect anchorRect=acinfo.anchorRect;
		double rectRange=0.3;
		rect.width=anchorRect.width*(1+rectRange);
		rect.height=anchorRect.height*(1+rectRange);
		rect.x=MIN(MAX(anchorRect.x - ((rect.width-anchorRect.width)>>1),0),img.cols-rect.width);
		rect.y = MIN(MAX(anchorRect.y - ((rect.height-anchorRect.height)>>1),0),img.rows-rect.height);*/
		returnValue=TiltCorrection(img,img,rect,originalPoint,result.angle);
		Mat imgRect=img(rect);
		int rectWDiff = abs(rect.width-acinfo.anchorRect.width);
		int rectHDiff = (rect.height-acinfo.anchorRect.height);
		if (abs(result.angle)>4||rectWDiff>7||rectHDiff>3||rectHDiff<-5)
		{
			returnValue=2;
		}
		//imshow("rect",imgRect);
		//cvWaitKey();
		//imwrite("I:\\aaa.jpg",imgRect);
		//getchar();
// 		originalPoint.x-=365;
// 		originalPoint.y-=358;
	/*	originalPoint.x=rect.x+acinfo.anchorRect.width>>1;
		originalPoint.y=rect.y+acinfo.anchorRect.height>>1;*/

		if (returnValue)
		{
			ATLTRACE("定位矩形检测异常，异常代码：%d\n",returnValue);
			result.errFlag=ANCHOR_POINT_ERR_BASE+returnValue;
			return ANCHOR_POINT_ERR_BASE+returnValue;
		}

	}
	for (int i=acinfo.pageMarker.size()-1;i>=0;i--)
	{
		acinfo.pageMarker[i].x+=originalPoint.x;
		acinfo.pageMarker[i].y+=originalPoint.y;
	}
	//页码标识块识别
	if (DetectIdPoint(img,acinfo.pageMarker,1.5)==false)
	{
		result.errFlag=PAGEMAKER_ERR;
		return PAGEMAKER_ERR;
	}

	result.img=img.clone();
	/************************************************************************/
	/* 裁切																	*/
	/************************************************************************/
	if (acinfo.cropAreaInfo.size()>0)
	{
		for(int i=acinfo.cropAreaInfo.size()-1;i>=0;i--)
		{
			acinfo.cropAreaInfo[i].pos.x+=originalPoint.x;
			acinfo.cropAreaInfo[i].pos.y+=originalPoint.y;
		}
		returnValue = CropAreas(img,acinfo.cropAreaInfo,result.cropAreaResult);
		if (returnValue)
		{
			result.errFlag=CROPAREA_ERR_BASE+returnValue;
	/*		ATLTRACE("裁切异常，异常代码：%d\n",returnValue);
			return CROPAREA_ERR_BASE+returnValue;*/
		}
	}
	//条形码检测
	if (acinfo.barGroup.size()>0)
	{
		for (int i=0;i<acinfo.barGroup.size();i++)
		{
			acinfo.barGroup[i].pos.x += originalPoint.x;
			acinfo.barGroup[i].pos.y += originalPoint.y;
		}
		returnValue=GetBar(img,acinfo.barGroup,result.barResult);
		if (returnValue)
		{
			result.errFlag=BAR_ERR_BASE;
			return BAR_ERR_BASE;
		}	
	}

	/************************************************************************/
	/* 用户自定义填涂点识别                                                               */
	/************************************************************************/

	//用户自定义填涂点检测
	if (acinfo.fillingPointGroup.size()>0)
	{

		for (int i=0;i<acinfo.fillingPointGroup.size();i++)
		{
			int fpReturnValue=0;
			FillingPoints_info3 fillingPointInfo=acinfo.fillingPointGroup[i];
			FillingPointsResult fpr;
			fpr.name=fillingPointInfo.name;
			fpr.type=fillingPointInfo.type;
			fpr.suspectFlag=0;
			switch (fillingPointInfo.type)
			{
				//			case OptionalQuestion:
			case PaperType:
				fpReturnValue = DetectPaperType(img,fillingPointInfo.fillingPoints[0],originalPoint,acargs.sensibilityThresh,acargs.areaThreshold,fpr);
				break;
			case Absent:
			case Discipline:
				fpReturnValue = DetectAbsent(img,fillingPointInfo.fillingPoints[0],originalPoint,acargs.areaThreshold,fpr);
				break;
			default:
				fpReturnValue = DetectNumericPoint(img,fillingPointInfo,originalPoint,acargs.sensibilityThresh,acargs.areaThreshold,fpr);
				break;

			}
			if (fpReturnValue)
			{

				result.errFlag=FILLING_POINT_ERR_BASE+returnValue+fpReturnValue;
				ATLTRACE("用户自定义填涂点检测异常，异常代码：%d\n",returnValue);
				return FILLING_POINT_ERR_BASE+returnValue+fpReturnValue;

			}
			else result.cfpResult.push_back(fpr);
		}

	}
	//初始化标记点组的Map结构

	map<ushort,MarkersBoundaryTable *> mbtMap;
	MarkersBoundaryTable mbt1;
	bool mbt1flag=false;
	if(acinfo.markerInfo.size()==1)
	{
		mbt1flag=true;
		vector<cv::Rect> xMarkers,yMarkers;
		xMarkers=acinfo.markerInfo[0].xMarker;
		yMarkers=acinfo.markerInfo[0].yMarker;

		for (int j=0;j<xMarkers.size();j++)
		{
			xMarkers[j].x += originalPoint.x;
		}
		for (int j=0;j<yMarkers.size();j++)
		{
			yMarkers[j].y += originalPoint.y;
		}
		mbt1.InitMarkersBoundaryTable(xMarkers,yMarkers,0.1);
	}else if(acinfo.markerInfo.size()>1)
	{
		for (int i=acinfo.markerInfo.size()-1;i>=0;i--)
		{
			ushort a=acinfo.markerInfo[i].id;
			vector<cv::Rect> xMarkers,yMarkers;
			xMarkers=acinfo.markerInfo[i].xMarker;
			yMarkers=acinfo.markerInfo[i].yMarker;

			for (int j=0;j<xMarkers.size();j++)
			{
				xMarkers[j].x += originalPoint.x;
			}
			for (int j=0;j<yMarkers.size();j++)
			{
				yMarkers[j].y += originalPoint.y;
			}
			MarkersBoundaryTable *mbt=new MarkersBoundaryTable;
			(*mbt).InitMarkersBoundaryTable(xMarkers,yMarkers,0.1);
			mbtMap.insert(pair<ushort,MarkersBoundaryTable *>(a,mbt));

		}
	}
	/************************************************************************/
	/* 答案识别                                                               */
	/************************************************************************/
	bool questionType = false;
	if(acinfo.questionType>0)
		questionType = true;
	acargs.sensibilityThresh=0;

	//答案识别
	if (acinfo.questioninfo.size()>0)
	{
		if (mbt1flag)   //如果只有一组标记点组
		{
			//returnValue = DetectAnswer1(img,acinfo.questioninfo,mbt1,result.answerResult,acargs.sensibilityThresh,acargs.areaThreshold);
			returnValue = DetectAnswer(img,acinfo.questioninfo,mbt1,result.answerResult,questionType,acargs.sensibilityThresh,acargs.areaThreshold,acargs.seSize);
		}else
		{
			returnValue = DetectAnswer(img,acinfo.questioninfo,mbtMap,result.answerResult,questionType,acargs.sensibilityThresh,acargs.areaThreshold,acargs.seSize);
			for (map<ushort,MarkersBoundaryTable*>::iterator iter=mbtMap.begin();iter!=mbtMap.end();iter++)
			{
				MarkersBoundaryTable * pMbt=iter->second;
				delete pMbt;
			}
		}
		if (returnValue)
		{
			result.errFlag=returnValue+ANSWER_ERR_BASE;
			ATLTRACE("答案检测异常，异常代码：%d\n",returnValue);
			return returnValue+ANSWER_ERR_BASE;
		}
	}


	return returnValue;
}
//类型一二识别
int MarkAnswerCard(Mat srcImg,AC_info acinfo,Result & result,AcArgs acargs)
{
	if (acinfo.ac_type==1||acinfo.ac_type==2)
		;
	else
		return ACTYPE_NOT_MATCH;

	//初始化
	Mat img = srcImg.clone();
	acargs.xRangeScale--;
	acargs.yRangeScale--;
	result.errFlag = 0;
	result.answerResult.suspectFlag = 0;
	result.blackLine=acinfo.blackLine;
	result.whiteLine=acinfo.whiteLine;

	/************************************************************************/
	/* 题卡判断                                                             */
	/************************************************************************/
	//判断是否为类型二
	bool istype2=true;
	if(acinfo.ac_type==1)
		istype2=false;
	else

		istype2=true;

	double xRangeScale=acargs.xRangeScale;
	double yRangeScale=acargs.yRangeScale;
	int returnValue = 0;
	cv::Point originalPoint;
	MarkersBoundaryTable mbt;
	result.angle=0;
	vector<cv::Rect> yMarkers,xMarkers;
	vector<cv::Rect> srcYMarker,srcXMarker;
	Size anchorSize;
	if (acinfo.isAnchorPointExist)
	{
		//定位点检测
		vector<cv::Rect> anchorPos(acinfo.anchorPointInfo.anchorPt);
		int markHight=max(acinfo.markerInfo.xSize.height,acinfo.markerInfo.ySize.height);
		returnValue=DetectAnchorPoint(img,anchorPos,acinfo.anchorPointInfo.anchorType,acinfo.markerInfo.xSize,acinfo.markerInfo.ySize,xRangeScale-1,yRangeScale);
		if (returnValue)
		     returnValue=DetectAnchorPoint(img,anchorPos,acinfo.anchorPointInfo.anchorType,acinfo.markerInfo.xSize,acinfo.markerInfo.ySize,0.5,yRangeScale);
		if (returnValue)
		{
			ATLTRACE("定位点检测异常，异常代码：%d\n",returnValue);
			result.errFlag=ANCHOR_POINT_ERR_BASE+returnValue;
			return ANCHOR_POINT_ERR_BASE+returnValue;
		}

		

		//倾斜校正
		returnValue = TiltCorrection(img,img,anchorPos,acinfo.anchorPointInfo.anchorType,result.angle);
		//acinfo.
		if (returnValue)
		{
			result.errFlag=TILTCORRECTION_ERR_BASE+returnValue;
			ATLTRACE("倾斜校正异常，异常代码：%d\n",returnValue);
			return TILTCORRECTION_ERR_BASE+returnValue;
		}
		originalPoint.x=anchorPos[0].x;
		originalPoint.y=anchorPos[0].y;
		anchorSize=Size(anchorPos[0].width,anchorPos[0].height);
		vector<PerMarker_info>::iterator iter = acinfo.xMarker.begin();
		for (;iter!=acinfo.xMarker.end();iter++)
		{
			srcXMarker.push_back(iter->pos);
		}
		//水平标记点检测
		if(acinfo.markerInfo.xNum)
		{

			returnValue = DetectXMarkers(img,acinfo.markerInfo,originalPoint,anchorSize,xMarkers,xRangeScale,yRangeScale*1.5);
			if (returnValue)
			{
				result.errFlag=returnValue+XMARKERS_ERR_BASE;
				ATLTRACE("xfang检测异常，异常代码：%d\n",returnValue);
				return XMARKERS_ERR_BASE+returnValue;
			}
		}
		//垂直标记点检测
		iter = acinfo.yMarker.begin();
		for (;iter!=acinfo.yMarker.end();iter++)
		{
			srcYMarker.push_back(iter->pos);
		}
		if(acinfo.markerInfo.yNum)
		{
			returnValue = DetectYMarkers(img,acinfo.markerInfo,originalPoint,anchorSize,yMarkers,xRangeScale,yRangeScale*1.5);
			if (returnValue)
			{
				result.errFlag=returnValue+YMARKERS_ERR_BASE;
				ATLTRACE("垂直定位点检测异常，异常代码：%d\n",returnValue);
				return YMARKERS_ERR_BASE+returnValue;
			}
		}
		if(istype2)
			mbt.InitMarkersBoundaryTable(xMarkers,yMarkers,0.1,false);
		else
			mbt.InitMarkersBoundaryTable(xMarkers,yMarkers,0.2,false);
		
		vector<cv::Rect> idPoint;
		for (int i=acinfo.idPoint.size()-1;i>=0;i--)
		{
			idPoint.push_back(mbt.GetQuestionBoundry(acinfo.idPoint[i]));
		}

		//Id点检测
		if (acinfo.idPoint.size()>0)
		{
			if(DetectIdPoint(img,idPoint,1)==false)
				return IDPOINT_NOT_MATCH;
		}
//		mbt.InitMarkersBoundaryTable(xMarkers,yMarkers,0.3,false);

	}

	result.img=img.clone();
	
	/************************************************************************/
	/* 裁切																	*/
	/************************************************************************/
	if (acinfo.cropAreaInfo.size()>0)
	{
		if (acinfo.isAnchorPointExist)
		{
			for(int i=acinfo.cropAreaInfo.size()-1;i>=0;i--)
			{
				acinfo.cropAreaInfo[i].pos.x+=originalPoint.x;
				acinfo.cropAreaInfo[i].pos.y+=originalPoint.y;
			}
		}

		returnValue = CropAreas(img,acinfo.cropAreaInfo,result.cropAreaResult);
		if (returnValue)
		{
			result.errFlag=CROPAREA_ERR_BASE+returnValue;
			ATLTRACE("裁切异常，异常代码：%d\n",returnValue);
			return CROPAREA_ERR_BASE+returnValue;
		}
	}
	//条形码检测
	if (acinfo.barGroup.size()>0)
	{
		if (acinfo.isAnchorPointExist)
		{
			for (int i=0;i<acinfo.barGroup.size();i++)
			{
				acinfo.barGroup[i].pos.x += originalPoint.x;
				acinfo.barGroup[i].pos.y += originalPoint.y;
			}

		}
		returnValue=GetBar(img,acinfo.barGroup,result.barResult,0,0);
		if(returnValue)
			returnValue=GetBar(img,acinfo.barGroup,result.barResult,xRangeScale,yRangeScale);
		if (returnValue)
		{
			result.errFlag=BAR_ERR_BASE;
			return BAR_ERR_BASE;
		}	
	}
	/************************************************************************/
	/* 用户自定义填涂点识别                                                               */
	/************************************************************************/

	//用户自定义填涂点检测
	if (acinfo.fillingPointGroup.size()>0)
	{

		map <short,cv::Mat> fillingPointBackgourndMap;
		for (int i = acinfo.fillingPointBackgroundInfo.size()-1;i>=0;i--)
		{
			short a=(short)acinfo.fillingPointBackgroundInfo[i].type;
			fillingPointBackgourndMap[a]=acinfo.fillingPointBackgroundInfo[i].bkInfo;
		}
		for (int i=0;i<acinfo.fillingPointGroup.size();i++)
		{
			int fpReturnValue=0;
			FillingPoints_info fillingPointInfo=acinfo.fillingPointGroup[i];
			FillingPointsResult fpr;
			Mat fpBackground;
			fpr.name=fillingPointInfo.name;
			fpr.suspectFlag=0;
			fpr.type=fillingPointInfo.type;
			if(fillingPointBackgourndMap.find((ushort) fillingPointInfo.type)!=fillingPointBackgourndMap.end())
			{
				fpBackground=fillingPointBackgourndMap[(ushort)fillingPointInfo.type];
			}
			else     //找不到匹配背景则报错
			{
				returnValue=FILLING_POINT_ERR_BASE+returnValue+1;
				result.errFlag=returnValue;
				return returnValue;
			}
			switch (fillingPointInfo.type)
			{
			case PaperType:
				fpReturnValue = DetectPaperType(img,istype2,fillingPointInfo.fillingPoints[0],mbt,acargs.sensibilityThresh,acargs.areaThreshold,fpr);
				break;
			case Absent:
			case Discipline:
				fpReturnValue = DetectAbsent(img,istype2,fillingPointInfo.fillingPoints[0],mbt,acargs.areaThreshold,fpr);
				break;
				// 			case OptionalQuestion:
				// 				break;
			default:
				fpReturnValue = DetectNumericPoint(img,istype2,fillingPointInfo,mbt,acargs.sensibilityThresh,acargs.areaThreshold,fpr);

			}
			if (fpReturnValue)
			{

				result.errFlag=FILLING_POINT_ERR_BASE+returnValue+fpReturnValue;
				ATLTRACE("用户自定义填涂点检测异常，异常代码：%d\n",returnValue);
				return FILLING_POINT_ERR_BASE+returnValue+fpReturnValue;

			}
			else result.cfpResult.push_back(fpr);
		}

	}

	/************************************************************************/
	/* 答案识别                                                               */
	/************************************************************************/
	if (acinfo.questioninfo.size() > 0 )
	{
		double refAngle = 0;
		Rect refMarker;
		Rect questImgRect(0,0,0,img.rows);
		questImgRect.width = MIN(img.cols,MAX(xMarkers[xMarkers.size()-1].x,yMarkers[0].x)+4*yMarkers[0].width);
		Mat quesImg = img(questImgRect).clone();
		if (acinfo.refPoint.size() > 0 )
		{
			Point rPRevise;
			rPRevise.x=(originalPoint.x-acinfo.anchorPointInfo.anchorPt[0].x);
			rPRevise.y=(originalPoint.y-acinfo.anchorPointInfo.anchorPt[0].y);
			returnValue=DetectRefPoint(quesImg,srcXMarker,xMarkers,srcYMarker,yMarkers,acinfo.refPoint,refMarker,rPRevise,refAngle);
			if(returnValue!=0)
			{
				result.errFlag=REFPOINT_ERROR;
				return REFPOINT_ERROR;
			}
			if (abs(refAngle)>0.1)
			{
				Mat warp_mat = getRotationMatrix2D(cv::Point2d(refMarker.x,refMarker.y),refAngle,1);
				warpAffine(quesImg, quesImg, warp_mat, img.size());
				Mat srcData(yMarkers.size(),3,CV_64FC1);
				for (int i=0;i<yMarkers.size();i++)
				{
					srcData.at<double>(i,0) = yMarkers[i].x;
					srcData.at<double>(i,1) = yMarkers[i].y;
					srcData.at<double>(i,2) = 1;
				}
				Mat dstData = srcData * warp_mat.t();
				for (int i=0;i<yMarkers.size();i++)
				{
					yMarkers[i].x = (int)(dstData.at<double>(i,0)+0.5);
					yMarkers[i].y = (int)(dstData.at<double>(i,1)+0.5);
				}
				if(istype2)
					mbt.InitMarkersBoundaryTable(xMarkers,yMarkers,0.2,false);
				else
					mbt.InitMarkersBoundaryTable(xMarkers,yMarkers,0.2,false);

			}
		}
		if(istype2)
		{
			bool questionType = false;
			if(acinfo.questionType>0)
				questionType = true;

			//答案识别
			returnValue = DetectAnswer(quesImg,acinfo.questioninfo,mbt,result.answerResult,questionType,acargs.sensibilityThresh,acargs.areaThreshold,acargs.seSize);
			if (returnValue)
			{
				result.errFlag=returnValue+ANSWER_ERR_BASE;
				ATLTRACE("答案检测异常，异常代码：%d\n",returnValue);
				return returnValue+ANSWER_ERR_BASE;
			}
		} 
		else
		{
			//答案识别   
			returnValue = DetectAnswer1(quesImg,acinfo.questioninfo,mbt,result.answerResult,acargs.sensibilityThresh,acargs.areaThreshold);
			if (returnValue)
			{
				result.errFlag=returnValue+ANSWER_ERR_BASE;
				ATLTRACE("答案检测异常，异常代码：%d\n",returnValue);
				return returnValue+ANSWER_ERR_BASE;
			}
		}
		 
	}



	return returnValue;
}