#pragma once
#include "..\XmlIO\ACStructs.h"
#include "qimage.h"
#include "qrect.h"
#include "qlist.h"
#include "qfile.h"
#include "qdatastream.h"

#define TYPE_ONE_MAGIC_NUM 0x0000AC01
#define TYPE_TWO_MAGIC_NUM 0x0000AC02
#define VERSION_NUMBER 106
//数据读取存储方式
enum DATA_IO
{
	DATA_OLD = -1,
	DATA_BAD,
	DATA_READ,
	DATA_WRITE
};

//数据类型
enum DATA_TYPE
{
	TYPE_BAD,
	TYPE_ONE,
	TYPE_TWO
};

struct AnchorData
{
	int anchorType;
	QRect anchorPoint[4];
};

struct MarkerData
{
	bool markerDone;
	QList<QRect> xRect;
	QList<QRect> yRect;
};

//类型12的填涂点二进制保存结构
struct FillPointData
{
	QString fillPointName;
	int fillPointType;

	int itemAmount;
	QList<int>  fillPointId;
	QList<bool> isCrossWise;
	QList<bool> singleChoice;
	QList<int>  interval;
	QList<int>  markerId1;
	QList<int>  markerId2;
	QList<int>  markerId3;
};

//类型3的填涂点二进制保存结构
struct FillPointData3
{
	QString fillPointName;
	int fillPointType;
	bool isCrossWise;
	QList<int> mat;

	int itemAmount;
	QList<int>  fillPointId;
	QList<bool> singleChoice;
	int posNum;
	QList<QRect> pos;
};

struct BarCodeData
{
	int barCodeType;
	QRect pos;
};

struct QuestionData
{
	int questionId;
	bool isCrossWise;
	bool singleChoice;
	int interval;
	int markerId1;
	int markerId2;
	int markerId3;
};

struct ClipData
{
	QString clipName;
	QRect pos;
	int groupNum;
	bool isSecret;
};

//类型12的二进制保存结构
struct DataInfo
{
	QImage image;
	cv::Rect anchorPoints[4];
	int anchorType;
//	bool isFront;
	cv::Rect markersRect[2];
	bool markerDone;
	vector<FillingPoints_info> fillingPointGroup;
	vector<Bar_info> barGroup;
	vector<ItemPos> questioninfo;
	vector<ItemPos> idPointInfo;
	vector<CropArea_info> cropAreaInfo;
	cv::Rect whiteLineRect;
	cv::Rect blackeLineRect;
	vector<cv::Rect> referPoint;
	int questionType;
};

//类型3的二进制保存结构
struct DataInfo3
{
	bool hasAnchorRect;
	cv::Rect anchorRect;
	cv::Point oriPoint;

	bool hasQuestion;
	bool isFront;
	QImage image;
	cv::Rect anchorPoints[4];
	int anchorType;
	cv::Size markerSize;
	Marker_info3 markersInfo;
	vector<Marker_info3> markers;
	bool markerDone;
	vector<FillingPoints_info3> fillingPointGroup;
	vector<Bar_info> barGroup;
	vector<QustionItemPos> questioninfo;
	vector<CropArea_info> cropAreaInfo;
	cv::Rect whiteLineRect;
	cv::Rect blackeLineRect;
	vector<cv::Rect> referPoint;
	vector<cv::Rect> pagePoint;
	int questionType;
};

class DataIO
{
public:
	DataIO(QString fileName, DATA_IO type = DATA_READ);
	~DataIO();

	int writeToDat(DataInfo& info);
	int writeFileHead(DATA_TYPE type);
	int writeImage(const QImage& img);
	int writeAnchorData(const cv::Rect anchorPoints[4], int type);
	int writeMarkerData(const cv::Rect markersRect[2], bool done);
	int writeFillPointData(vector<FillingPoints_info>& fillingPointGroup);
	int writeBarCodeData(vector<Bar_info>& barGroup);
	int writeQuestionData(vector<ItemPos>& questioninfo,int questionType);
	int writeIdPointData(vector<ItemPos>& idPointInfo);
	int writeClipData(vector<CropArea_info>& cropAreaInfo);
	int writeWhiteLineData(const cv::Rect &whiteLineRect);
	int writeBlackLineData(const cv::Rect &blackLineRect);
	int writeReferPointData(vector<cv::Rect> &referPoint);
	
	int readFromDat(DataInfo& info);
	int readFileHead();
	int readImage(QImage& img);
	int readAnchorInfo(cv::Rect anchorPoints[4], int &type);
	int readMarkerInfo(cv::Rect markersRect[2], bool &done);
	int readFillPointInfo(vector<FillingPoints_info>& fillingPointGroup);
	int readBarCodeInfo(vector<Bar_info>& barGroup);
	int readQuestionInfo(vector<ItemPos>& questioninfo, int& questionType);
	int readIdPointInfo(vector<ItemPos>& idPointInfo);
	int readCropAreaInfo(vector<CropArea_info>& cropAreaInfo);
	int readWhiteLineData(cv::Rect &whiteLineRect);
	int readBlackLineData(cv::Rect &blackLineRect);
	int readReferPointInfo(vector<cv::Rect> &referPoint);

	DATA_IO getDataFlag() const {return m_flag;}
	void closeFile()
	{
		if (m_file.isOpen()) 
		{
			m_file.close();
			m_PrepareState = true;
		}
	}

private:
	QRect cvRect2QRect(const cv::Rect& rect);
	FillPointData fillPointInfo2FillPointData(FillingPoints_info& info);
	BarCodeData barInfo2BarCodeData(const Bar_info& info);
	QuestionData questionInfo2QuestionData(const ItemPos& info);
	ClipData cropAreaInfo2ClipData(const CropArea_info& info);

	cv::Rect qRect2CvRect(const QRect& rect);
	FillingPoints_info fillPointData2FillPointInfo(const FillPointData& data);
	Bar_info barCodeData2BarInfo(const BarCodeData& data);
	ItemPos questionData2ItemPos(const QuestionData& data);
	CropArea_info clipData2CropAreaInfo(const ClipData& data);

private:
	QFile m_file;
	QDataStream m_data;
	DATA_IO m_flag;
	bool m_PrepareState;//是否处于准备阶段
};
