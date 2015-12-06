
#ifdef _DLL_MARKAC
#define DLL_MARKAC_API   __declspec(dllexport) __stdcall
#else
#define DLL_MARKAC_API   __declspec(dllimport)
#endif
#ifndef _MARKAC_H
#define _MARKAC_H
#include "CommonStruct.h"

//获取识别结果，输入为待识别图像数据块，识别结果保存在result结构体中，返回值为识别结果状态信息，为0表示识别正常，不为0则返回出错状态。该函数需要先导入题卡描述信息。
extern "C" int DLL_MARKAC_API MarkAnswerCard(uchar* img,cv::Size size, int actype,int acinfoAddress,AC_RST **pResult,AcArgs acargs);
//套卡识别 单张图片
extern "C" int DLL_MARKAC_API MarkTaokaSinglePage(uchar* img,cv::Size imgSize, int actype,int tkinfoAddress,AC_RST * *pResult,AcArgs acargs);
//套卡识别 两张图片 正反面
extern "C" int DLL_MARKAC_API MarkTaokaDoublePage(uchar* frontImg,cv::Size fImgSize, uchar* rearImg,cv::Size rImgSize,int actype,int tkinfoAddress,AC_RST ** pFrontResult,AC_RST ** pRearResult,AcArgs acargs);
//清理地址空间
//套卡识别 单张图片
extern "C" int DLL_MARKAC_API MarkTaokaSPage(const char *imgPath, int actype,int tkinfoAddress,AC_RST * *pResult,AcArgs acargs);
//套卡识别 两张图片 正反面
extern "C" int DLL_MARKAC_API MarkTaokaDPage(const char* frontImgPath, const char* rearImgPath,int actype,int tkinfoAddress,AC_RST ** pFrontResult,AC_RST ** pRearResult,AcArgs acargs);
//获取卡格式结构体信息  因为类型一、二和类型三的结构体不同所以分两个函数
extern "C" int DLL_MARKAC_API GetCum_TkInfo(int tkinfoAddress,Cum_TK_info **tkinfo);
extern "C" int DLL_MARKAC_API GetCum_TkInfo3(int tkinfoAddress,Cum_TK_info3 **tkinfo);
//释放卡格式结构体
extern "C" void DLL_MARKAC_API freeCumTkInfo(Cum_TK_info *tkinfo);
extern "C" void DLL_MARKAC_API freeCumTkInfo3(Cum_TK_info3 *tkinfo);
extern "C" void DLL_MARKAC_API freeResult(AC_RST * pResult);//释放识别结果
#endif