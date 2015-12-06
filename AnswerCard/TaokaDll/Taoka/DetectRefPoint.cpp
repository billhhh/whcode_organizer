#include "DetectRefPoint.h"
#include <highgui.h>
int DetectRefPoint(Mat img,vector<Rect> srcXMarker,vector<Rect> xMarker,vector<Rect> srcYMarker, vector<Rect>  yMarker,vector<Rect>  &refPoint,Rect & refMarkerPos, Point posRevise,double &angle)
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
	int refYMarker[10];
	int refXMarker[10];
	SortRects(srcXMarker,true);
	SortRects(xMarker,true);
	SortRects(srcYMarker,false);
	SortRects(yMarker,false);
	int refNum=MIN(refPoint.size() , 10);
	for(int i=0;i<refNum;i++){					//计算感兴趣区域
		refXMarker[i]=GetXMarker(srcXMarker,refPoint[i]);
		refYMarker[i]=GetYMarker(srcYMarker,refPoint[i]);
		refPointSize=refPoint.at(i).size();	
		roiRect.width = xRangeScale*refPoint.at(i).width;
		roiRect.height = yRangeScale*refPoint.at(i).height;
		roiRect.x = MIN(MAX(xMarker[refXMarker[i]].x - srcXMarker[refXMarker[i]].x+refPoint.at(i).x - ((roiRect.width-refPoint.at(i).width)>>1),0),srcimg.cols-roiRect.width);
		roiRect.y = MIN(MAX(yMarker[refYMarker[i]].y - srcYMarker[refYMarker[i]].y + refPoint.at(i).y - ((roiRect.height-refPoint.at(i).height)>>1),0),srcimg.rows-roiRect.height);
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
	if (refNum >2)
	{
		refMarkerPos = yMarker[refYMarker[1]];
	/*	refMarkerPos.x = (preRefPoint[1].x + refMarkerPos.x)/2;*/
	}
	else
		refMarkerPos = yMarker[refYMarker[0]];
	double refMarkerAngle[10];
	double preRefMarkerAngle[10];
	for(int i=0;i<refNum;i++)
	{
		GetrefMarkerAngle(srcYMarker[refYMarker[i]],refPoint[i],refMarkerAngle[i]);
		GetrefMarkerAngle(yMarker[refYMarker[i]],preRefPoint[i],preRefMarkerAngle[i]);
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
		if (refNum > 2)
		{
			double maxAngle,minAngle,aveAngle = 0;
			maxAngle=minAngle=preRefMarkerAngle[0];
			for(int i=1;i<refNum;i++)
			{
				if (maxAngle<preRefMarkerAngle[i])
				{
					maxAngle=preRefMarkerAngle[i];
				}
				if (minAngle<preRefMarkerAngle[i])
				{
					minAngle=preRefMarkerAngle[i];
				}
				aveAngle+=preRefMarkerAngle[i];
			}
			if (abs(maxAngle-minAngle)>0.3)
			{
				return -2;
			}
			else
				angle = aveAngle/refNum;
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
	//闭操作
	Mat se = getStructuringElement(MORPH_RECT,Size(3,3));
	morphologyEx(tmp,tmp,cv::MORPH_CLOSE,se);
	//开操作
	se = getStructuringElement(MORPH_RECT,Size(refSize.width*0.7,refSize.height*0.7));
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

//计算识别参考点对应的y方向标记点
int GetYMarker(const vector<Rect> &srcYMarker,Rect refPoint)
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
	if (refMarker >= srcYMarker.size())
	{
		refMarker = srcYMarker.size()-1;
	}
	if (abs(srcYMarker[refMarker].y - refPoint.y) > abs(srcYMarker[refMarker-1].y-refPoint.y))
	{
		refMarker--;
	}
	return refMarker;
}


//计算识别参考点对应的x方向标记点
int GetXMarker(const vector<Rect> &srcXMarker,Rect refPoint)
{
	int refMarker=0;
	vector<Rect>::const_iterator iter = srcXMarker.begin();
	for (;iter!=srcXMarker.end();iter++)
	{
		if (iter->x < refPoint.x)
		{
			refMarker++;
		} 
		else
		{
			break;
		}
	}
	if (refMarker >= srcXMarker.size())
	{
		refMarker = srcXMarker.size()-1;
	}
	if (abs(srcXMarker[refMarker].x- refPoint.x) > abs(srcXMarker[refMarker-1].x-refPoint.x))
	{
		refMarker--;
	}
	return refMarker;
}