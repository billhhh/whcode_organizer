/************************************************************************/
/*异常代码定义
定位点检测异常					1-15
倾斜校正异常					16-31
X方向标记点检测异常				32-47
Y方向标记点检测异常				48-63
条形码检测异常					64-79
预定义填涂点组异常				80-111
褶皱异常						112
裁切区域异常					255-511
答案检测异常					512-INF
*/
/************************************************************************/
#include <cv.h>
#ifndef _COMMONSTRUCT_H
#define _COMMONSTRUCT_H
#define REFPOINT_ERROR -4               //识别参考点异常
#define ACTYPE_NOT_MATCH -3                //答题卡类型不匹配
#define ACINFO_NOT_MATCH -2                //结构体不匹配
#define IDPOINT_NOT_MATCH 1                //id点不匹配
#define	ANCHOR_POINT_ERR_BASE 1          //定位点识别错误
#define PAGEMAKER_ERR 8					 //页码标识块不匹配
#define	TILTCORRECTION_ERR_BASE 16       //倾斜矫正错误
#define	XMARKERS_ERR_BASE 32             //X方向标记点错误
#define	YMARKERS_ERR_BASE 48            //Y方向标记点错误
#define	BAR_ERR_BASE 64                 //条形码识别错误
#define FILLING_POINT_ERR_BASE 96       //预定义填涂点识别错误   
#define	FOLD_ERR 112
#define	CROPAREA_ERR_BASE 255;          
#define ANSWER_ERR_BASE 512
using namespace cv;
//用户可调参数集
typedef struct AcArgs{
	double xRangeScale;    //标记点宽度尺度范围
	double yRangeScale;      //标记点高度尺度范围
	double sensibilityThresh;   //填涂一致性灵敏度
	double areaThreshold;       //最小填涂阈值
	int seSize;                //是否调小形态学模板大小 为0不做调整  大于0则做调整
} AcArgs;

enum FillingPointsType :ushort{
	SeatNumZeroFirst,                //座位号 从0开始
	ExamHallNumZeroFirst,			//考场号 从0开始
	ExamRoomNumZeroFirst,			//考室号 从0开始
	FirstCandidateNumZeroFirst,		//首考生号 从0开始
	TickerNumZeroFirst,				//准考证号 从0开始
	CourseNumZeroFirst,				//科目号 从0开始
	SeatNumOneFirst,                //座位号 从1开始
	ExamHallNumOneFirst,			//考场号 从1开始
	ExamRoomNumOneFirst,			//考室号 从1开始
	FirstCandidateNumOneFirst,		//首考生号 从1开始
	TickerNumOneFirst,				//准考证号 从1开始
	CourseNumOneFirst,				//科目号 从1开始
	Absent,							//缺考
	PaperType,						//试卷类型
	OptionalQuestion,				//选做题
	Discipline,						//违纪
	Question,						//选择题
	PageNum                         //页码
};
enum BarType :ushort{
	PaperTypeBar,				//试卷类型
	TickerNumBar,				//准考证号
	ExamRoomNumBar,			//考室号
	AbsentBar,					//缺考
};
//识别结果结构体定义

//条形码识别结果结构体
typedef struct Bar_RST{
	BarType barType;
	char * bar;
	bool errflag;  //出错标记
}Bar_RST;


//2.答案信息结构体定义
//2.1小题答案信息结构体
typedef struct  Perquestion_RST{
	int questionId;      //题号
	//	ushort answer;   //答案
	int answer;
	int suspectFlag;      //可疑标记，为0表示识别正常，否则返回可疑状态信息。
	/*	vector<cv::Point> answerPos;  */
	cv::Point *answerPos;   //填涂中心位置
	int answerPosCount;     //答案数量

}Perquestion_RST;
//2.答案信息结构体定义
typedef struct  Answer_RST{
	int suspectFlag;      //可疑标记，为0表示识别正常，否则返回可疑状态信息。
	Perquestion_RST * answer;   //答案识别结果
	int answerCount;
}Answer_RST;
//3.裁切区域
typedef struct CropArea_RST{
	char * name;		//裁切区域名字
	int groupNum;      //合并组号
	bool isSecret;      //保密属性
	//	Mat img	;		//裁切区域位置
	cv::Rect cropRect;                   //此处光用一个rect返回是不正确的
}CropArea_RST;
//4.预定义填涂区域
typedef struct  PerFP_RST{
	int result;   //答案
	int suspectFlag;      //可疑标记，为0表示识别正常，否则返回可疑状态信息。
	cv::Point *resultPos;  //填涂点中心位置
	int resultPosCount;    //填涂点各数

}PerFP_RST;

typedef struct FillingPoints_RST{
	char* name;				//名字
	FillingPointsType fPType;     //预定义填涂点类型
	PerFP_RST *fillingResult;		//答案
	int fillingResultCount;     //答案个数
	int suspectFlag;			//可疑标记，为0表示识别正常，否则返回可疑状态信息。
}FillingPoints_RST;

//识别结果结构体，包括考生信息识别结果和答案识别结果以及出错信息
typedef struct  AC_RST{
	int tkId;         //套卡编号(类型一、类型二)
	int pageId;        //试卷编号(类型一、类型二)
	int errFlag;           //出错标记，为0表示识别正常，否则返回出错状态信息。
	double angle;			//倾斜角度
	Rect blackLine;             //黑检测线位置
	Rect whiteLine;             //白检测线位置
	cv::Size imgSize;       //图像尺寸
	uchar* img;             //矫正后图像数据
	Answer_RST answerResult;   //答案信息识别结果
	Bar_RST * barResult;  //条码识别结果
	int barResultCount;
	CropArea_RST * cropAreaResult;	//裁切区域结果
	int cropAreaResultCount;
	FillingPoints_RST * cfpResult;	//预定义填涂点识别结果
	int cfpResultCount;
}AC_RST;


/************************************************************************/
/* 转换后的卡格式结构体定义                                             */
/************************************************************************/
//小题位置和准考证号位置结构体
typedef struct Cum_QustionItemPos{
	int id;    //序号
	ushort mark_id;  //所在标记点组的组号
	bool isCrosswise; //是否是横向的
	bool isSingleChoice;	//是否是单选
	ushort interval ;      //横向/纵向间隔，若选项排布为横向则为横向间隔
	ushort markerIdx[3];	//题目对应定位点索引，若为横向则[0]存储y方向的索引号，[1] [2]存x方向索引号；若为纵向则[0]存储x方向的索引号，[1] [2]存y方向索引号
}Cum_QustionItemPos,Cum_ItemPos;

//1.填涂点信息结构体定义
typedef struct Cum_FillingpointItemPos{
	int id;    //序号
	bool isSingleChoice;	//是否是单选
	Rect * pos;        //相对左上角定位点位置信息
	int posCount;
}Cum_FillingpointItemPos;
//1.2条形码信息结构体定义
typedef struct Cum_Bar_info{
	BarType barType;      //条码类型
	cv::Rect pos;  //所在位置，(x,y)表示左上角相对定位点的相对坐标。with和high表示区域的大小
}Cum_Bar_info;
//填涂区域
typedef struct Cum_FillingPoints_info{
	char * name;				//名字
	FillingPointsType fptype;    //预定义填涂点类型
	Cum_ItemPos * fillingPoints;		//各填涂点的位置信息
	int fillingPointsCount;
}Cum_FillingPoints_info;

typedef struct Cum_FillingPoints_info3{
	char * name;				//名字
	FillingPointsType fptype;    //预定义填涂点类型
	bool isCrosswise;			//是否是横向的
	Cum_FillingpointItemPos *fillingPoints;		//各填涂点的位置信息
	int fillingPointsCount;
}Cum_FillingPoints_info3;

//3.定位点信息结构体定义
typedef struct Cum_AnchorPoint_info{
	int num;  //定位点数量
	short anchorType; //定位点分布类型
	Rect *anchorPt;  //各个定位点的外接矩形，坐标原点为图像左上角。
	int anchorPtCount;
}Cum_AnchorPoint_info;

//4.标记点信息结构体定义
typedef struct Cum_Marker_info{
	int xNum;    //横向标记点数量
	int yNum;    //纵向标记点数量
	cv::Size xSize;   //横向标记点尺寸
	cv::Size ySize;  //纵向标记点尺寸
	cv::Rect xMarker;  //横向标记点组所在区域
	cv::Rect yMarker;   //纵向标记点组所在区域
}Cum_Marker_info;
typedef struct Cum_Marker_info3{
	ushort id;             //自定义标记点组组号
	Rect * xMarker;  //横向标记点组所在区域 相对定位点的位置信息
	Rect * yMarker;   //纵向标记点组所在区域
	int xMarkerCount;
	int yMarkerCount;
}Cum_Marker_info3;
//5.裁切区域信息
typedef struct Cum_CropArea_info{
	char * name;		//裁切区域名字
	cv::Rect pos;		//裁切区域位置
	int groupNum;      //合并组号
	bool isSecret;      //保密属性
}Cum_CropArea_info;
//同步头的位置信息
typedef struct Cum_PerMarker_info{
	int id;    //同步头的索引号
	Rect pos;  //同步头位置
}Cum_PerMarker_info;

//题卡信息各结构体定义,分四个部分：1.考生信息结构体；2.答案信息结构体；3.定位点信息；4.横纵标记点信息
typedef struct Cum_AC_info3{
	ushort ac_type;   //答题卡类型  1表示类型一，2表示类型二，3表示类型三有标记点，4表示类型三无标记点
	char * ac_id;   //试卷编号
	bool isFront;       //是否为正面
	cv::Size imgSize;
	bool isAnchorPointExist;           //是否存在定位点
	Cum_AnchorPoint_info anchorPointInfo;  //定位点信息
	bool isAnchorRectExist;            //是否存在定位矩形
	cv::Rect anchorRect;                   //定位矩形所在区域
	Rect *pageMarker;			   //页码标识块所在区域
	int pageMarkerCount;
	Cum_Marker_info3  * markerInfo;          //虚拟同步头信息
	int markInfoCunt;
	Cum_Bar_info *barGroup;     //条形码组
	int barGroupCount;
	Cum_FillingPoints_info3 * fillingPointGroup;	//预定义填涂点组
	int fillingPointGroupCount;
	Cum_QustionItemPos * questionInfo;   //题目信息
	int questionInfoCount;
	Cum_CropArea_info * cropAreaInfo;		//裁切区域信息
	int cropAreaInfoCount;
	Rect blackLine;             //黑检测线位置
	Rect whiteLine;             //白检测线位置
	Rect * refPoint;  //各识别参考点的位置，坐标原点为图像左上角。
	int refPointCount;
}Cum_AC_info3;

typedef struct Cum_AC_info{
	ushort ac_type;   //答题卡类型  1表示类型一，2表示类型二，3表示类型三有定位点，4表示类型三无定位点
	bool isFront;       //是否为正面
	bool isAnchorPointExist;           //是否存在定位点
	cv::Size imgSize;
	Cum_AnchorPoint_info anchorPointInfo;  //定位点信息
	Cum_Marker_info markerInfo;            //标记点信息
	Cum_ItemPos * idPoint;           //区分试卷的ID点的位置信息
	int idPointCount;
	Cum_Bar_info * barGroup;         //条形码组
	int barGroupCount;
	Cum_FillingPoints_info * fillingPointGroup;	//预定义填涂点组
	int fillingPointGroupCount;
	Cum_QustionItemPos * questionInfo;   //题目信息
	int questionInfoCount;
	Cum_CropArea_info * cropAreaInfo;		//裁切区域信息，当定位点不存在时以左上角为原点
	int cropAreaInfoCount;
	Rect blackLine;             //黑检测线位置
	Rect whiteLine;             //白检测线位置
	Rect * refPoint;  //各识别参考点的位置，坐标原点为图像左上角。
	int refPointCount;   //识别参考点数量
	int xMarkerCount;   //横向同步头数量
	int yMarkerCount;   //纵向同步头数量
	Cum_PerMarker_info *xMarker;  //横向同步头位置信息
	Cum_PerMarker_info *yMarker;  //纵向同步头位置信息
}Cum_AC_info;
//单张答题卡信息结构体
typedef struct Cum_PerAC_info{
	int tkId;         //套卡编号
	int pageId;        //试卷编号
	Cum_AC_info * acInfo;  //如有正反面，则第一个为正面信息，第二个为反面信息
	int acInfoCount;
}Cum_PerAC_info;
//类型三单张答题卡信息结构体
typedef struct Cum_PerAC_info3{
	int pageId;        //试卷页号
	Cum_AC_info3 * acinfo;
	int acInfoCount;
}Cum_PerAC_info3;

//套卡信息结构体
typedef struct Cum_TK_info{
	Cum_PerAC_info * tkInfo;
	int tkInfoCount;

}Cum_TK_info;

typedef struct Cum_TK_info3{
	Cum_PerAC_info3 * tkInfo;
	int tkInfoCount;
}Cum_TK_info3;

#endif