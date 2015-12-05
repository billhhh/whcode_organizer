#pragma once
#include <sstream>
#include <cv.h>
using namespace cv;
using namespace std;
class DataTypeConversion
{
public:
	DataTypeConversion(void);
	~DataTypeConversion(void);
	//成员变量
	stringstream sStream;
	// 布尔值到字符串转换
	string Bool2String(bool boolVaule);
	// 无符号短整形到字符串转换
	string Ushort2String(ushort ushortValue);
	// 短整形到字符串转换
	string Short2String(short shortValue);
	// 整形到字符串转换
	string Int2String(int intValue);
	// 浮点型形到字符串转换
	string Float2String(float floatValue);
	// 双精度浮点型形到字符串转换s
	string Double2String(double doubleValue);

	// opencv矩形到字符串
	string Rect2String(cv::Rect rect);
	// opencv尺寸到字符串转换
	string Size2String(cv::Size size);
	//opencv CV_32S矩阵到字符串转换
	string Mat32s2String(cv::Mat mat);

	//////////////////////////////////////////////////////////////////////////
	//字符串到布尔值
	bool String2Bool(string stringValue);
	//字符串到无符号短整型
	ushort String2Ushort(string stringValue);
	//字符串到短整型
	short String2Short(string stringValue);
	//字符串到整型
	int String2Int(string stringValue);
	//字符串到浮点型
	float String2Float(string stringValue);
	//字符串到双精度浮点型
	double String2Double(string stringValue);

	//字符串到opencv矩形
	cv::Rect String2Rect(string stringValue);
	//字符串到opencv尺寸
	cv::Size String2Size(string stringValue);
	//字符串到opencv CV_32S矩阵
	cv::Mat String2Mat32s(string stringValue);

};

