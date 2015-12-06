#pragma once
#include <string>
using namespace std;
class CChineseCode
{
public:
	CChineseCode(void);
	~CChineseCode(void);
	static string GBKToUTF8(const std::string& strGBK);
	static string UTF8ToGBK(const std::string& strUTF8);
};

