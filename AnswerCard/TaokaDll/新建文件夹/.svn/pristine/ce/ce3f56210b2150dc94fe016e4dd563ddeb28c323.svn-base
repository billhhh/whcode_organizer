#include"ACStructs.h"
#include"MarkersBoundaryTable.h"
//识别Id点
bool DetectIdPoint(Mat img,vector<cv::Rect> idPInfo,double areaThresh);
//识别试卷类型、选做题
int DetectPaperType(Mat Img,bool istype2,ItemPos fPInfo,MarkersBoundaryTable &mbt,double sensibilityThresh,double areaThreshold,FillingPointsResult &fpr);
int DetectPaperType(Mat,FillingpointItemPos fPInfo,cv::Point originalPoint,double sensibilityThresh,double areaThreshold,FillingPointsResult &fpr);   //类型三
//识别缺考标记和违纪填涂点
int DetectAbsent(Mat Img,bool istype2,ItemPos fPInfo,MarkersBoundaryTable &mbt,double areaThreshold,FillingPointsResult &fpr);
int DetectAbsent(Mat,FillingpointItemPos fPInfo,cv::Point originalPoint,double areaThreshold,FillingPointsResult &fpr);		//类型三
//识别数字型的填涂点
int DetectNumericPoint(Mat Img,bool istype2,FillingPoints_info fPInfo,MarkersBoundaryTable &mbt,double sensibilityThresh,double areaThreshold,FillingPointsResult &fpr);
int DetectNumericPoint(Mat,FillingPoints_info3 fPInfo,cv::Point originalPoint,double sensibilityThresh,double areaThreshold,FillingPointsResult &fpr);		//类型三
//填涂点的填涂结果识别
int DetectPreFillingPoint( Mat roi,bool istype2,ItemPos fPPos,MarkersBoundaryTable &mbt,Point rectPos,double sensibilityThresh,double areaThreshold,PerFPResult &result);
//类型三
int DetectPreFillingPoint( Mat img,vector<Rect> pos,bool isSingleChoice,cv::Point originalPoint,double sensibilityThresh,double areaThreshold,PerFPResult &result);