#include "StdAfx.h"
#include "DataTypeConversion.h"


DataTypeConversion::DataTypeConversion(void)
{
}


DataTypeConversion::~DataTypeConversion(void)
{
	
}

stringstream DataTypeConversion::sStream;

// 无符号短整形到字符串转换
string DataTypeConversion::Ushort2String(ushort ushortValue)
{
	DataTypeConversion::sStream.clear();
	DataTypeConversion::sStream.str("");
	DataTypeConversion::sStream<<ushortValue;
	return DataTypeConversion::sStream.str();
}
// 短整形到字符串转换
string DataTypeConversion::Short2String(short shortValue)
{
	DataTypeConversion::sStream.clear();
	DataTypeConversion::sStream.str("");
	DataTypeConversion::sStream<<shortValue;
	return DataTypeConversion::sStream.str();
}
// 整形到字符串转换
string DataTypeConversion::Int2String(int intValue)
{
	DataTypeConversion::sStream.clear();
	DataTypeConversion::sStream.str("");
	DataTypeConversion::sStream<<intValue;
	return DataTypeConversion::sStream.str();
}
// 浮点型形到字符串转换
string DataTypeConversion::Float2String(float floatValue)
{
	DataTypeConversion::sStream.clear();
	DataTypeConversion::sStream.str("");
	DataTypeConversion::sStream<<floatValue;
	return DataTypeConversion::sStream.str();
}
// 双精度浮点型形到字符串转换
string DataTypeConversion::Double2String(double doubleValue)
{
	DataTypeConversion::sStream.clear();
	DataTypeConversion::sStream.str("");
	DataTypeConversion::sStream<<doubleValue;
	return DataTypeConversion::sStream.str();
}

// opencv矩形到字符串
string DataTypeConversion::Rect2String(cv::Rect rect)
{
	DataTypeConversion::sStream.clear();
	DataTypeConversion::sStream.str("");
	DataTypeConversion::sStream<<rect.x<<' '<<rect.y<<' '<<rect.width<<' '<<rect.height;
	return DataTypeConversion::sStream.str();
}


// opencv尺寸到字符串转换
string DataTypeConversion::Size2String(cv::Size size)
{
	DataTypeConversion::sStream.clear();
	DataTypeConversion::sStream.str("");
	DataTypeConversion::sStream<<size.width<<' '<<size.height;
	return DataTypeConversion::sStream.str();
	return string();
}


// 布尔值到字符串转换
string DataTypeConversion::Bool2String(bool boolVaule)
{
	if (boolVaule)
	{
		return "true";
	}else{
		return "false";
	}
}
//opencv CV_32S矩阵到字符串转换
string DataTypeConversion::Mat32s2String(cv::Mat mat){
	if (mat.type()!=CV_32S)
	{
		return "error";
	}
	DataTypeConversion::sStream.clear();
	DataTypeConversion::sStream.str("");
	DataTypeConversion::sStream<<mat.cols<<' '<<mat.rows<<' ';

	for (int i = 0;i<mat.rows;i++)
	{
		for (int j=0;j<mat.cols;j++)
		{
			DataTypeConversion::sStream<<mat.at<int>(i,j)<<' ';
		}
		//DataTypeConversion::sStream<<endl;
	}
	return DataTypeConversion::sStream.str();
	return string();
}
//字符串到布尔值
bool DataTypeConversion::String2Bool(string stringValue)
{
	if (stringValue.compare("true")==0)
	{
		return true;
	}else
		return false;
}
//字符串到无符号短整型
ushort DataTypeConversion::String2Ushort(string stringValue)
{
	DataTypeConversion::sStream.clear();
	DataTypeConversion::sStream.str("");
	DataTypeConversion::sStream<<stringValue;
	ushort tmp;
	DataTypeConversion::sStream>>tmp;
	return tmp;
}
//字符串到短整型
short DataTypeConversion::String2Short(string stringValue)
{
	DataTypeConversion::sStream.clear();
	DataTypeConversion::sStream.str("");
	DataTypeConversion::sStream<<stringValue;
	short tmp;
	DataTypeConversion::sStream>>tmp;
	return tmp;
}
//字符串到整型
int DataTypeConversion::String2Int(string stringValue)
{
	DataTypeConversion::sStream.clear();
	DataTypeConversion::sStream.str("");
	DataTypeConversion::sStream<<stringValue;
	int tmp;
	DataTypeConversion::sStream>>tmp;
	return tmp;
}
//字符串到浮点型
float DataTypeConversion::String2Float(string stringValue)
{
	DataTypeConversion::sStream.clear();
	DataTypeConversion::sStream.str("");
	DataTypeConversion::sStream<<stringValue;
	float tmp;
	DataTypeConversion::sStream>>tmp;
	return tmp;
}
//字符串到双精度浮点型
double DataTypeConversion::String2Double(string stringValue)
{
	DataTypeConversion::sStream.clear();
	DataTypeConversion::sStream.str("");
	DataTypeConversion::sStream<<stringValue;
	double tmp;
	DataTypeConversion::sStream>>tmp;
	return tmp;
}

//字符串到opencv矩形
cv::Rect DataTypeConversion::String2Rect(string stringValue)
{
	DataTypeConversion::sStream.clear();
	DataTypeConversion::sStream.str("");
	DataTypeConversion::sStream<<stringValue;
	cv::Rect tmp;
	DataTypeConversion::sStream>>tmp.x>>tmp.y>>tmp.width>>tmp.height;
	return tmp;
}
//字符串到opencv尺寸
cv::Size DataTypeConversion::String2Size(string stringValue)
{
	DataTypeConversion::sStream.clear();
	DataTypeConversion::sStream.str("");
	DataTypeConversion::sStream<<stringValue;
	cv::Size tmp;
	DataTypeConversion::sStream>>tmp.width>>tmp.height;
	return tmp;
}
//字符串到opencv CV_32S矩阵
cv::Mat DataTypeConversion::String2Mat32s(string stringValue)
{
	DataTypeConversion::sStream.clear();
	DataTypeConversion::sStream.str("");
	DataTypeConversion::sStream<<stringValue;
	cv::Size size;
	DataTypeConversion::sStream>>size.width>>size.height;
	cv::Mat mat(size,CV_32S);
	int length = size.width*size.height;
	for (int i=0;i<length;i++)
	{
		DataTypeConversion::sStream>>mat.at<int>(i);
	}
	return mat;
}