#include "stdafx.h"
#include"cv.h"
#include "DetectFillingPoint.h"
#include"ACStructs.h"
#include <highgui.h>
#include <map>
using namespace cv;
//识别试卷类型、选做题  类型三
int DetectPaperType(Mat img,FillingpointItemPos fPInfo,cv::Point originalPoint,double sensibilityThresh,double areaThreshold,FillingPointsResult &fpr)
{
	PerFPResult perFpResult;
	perFpResult.suspectFlag=0;
	int returnValue=DetectPreFillingPoint(img,fPInfo.pos,fPInfo.isSingleChoice,originalPoint,sensibilityThresh,areaThreshold,perFpResult);
	fpr.suspectFlag=returnValue;
	fpr.fillingResult.push_back(perFpResult);
	return 0;
}
//识别试卷类型、选做题
int DetectPaperType(Mat Img,bool istype2,ItemPos fPInfo,MarkersBoundaryTable &mbt,double sensibilityThresh,double areaThreshold,FillingPointsResult &fpr)
{
	PerFPResult perFpResult;
	perFpResult.suspectFlag=0;
	int optionNum=fPInfo.markerIdx[2]-fPInfo.markerIdx[1]+1;
	int interval=fPInfo.interval;
	Rect roiRect = mbt.GetQuestionBoundry(fPInfo);
	Point rectPos = Point(roiRect.x,roiRect.y);
	Mat roi=Img(roiRect);
	int returnValue=DetectPreFillingPoint(roi,istype2,fPInfo,mbt,rectPos,sensibilityThresh,areaThreshold,perFpResult);
	fpr.suspectFlag=returnValue;
	fpr.fillingResult.push_back(perFpResult);
	return 0;
}

bool DetectIdPoint(Mat img,vector<cv::Rect> idPInfo,double areaThresh)
{
	for (int i=idPInfo.size()-1;i>=0;i--)
	{
//		ItemPos pIdPInfo=ip;
		Rect roiRect = idPInfo[i];
		Mat roi;
		img(roiRect).copyTo(roi);
		//形态学闭操作
		
		Mat closed_roi;
		cv::Size seSize;
		seSize.width = 5;
		seSize.height= 4;
		Mat se = getStructuringElement(MORPH_RECT,seSize);
		cv::morphologyEx(255-roi,closed_roi,MORPH_OPEN,se);
 		//imshow("roiimg",roi);
 		//imshow("closeroi",closed_roi);
 		//waitKey();
		int diff=(int)cv::sum(closed_roi).val[0];
		int threshhold=roiRect.area()*7*areaThresh;
		if (diff>threshhold)
		{
			continue;
		}
		else 
			return false;
	}
	return true;
	
}


//识别缺考标记和违纪填涂点
int DetectAbsent(Mat img,bool istype2,ItemPos fPInfo,MarkersBoundaryTable &mbt,double areaThreshold,FillingPointsResult &fpr)
{
	PerFPResult perFpResult;
	perFpResult.suspectFlag=0;
	perFpResult.result=0;
	fpr.suspectFlag=0;
	Rect roiRect = mbt.GetQuestionBoundry(fPInfo);
	cv::Point resultPos;
	resultPos.x=roiRect.x+(roiRect.width>>1);
	resultPos.y=roiRect.y+(roiRect.height>>1);
	Mat roi;
	img(roiRect).copyTo(roi);
	//形态学闭操作

	Mat closed_roi;
	cv::Size seSize;
	if(istype2)
	{
		seSize.width = roiRect.width>>1;
		seSize.height= roiRect.height>>1;
		Mat se = getStructuringElement(MORPH_RECT,seSize);
		cv::morphologyEx(255-roi,closed_roi,MORPH_OPEN,se);
	}else closed_roi=255-roi;
	int diff=(int)cv::sum(closed_roi).val[0];
	int threshhold=roiRect.area()*7*(1+0.5*areaThreshold);
	if (diff>threshhold)
	{
		perFpResult.result=1;
		perFpResult.resultPos.push_back(resultPos);
	}
	else
		if(diff>threshhold*0.9)
			fpr.suspectFlag=1;
	fpr.fillingResult.push_back(perFpResult);
	return 0;
}

//识别缺考标记和违纪填涂点 类型三
int DetectAbsent(Mat img,FillingpointItemPos fPInfo,cv::Point originalPoint,double areaThreshold,FillingPointsResult &fpr)
{
	PerFPResult perFpResult; 
	perFpResult.suspectFlag=0;
	perFpResult.result=0;
	fpr.suspectFlag=0;
	Rect roiRect = fPInfo.pos[0];
	roiRect.x+=originalPoint.x;
	roiRect.y+=originalPoint.y;
	cv::Point resultPos;
	resultPos.x=roiRect.x+(roiRect.width>>1);
	resultPos.y=roiRect.y+(roiRect.height>>1);
	
	Mat roi;
	img(roiRect).copyTo(roi);
	//形态学闭操作
	Mat closed_roi;
	cv::Size seSize;
	seSize.width = roiRect.width>>1;
	seSize.height= roiRect.height>>1;
	Mat se = getStructuringElement(MORPH_RECT,seSize);
	cv::morphologyEx(255-roi,closed_roi,MORPH_OPEN,se);
	int diff=(int)cv::sum(closed_roi).val[0];
	int threshhold=roiRect.area()*7*(1+0.5*areaThreshold);
	if (diff>threshhold)
	{
		perFpResult.result=1;
		perFpResult.resultPos.push_back(resultPos);
	}
	else
		if(diff>threshhold*0.9)
			fpr.suspectFlag=1;
	fpr.fillingResult.push_back(perFpResult);
	return 0;
}
//识别数字型的填涂点
int DetectNumericPoint(Mat img,bool istype2,FillingPoints_info fPInfo,MarkersBoundaryTable &mbt,double sensibilityThresh,double areaThreshold,FillingPointsResult &fpr)
{
	int num=fPInfo.fillingPoints.size();
	
	for(int i=0;i<num;i++)
	{
		PerFPResult perFpResult;
		perFpResult.suspectFlag=0;
		ItemPos perFpInfo=fPInfo.fillingPoints[i];
		Rect roiRect = mbt.GetQuestionBoundry(perFpInfo);
		Point rectPos = Point(roiRect.x,roiRect.y);
		Mat roi=img(roiRect);
		int returnValue=DetectPreFillingPoint(roi,istype2,perFpInfo,mbt,rectPos,sensibilityThresh,areaThreshold,perFpResult);

		if (perFpResult.resultPos.size()>0)
		{
			perFpResult.resultPos.back().x += roiRect.x;
			perFpResult.resultPos.back().y += roiRect.y;
		}
		fpr.fillingResult.push_back(perFpResult);
		if(returnValue)
			fpr.suspectFlag=returnValue;
	}
	return 0;
}


//识别数字型的填涂点  类型三
int DetectNumericPoint(Mat img,FillingPoints_info3 fPInfo,cv::Point originalPoint,double sensibilityThresh,double areaThreshold,FillingPointsResult &fpr)
{
	int num=fPInfo.fillingPoints.size();
	fpr.suspectFlag=0;
	for(int i=0;i<num;i++)
	{
		PerFPResult perFpResult;
		perFpResult.suspectFlag=0;
		cv::Point resultPt;
		FillingpointItemPos perFpInfo=fPInfo.fillingPoints[i];
		int returnValue=DetectPreFillingPoint(img,perFpInfo.pos,perFpInfo.isSingleChoice,originalPoint,sensibilityThresh,areaThreshold,perFpResult);
/*		perFpResult.suspectFlag=returnValue;*/
		
		fpr.fillingResult.push_back(perFpResult);
		if(perFpResult.suspectFlag)
			fpr.suspectFlag=perFpResult.suspectFlag;
	}
	return 0;
}

//填涂点答案识别

int DetectPreFillingPoint(Mat roi,bool istype2,ItemPos perFpInfo,MarkersBoundaryTable &mbt,Point rectPos,double sensibilityThresh,double areaThreshold,PerFPResult &result)  //0.正常 1.没有填涂
{
	int num=perFpInfo.markerIdx[2]-perFpInfo.markerIdx[1]+1;
	int interval=perFpInfo.interval;
	int optionNum=(num+interval)/(interval+1);
	int suspectFlag=0;
	int threshold_filled,threshold_suspect;
	bool isCrosswise = perFpInfo.isCrosswise;
	bool isSingleChoice = perFpInfo.isSingleChoice;
	Mat questionGraySum(1,optionNum,CV_32S);
	//选项矩形
	Rect optionRect;
	double step;
	result.result=0;
	result.suspectFlag=0;
	if(isCrosswise)
	{
		step = roi.cols/num;
		optionRect = Rect(0,0,(int)step,roi.rows);
	}else
	{
		step = roi.rows/num;
		optionRect = Rect(0,0,roi.cols,(int)step);
	}
	//形态学闭操作
	Mat closed_roi;
	cv::Size seSize;
	if(istype2)
	{
		seSize.width = optionRect.width>>2;
		seSize.height= optionRect.height>>2;
		Mat se = getStructuringElement(MORPH_RECT,seSize);
		cv::morphologyEx(255-roi,closed_roi,MORPH_OPEN,se);

	}else closed_roi=255-roi;
	
 	//imshow("roi",roi);
 	//imshow("closed",closed_roi);
 	//waitKey();

	threshold_filled = optionRect.area()*7*(1+0.5*areaThreshold);
	threshold_suspect = threshold_filled*.5;
	perFpInfo.markerIdx[2]=perFpInfo.markerIdx[1];
	//如果横排
	
		Mat optionImg;
		int j=0;
		for (int i=0;i<num;i=i+interval+1)
		{
			
//			optionRect.x=min((int)step*i,roi.cols-optionRect.width);
			optionRect=mbt.GetQuestionBoundry(perFpInfo);
			optionRect.x-=rectPos.x;
			optionRect.y-=rectPos.y; 
//			取出每个选项区域并反相
			optionImg = closed_roi(optionRect);
//			保存各选项灰度和
			questionGraySum.at<int>(j) = (int)cv::sum(optionImg).val[0];
			perFpInfo.markerIdx[1]+=(perFpInfo.interval+1);
			perFpInfo.markerIdx[2]+=(perFpInfo.interval+1);
			j++;
		} 

	//求最大值
	double minValue,maxVaule;
	int minIdx[2],maxIdx[2];
	cv::minMaxIdx(questionGraySum,&minValue,&maxVaule,minIdx,maxIdx);
	//一致性阈值设置
	double suspect_upperBound,suspect_lowerBound;
	if (isSingleChoice)
	{
		suspect_upperBound = 0.9;
		suspect_lowerBound = 0.9;
	} 
	else
	{
		suspect_upperBound = 0.6;
		suspect_lowerBound = 0.5;
	}
	int threshold_true_filled,threshold_may_filled;

	/*cout<<questionGraySum<<endl;*/

	if (maxVaule>threshold_filled)
	{
		int maxDiffValue = (int)(maxVaule*(suspect_upperBound+0.2*sensibilityThresh));
		int suspectValue = (int)(maxVaule*(suspect_lowerBound+0.2*sensibilityThresh));
		result.result = 0;result.suspectFlag=0;
		for (int i=0;i<optionNum;i++)
		{
			//一致性判断
			if (questionGraySum.at<int>(i)>=maxDiffValue)
			{
				result.result = result.result|(1<<i);
				if (isCrosswise)
				{
					Point point;
					point.x = (int)((i+0.5)*step);
					point.y = roi.rows>>1;
					result.resultPos.push_back(point);

				}else
				{
					Point point;
					point.y = (int)((i+0.5)*step);
					point.x = roi.cols>>1;
					result.resultPos.push_back(point);
				}
				
				
			}//填涂一致性可疑判断
			else if (questionGraySum.at<int>(i)>suspectValue)
			{
				result.suspectFlag = 1;
			}
		}
	}//填涂偏浅可疑判断
	else if (maxVaule>threshold_suspect)
	{
		result.suspectFlag = 2;
		result.result=0;
	}else{
		result.result= 0;
	}
	return suspectFlag;
}

//填涂点答案识别 类型三

int DetectPreFillingPoint( Mat img,vector<Rect> pos,bool isSingleChoice,cv::Point originalPoint,double sensibilityThresh,double areaThreshold,PerFPResult &result)  //0.正常 1.没有填涂  -1.出错，背景维数和填涂点维数不一致
{
	result.suspectFlag = 0;
	double suspect_upperBound,suspect_lowerBound;
	int optionNum=pos.size();
	if (isSingleChoice)
	{
		suspect_upperBound = 0.8;
		suspect_lowerBound = 0.8;
	} 
	else
	{
		suspect_upperBound = 0.55;
		suspect_lowerBound = 0.35;
	}
	int suspectFlag=0;
	int threshold_filled,threshold_suspect;
	Mat questionGraySum(1,optionNum,CV_32S);
	result.result=0;
	result.suspectFlag=0;
	int resultNum=0;
	//选项矩形
	Rect optionRect;
	for(int i=0;i<optionNum;i++)
	{
		optionRect =pos[i];
		optionRect.x +=originalPoint.x;
		optionRect.y +=originalPoint.y;
		threshold_filled = (int)(optionRect.area()*7*(1+0.5*areaThreshold));
		threshold_suspect = (int)(threshold_filled*.5);
		Mat optionImg;

 		//	imshow("aadfaa",img(optionRect));
 		//waitKey();
		

		//形态学闭操作
		Mat closed_roi;
		cv::Size seSize;
		seSize.width = optionRect.width>>2;
		seSize.height= optionRect.height>>2;
		Mat roi;
		img(optionRect).copyTo(roi);
		Mat se = getStructuringElement(MORPH_RECT,seSize);
		cv::morphologyEx(255-roi,optionImg,MORPH_OPEN,se);

		//取出每个选项区域并反相
// 		imshow("afteropen",optionImg);
// 		waitKey();


		//保存各选项灰度和
		questionGraySum.at<int>(i) = (int)cv::sum(optionImg).val[0];
		
	}
	
	//求最大值
	double minValue,maxVaule;
	int minIdx[2],maxIdx[2];
	cv::minMaxIdx(questionGraySum,&minValue,&maxVaule,minIdx,maxIdx);
	if (maxVaule>threshold_filled)
	{
		int maxDiffValue = (int)(maxVaule*(suspect_upperBound+0.2*sensibilityThresh));
		int suspectValue = (int)(maxVaule*(suspect_lowerBound+0.2*sensibilityThresh));
		for (int i=0;i<optionNum;i++)
		{
			//一致性判断
			if (questionGraySum.at<int>(i)>=maxDiffValue)
			{
				result.result = result.result|(1<<i);
				resultNum++;
				Point point;
				point.y = pos[i].y+originalPoint.y+(pos[i].height>>1);
				point.x = pos[i].x+originalPoint.x+(pos[i].width>>1);
				result.resultPos.push_back(point);

			}//填涂一致性可疑判断
			else if (questionGraySum.at<int>(i)>suspectValue)
			{
				result.suspectFlag = 1;
			}
		}
		if (resultNum>1)
		{
			result.suspectFlag=3;
		}
	}//填涂偏浅可疑判断
	else if (maxVaule>threshold_suspect)
	{
		result.suspectFlag = 2;
		
	}
	return 0;
}
