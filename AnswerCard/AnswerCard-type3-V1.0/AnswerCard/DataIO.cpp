#include "DataIO.h"

DataIO::DataIO(QString fileName, DATA_IO type)
	:m_flag(type),m_PrepareState(true)
{
	m_file.setFileName(fileName);
	
	switch (m_flag)
	{
	case DATA_READ:
		if (!m_file.open(QIODevice::ReadOnly))
		{
			m_flag = DATA_BAD;
			break;
		}
		m_PrepareState = false;
		m_data.setDevice(&m_file);
		m_data.setVersion(QDataStream::Qt_4_8);
		break;
	case DATA_WRITE:
		if (!m_file.open(QIODevice::WriteOnly))
		{
			m_flag = DATA_BAD;
			break;
		}
		m_PrepareState = false;
		m_data.setDevice(&m_file);
		m_data.setVersion(QDataStream::Qt_4_8);
		break;
	default:
		m_flag = DATA_BAD;
		break;
	}
}

DataIO::~DataIO()
{
	if (m_file.isOpen())
	{
		m_file.close();
	}
}


////////////////////////////////////写操作//////////////////////////////////////
int  DataIO::writeToDat(DataInfo3& info)
{
	writeFileHead(TYPE_TWO);
	writeHasQuestion(info.hasQuestion);
	writeIsFront(info.isFront);
	writeImage(info.image);
	writeAnchorRectData(info.anchorRect, info.hasAnchorRect, info.oriPoint);
	writeAnchorData(info.anchorPoints, info.anchorType);
	writeMarkerData(info.markerSize, info.markersInfo, info.markers, info.markerDone);
	writeBarCodeData(info.barGroup);
	writeQuestionData(info.questioninfo,info.questionType);
	writeFillPointData(info.fillingPointGroup);
	writeClipData(info.cropAreaInfo);
	writeWhiteLineData(info.whiteLineRect);
	writeBlackLineData(info.blackeLineRect);
	writeReferPointData(info.referPoint);
	writePagePointData(info.pagePoint);
	return 1;
}

int DataIO::writeFileHead(DATA_TYPE type)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		quint32 magic;
		if (type == TYPE_ONE)
		{
			magic = quint32(TYPE_ONE_MAGIC_NUM);
		}
		else if (type == TYPE_TWO)
		{
			magic = quint32(TYPE_TWO_MAGIC_NUM);
		}
		else
		{
			m_flag = DATA_BAD;
			return TYPE_BAD;
		}

		m_data<<magic<<quint32(VERSION_NUMBER);
		m_PrepareState = false;

		return DATA_WRITE;
	}

	m_flag = DATA_BAD;
	return DATA_BAD;
}

int DataIO::writeHasQuestion(bool hasQuestion)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		m_data<<hasQuestion;
		return DATA_WRITE;
	}

	return DATA_BAD;
}

int DataIO::writeIsFront(bool isFront)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		m_data<<isFront;
		return DATA_WRITE;
	}

	return DATA_BAD;
}

int DataIO::writeImage(const QImage& img)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		m_data<<img;
		return DATA_WRITE;
	}

	return DATA_BAD;
}

int DataIO::writeAnchorRectData(const cv::Rect anchorRect, bool hasAnchorRect, cv::Point point)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		QRect rect;
		rect = cvRect2QRect(anchorRect);


		m_data<<hasAnchorRect<<rect<<point.x<<point.y;

		return DATA_WRITE;
	}

	return DATA_BAD;
}

int DataIO::writeAnchorData(const cv::Rect anchorPoints[4], int type)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		QRect rect[4];

		for (int i = 0; i < 4; ++i)
		{
			rect[i] = cvRect2QRect(anchorPoints[i]);
		}

		m_data<<type<<rect[0]<<rect[1]<<rect[2]<<rect[3];

		return DATA_WRITE;
	}

	return DATA_BAD;
}

int DataIO::writeMarkerData(const cv::Size &size, Marker_info3 &markersInfo, 
	vector<Marker_info3>& markers, bool done)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		QList<QRect> rect[2];

		vector<cv::Rect>::iterator xiter = markersInfo.xMarker.begin();
		for (; xiter != markersInfo.xMarker.end(); ++xiter)
		{
			QRect rt = cvRect2QRect(*xiter);
			rect[0].push_back(rt);
		}

		vector<cv::Rect>::iterator yiter = markersInfo.yMarker.begin();
		for (; yiter != markersInfo.yMarker.end(); ++yiter)
		{
			QRect rt = cvRect2QRect(*yiter);
			rect[1].push_back(rt);
		}

		m_data<<done<<size.width<<size.height<<rect[0]<<rect[1];

		int markerSize = markers.size();
		m_data<<markerSize;

		vector<Marker_info3>::iterator iter = markers.begin();

		for (; iter != markers.end(); ++iter)
		{
			MarkerData dat = markerInfo32MarkerData(*iter);
			m_data<<dat.markerId<<dat.xRect<<dat.yRect;
		}

		return DATA_WRITE;
	}

	return DATA_BAD;
}

int DataIO::writeFillPointData(vector<FillingPoints_info3>& fillingPointGroup)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		int groupSize = fillingPointGroup.size();
		m_data<<groupSize;

		vector<FillingPoints_info3>::iterator iter = fillingPointGroup.begin();
		for (;iter != fillingPointGroup.end(); ++iter)
		{
			FillPointData3 data = fillPointInfo2FillPointData3(*iter);
			m_data<<data.fillPointName<<data.fillPointType<<data.singleChoice<<data.mat
				<<data.itemAmount<<data.fillPointId<<data.isCrossWise<<data.posNum<<data.pos;
		}

		return DATA_WRITE;
	}

	return DATA_BAD;
}

int DataIO::writeBarCodeData(vector<Bar_info>& barGroup)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		int groupSize = barGroup.size();
		m_data<<groupSize;

		vector<Bar_info>::iterator iter = barGroup.begin();
		for (;iter != barGroup.end(); ++iter)
		{
			BarCodeData data = barInfo2BarCodeData(*iter);
			m_data<<data.barCodeType<<data.pos;
		}
		return DATA_WRITE;
	}

	return DATA_BAD;
}

int DataIO::writeQuestionData(vector<QustionItemPos>& questioninfo,int questionType)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		int groupSize = questioninfo.size();
		m_data<<questionType<<groupSize;

		vector<QustionItemPos>::iterator iter = questioninfo.begin();
		for (;iter != questioninfo.end(); ++iter)
		{
			QuestionData data = questionInfo2QuestionData(*iter);
			m_data<<data.questionId<<data.isCrossWise
				<<data.singleChoice<<data.interval
				<<data.markerId1<<data.markerId2
				<<data.markerId3<<data.markerId;
		}
		return DATA_WRITE;
	}

	return DATA_BAD;
}

int DataIO::writeClipData(vector<CropArea_info>& cropAreaInfo)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		int groupSize = cropAreaInfo.size();
		m_data<<groupSize;

		vector<CropArea_info>::iterator iter = cropAreaInfo.begin();
		for (;iter != cropAreaInfo.end(); ++iter)
		{
			ClipData data = cropAreaInfo2ClipData(*iter);
			m_data<<data.clipName<<data.groupNum
				<<data.isSecret<<data.pos;
		}
		return DATA_WRITE;
	}

	return DATA_BAD;
}

int DataIO::writeWhiteLineData(const cv::Rect &whiteLineRect)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		QRect rect = cvRect2QRect(whiteLineRect);
		m_data<<rect;
		return DATA_WRITE;
	}

	return DATA_BAD;
}

int DataIO::writeBlackLineData(const cv::Rect &blackLineRect)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		QRect rect = cvRect2QRect(blackLineRect);
		m_data<<rect;
		return DATA_WRITE;
	}

	return DATA_BAD;
}

int DataIO::writeReferPointData(vector<cv::Rect> &referPoint)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		int referSize = referPoint.size();
		m_data<<referSize;

		vector<cv::Rect>::iterator iter = referPoint.begin();
		for (;iter != referPoint.end(); ++iter)
		{
			QRect rect = cvRect2QRect(*iter);
			m_data<<rect;
		}
		return DATA_WRITE;
	}

	return DATA_BAD;
}

int DataIO::writePagePointData(vector<cv::Rect> &pagePoint)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		int size = pagePoint.size();
		m_data<<size;

		vector<cv::Rect>::iterator iter = pagePoint.begin();
		for (;iter != pagePoint.end(); ++iter)
		{
			QRect rect = cvRect2QRect(*iter);
			m_data<<rect;
		}
		return DATA_WRITE;
	}

	return DATA_BAD;
}

//////////////////////////////////////读操作/////////////////////////////////////////
int DataIO::readFromDat(DataInfo3& info)
{	
	int rst = readFileHead();
	if (rst == TYPE_TWO)
	{
		readHasQuestion(info.hasQuestion);
		readIsFront(info.isFront);
		readImage(info.image);
		readAnchorRectInfo(info.anchorRect, info.hasAnchorRect, info.oriPoint);
		readAnchorInfo(info.anchorPoints, info.anchorType);
		readMarkerInfo(info.markerSize, info.markersInfo, info.markers, info.markerDone);
		readBarCodeInfo(info.barGroup);
		readQuestionInfo(info.questioninfo,info.questionType);
		readFillPointInfo(info.fillingPointGroup);
		readCropAreaInfo(info.cropAreaInfo);
		readWhiteLineData(info.whiteLineRect);
		readBlackLineData(info.blackeLineRect);
		readReferPointInfo(info.referPoint);
		readPagePointInfo(info.pagePoint);
	}
	return rst;
}

int DataIO::readFileHead()
{
	if (m_flag == DATA_READ && m_PrepareState == false)
	{
		quint32 magic;
		quint32 version;
		m_data>>magic>>version;

		if (magic == (quint32)TYPE_ONE_MAGIC_NUM)
		{
			if (version == (quint32)VERSION_NUMBER)
			{
				return TYPE_ONE;
			}
			else
			{
				return DATA_OLD;
			}
		}
		else if ((magic == (quint32)TYPE_TWO_MAGIC_NUM))
		{
			if (version == (quint32)VERSION_NUMBER)
			{
				return TYPE_TWO;
			}
			else
			{
				return DATA_OLD;
			}
		}
		
		m_flag = DATA_BAD;
		return TYPE_BAD;

	}

	m_flag = DATA_BAD;
	return DATA_BAD;
}

int DataIO::readHasQuestion(bool &hasQuestion)
{
	if (m_flag == DATA_READ && m_PrepareState == false)
	{
		bool b;
		m_data>>b;
		hasQuestion = b;

		return DATA_READ;
	}
	return DATA_BAD;
}

int DataIO::readIsFront(bool &isFront)
{
	if (m_flag == DATA_READ && m_PrepareState == false)
	{
		bool b;
		m_data>>b;
		isFront = b;

		return DATA_READ;
	}
	return DATA_BAD;
}

int DataIO::readImage(QImage& img)
{
	if (m_flag == DATA_READ && m_PrepareState == false)
	{
		QImage image;
		m_data>>image;
		img = QImage(image);

		return DATA_READ;
	}
	return DATA_BAD;
}

int DataIO::readAnchorRectInfo(cv::Rect &anchorRect, bool &hasAnchorRect, cv::Point &point)
{
	if (m_flag == DATA_READ && m_PrepareState == false)
	{
		QRect rect;
		bool has;
		int x,y;

		m_data>>has>>rect>>x>>y;

		anchorRect = qRect2CvRect(rect);
		
		hasAnchorRect = has;
		point.x = x;
		point.y = y;
		return DATA_READ;
	}
	return DATA_BAD;
}

int DataIO::readAnchorInfo(cv::Rect anchorPoints[4], int &anchorType)
{
	if (m_flag == DATA_READ && m_PrepareState == false)
	{
		QRect rect[4];
		int type;

		m_data>>type>>rect[0]>>rect[1]>>rect[2]>>rect[3];

		for (int i = 0; i < 4; ++i)
		{
			anchorPoints[i] = qRect2CvRect(rect[i]);
		}

		anchorType = type;
		return DATA_READ;
	}
	return DATA_BAD;
}

int DataIO::readMarkerInfo(cv::Size &size, Marker_info3 &markersInfo, 
	vector<Marker_info3>& markers, bool &done)
{
	if (m_flag == DATA_READ && m_PrepareState == false)
	{
		QList<QRect> rect2[2];
		bool markerDone ;
		int width, height;
		m_data>>markerDone>>width>>height>>rect2[0]>>rect2[1];

		QList<QRect>::iterator iter = rect2[0].begin();
		for (;iter != rect2[0].end(); ++iter)
		{
			markersInfo.xMarker.push_back(qRect2CvRect(*iter));
		}

		QList<QRect>::iterator iter2 = rect2[1].begin();
		for (;iter2 != rect2[1].end(); ++iter2)
		{
			markersInfo.yMarker.push_back(qRect2CvRect(*iter2));
		}

		done = markerDone;
		size = cv::Size(width, height);

		int markerAmount;
		m_data>>markerAmount;
		
		for (int i = 0; i < markerAmount; ++i)
		{
			MarkerData data;
			m_data>>data.markerId>>data.xRect>>data.yRect;

			Marker_info3 info = MarkerData2MarkerInfo3(data);
			markers.push_back(info);
		}

		return DATA_READ;
	}
	return DATA_BAD;
}

int DataIO::readFillPointInfo(vector<FillingPoints_info3>& fillingPointGroup)
{
	if (m_flag == DATA_READ && m_PrepareState == false)
	{
		int groupSize;
		m_data>>groupSize;

		for (int i = 0; i < groupSize; ++i)
		{
			FillPointData3 fpData;
			m_data>>fpData.fillPointName>>fpData.fillPointType>>fpData.singleChoice>>fpData.mat
				>>fpData.itemAmount>>fpData.fillPointId>>fpData.isCrossWise>>fpData.posNum>>fpData.pos;

			FillingPoints_info3 info = fillPointData2FillPointInfo3(fpData);
			fillingPointGroup.push_back(info);
		}

		return DATA_READ;
	}
	return DATA_BAD;
}

int DataIO::readBarCodeInfo(vector<Bar_info>& barGroup)
{
	if (m_flag == DATA_READ && m_PrepareState == false)
	{
		int groupSize;
		m_data>>groupSize;

		for (int i = 0; i < groupSize; ++i)
		{
			BarCodeData data;
			m_data>>data.barCodeType>>data.pos;

			Bar_info info = barCodeData2BarInfo(data);
			barGroup.push_back(info);
		}

		return DATA_READ;
	}
	return DATA_BAD;
}

int DataIO::readQuestionInfo(vector<QustionItemPos>& questioninfo,int& questionType)
{
	if (m_flag == DATA_READ && m_PrepareState == false)
	{
		int groupSize;
		int type;
		m_data>>type>>groupSize;
		questionType = type;

		for (int i = 0; i < groupSize; ++i)
		{
			QuestionData data;
			m_data>>data.questionId>>data.isCrossWise
				>>data.singleChoice>>data.interval
				>>data.markerId1>>data.markerId2
				>>data.markerId3>>data.markerId;

			QustionItemPos info = questionData2ItemPos(data);
			questioninfo.push_back(info);
		}
		return DATA_READ;
	}

	return DATA_BAD;
}

int DataIO::readCropAreaInfo(vector<CropArea_info>& cropAreaInfo)
{
	if (m_flag == DATA_READ && m_PrepareState == false)
	{
		int groupSize;
		m_data>>groupSize;

		for (int i = 0; i < groupSize; ++i)
		{
			ClipData data;
			m_data>>data.clipName>>data.groupNum
				>>data.isSecret>>data.pos;

			CropArea_info info = clipData2CropAreaInfo(data);
			cropAreaInfo.push_back(info);
		}

		return DATA_READ;
	}

	return DATA_BAD;
}

int DataIO::readWhiteLineData(cv::Rect &whiteLineRect)
{
	if (m_flag == DATA_READ && m_PrepareState == false)
	{
		QRect rect;
		m_data>>rect;

		whiteLineRect = cv::Rect(qRect2CvRect(rect));
		return DATA_READ;
	}

	return DATA_BAD;
}

int DataIO::readBlackLineData(cv::Rect &blackLineRect)
{
	if (m_flag == DATA_READ && m_PrepareState == false)
	{
		QRect rect;
		m_data>>rect;

		blackLineRect = cv::Rect(qRect2CvRect(rect));
		return DATA_READ;
	}

	return DATA_BAD;
}

int DataIO::readReferPointInfo(vector<cv::Rect> &referPoint)
{
	if (m_flag == DATA_READ && m_PrepareState == false)
	{
		int groupSize;
		m_data>>groupSize;

		for (int i = 0; i < groupSize; ++i)
		{
			QRect rt;
			m_data>>rt;

			cv::Rect rt2 = cv::Rect(qRect2CvRect(rt));
			referPoint.push_back(rt2);
		}

		return DATA_READ;
	}

	return DATA_BAD;
}

int DataIO::readPagePointInfo(vector<cv::Rect> &pagePoint)
{
	if (m_flag == DATA_READ && m_PrepareState == false)
	{
		int groupSize;
		m_data>>groupSize;

		for (int i = 0; i < groupSize; ++i)
		{
			QRect rt;
			m_data>>rt;

			cv::Rect rt2 = cv::Rect(qRect2CvRect(rt));
			pagePoint.push_back(rt2);
		}

		return DATA_READ;
	}

	return DATA_BAD;
}

/////////////////////////////////////数据转换////////////////////////////////////////
QRect DataIO::cvRect2QRect(const cv::Rect& rect)
{
	return QRect(QPoint(rect.tl().x,rect.tl().y), QPoint(rect.br().x,rect.br().y));
}

MarkerData DataIO::markerInfo32MarkerData(Marker_info3 &info)
{
	MarkerData data;
	data.markerId = info.id;

	vector<Rect>::iterator xiter = info.xMarker.begin();
	for (; xiter != info.xMarker.end(); ++xiter)
	{
		data.xRect.push_back(cvRect2QRect(*xiter));
	}

	vector<Rect>::iterator yiter = info.yMarker.begin();
	for (; yiter != info.yMarker.end(); ++yiter)
	{
		data.yRect.push_back(cvRect2QRect(*yiter));
	}

	return data;
}

FillPointData3 DataIO::fillPointInfo2FillPointData3(FillingPoints_info3& info)
{
	FillPointData3 data;
	data.fillPointName = QString::fromLocal8Bit(info.name.c_str());
	data.fillPointType = (int)(info.type);
	data.isCrossWise = info.isCrosswise;
	data.posNum = info.fillingPoints.at(0).pos.size();
	
	for (int i = 0; i < info.bgInfo.rows * info.bgInfo.cols; ++i)
	{
		data.mat.push_back(info.bgInfo.at<int>(i));
	}

	data.itemAmount = info.fillingPoints.size();

	vector<FillingpointItemPos>::iterator iter = info.fillingPoints.begin();

	for (;iter != info.fillingPoints.end(); ++iter)
	{
		data.singleChoice.push_back(iter->isSingleChoice);
		data.fillPointId.push_back(iter->id);

		vector<cv::Rect>::iterator rtIter = iter->pos.begin(); 
		for (; rtIter != iter->pos.end(); ++ rtIter)
		{
			data.pos.push_back(cvRect2QRect(*rtIter));
		}
	}

	return data;
}

BarCodeData DataIO::barInfo2BarCodeData(const Bar_info& info)
{
	BarCodeData data;
	data.barCodeType = (int)(info.barType);
	data.pos = cvRect2QRect(info.pos);
	return data;
}

QuestionData DataIO::questionInfo2QuestionData(const QustionItemPos& info)
{
	QuestionData data;
	data.questionId = info.id;
	data.markerId = info.mark_id;
	data.isCrossWise = info.isCrosswise;
	data.singleChoice = info.isSingleChoice;
	data.interval = info.interval;
	data.markerId1 = info.markerIdx[0];
	data.markerId2 = info.markerIdx[1];
	data.markerId3 = info.markerIdx[2];

	return data;
}

ClipData DataIO::cropAreaInfo2ClipData(const CropArea_info& info)
{
	ClipData data;
	data.clipName = QString::fromLocal8Bit(info.name.c_str());
	data.groupNum = info.groupNum;
	data.isSecret = info.isSecret;
	data.pos = cvRect2QRect(info.pos);

	return data;
}

cv::Rect DataIO::qRect2CvRect(const QRect& rect)
{
	return cv::Rect(cv::Point(rect.topLeft().x(), rect.topLeft().y()),
		cv::Point(rect.bottomRight().x(), rect.bottomRight().y()));
}

Marker_info3 DataIO::MarkerData2MarkerInfo3(MarkerData &data)
{
	Marker_info3 info;
	info.id = data.markerId;

	QList<QRect>::Iterator xiter = data.xRect.begin();
	for (;xiter != data.xRect.end(); ++xiter)
	{
		info.xMarker.push_back(qRect2CvRect(*xiter));
	}

	QList<QRect>::Iterator yiter = data.yRect.begin();
	for (;yiter != data.yRect.end(); ++yiter)
	{
		info.yMarker.push_back(qRect2CvRect(*yiter));
	}

	return info;
}

FillingPoints_info3 DataIO::fillPointData2FillPointInfo3(const FillPointData3& data)
{
	FillingPoints_info3 info;
	info.name = data.fillPointName.toStdString();
	info.type = (FillingPointsType)(data.fillPointType);
	info.isCrosswise = data.isCrossWise;

//	QList<int>::iterator iter = data.mat.begin();
	cv::Size matSize(data.posNum, data.mat.size() / data.posNum);
	info.bgInfo = cv::Mat(matSize, CV_32S);

	for (int i = 0; i < data.mat.size(); ++i)
	{
		info.bgInfo.at<int>(i) = data.mat.at(i);
	}

	int size = data.itemAmount;
	for (int i = 0; i < size; ++i)
	{
		FillingpointItemPos pos;
		pos.id = data.fillPointId[i];
		pos.isSingleChoice = data.singleChoice[i];

		for (int j = 0; j < data.posNum; ++j)
		{
			pos.pos.push_back(qRect2CvRect(data.pos[i * data.posNum + j]));
		}

		info.fillingPoints.push_back(pos);
	}

	return info;
}

Bar_info DataIO::barCodeData2BarInfo(const BarCodeData& data)
{
	Bar_info info;
	info.barType = (BarType)(data.barCodeType);
	info.pos = qRect2CvRect(data.pos);

	return info;
}

QustionItemPos DataIO::questionData2ItemPos(const QuestionData& data)
{
	QustionItemPos info;
	info.id = data.questionId;
	info.interval = data.interval;
	info.isCrosswise = data.isCrossWise;
	info.isSingleChoice = data.singleChoice;
	info.mark_id = data.markerId;
	info.markerIdx[0] = data.markerId1;
	info.markerIdx[1] = data.markerId2;
	info.markerIdx[2] = data.markerId3;

	return info;
}

CropArea_info DataIO::clipData2CropAreaInfo(const ClipData& data)
{
	CropArea_info info;
	info.name = data.clipName.toStdString();
	info.isSecret = data.isSecret;
	info.groupNum = data.groupNum;
	info.pos = qRect2CvRect(data.pos);

	return info;
}