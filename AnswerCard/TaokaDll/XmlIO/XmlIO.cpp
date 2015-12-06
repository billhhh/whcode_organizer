// XmlIO.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "XmlIO.h"
#include "XmlIODLL.h"
//#include "../Demo/debug_new.h"
#pragma comment(lib,"../debug/XmlIoDll.lib")
int GetACInfo(char * filename,int actype,int &acinfoAddress)
{
	XmlIo xmlo;
	int returnValue=0;
	if (actype==1||actype==2)
	{
		AC_info *ac_info=new AC_info;


		returnValue=xmlo.Read(filename,*ac_info);
		if (returnValue==0)
		{
			acinfoAddress=(int)ac_info;
		}else
			return returnValue;

	}else if (actype==3||actype==4)
	{
		AC_info3 * ac_info3=new AC_info3;
		returnValue=xmlo.Read(filename,*ac_info3);
		if (returnValue==0)
		{
			acinfoAddress=(int)ac_info3;
		}else
			return returnValue;
	}
	else return -1;
	
	return 0;
}

//获取套卡卡格式定义
int  GetTKInfo(const char * filename,int &actype,int &tkinfoAddress)
{
	XmlIo xmlio;
	int returnValue=0;
	xmlio.GetACType(filename,actype);
	if (actype==1||actype==2)
	{
		TK_info * tk_info=new TK_info;
		returnValue=xmlio.Read(filename,*tk_info);
		if (returnValue==0)
		{
			tkinfoAddress=(int)tk_info;
		}else
			return returnValue;

	}else if (actype==3||actype==4)
	{
		TK_info3 *tk_info3=new TK_info3;
		returnValue=xmlio.Read(filename,*tk_info3);
		if (returnValue==0)
		{
			tkinfoAddress=(int)tk_info3;
		}else
			return returnValue;
	}
	else return -1;
	return 0;
}

void freeACInfo(int acinfoAddress,int actype)
{
	if (actype==1||actype==2)
	{
		delete((AC_info *)acinfoAddress);
	}
	else if (actype==3||actype==4)
	{
		delete((AC_info3 *)acinfoAddress);
	}

}

void freeTkInfo(int tkinfoAddress,int actype)
{
	if (actype==1||actype==2)
	{
		TK_info * tkinfo=(TK_info *)tkinfoAddress;
		/*tkinfo->tkinfo.clear();*/
		delete tkinfo;
		
	}
	else if (actype==3||actype==4)
	{
		TK_info3 *tkinfo3=(TK_info3 *)tkinfoAddress;
		/*tkinfo3->tkinfo.clear();*/
		delete tkinfo3;
	}

}