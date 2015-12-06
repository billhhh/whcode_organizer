#pragma once

#include "ACStructs.h"
 #include <libxml/parser.h>
 #include <libxml/tree.h>
#include "DataTypeConversion.h"
#ifdef _DLL_XMLIO
#define DLL_XMLIO_API __declspec(dllexport)
#else
#define DLL_XMLIO_API __declspec(dllimport)
#endif
class DLL_XMLIO_API XmlIo
{
public:
// 	XmlIo(void);
// 	~XmlIo(void);
	//读写接口
	int Read(string filename,AC_info &acInfo);
	int Read(string filename,AC_info3 &acInfo);
	int Read(string filename,TK_info  &tkInfo);
	int Read(string filename,TK_info3  &tkInfo);
	int GetACType(string filename,int &acType);
	int Write(string filename,AC_info acInfo);
	int Write(string filename,AC_info3 acInfo);
	int Write(string filename,TK_info tkInfo);
	int Write(string filename,TK_info3 tkInfo);
protected:
	/////////////////////////////////////写模块/////////////////////////////////////
	//AC_info3结构体
	int WriteACInfo3(xmlNodePtr root_node,AC_info3 acInfo);
	//AC_info结构体
	int WriteACInfo(xmlNodePtr root_node,AC_info acInfo);
	//页码标识块模块
	int WritePageMarkerInfo(xmlNodePtr root_node,vector<cv::Rect> pageMarker);
	//定位点模块
	int WriteAnchorPointInfo(xmlNodePtr root_node,AnchorPoint_info anchorPointInfo);
	// 标记点模块
	int WriteMarkerInfo(xmlNodePtr root_node, Marker_info markerInfo);
	// 标记点模块
	int WriteMarkerInfo3(xmlNodePtr root_node, vector<Marker_info3> markerGroupInfo);
	//id点信息
	int WriteIdPointInfo(xmlNodePtr root_node,vector<ItemPos> idPoint);
	//条码信息
	int WriteBarInfo(xmlNodePtr root_node,vector<Bar_info> barGroup);
	//预定义填涂点组
	int WriteFillingPointsInfo(xmlNodePtr root_node,vector<FillingPoints_info> fillingPointGroup);
	//预定义填涂点组
	int WriteFillingPointsInfo3(xmlNodePtr root_node,vector<FillingPoints_info3> fillingPointGroup);
	//选项信息结构体
	int WriteItemPosInfo(xmlNodePtr partent_node,ItemPos itemPos);
	//选项信息结构体
	int WriteFillingpointItemPos(xmlNodePtr partent_node,FillingpointItemPos itemPos);
	//填涂点背景信息
	int WriteFillingPointBackgroundInfo(xmlNodePtr root_node,vector<PerFillingPtBackground_info> fillingPointBackgroundInfo);
	//题目信息
	int WriteQuestionInfo(xmlNodePtr root_node,vector<ItemPos> questionInfo);
	//题目背景信息
	int WriteQuestionBackgroundInfo(xmlNodePtr root_node,vector<PerQuestionBackground_info> questionBackgroundInfo);
	//答题区域
	int WriteCropAreaInfo(xmlNodePtr root_node,vector<CropArea_info> cropAreaInfo);
	//黑白检测线
	int WriteBlackWhiteLine(xmlNodePtr root_node,Rect blackLine,Rect whiteLine);
	//识别参考点
	int WriteRefPoint(xmlNodePtr root_node,vector<Rect> refPoint);
	//横纵同步头
	int WriteMarker(xmlNodePtr root_node,vector<PerMarker_info> marker);
	/////////////////////////////////////读模块/////////////////////////////////////
	//类型一二
	int ReadACInfo(xmlNodePtr root_node,AC_info &acInfo);
	//类型三
	int ReadACInfo3(xmlNodePtr root_node,AC_info3 &acInfo);
	//定位点模块
	int ReadAnchorPointInfo(xmlNodePtr root_node,AnchorPoint_info &anchorPointInfo);
	//页码标识块模块
	int ReadPageMakerInfo(xmlNodePtr root_node,vector<cv::Rect> &pageMarker);
	// 标记点模块
	int ReadMarkerInfo(xmlNodePtr root_node, Marker_info &markerInfo);
	int ReadMarkerGroupInfo(xmlNodePtr root_node, vector<Marker_info3> &markerInfo);
	//id点信息
	int ReadIdPointInfo(xmlNodePtr root_node,vector<ItemPos> &idPoint);
	//条码信息
	int ReadBarInfo(xmlNodePtr root_node,vector<Bar_info> &barGroup);
	//预定义填涂点组
	int ReadFillingPointsInfo(xmlNodePtr root_node,vector<FillingPoints_info> &fillingPointGroup);
	int ReadFillingPointsInfo(xmlNodePtr root_node,vector<FillingPoints_info3> &fillingPointGroup);
	//选项信息结构体
	int ReadItemPosInfo(xmlNodePtr partent_node,ItemPos &itemPos);
	int ReadFillingpointItemPos(xmlNodePtr firstItemPosPtr,FillingpointItemPos & itemPos);
	//填涂点背景信息
	int ReadFillingPointBackgroundInfo(xmlNodePtr root_node,vector<PerFillingPtBackground_info> &fillingPointBackgroundInfo);
	//题目信息
	int ReadQuestionInfo(xmlNodePtr root_node,vector<ItemPos> &questionInfo);
	//题目背景信息
	int ReadQuestionBackgroundInfo(xmlNodePtr root_node,vector<PerQuestionBackground_info> &questionBackgroundInfo);
	//答题区域
	int ReadCropAreaInfo(xmlNodePtr root_node,vector<CropArea_info> &cropAreaInfo);
	//识别参考点
	
	//横向同步头

	//纵向同步头
	// 获得下一个有效元素
	int GetNextElement(string elementName, xmlNodePtr &cur_node);
	// 读取选项位置信息
	int ReadItemPos(xmlNodePtr firstItemPosPtr,ItemPos &itemPos);
	//识别参考点
	int ReadRefPoint(xmlNodePtr root_node,vector<Rect> &refPoint);
	//横纵同步头
	int ReadMarker(xmlNodePtr root_node,vector<PerMarker_info> &marker);
};

