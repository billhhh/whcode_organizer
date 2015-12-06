#include "ACStructs.h"
#include <cv.h>
using namespace cv;
//识别参考点
 int DetectRefPoint(Mat srcImg,vector<Rect> srcYMarker,vector<Rect> yMarker,vector<Rect> & refPoint,Rect & refMarkerPos,Point posRevise,double &angle);
//预处理
void PreprocesrefPointRoi(Mat &RoiImage,cv::Size refSize);
extern vector<cv::Rect> DetectRectangle(Mat roi_img,Size rectSize);

extern void SortRects(vector<cv::Rect>& rects,bool isSortByX);
//计算识别参考点和对应标记点之间的角度
void GetrefMarkerAngle(const Rect &yMarker,const Rect &refPoint,double &angle);
//计算识别参考点对应的标记点
int GetMarker(const vector<Rect> &srcYMarker,Rect refPoint);





