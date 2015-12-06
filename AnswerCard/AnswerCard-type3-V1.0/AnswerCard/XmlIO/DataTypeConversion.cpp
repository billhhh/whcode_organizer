#include "DataTypeConversion.h"


DataTypeConversion::DataTypeConversion(void)
{
}


DataTypeConversion::~DataTypeConversion(void)
{
}

// 无符号短整形到字符串转换
string DataTypeConversion::Ushort2String(ushort ushortValue)
{
	sStream.clear();
	sStream.str("");
	sStream<<ushortValue;
	return sStream.str();
}
// 短整形到字符串转换
string DataTypeConversion::Short2String(short shortValue)
{
	sStream.clear();
	sStream.str("");
	sStream<<shortValue;
	return sStream.str();
}
// 整形到字符串转换
string DataTypeConversion::Int2String(int intValue)
{
	sStream.clear();
	sStream.str("");
	sStream<<intValue;
	return sStream.str();
}
// 浮点型形到字符串转换
string DataTypeConversion::Float2String(float floatValue)
{
	sStream.clear();
	sStream.str("");
	sStream<<floatValue;
	return sStream.str();
}
// 双精度浮点型形到字符串转换
string DataTypeConversion::Double2String(double doubleValue)
{
	sStream.clear();
	sStream.str("");
	sStream<<doubleValue;
	return sStream.str();
}

// opencv矩形到字符串
string DataTypeConversion::Rect2String(cv::Rect rect)
{
	sStream.clear();
	sStream.str("");
	sStream<<rect.x<<' '<<rect.y<<' '<<rect.width<<' '<<rect.height;
	return sStream.str();
}


// opencv尺寸到字符串转换
string DataTypeConversion::Size2String(cv::Size size)
{
	sStream.clear();
	sStream.str("");
	sStream<<size.width<<' '<<size.height;
	return sStream.str();
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
	sStream.clear();
	sStream.str("");
	sStream<<mat.cols<<' '<<mat.rows<<' ';

	for (int i = 0;i<mat.rows;i++)
	{
		for (int j=0;j<mat.cols;j++)
		{
			sStream<<mat.at<int>(i,j)<<' ';
		}
		//sStream<<endl;
	}
	return sStream.str();
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
	sStream.clear();
	sStream.str("");
	sStream<<stringValue;
	ushort tmp;
	sStream>>tmp;
	return tmp;
}
//字符串到短整型
short DataTypeConversion::String2Short(string stringValue)
{
	sStream.clear();
	sStream.str("");
	sStream<<stringValue;
	short tmp;
	sStream>>tmp;
	return tmp;
}
//字符串到整型
int DataTypeConversion::String2Int(string stringValue)
{
	sStream.clear();
	sStream.str("");
	sStream<<stringValue;
	int tmp;
	sStream>>tmp;
	return tmp;
}
//字符串到浮点型
float DataTypeConversion::String2Float(string stringValue)
{
	sStream.clear();
	sStream.str("");
	sStream<<stringValue;
	float tmp;
	sStream>>tmp;
	return tmp;
}
//字符串到双精度浮点型
double DataTypeConversion::String2Double(string stringValue)
{
	sStream.clear();
	sStream.str("");
	sStream<<stringValue;
	double tmp;
	sStream>>tmp;
	return tmp;
}

//字符串到opencv矩形
cv::Rect DataTypeConversion::String2Rect(string stringValue)
{
	sStream.clear();
	sStream.str("");
	sStream<<stringValue;
	cv::Rect tmp;
	sStream>>tmp.x>>tmp.y>>tmp.width>>tmp.height;
	return tmp;
}
//字符串到opencv尺寸
cv::Size DataTypeConversion::String2Size(string stringValue)
{
	sStream.clear();
	sStream.str("");
	sStream<<stringValue;
	cv::Size tmp;
	sStream>>tmp.width>>tmp.height;
	return tmp;
}
//字符串到opencv CV_32S矩阵
cv::Mat DataTypeConversion::String2Mat32s(string stringValue)
{
	sStream.clear();
	sStream.str("");
	sStream<<stringValue;
	cv::Size size;
	sStream>>size.width>>size.height;
	cv::Mat mat(size,CV_32S);
	int length = size.width*size.height;
	for (int i=0;i<length;i++)
	{
		sStream>>mat.at<int>(i);
	}
	return mat;
}