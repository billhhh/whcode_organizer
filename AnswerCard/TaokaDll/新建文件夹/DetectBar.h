#ifndef _ACALGORITHM_H
#define _ACALGORITHM_H
#include<string>
#include "ACStructs.h"
#include<cv.h>
#include<zbar.h>
using namespace cv;
using namespace zbar;
//extern AC_info acinfo;  //题卡信息结构体
bool GetBar(Mat bar,string &str);//条形码检测 Mat为条形码所在区域的图像块,str为识别结果。Mat必须为灰度图片，否则识别不出结果。
bool GetBar(Mat src,Rect rect,string &str);//条形码检测；src为源图像，Rect为条形码所在区域，str为结果字符串。
int GetBar(Mat src,vector<Bar_info> barGroup,vector<BarResult> &barResult,double xRangeScale,double yRangeScale);//条形码检测，bargroup为条形码组的所在区域信息，barresult为识别结果
int GetBar(Mat src,vector<Bar_info> barGroup,vector<BarResult> &barResult);     //类型三条形码检测，没必要扩大搜索区域
#endif