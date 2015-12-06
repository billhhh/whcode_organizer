#include <cv.h>
using namespace cv;
#define ANCHOR_ERR_OVERNUM  1
#define ANCHOR_ERR_NORECT	2
#define ANCHOR_ERR_BASE 0
#define ANCHOR_ERR_FOLD 8
const float se_rate = 0.9f;
extern void SortRects(vector<cv::Rect>& rects,bool isSortByX);
//定位点检测
int DetectAnchorPoint(Mat srcimg,vector<cv::Rect> &AnchorPos,short anchorType,double xRangeScale,double yRangeScale);
//定位点检测 添加同步头的大小信息 以适应将同步头做成定位点时旁边同步头可能造成的干扰
int DetectAnchorPoint(Mat srcimg,vector<cv::Rect> &AnchorPos,short anchorType,Size xMarkSize,Size yMarkSize,double xRangeScale,double yRangeScale);
//预处理
void PreprocesRoi(Mat &RoiImage,cv::Size Achorsize);
void PreprocesAnchorRoi(Mat &RoiImage,cv::Size Achorsize);
//矩形块检测
vector<cv::Rect> DetectRectangle(Mat roi_img,Size rectSize);
vector<cv::Rect> DetectRectangle(Mat roi_img,Size rectSize,int markHight);
//定位点异常检测
int DetectAncorERR(Mat roi,vector<cv::Rect> &DetectedRect,Rect AnchorPos);
int DetectAnchor(vector<cv::Rect> &DetectedRect,int i,short anchorType,Size xMarkSize,Size yMarkSize);