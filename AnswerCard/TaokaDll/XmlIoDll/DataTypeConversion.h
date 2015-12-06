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
	static stringstream sStream;
	// 布尔值到字符串转换
	static string Bool2String(bool boolVaule);
	// 无符号短整形到字符串转换
	static string Ushort2String(ushort ushortValue);
	// 短整形到字符串转换
	static string Short2String(short shortValue);
	// 整形到字符串转换
	static string Int2String(int intValue);
	// 浮点型形到字符串转换
	static string Float2String(float floatValue);
	// 双精度浮点型形到字符串转换s
	static string Double2String(double doubleValue);

	// opencv矩形到字符串
	static string Rect2String(cv::Rect rect);
	// opencv尺寸到字符串转换
	static string Size2String(cv::Size size);
	//opencv CV_32S矩阵到字符串转换
	static string Mat32s2String(cv::Mat mat);

	//////////////////////////////////////////////////////////////////////////
	//字符串到布尔值
	static bool String2Bool(string stringValue);
	//字符串到无符号短整型
	static ushort String2Ushort(string stringValue);
	//字符串到短整型
	static short String2Short(string stringValue);
	//字符串到整型
	static int String2Int(string stringValue);
	//字符串到浮点型
	static float String2Float(string stringValue);
	//字符串到双精度浮点型
	static double String2Double(string stringValue);

	//字符串到opencv矩形
	static cv::Rect String2Rect(string stringValue);
	//字符串到opencv尺寸
	static cv::Size String2Size(string stringValue);
	//字符串到opencv CV_32S矩阵
	static cv::Mat String2Mat32s(string stringValue);

};

