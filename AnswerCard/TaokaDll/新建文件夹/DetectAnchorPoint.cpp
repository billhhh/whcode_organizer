#include "stdafx.h"
#include "DetectAnchorPoint.h"
#include <iostream>
#include<highgui.h>
using namespace std;
using namespace cv;
/*感兴趣区域的预处理*/
void PreprocesRoi(Mat &RoiImage,cv::Size Achorsize){
// 	Mat close_se(Achorsize.height*se_rate,Achorsize.width*se_rate,CV_8U,Scalar(1));
// 	Mat dstImg;
// 	morphologyEx(RoiImage,dstImg,MORPH_CLOSE ,close_se);
// 	threshold(dstImg,RoiImage,160,255,THRESH_BINARY_INV);	//转换为二值图像	
	Mat tmp;
	//自适应二值化
	double t = threshold(RoiImage,tmp,128,255,THRESH_OTSU);
	threshold(RoiImage,tmp,t*1.1,255,THRESH_BINARY_INV);
	//imshow("t",tmp);
 // 	waitKey(0);
	//开操作
	Mat se = getStructuringElement(MORPH_ELLIPSE,Size(Achorsize.width*0.7,Achorsize.height*0.7));
	morphologyEx(tmp,tmp,cv::MORPH_OPEN,se);
	//imshow("t2",tmp);
 // 	waitKey(0);
	//闭操作
// 	Mat bw;
// 	se = getStructuringElement(MORPH_RECT,Size(6,5));
// 	morphologyEx(tmp,bw,cv::MORPH_CLOSE,se);

// 	vector<vector<Point> > contours;
// 	findContours(bw.clone(),contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );
// 	for (int i=0;i<contours.size();i++)
// 	{
// 		Rect bRect = boundingRect(contours[i]);
// 		bRect.width++;
// 		bRect.height++;
// 		Mat perContours = RoiImage(bRect);
// 		double avgGray = cv::mean(perContours).val[0];
// 		if (avgGray>t)
// 		{
// 			//drawContours(bw,contours,i,Scalar(0,0,0),CV_FILLED);
// 			bw(bRect)= 0;
// 		}
// 	}
 	RoiImage = tmp;

//   	imshow("t",RoiImage);
//   	waitKey(0);
}

void PreprocesAnchorRoi(Mat &RoiImage,cv::Size Achorsize){
// 	Mat close_se(Achorsize.height*se_rate,Achorsize.width*se_rate,CV_8U,Scalar(1));
// 	Mat dstImg;
// 	morphologyEx(RoiImage,dstImg,MORPH_CLOSE ,close_se);
// 	threshold(dstImg,RoiImage,160,255,THRESH_BINARY_INV);	//转换为二值图像	
	Mat tmp;
	//自适应二值化
	double t = threshold(RoiImage,tmp,128,255,THRESH_OTSU);
	threshold(RoiImage,tmp,t*1.1,255,THRESH_BINARY_INV);
	//闭操作
	Mat se = getStructuringElement(MORPH_RECT,Size(5,4));
	morphologyEx(tmp,tmp,cv::MORPH_CLOSE,se);
	//开操作
	se = getStructuringElement(MORPH_ELLIPSE,Size(Achorsize.width*0.7,Achorsize.height*0.7));
	morphologyEx(tmp,tmp,cv::MORPH_OPEN,se);

// 	vector<vector<Point> > contours;
// 	findContours(bw.clone(),contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );
// 	for (int i=0;i<contours.size();i++)
// 	{
// 		Rect bRect = boundingRect(contours[i]);
// 		bRect.width++;
// 		bRect.height++;
// 		Mat perContours = RoiImage(bRect);
// 		double avgGray = cv::mean(perContours).val[0];
// 		if (avgGray>t)
// 		{
// 			//drawContours(bw,contours,i,Scalar(0,0,0),CV_FILLED);
// 			bw(bRect)= 0;
// 		}
// 	}
 	RoiImage = tmp;
// 	cout<<RoiImage<<endl;
//   	imshow("t",RoiImage);
//  	waitKey(0);
}

/************************************************************************/
/*								检测定位点
参数：
	srcimg：	答题卡图像
	AnchorPos：	样卡中定位点的外接矩形的位置及大小，检测得到的定位点的实际位置通过该参数传递
	anchorType：定位点样式
返回值：
	0：		正常
	!0：	异常
*/
/************************************************************************/
int DetectAnchorPoint(Mat srcimg,vector<cv::Rect> &AnchorPos,short anchorType,double xRangeScale,double yRangeScale){
	int i,anchorNum=0;
	//定位点数量
	switch(anchorType)
	{
		//123缺4
	case 15:
		anchorNum = 4;
		break;
	case 7:
	case 11:
	case 13:
	case 14:
		anchorNum = 3;
		break;
	case 3:
	case 5:
	case 10:
	case 12:
		anchorNum = 2;
		break;
	}
	vector<cv::Rect>  AnchorPointRect;	//

	cv::Size achorSize;
	cv::Rect roiRect;
	for(i=0;i<anchorNum;i++){					//计算感兴趣区域
		achorSize=AnchorPos.at(i).size();		//每个定位点的大小可能都不相同
		roiRect.width = AnchorPos.at(i).width+xRangeScale*AnchorPos.at(i).width+AnchorPos.at(i).width;
		roiRect.height = AnchorPos.at(i).height+yRangeScale*AnchorPos.at(i).height+AnchorPos.at(i).height;
		roiRect.x = MIN(MAX(AnchorPos.at(i).x - ((roiRect.width-AnchorPos.at(i).width)>>1),0),srcimg.cols-roiRect.width);
		roiRect.y = MIN(MAX(AnchorPos.at(i).y - ((roiRect.height-AnchorPos.at(i).height)>>1),0),srcimg.rows-roiRect.height);
		Mat roiImage=srcimg(roiRect).clone();

// 		imshow("aa",roiImage);
// 		waitKey();

		PreprocesAnchorRoi(roiImage,achorSize);		//对裁剪图像进行预处理
		vector<cv::Rect> DetectedRect;
		DetectedRect = DetectRectangle(roiImage,AnchorPos.at(i).size());
		roiImage=srcimg(roiRect).clone();
		int err_ID = DetectAncorERR(roiImage,DetectedRect,AnchorPos[i]);
		if (!err_ID)
		{
			DetectedRect[0].x += roiRect.x;
			DetectedRect[0].y += roiRect.y;
			AnchorPos[i] = DetectedRect[0];
		}else
		{
			return ANCHOR_ERR_BASE+i+i+err_ID;
		}
	}
	cv::Point p1,p2;
	double fold_threshold = 2.6;

	switch(anchorType)
	{
		//123缺4
	case 15:
	case 7:
		{
			p1.x = AnchorPos[2].x - AnchorPos[0].x;
			p1.y = AnchorPos[2].y - AnchorPos[0].y;
			p2.x = AnchorPos[1].x - AnchorPos[0].x;
			p2.y = AnchorPos[1].y - AnchorPos[0].y;
			double angle = acos((p2.y*p1.y+p2.x*p1.x)/sqrt((double)(p1.x*p1.x+p1.y*p1.y)*(p2.x*p2.x+p2.y+p2.y)))*180/CV_PI;
			if (abs(angle-90)>fold_threshold)
			{
				return ANCHOR_ERR_FOLD;
			}
			break;
		}
		//124缺3
	case 11:
		{
			p1.x = AnchorPos[2].x - AnchorPos[1].x;
			p1.y = AnchorPos[2].y - AnchorPos[1].y;
			p2.x = AnchorPos[0].x - AnchorPos[1].x;
			p2.y = AnchorPos[0].y - AnchorPos[1].y;
			double angle = acos((p2.y*p1.y+p2.x*p1.x)/sqrt((double)(p1.x*p1.x+p1.y*p1.y)*(p2.x*p2.x+p2.y+p2.y)))*180/CV_PI;
			if (abs(angle-90)>fold_threshold)
			{
				return ANCHOR_ERR_FOLD;
			}
			break;
		}
		//134缺2
	case 13:
		{
			p1.x = AnchorPos[2].x - AnchorPos[1].x;
			p1.y = AnchorPos[2].y - AnchorPos[1].y;
			p2.x = AnchorPos[0].x - AnchorPos[1].x;
			p2.y = AnchorPos[0].y - AnchorPos[1].y;
			double angle = acos((p2.y*p1.y+p2.x*p1.x)/sqrt((double)(p1.x*p1.x+p1.y*p1.y)*(p2.x*p2.x+p2.y+p2.y)))*180/CV_PI;
			if (abs(angle-90)>fold_threshold)
			{
				return ANCHOR_ERR_FOLD;
			}
			break;
		}
		//234缺1
	case 14:
		{
			p1.x = AnchorPos[2].x - AnchorPos[1].x;
			p1.y = AnchorPos[2].y - AnchorPos[1].y;
			p2.x = AnchorPos[0].x - AnchorPos[2].x;
			p2.y = AnchorPos[0].y - AnchorPos[2].y;
			double angle = acos((p2.y*p1.y+p2.x*p1.x)/sqrt((double)(p1.x*p1.x+p1.y*p1.y)*(p2.x*p2.x+p2.y+p2.y)))*180/CV_PI;
			if (abs(angle-90)>fold_threshold)
			{
				return ANCHOR_ERR_FOLD;
			}
			break;
		}
	case 3:
	case 12:  //仅 3 4
		{
			double angle = atan(((double)(AnchorPos[1].y-AnchorPos[0].y))/(AnchorPos[1].x-AnchorPos[0].x))*180/CV_PI;
			if (abs(angle)>fold_threshold)
			{
				return ANCHOR_ERR_FOLD;
			}
			break;
		}
	case 10: //仅2 4
	case 5:  //仅1 3
		{
			double angle = atan(((double)(AnchorPos[1].x-AnchorPos[0].x))/(AnchorPos[1].y-AnchorPos[0].y))*180/CV_PI;
			if (abs(angle)>fold_threshold)
			{
				return ANCHOR_ERR_FOLD;
			}
			break;
		}
	default:
		//未定义定位点分布类型
		return 2;
	}
	return 0;
}

int DetectAnchorPoint(Mat srcimg,vector<cv::Rect> &AnchorPos,short anchorType,Size xMarkSize,Size yMarkSize,double xRangeScale,double yRangeScale){
	int i,anchorNum=0;
	int markHight=MAX(xMarkSize.height,yMarkSize.height);
	//定位点数量
	switch(anchorType)
	{
		//123缺4
	case 15:
		anchorNum = 4;
		break;
	case 7:
	case 11:
	case 13:
	case 14:
		anchorNum = 3;
		break;
	case 3:
	case 5:
	case 10:
	case 12:
		anchorNum = 2;
		break;
	}
	vector<cv::Rect>  AnchorPointRect;	//

	cv::Size achorSize;
	cv::Rect roiRect;
	for(i=0;i<anchorNum;i++){					//计算感兴趣区域
		achorSize=AnchorPos.at(i).size();		//每个定位点的大小可能都不相同
		roiRect.width = AnchorPos.at(i).width+xRangeScale*AnchorPos.at(i).width+AnchorPos.at(i).width;
		roiRect.height = AnchorPos.at(i).height+yRangeScale*AnchorPos.at(i).height+AnchorPos.at(i).height;
		roiRect.x = MIN(MAX(AnchorPos.at(i).x - ((roiRect.width-AnchorPos.at(i).width)>>1),0),srcimg.cols-roiRect.width);
		roiRect.y = MIN(MAX(AnchorPos.at(i).y - ((roiRect.height-AnchorPos.at(i).height)>>1),0),srcimg.rows-roiRect.height);
		Mat roiImage=srcimg(roiRect).clone();
 	
		//imshow("roiingm",roiImage);
 	//	waitKey();

		PreprocesAnchorRoi(roiImage,achorSize);		//对裁剪图像进行预处理
		vector<cv::Rect> DetectedRect;
		DetectedRect = DetectRectangle(roiImage,AnchorPos.at(i).size(),markHight);
		roiImage=srcimg(roiRect).clone();
		if (DetectedRect.size()>1&&anchorNum>=3)
		{
			int xMarkdiff=MAX(abs(achorSize.width-xMarkSize.width),abs(achorSize.height-xMarkSize.height));
			int yMarkdiff=MAX(abs(achorSize.width-yMarkSize.width),abs(achorSize.height-yMarkSize.height));
			if (xMarkdiff<=2||yMarkdiff<=5)
			{
				DetectAnchor(DetectedRect,i,anchorType,xMarkSize,yMarkSize);
			}
		}
		int err_ID = DetectAncorERR(roiImage,DetectedRect,AnchorPos[i]);
		if (!err_ID)
		{
			DetectedRect[0].x += roiRect.x;
			DetectedRect[0].y += roiRect.y;
			AnchorPos[i] = DetectedRect[0];
		}else
		{
			return ANCHOR_ERR_BASE+i+i+err_ID;
		}
	}
	cv::Point p1,p2;
	double fold_UpThreshold = 91,fold_LowThreshold=88;
	double fold_threshold=2.5;

	switch(anchorType)
	{
		//123缺4
	case 15:
	case 7:
		{
			p1.x = AnchorPos[2].x - AnchorPos[0].x;
			p1.y = AnchorPos[2].y - AnchorPos[0].y;
			p2.x = AnchorPos[1].x - AnchorPos[0].x;
			p2.y = AnchorPos[1].y - AnchorPos[0].y;
			double angle = acos((p2.y*p1.y+p2.x*p1.x)/sqrt((double)(p1.x*p1.x+p1.y*p1.y)*(p2.x*p2.x+p2.y+p2.y)))*180/CV_PI;
			if (angle>fold_UpThreshold||angle<fold_LowThreshold)
			{
				return ANCHOR_ERR_FOLD;
			}
			break;
		}
		//124缺3
	case 11:
		{
			p1.x = AnchorPos[2].x - AnchorPos[1].x;
			p1.y = AnchorPos[2].y - AnchorPos[1].y;
			p2.x = AnchorPos[0].x - AnchorPos[1].x;
			p2.y = AnchorPos[0].y - AnchorPos[1].y;
			double angle = acos((p2.y*p1.y+p2.x*p1.x)/sqrt((double)(p1.x*p1.x+p1.y*p1.y)*(p2.x*p2.x+p2.y+p2.y)))*180/CV_PI;
			if (angle>fold_UpThreshold||angle<fold_LowThreshold)
			{
				return ANCHOR_ERR_FOLD;
			}
			break;
		}
		//134缺2
	case 13:
		{
			p1.x = AnchorPos[2].x - AnchorPos[1].x;
			p1.y = AnchorPos[2].y - AnchorPos[1].y;
			p2.x = AnchorPos[0].x - AnchorPos[1].x;
			p2.y = AnchorPos[0].y - AnchorPos[1].y;
			double angle = acos((p2.y*p1.y+p2.x*p1.x)/sqrt((double)(p1.x*p1.x+p1.y*p1.y)*(p2.x*p2.x+p2.y+p2.y)))*180/CV_PI;
			if (angle>fold_UpThreshold||angle<fold_LowThreshold)
			{
				return ANCHOR_ERR_FOLD;
			}
			break;
		}
		//234缺1
	case 14:
		{
			p1.x = AnchorPos[2].x - AnchorPos[1].x;
			p1.y = AnchorPos[2].y - AnchorPos[1].y;
			p2.x = AnchorPos[0].x - AnchorPos[2].x;
			p2.y = AnchorPos[0].y - AnchorPos[2].y;
			double angle = acos((p2.y*p1.y+p2.x*p1.x)/sqrt((double)(p1.x*p1.x+p1.y*p1.y)*(p2.x*p2.x+p2.y+p2.y)))*180/CV_PI;
			if (angle>fold_UpThreshold||angle<fold_LowThreshold)
			{
				return ANCHOR_ERR_FOLD;
			}
			break;
		}
	case 3:
	case 12:  //仅 3 4
		{
			double angle = atan(((double)(AnchorPos[1].y-AnchorPos[0].y))/(AnchorPos[1].x-AnchorPos[0].x))*180/CV_PI;
			if (abs(angle)>fold_threshold)
			{
				return ANCHOR_ERR_FOLD;
			}
			break;
		}
	case 10: //仅2 4
	case 5:  //仅1 3
		{
			double angle = atan(((double)(AnchorPos[1].x-AnchorPos[0].x))/(AnchorPos[1].y-AnchorPos[0].y))*180/CV_PI;
			if (abs(angle)>fold_threshold)
			{
				return ANCHOR_ERR_FOLD;
			}
			break;
		}
	default:
		//未定义定位点分布类型
		return 2;
	}
	return 0;
}
/*检测定位点矩形的异常*/
int DetectAncorERR(Mat roi,vector<cv::Rect> &DetectedRect,Rect AnchorPos){
	if(DetectedRect.size()>1)
	{
		// 		vector<vector<Point> > contours;
		// 		findContours(bw.clone(),contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );
		Mat tmp;
		double t = threshold(roi,tmp,128,255,THRESH_OTSU);
		for(vector<cv::Rect>::iterator it  = DetectedRect.begin(); it != DetectedRect.end(); )  
		{  
			Rect bRect = *it;
			Mat perContours = roi(bRect);
			double avgGray = cv::mean(perContours).val[0];
			if (avgGray>t)
			{
				it = DetectedRect.erase(it);
			}else
				it++;			
		} 
		if (DetectedRect.size()>1)
		{
			for(vector<cv::Rect>::iterator iter  = DetectedRect.begin(); iter != DetectedRect.end();)  
			{
				if (abs(iter->height-AnchorPos.height) > 4 || abs(iter->width-AnchorPos.width) >4 )
				{
					iter = DetectedRect.erase(iter);
				}
				else
					iter++;
			}

		}
		if (DetectedRect.size()>1)
		{
			Rect bRect = DetectedRect[0];
			for(vector<cv::Rect>::iterator iter  = DetectedRect.begin(); iter != DetectedRect.end();iter++)  
			{
				if (iter->height>bRect.height&iter->width>bRect.width)
				{
					bRect=*iter;
				}
			}
			DetectedRect.clear();
			DetectedRect.push_back(bRect);
				
// 			imshow("debug",roi);
// 			waitKey(0);
		}
		if (DetectedRect.size()>1)
		{

			return ANCHOR_ERR_OVERNUM;
		} 
		else if(DetectedRect.size()<1)
		{
// 			imshow("debug",roi);
// 			waitKey(0);
			return ANCHOR_ERR_NORECT;
		}
	}

	else if(DetectedRect.size()<1)
	{
// 		imshow("debug",roi);
// 		waitKey(0);
		return ANCHOR_ERR_NORECT;
	}
	return 0;
}

/*检测感兴趣区域内的矩形*/

vector<cv::Rect> DetectRectangle(Mat roi_img,Size rectSize,int markHight){


 /*	imshow("anchor",roi_img);
 	cvWaitKey();*/
	vector<vector<Point> > contours;    //轮廓数组（非矩形数组），每个轮廓是一个Point型的vector
	findContours(roi_img,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );
	vector<cv::Rect> boundRect;                           //包围点集的最小矩形vector @if contours.size()>2
	Rect bRect;
	double diff_threashold = 0.65;
	int downHThreashold=MAX(4,abs(rectSize.height-markHight))*diff_threashold;
	Size maxDiffSize(rectSize.width*diff_threashold*.5+0.5,rectSize.height*diff_threashold*.6+0.5);
	for(int i = contours.size()-1;i>=0; i-- )
	{
		bRect = boundingRect(contours[i]);
		double area=contourArea(contours[i]);
		if(area/bRect.area()<diff_threashold)
			continue;

		//面积检测
		if (abs(1-(float)rectSize.area()/bRect.area())<diff_threashold)
		{
			int hDiff=rectSize.height-bRect.height;
			cv::Size sizeDiff(abs(rectSize.width-bRect.width),abs(hDiff));
			if (hDiff>=downHThreashold)
			{
				continue;
			}
			if (sizeDiff.width<=maxDiffSize.width&&sizeDiff.height<=maxDiffSize.height)
			{
				boundRect.push_back(bRect);    //计算并返回包围轮廓点集的最小矩形
			}
// 			float aspectRatioDiff = abs((float)rectSize.width/rectSize.height-(float)bRect.width/bRect.height);
// 			//宽高比检测
// 			if (aspectRatioDiff*aspectRatioDiff<diff_threashold)
// 			{
// 				boundRect.push_back(bRect);    //计算并返回包围轮廓点集的最小矩形
// 			}
		}
		
	}

	return boundRect;
}
vector<cv::Rect> DetectRectangle(Mat roi_img,Size rectSize){

// 	imshow("anchor",roi_img);
// 	cvWaitKey();
	vector<vector<Point> > contours;    //轮廓数组（非矩形数组），每个轮廓是一个Point型的vector
	findContours(roi_img,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );
	vector<cv::Rect> boundRect;                           //包围点集的最小矩形vector @if contours.size()>2
	Rect bRect;
	double diff_threashold = 0.6;
	Size maxDiffSize(rectSize.width*diff_threashold*.5,rectSize.height*diff_threashold*.6);
	for(int i = contours.size()-1;i>=0; i-- )
	{
		bRect = boundingRect(contours[i]);
		double area=contourArea(contours[i]);
		if(area/bRect.area()<diff_threashold)
			continue;

		//面积检测
		if (abs(1-(float)rectSize.area()/bRect.area())<diff_threashold)
		{
			int hDiff=rectSize.height-bRect.height;
			cv::Size sizeDiff(abs(rectSize.width-bRect.width),abs(hDiff));
			if (sizeDiff.width<maxDiffSize.width&&sizeDiff.height<=maxDiffSize.height)
			{
				boundRect.push_back(bRect);    //计算并返回包围轮廓点集的最小矩形
			}
// 			float aspectRatioDiff = abs((float)rectSize.width/rectSize.height-(float)bRect.width/bRect.height);
// 			//宽高比检测
// 			if (aspectRatioDiff*aspectRatioDiff<diff_threashold)
// 			{
// 				boundRect.push_back(bRect);    //计算并返回包围轮廓点集的最小矩形
// 			}
		}
		
	}
	return boundRect;
}


//去除定位点识别时的干扰  将同步头做成定位点时，附件的同步头会对定位点的识别造成干扰
int DetectAnchor(vector<cv::Rect> &DetectedRect,int i,short anchorType,Size xMarkSize,Size yMarkSize)
{
	if(i==0)
	{
		SortRects(DetectedRect,false);
		Rect anRect=DetectedRect[0];
		DetectedRect.clear();
		DetectedRect.push_back(anRect);
	}
	if (i==1)
	{
		if (anchorType==11)
		{
			SortRects(DetectedRect,false);
			Rect anRect=DetectedRect[0];
			DetectedRect.clear();
			DetectedRect.push_back(anRect);
		}else if (anchorType==13)
		{
			SortRects(DetectedRect,false);
			Rect anRect=DetectedRect[DetectedRect.size()-1];
			DetectedRect.clear();
			DetectedRect.push_back(anRect);
		}
	}
	if(i==2)
	{
		SortRects(DetectedRect,false);
		Rect anRect=DetectedRect[DetectedRect.size()-1];
		DetectedRect.clear();
		DetectedRect.push_back(anRect);
	}
return 0;
}
