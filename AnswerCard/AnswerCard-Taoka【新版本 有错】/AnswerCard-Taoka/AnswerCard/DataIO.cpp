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
int  DataIO::writeToDat(DataInfo& info)
{
	writeFileHead(TYPE_ONE);
	writeImage(info.image);
	writeAnchorData(info.anchorPoints, info.anchorType);
	writeMarkerData(info.markersRect, info.markerDone);
	writeBarCodeData(info.barGroup);
	writeQuestionData(info.questioninfo,info.questionType);
	writeFillPointData(info.fillingPointGroup);
	writeClipData(info.cropAreaInfo);
	writeWhiteLineData(info.whiteLineRect);
	writeBlackLineData(info.blackeLineRect);
	writeIdPointData(info.idPointInfo);
	writeReferPointData(info.referPoint);
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

int DataIO::writeImage(const QImage& img)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		m_data<<img;
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

int DataIO::writeMarkerData(const cv::Rect markersRect[2], bool done)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		QRect rect2[2];

		for (int i = 0; i < 2; ++i)
		{
			rect2[i] = cvRect2QRect(markersRect[i]);
		}

		m_data<<done<<rect2[0]<<rect2[1];

		return DATA_WRITE;
	}

	return DATA_BAD;
}

int DataIO::writeFillPointData(vector<FillingPoints_info>& fillingPointGroup)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		int groupSize = fillingPointGroup.size();
		m_data<<groupSize;

		vector<FillingPoints_info>::iterator iter = fillingPointGroup.begin();
		for (;iter != fillingPointGroup.end(); ++iter)
		{
			FillPointData data = fillPointInfo2FillPointData(*iter);
			m_data<<data.fillPointName<<data.fillPointType<<data.itemAmount
				<<data.fillPointId<<data.isCrossWise<<data.singleChoice
				<<data.interval<<data.markerId1
				<<data.markerId2<<data.markerId3;
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

int DataIO::writeQuestionData(vector<ItemPos>& questioninfo,int questionType)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		int groupSize = questioninfo.size();
		m_data<<questionType<<groupSize;

		vector<ItemPos>::iterator iter = questioninfo.begin();
		for (;iter != questioninfo.end(); ++iter)
		{
			QuestionData data = questionInfo2QuestionData(*iter);
			m_data<<data.questionId<<data.isCrossWise
				<<data.singleChoice<<data.interval
				<<data.markerId1<<data.markerId2
				<<data.markerId3;
		}
		return DATA_WRITE;
	}

	return DATA_BAD;
}

int DataIO::writeIdPointData(vector<ItemPos>& idPointInfo)
{
	if (m_flag == DATA_WRITE && m_PrepareState == false)
	{
		int groupSize = idPointInfo.size();
		m_data<<groupSize;

		vector<ItemPos>::iterator iter = idPointInfo.begin();
		for (;iter != idPointInfo.end(); ++iter)
		{
			QuestionData data = questionInfo2QuestionData(*iter);
			m_data<<data.questionId<<data.isCrossWise
				<<data.singleChoice<<data.interval
				<<data.markerId1<<data.markerId2
				<<data.markerId3;
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
//////////////////////////////////////读操作/////////////////////////////////////////
int DataIO::readFromDat(DataInfo& info)
{	
	int rst = readFileHead();
	if (rst == TYPE_ONE)
	{
		readImage(info.image);
		readAnchorInfo(info.anchorPoints, info.anchorType);
		readMarkerInfo(info.markersRect, info.markerDone);
		readBarCodeInfo(info.barGroup);
		readQuestionInfo(info.questioninfo,info.questionType);
		readFillPointInfo(info.fillingPointGroup);
		readCropAreaInfo(info.cropAreaInfo);
		readWhiteLineData(info.whiteLineRect);
		readBlackLineData(info.blackeLineRect);
		readIdPointInfo(info.idPointInfo);
		readReferPointInfo(info.referPoint);
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

int DataIO::readMarkerInfo(cv::Rect markersRect[2], bool &markerDone)
{
	if (m_flag == DATA_READ && m_PrepareState == false)
	{
		QRect rect2[2];
		bool done ;

		m_data>>done>>rect2[0]>>rect2[1];

		for (int i = 0; i < 2; ++i)
		{
			markersRect[i] = qRect2CvRect(rect2[i]);
		}

		markerDone = done;
		return DATA_READ;
	}
	return DATA_BAD;
}

int DataIO::readFillPointInfo(vector<FillingPoints_info>& fillingPointGroup)
{
	if (m_flag == DATA_READ && m_PrepareState == false)
	{
		int groupSize;
		m_data>>groupSize;

		for (int i = 0; i < groupSize; ++i)
		{
			FillPointData fpData;
			m_data>>fpData.fillPointName>>fpData.fillPointType>>fpData.itemAmount
				>>fpData.fillPointId>>fpData.isCrossWise>>fpData.singleChoice
				>>fpData.interval>>fpData.markerId1
				>>fpData.markerId2>>fpData.markerId3;

			FillingPoints_info info = fillPointData2FillPointInfo(fpData);
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

int DataIO::readIdPointInfo(vector<ItemPos>& idPointInfo)
{
	if (m_flag == DATA_READ && m_PrepareState == false)
	{
		int groupSize;
		m_data>>groupSize;

		for (int i = 0; i < groupSize; ++i)
		{
			QuestionData data;
			m_data>>data.questionId>>data.isCrossWise
				>>data.singleChoice>>data.interval
				>>data.markerId1>>data.markerId2
				>>data.markerId3;

			ItemPos info = questionData2ItemPos(data);
			idPointInfo.push_back(info);
		}
		return DATA_READ;
	}

	return DATA_BAD;
}

int DataIO::readQuestionInfo(vector<ItemPos>& questioninfo,int &questionType)
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
				>>data.markerId3;

			ItemPos info = questionData2ItemPos(data);
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

/////////////////////////////////////数据转换////////////////////////////////////////
QRect DataIO::cvRect2QRect(const cv::Rect& rect)
{
	return QRect(QPoint(rect.tl().x,rect.tl().y), QPoint(rect.br().x,rect.br().y));
}

FillPointData DataIO::fillPointInfo2FillPointData(FillingPoints_info& info)
{
	FillPointData data;
	data.fillPointName = QString::fromLocal8Bit(info.name.c_str());
	data.fillPointType = (int)(info.type);
	data.itemAmount = info.fillingPoints.size();

	vector<ItemPos>::iterator iter = info.fillingPoints.begin();

	for (;iter != info.fillingPoints.end(); ++iter)
	{
		data.fillPointId.push_back(iter->id);
		data.isCrossWise.push_back(iter->isCrosswise);
		data.interval.push_back(iter->interval);
		data.singleChoice.push_back(iter->isSingleChoice);
		data.markerId1.push_back(iter->markerIdx[0]);
		data.markerId2.push_back(iter->markerIdx[1]);
		data.markerId3.push_back(iter->markerIdx[2]);
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

QuestionData DataIO::questionInfo2QuestionData(const ItemPos& info)
{
	QuestionData data;
	data.questionId = info.id;
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

FillingPoints_info DataIO::fillPointData2FillPointInfo(const FillPointData& data)
{
	FillingPoints_info info;
	info.name = data.fillPointName.toAscii().data();
	info.type = (FillingPointsType)(data.fillPointType);

	int size = data.itemAmount;
	for (int i = 0; i < size; ++i)
	{
		ItemPos pos;
		pos.id = data.fillPointId[i];
		pos.interval = data.interval[i];
		pos.isCrosswise = data.isCrossWise[i];
		pos.isSingleChoice = data.singleChoice[i];
		pos.markerIdx[0] = data.markerId1[i];
		pos.markerIdx[1] = data.markerId2[i];
		pos.markerIdx[2] = data.markerId3[i];

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

ItemPos DataIO::questionData2ItemPos(const QuestionData& data)
{
	ItemPos info;
	info.id = data.questionId;
	info.interval = data.interval;
	info.isCrosswise = data.isCrossWise;
	info.isSingleChoice = data.singleChoice;
	info.markerIdx[0] = data.markerId1;
	info.markerIdx[1] = data.markerId2;
	info.markerIdx[2] = data.markerId3;

	return info;
}

CropArea_info DataIO::clipData2CropAreaInfo(const ClipData& data)
{
	CropArea_info info;
	info.name = data.clipName.toAscii().data();
	info.isSecret = data.isSecret;
	info.groupNum = data.groupNum;
	info.pos = qRect2CvRect(data.pos);

	return info;
}