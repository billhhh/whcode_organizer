#pragma once
#ifndef ANSWERCARD_H
#define ANSWERCARD_H

#include <cv.h>
#include <highgui.h>
#include "qpoint.h"
#include "qstring.h"
#include "qsettings.h"
#include "AnswerCardProcessing.h"
#include "MarkersBoundaryTable.h"
#include "..\XmlIO\XmlIO.h"

using namespace cv;

struct FillPoint
{
	ushort type;
	cv::Rect rect;
	int interval;
	bool isCrossWise;
	short num;
};

struct Questions
{
	short num;
	int interval;
	cv::Rect rect;
	bool isCrossWise;
};

//组状态
enum GroupState
{
	InitialState,   //初始状态
	AnchorState,   //定位点
	MarkerState,    //标记点
	BarCodeState,//条形码
	FillPointState,//填涂点
	ClipState,//裁切
	QuestionState,//答案填涂
	MarkerMakeState,
	WhiteLineState,//白检测
	BlackLineState,//黑检测
	AnchorRectState,
	IdPointState,//id点
	PagePointState
};

enum AnchorSubState
{
	AnchorInitial,
	LTBegin,
	LTEnd,
	RTBegin,
	RTEnd,
	LBBegin,
	LBEnd,
	RBBegin,
	RBEnd
};

enum MarkerSubState
{
	MarkerInitial,
	RowBegin,
	RowPress,
	RowRelease,
	ColBegin,
	ColPress,
	ColRelease
};

enum BaseSubState
{
	BaseInitial,
	BaseBegin,
	BasePress,
	BaseRelease,
	BaseEnd
};

enum QuestionSubState
{
	QuestionInitial,
	SingleBegin,
	SinglePress,
	SingleRelease,
	SingleEnd,
	MultiBegin,
	MultiPress,
	MultiRelease,
	MultiEnd
};

double GetEmptyRate(Mat gray);
PerFillingPtBackground_info  GetPerFillingPtBackground_info(Mat img2,
	int num,int interval,bool isCrosswise,FillingPointsType type);
PerQuestionBackground_info  GetPerQuestionBackground_info(Mat img2,int num,bool isCrosswise);

class CAnswerCardApp
{
public:
	CAnswerCardApp();

	bool m_hasQuestions;
	///////////////////////////////////存储数据///////////////////////////////////////
	// 组状态
	unsigned short m_group_state;
	// 子状态
	unsigned short m_state;
	// 定位点分布类型
	int anchor_type;
	//定位点组
	cv::Rect anchorPoints[4];
	//水平、垂直标记点区域
	cv::Rect markersRect[2];
	//水平标记点组
	vector<cv::Rect> hmarkers;
	//垂直标记点组
	vector<cv::Rect> vmarkers;
	//题目信息
	vector<ItemPos> questionInfo;
	//标记点边界表
	MarkersBoundaryTable markerBT;
	//自定义填涂点
	vector<FillingPoints_info> cfp_group;
	cv::Rect cfp_tmpRect;
	//裁切区域
	vector<CropArea_info> cropAreas;
	//条形码区域
	vector<Bar_info> barGroup;
	//ID点
	vector<ItemPos> idGroup;
	//
	cv::Rect whiteLineRect;
	cv::Rect blackLineRect;
	//识别参考点
	vector<cv::Rect> referPoint;

	int questionType;

	void clear();
	vector<FillPoint> CountFillPointsBackground();
	vector<Questions> CountQuestionsBackground();

	////////////////////////////////绘制数据/////////////////////////////////////////
	//opencv
	Mat img_raw;
	Mat img_gray;
	Mat img_bw;
	Mat img_show;
	Mat img_bk;
	// 定位点颜色、线宽
	Scalar anchor_point_color;
	unsigned short anchor_point_thickness;
	//标记点区域颜色、线宽
	Scalar markers_point_color;
	unsigned short markers_point_thickness;
	//条形码区域颜色线宽
	Scalar barcode_color;
	unsigned short barcode_thickness;
	Scalar barcodeClicked_color;
	unsigned short barcodeClicked_thickness;
	//答案填涂点颜色线宽
	Scalar answer_color;
	Scalar answer_multi_color;
	unsigned short answer_single_thickness;
	unsigned short answer_multi_thickness;
	Scalar answerClicked_color;
	Scalar answerClicked_multi_color;
	unsigned short answerClicked_single_thickness;
	unsigned short answerClicked_multi_thickness;
	//用户自定义填涂点区域颜色、线宽
	Scalar cfp_color;
	unsigned short cfp_thickness;
	Scalar cfpClicked_color;
	unsigned short cfpClicked_thickness;
	//裁切区域颜色、线宽
	Scalar cropArea_color;
	unsigned short cropArea_thickness;
	Scalar cropAreaClicked_color;
	unsigned short cropAreaClicked_thickness;
	//白检测线颜色、线宽
	Scalar whiteLine_color;
	unsigned short whiteLine_thickness;
	//黑检测线颜色、线宽
	Scalar blackLine_color;
	unsigned short blackLine_thickness;
	//虚拟标记点颜色
	Scalar marker_color;
	Scalar markerClicked_color;
	unsigned short markerClicked_thickness;
	//id点颜色线宽
	Scalar idPoint_color;
	unsigned short idPoint_thickness;
	Scalar idPointClicked_color;
	unsigned short idPointClicked_thickness;
	//读取配置文件，配置各种线框颜色及宽度
	void readConfig();

	///////////////////////////////////输出数据///////////////////////////////////////
public:
	AC_info acinfo;

public:
	// 计算点所在的连通域外接矩形，并绘制
	bool GetArchorPointRect(QPoint pt, int ap_idx, bool is_draw= true);
	// 重新绘制
	int Redraw(void);
	// 所显示图像与数据是否同步
	bool is_synchronous;
	// 计算标记点数量
	vector<cv::Rect> GetMarkersNum(Mat roi);
	//对标记点排序
	void SortMarkers(bool is_hmarkers);
	// 标记点最小面积
	int min_markers_area;
	// 从文件中读取图像
	int LoadImg(const QString &path);
	// 转换成输出结构体
	int TransToOutputStruct();
	// 新加一道题
	void AddQuestion(int id, bool isCrosswise, bool isSingleChoice, ushort interval,
		ushort markerIdx0, ushort markerIdx1, ushort markerIdx2);
	void AddFillPoint(string name, FillingPointsType type, bool isCrosswise, 
		int cspace, int rspace, int idx_l, int idx_r, int idx_t, int idx_b);
	void AddIdPoint(int id, ushort markerIdx0, ushort markerIdx1, ushort markerIdx2);
	//清空坐标信息
	void clearACInfo();
};

extern CAnswerCardApp theApp;

#endif