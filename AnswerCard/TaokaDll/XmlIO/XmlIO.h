#pragma once

#ifdef _DLL_XMLIO
#define DLL_XMLIODLL_API   __declspec(dllexport) __stdcall
#else
#define DLL_XMLIODLL_API   __declspec(dllimport) 
#endif
//获取卡格式定义
extern "C" int DLL_XMLIODLL_API GetACInfo(char * filename,int actype,int &acinfoAddress);
//获取套卡卡格式定义
extern "C" int DLL_XMLIODLL_API GetTKInfo(const char * filename,int &actype,int &tkinfoAddress);
extern "C" void DLL_XMLIODLL_API freeACInfo(int acinfoAddress,int actype);//释放题卡格式结构体
extern "C" void DLL_XMLIODLL_API freeTkInfo(int tkinfoAddress,int actype);//释放套卡格式结构体
