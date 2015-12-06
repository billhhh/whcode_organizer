#include <vector>
#include "CommonStruct.h"
using namespace cv;
using namespace std;
#ifndef _SRUCTDEFINE_H
#define _SRUCTDEFINE_H

//题卡信息各结构体定义,分四个部分：1.预定义填涂点信息结构体；2.答案信息结构体；3.定位点信息；4.横纵标记点信息；5.条形码信息
//小题位置和准考证号位置结构体
typedef struct QustionItemPos{
	int id;    //序号
	ushort mark_id;  //所在标记点组的组号
	bool isCrosswise; //是否是横向的
	bool isSingleChoice;	//是否是单选
	ushort interval ;      //横向/纵向间隔，若选项排布为横向则为横向间隔
	ushort markerIdx[3];	//题目对应定位点索引，若为横向则[0]存储y方向的索引号，[1] [2]存x方向索引号；若为纵向则[0]存储x方向的索引号，[1] [2]存y方向索引号


}QustionItemPos,ItemPos;

//1.填涂点信息结构体定义


typedef struct FillingpointItemPos{
	int id;    //序号
	bool isSingleChoice;	//是否是单选
	vector<Rect> pos;        //相对左上角定位点位置信息
}FillingpointItemPos;
//1.2条形码信息结构体定义
typedef struct Bar_info{
	BarType barType;      //条码类型
	cv::Rect pos;  //所在位置，(x,y)表示左上角相对定位点的相对坐标。with和high表示区域的大小
}Bar_info;
//填涂区域
typedef struct FillingPoints_info{
	string name;				//名字
	FillingPointsType type;    //预定义填涂点类型
	vector<ItemPos> fillingPoints;		//各填涂点的位置信息
}FillingPoints_info;

typedef struct FillingPoints_info3{
	string name;				//名字
	FillingPointsType type;    //预定义填涂点类型
	bool isCrosswise;			//是否是横向的
	Mat bgInfo;				//背景信息
	vector<FillingpointItemPos> fillingPoints;		//各填涂点的位置信息
}FillingPoints_info3;

//3.定位点信息结构体定义
typedef struct AnchorPoint_info{
	int num;  //定位点数量
	short anchorType; //定位点分布类型
	vector<cv::Rect> anchorPt;  //各个定位点的外接矩形，坐标原点为图像左上角。
}AnchorPoint_info;

//4.标记点信息结构体定义
typedef struct Marker_info{
	int xNum;    //横向标记点数量
	int yNum;    //纵向标记点数量
	cv::Size xSize;   //横向标记点尺寸
	cv::Size ySize;  //纵向标记点尺寸
	cv::Rect xMarker;  //横向标记点组所在区域
	cv::Rect yMarker;   //纵向标记点组所在区域
}Marker_info;
typedef struct Marker_info3{
	ushort id;             //自定义标记点组组号
	vector<Rect> xMarker;  //横向标记点组所在区域 相对定位点的位置信息
	vector<Rect> yMarker;   //纵向标记点组所在区域
}Marker_info3;
//5.裁切区域信息
typedef struct CropArea_info{
	string name;		//裁切区域名字
	cv::Rect pos;		//裁切区域位置
	int groupNum;      //合并组号
	bool isSecret;      //保密属性
}CropArea_info;

//每种类型预定义填涂点背景信息
typedef struct PerFillingPtBackground_info{
	FillingPointsType type;    //填涂点类型
	Mat bkInfo;		//填涂点背景
}PerFillingPtBackground_info;
//每种类型答案填涂点背景信息
typedef struct PerQuestionBackground_info{
	short type;    //填涂点数量
	Mat bkInfo;
}PerQuestionBackground_info;
typedef struct PerMarker_info{
	ushort id;        //同步头的索引号
	Rect pos;         //同步头位置
}PerMarker_info;
//类型三页码标识块

//题卡信息各结构体定义,分四个部分：1.考生信息结构体；2.答案信息结构体；3.定位点信息；4.横纵标记点信息
typedef struct AC_info3{
	ushort ac_type;   //答题卡类型  1表示类型一，2表示类型二，3表示类型三有标记点，4表示类型三无标记点
	string ac_id;   //试卷编号
	bool isFront;       //是否为正面
	int dpi;    //分辨率
	cv::Size imgSize;    //源图像Size
	vector<cv::Rect> pageMarker;  //页码标识块
	bool isAnchorPointExist;           //是否存在定位点
	AnchorPoint_info anchorPointInfo;  //定位点信息
	bool isAnchorRectExist;            //是否存在定位矩形
	Rect anchorRect;                   //定位矩形所在区域
	vector<Marker_info3> markerInfo;          //标记点信息
	vector<Bar_info> barGroup;     //条形码组
	vector<FillingPoints_info3> fillingPointGroup;	//预定义填涂点组
	vector<QustionItemPos> questioninfo;   //题目信息
	int questionType;                      //为0表示选择题中间没有ABCD，为1表示中间有ABCD
	vector<PerQuestionBackground_info> questionBackgroundInfo;	//填涂点背景信息
	vector<CropArea_info> cropAreaInfo;		//裁切区域信息
	Rect blackLine;             //黑检测线位置
	Rect whiteLine;             //白检测线位置
	vector<cv::Rect> refPoint;  //各识别参考点的位置，坐标原点为图像左上角。
	
}AC_info3;

typedef struct AC_info{
	ushort ac_type;   //答题卡类型  1表示类型一，2表示类型二，3表示类型三有定位点，4表示类型三无定位点
	int dpi;    //分辨率
	cv::Size imgSize;    //源图像Size
	bool isFront;       //是否为正面
	bool isAnchorPointExist;           //是否存在定位点
	AnchorPoint_info anchorPointInfo;  //定位点信息
	Marker_info markerInfo;            //标记点信息
	vector<ItemPos> idPoint;           //区分试卷的ID点的位置信息
	vector<Bar_info> barGroup;         //条形码组
	vector<FillingPoints_info> fillingPointGroup;	//预定义填涂点组
	vector<PerFillingPtBackground_info> fillingPointBackgroundInfo;	//填涂点背景信息
	vector<QustionItemPos> questioninfo;   //题目信息
	int questionType;                      //为0表示选择题中间没有ABCD，为1表示中间有ABCD
	vector<PerQuestionBackground_info> questionBackgroundInfo;	//填涂点背景信息
	vector<CropArea_info> cropAreaInfo;		//裁切区域信息，当定位点不存在时以左上角为原点
	Rect blackLine;             //黑检测线位置
	Rect whiteLine;             //白检测线位置
	vector<cv::Rect> refPoint;  //各识别参考点的位置，坐标原点为图像左上角。
	vector<PerMarker_info> xMarker; //每一横向同步头的位置信息
	vector<PerMarker_info> yMarker; //每一纵向同步头的位置信息
}AC_info;
//单张答题卡信息结构体
typedef struct PerAC_info{
	int tkId;         //套卡编号
	int pageId;        //试卷编号
	vector<AC_info> acinfo;  //如有正反面，则第一个为正面信息，第二个为反面信息
}PerAC_info;
//类型三单张答题卡信息结构体
typedef struct PerAC_info3{
	int pageId;        //试卷页号
	vector<AC_info3> acinfo;  //如有正反面，则第一个为正面信息，第二个为反面信息
}PerAC_info3;
//套卡信息结构体
typedef struct TK_info{
	vector<PerAC_info> tkinfo;

}TK_info;

typedef struct TK_info3{
	vector<PerAC_info3> tkinfo;
}TK_info3;


//识别结果结构体定义

//条形码识别结果结构体
typedef struct BarResult{
	BarType barType;
	string bar;
	bool errflag;  //出错标记
}BarResult;


//2.答案信息结构体定义
//2.1小题答案信息结构体
typedef struct  PerquestionResult{
	int questionId;      //题号
	int answer;   //答案
	int suspectFlag;      //可疑标记，为0表示识别正常，否则返回可疑状态信息。
	vector<cv::Point> answerPos;  //填涂中心位置
}PerquestionResult;
//2.答案信息结构体定义
typedef struct  AnswerResult{
	int suspectFlag;      //可疑标记，为0表示识别正常，否则返回可疑状态信息。
	vector<PerquestionResult>  answer;   //答案识别结果
}AnswerResult;
//3.裁切区域
typedef struct CropAreaResult{
	string name;		//裁切区域名字
	int groupNum;      //合并组号
	bool isSecret;      //保密属性
//	Mat img	;		//裁切区域位置
	cv::Rect rect;  //裁切区域位置
}CropAreaResult;
//4.预定义填涂区域
typedef struct  PerFPResult{
	int result;   //答案
	int suspectFlag;      //可疑标记，为0表示识别正常，否则返回可疑状态信息。
	vector<cv::Point> resultPos;  //填涂中心位置
}PerFPResult;

typedef struct FillingPointsResult{
	string name;				//名字
	FillingPointsType type;     //预定义填涂点类型
	vector<PerFPResult> fillingResult;		//答案
	int suspectFlag;			//可疑标记，为0表示识别正常，否则返回可疑状态信息。
}FillingPointsResult;

//识别结果结构体，包括考生信息识别结果和答案识别结果以及出错信息
typedef struct  Result{
	int tkId;         //套卡编号(类型一、类型二)
	int pageId;        //试卷页码
	int errFlag;           //出错标记，为0表示识别正常，否则返回出错状态信息。
	double angle;			//倾斜角度
	Rect blackLine;             //黑检测线位置
	Rect whiteLine;             //白检测线位置
	Mat img;        //试卷矫正后图像
	AnswerResult answerResult;   //答案信息识别结果
	vector<BarResult> barResult;  //条码识别结果
	vector<CropAreaResult> cropAreaResult;	//裁切区域结果
	vector<FillingPointsResult> cfpResult;	//预定义填涂点识别结果
}Result;


#endif