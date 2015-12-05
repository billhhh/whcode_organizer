
#include "ACZip.h"
#include <iostream>
using namespace std;

int	ACUnZip(string zipname, string path){
	char zipName[MAX_PATH];
	strcpy(zipName,zipname.c_str());
	//声明对象
	MyCab umc;
	//执行解包
	umc.DoUnCAB(zipName,path);
	cout<<"解包完成"<<endl;
	return 0;
}