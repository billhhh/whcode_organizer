#pragma once

#include "ACStructs.h"

#ifdef _DLL_XMLIO
#define DLL_XMLIO_API __declspec(dllexport)
#else
#define DLL_XMLIO_API __declspec(dllimport)
#endif
DLL_XMLIO_API class XmlIo
{
public:
	//¶ÁÐ´½Ó¿Ú
	int Read(string filename,AC_info &acInfo);
	int Read(string filename,AC_info3 &acInfo);
	int Read(string filename,TK_info &tkInfo);
	int Write(string filename,AC_info acInfo);
	int Write(string filename,AC_info3 acInfo);
	int Write(string filename,TK_info tkInfo);
};

