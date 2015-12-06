#include "DetectRefPoint.h"
#include <highgui.h>
int DetectRefPoint(Mat img,vector<Rect> srcYMarker, vector<Rect>  yMarker,vector<Rect>  &refPoint,Rect & refMarkerPos, Point posRevise,double &angle)
{
	Mat srcimg = img.clone();
	double xRangeScale=2,yRangeScale=4;
	cv::Size refPointSize;
	cv::Rect roiRect;
	vector<Rect> preRefPoint;
	vector<Rect>::iterator iter = refPoint.begin();
	for (;iter != refPoint.end();)
	{
		if (abs(iter->x - srcYMarker[0].x) < (srcimg.cols>>1))
		{
			iter = refPoint.erase(iter);
		}
		else
			iter++;
	}
	if (refPoint.size()==0)
	{
		angle = 0;
		return 0;
	}
	int refMarker[2];
	SortRects(srcYMarker,false);
	SortRects(yMarker,false);
	int refNum=MIN(refPoint.size() , 2);
	for(int i=0;i<refNum;i++){					//计算感兴趣区域
		refMarker[i]=GetMarker(srcYMarker,refPoint[i]);
		refPointSize=refPoint.at(i).size();	
		roiRect.width = xRangeScale*refPoint.at(i).width;
		roiRect.height = yRangeScale*refPoint.at(i).height;
		roiRect.x = MIN(MAX(refPoint.at(i).x +posRevise.x - ((roiRect.width-refPoint.at(i).width)>>1),0),srcimg.cols-roiRect.width);
		roiRect.y = MIN(MAX(yMarker[refMarker[i]].y - srcYMarker[refMarker[i]].y + refPoint.at(i).y - ((roiRect.height-refPoint.at(i).height)>>1),0),srcimg.rows-roiRect.height);
		Mat roiImage=srcimg(roiRect).clone();
// 		imshow("aa",roiImage);
// 		waitKey();
		PreprocesrefPointRoi(roiImage,refPointSize);		//对裁剪图像进行预处理
//  		imshow("bb",roiImage);
//  		waitKey();
		vector<cv::Rect> DetectedRect;
		DetectedRect = DetectRectangle(roiImage,refPoint.at(i).size());
		if (DetectedRect.size()>1||DetectedRect.size()==0)
		{
			return -1;
		}
		else
		{
			DetectedRect[0].x += roiRect.x;
			DetectedRect[0].y += roiRect.y;
			preRefPoint.push_back(DetectedRect[0]);
		}
		
	}
	refMarkerPos = yMarker[refMarker[0]];
	double refMarkerAngle[2];
	double preRefMarkerAngle[2];
	for(int i=0;i<refNum;i++)
	{
		GetrefMarkerAngle(srcYMarker[refMarker[i]],refPoint[i],refMarkerAngle[i]);
		GetrefMarkerAngle(yMarker[refMarker[i]],preRefPoint[i],preRefMarkerAngle[i]);
		preRefMarkerAngle[i]-=refMarkerAngle[i];
	}
	if (refNum==2)
	{
		if (abs(preRefMarkerAngle[0] - preRefMarkerAngle[1]) > 0.45)
		{
			return -2;
		}
		else
			angle = (preRefMarkerAngle[1]+preRefMarkerAngle[0])/2;
	}
	else
		angle = preRefMarkerAngle[0];
	return 0;

}

void PreprocesrefPointRoi(Mat &RoiImage,cv::Size refSize){
	Mat tmp;
	//自适应二值化
	double t = threshold(RoiImage,tmp,128,255,THRESH_OTSU);
	threshold(RoiImage,tmp,t*1.1,255,THRESH_BINARY_INV);
	//开操作
	Mat se = getStructuringElement(MORPH_ELLIPSE,Size(refSize.width*0.7,refSize.height*0.7));
	morphologyEx(tmp,tmp,cv::MORPH_OPEN,se);
	RoiImage = tmp;
}

//vector<cv::Rect> DetectRectangle(Mat roi_img,Size rectSize){
//
//	vector<vector<Point> > contours;    //轮廓数组（非矩形数组），每个轮廓是一个Point型的vector
//	findContours(roi_img,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );
//	vector<cv::Rect> boundRect;                           //包围点集的最小矩形vector @if contours.size()>2
//	Rect bRect;
//	double diff_threashold = 0.6;
//	Size maxDiffSize(rectSize.width*diff_threashold*.5,rectSize.height*diff_threashold*.6);
//	for(int i = contours.size()-1;i>=0; i-- )
//	{
//		bRect = boundingRect(contours[i]);
//		double area=contourArea(contours[i]);
//		if(area/bRect.area()<diff_threashold)
//			continue;
//
//		//面积检测
//		if (abs(1-(float)rectSize.area()/bRect.area())<diff_threashold)
//		{
//			int hDiff=rectSize.height-bRect.height;
//			cv::Size sizeDiff(abs(rectSize.width-bRect.width),abs(hDiff));
//			if (sizeDiff.width<maxDiffSize.width&&sizeDiff.height<=maxDiffSize.height)
//			{
//				boundRect.push_back(bRect);    //计算并返回包围轮廓点集的最小矩形
//			}
//		}
//
//	}
//	return boundRect;
//}

//计算识别参考点和对应标记点之间的角度
void GetrefMarkerAngle(const Rect &yMarkerPos,const Rect & refPointPos,double &angle)
{
	Point yMarker,refPoint;
	yMarker.x =yMarkerPos.x + yMarkerPos.width>>1; 
	yMarker.y =yMarkerPos.y + yMarkerPos.height>>1; 
	refPoint.x =refPointPos.x + refPointPos.width>>1; 
	refPoint.y =refPointPos.y + refPointPos.height>>1; 
	if (yMarker.y==refPoint.y)
	{
		angle=0;
	}
	else
	{
		angle=atan(((double)(yMarker.y-refPoint.y))/(yMarker.x-refPoint.x))*180/CV_PI;
	}
}

//计算识别参考点对应的标记点
int GetMarker(const vector<Rect> &srcYMarker,Rect refPoint)
{
	int refMarker=0;
	vector<Rect>::const_iterator iter = srcYMarker.begin();
	for (;iter!=srcYMarker.end();iter++)
	{
		if (iter->y < refPoint.y)
		{
			refMarker++;
		} 
		else
		{
			break;
		}
	}
	if (abs(srcYMarker[refMarker].y - refPoint.y) > abs(srcYMarker[refMarker-1].y-refPoint.y))
	{
		refMarker--;
	}
	return refMarker;
}