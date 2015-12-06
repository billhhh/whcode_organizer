#include "ACStructs.h"
#include "CommonStruct.h"
#include <string>
using namespace std;
void AC_RST2Result(Result &result,const AC_RST &acrst);
void Result2AC_RST(const Result &result,AC_RST &acrst);
//十六进制的string转int
int HexString2Int(const string &hexStr);
//转换卡格式结构体
void TransTkinfo(const TK_info &tkInfo,Cum_TK_info &cumTkInfo);
void TransTkinfo3(const TK_info3 &tkInfo,Cum_TK_info3 &cumTkInfo);
void transACInfo(const AC_info &acinfo,Cum_AC_info &cum_acinfo);
void transACInfo3(const AC_info3 &acinfo,Cum_AC_info3 &cum_acinfo);
void transItemPos(vector<ItemPos>::const_iterator itemBegin,vector<ItemPos>::const_iterator itemEnd,Cum_ItemPos *itemPos);
void transMarker(vector<PerMarker_info>::const_iterator itemBegin,vector<PerMarker_info>::const_iterator itemEnd,Cum_PerMarker_info *perMarker);