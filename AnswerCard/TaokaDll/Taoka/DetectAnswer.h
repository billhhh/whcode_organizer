#include"ACStructs.h"
#include"MarkersBoundaryTable.h"
#define QUESSTION_ERERR_SMALL    1           //区域块太小
#define QUESSTION_ERERR_LARGE  2          //区域块太大
Point GetMinCropArea(MarkersBoundaryTable &mbt,vector<FillingPoints_info> fillingPointGroup);
//类型二、三
//int DetectAnswer1(Mat Img,vector<ItemPos> questionInfo,MarkersBoundaryTable &mbt,AnswerResult &ar,double sensibilityThresh,double areaThreshold);
//类型三
int DetectAnswer(Mat Img,vector<ItemPos> questionInfo,MarkersBoundaryTable &mbt,AnswerResult &ar,bool quetionType,double sensibilityThresh,double areaThreshold,double seSize=0);
//类型三多组
int DetectAnswer(Mat Img,vector<ItemPos> questionInfo,map<ushort,MarkersBoundaryTable*> &mbtMap,AnswerResult &ar,bool quetionType,double sensibilityThresh,double areaThreshold,double seSize=0);
//类型一
int DetectAnswer1(Mat Img,vector<ItemPos> questionInfo,MarkersBoundaryTable &mbt,AnswerResult &ar,double sensibilityThresh,double areaThreshold);
//类型二、三 每小题的答案识别
int DetectPreQuestionAnswer( Mat roi,bool isCrosswise,bool isSingleChoice,int optionNum,bool quetionType,double sensibilityThresh,double areaThreshold,double seSizeTh,PerquestionResult &result);
//类型一 每小题的答案识别
int DetectPreQuestionAnswer1( Mat roi,ItemPos itemPos,int optionNum,double sensibilityThresh,double areaThreshold,PerquestionResult &result);  //0.正常 1.没有填涂
//类型一、二 每小题的答案识别 利用mbt精确定位
int DetectPreQuestionAnswer1( Mat roi,int &globalGray,MarkersBoundaryTable &mbt,Point rectPos,ItemPos perQuestionInfo,int optionNum,double sensibilityThresh,double areaThreshold,PerquestionResult &result);

