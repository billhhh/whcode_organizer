#include <math.h>
#include <cv.h>

using namespace cv;
//倾斜校正
//其中参数rt为4个定位点的外接矩形组	1|2
//索引定义如图						-+-
//									3|4
int TiltCorrection(Mat src,Mat &dst,cv::Rect* rt,double &angle);
int TiltCorrection(Mat src,Mat &dst,vector<cv::Rect> &anchorPt,short anchorType,double &angle);
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/* 类型三无定位点 的倾斜矫正与定位矩形和参考点的获取                    */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////

//src为源图像，dst为倾斜矫正后的图像，anchorRect为定位矩形区域，originalPoint为定位基准点，angle为倾斜角度
int TiltCorrection(Mat src,Mat &dst,Rect &anchorRect,Point &originalPoint, double &angle);
//获取矫正后图像的矩形框位置与大小
int GetOriginalPoint(Mat src,Rect &anchorRect,Point &originalPoint);
void SortPoint(vector<cv::Point>& points,bool isSortByX=true);
//褶皱检测
bool DetectFold(vector<Rect> anchorPoints,vector<Rect> anchorPoints2);
//定位点最大位移阈值，相对定位点高度的倍数
const double anchor_point_max_shift = 1.0f;