
#include "ACZip.h"
#include <memory.h>
#include <iostream>
#include <stdio.h>
//#include <stdlib.h>
#include <string>
#include <error.h>
using namespace std;

int	ACZip( vector<string> files,string zipname){
	char zipName[MAX_PATH];
	strcpy(zipName,zipname.c_str());
	//声明对象
	MyCab mc;
	//设置输出文件
	mc.SetOutPutFile(zipName);
	//添加要打包的文件
	for (unsigned int i=0;i<files.size();i++)
	{
		mc.AddFile(files.at(i));
	}
	
	//执行打包
	mc.DoMakeCAB();
	return 0;
}

MyCab::MyCab() {
	memset(&fh,0x0,sizeof(fh));
	memset(ObjectFilePathName,0x0,sizeof(ObjectFilePathName));
 }

 //添加文件到包内
void MyCab::AddFile(string FilePathName){
	if ( fh.FileCount >= MAX_FILE_COUNT - 1 )
	{
	   cout<<"最多支持"<<MAX_FILE_COUNT<<"个文件"<<endl;
	   return;
	}
	strcpy(fh.FileName[fh.FileCount],FilePathName.c_str());
	fh.FileCount++;
 }

 //设置打包输出文件
void MyCab::SetOutPutFile(char * OutFile)
 {
	memset(ObjectFilePathName,0x0,sizeof(ObjectFilePathName));
	strcpy(ObjectFilePathName,OutFile);
 }

//获取文件大小(传入以二进制方式打开的文件指针)
long MyCab::GetFileSize(FILE *pf)
 {
	//指针移到文件尾
	fseek(pf,0,/*SEEK_END*/ 2);
	return ftell(pf);
 }

 //制作打包文件
 void MyCab::DoMakeCAB()
 {
	if ( fh.FileCount < 1 )
	{
		cout<<"没有文件添加到打包"<<endl;
		return;
	}
	if ( strlen(ObjectFilePathName) < 1 )
	{
		cout<<"没有指定打包文件输出位置"<<endl;
		return;
	}
	FILE *pOutFile = NULL;
	FILE *pWorkFile = NULL;
	//获取所有文件大小
	for ( int i = 0 ; i < fh.FileCount ; i++ )
	{
		pWorkFile = fopen(fh.FileName[i],"rb");
		if ( NULL == pWorkFile )
		{
			cout<<"文件:"<<fh.FileName[i]<<"无法读取["<<strerror(errno)<<"]"<<endl;
			return;
		}
		fh.FileLen[i] = GetFileSize(pWorkFile);
		fclose(pWorkFile);
	}
	//开始合并写文件
	pOutFile = fopen(ObjectFilePathName,"wb");
	if ( NULL == pOutFile )
	{
		cout<<"输出文件创建失败["<<strerror(errno)<<"]"<<endl;
		return;
	}
	//写入文件头
	fwrite(&fh,sizeof(fh),1,pOutFile);
	//写入各文件
	for ( int i = 0 ; i < fh.FileCount ; i++ )
	{
		unsigned char *pTmpData = NULL;
		pWorkFile = fopen(fh.FileName[i],"rb");
		if ( NULL == pWorkFile )
		{
			cout<<"文件:"<<fh.FileName[i]<<"无法读取["<<strerror(errno)<<"]"<<endl;
			fclose(pWorkFile);
			fclose(pOutFile);
			return;
		}
		pTmpData = new unsigned char[fh.FileLen[i]];
		fread(pTmpData,fh.FileLen[i],1,pWorkFile);
		if ( ferror(pWorkFile) )
		{
			cout<<"文件:"<<fh.FileName[i]<<"无法读取["<<strerror(errno)<<"]"<<endl;
			fclose(pWorkFile);
			fclose(pOutFile);
			return;
		}
		fwrite(pTmpData,fh.FileLen[i],1,pOutFile);
		if ( ferror(pOutFile) )
		{
			cout<<"文件:"<<ObjectFilePathName<<"无法写入["<<strerror(errno)<<"]"<<endl;
			fclose(pWorkFile);
			fclose(pOutFile);
			return;
		}
		delete [] pTmpData;
		fclose(pWorkFile);
	}
	fclose(pOutFile);
	cout<<"打包完成"<<endl;
 }

 //解包(为了节省时间不写错误处理了,可以根据上面自己添加)
 void MyCab::DoUnCAB(char *CabFilePathName,string path)
 {
	FILE *pCAB = NULL;
	FILE *pWork = NULL;
	pCAB = fopen(CabFilePathName,"rb");
	//读文件头
	memset(&fh,0x0,sizeof(fh));
	fread(&fh,sizeof(fh),1,pCAB);
	printCAB();
	//解包的所有文件放到当前目录下
	for ( int i = 0 ; i < fh.FileCount ; i++ )
	{
		unsigned char *pTmpData = NULL;
		pTmpData = new unsigned char[fh.FileLen[i]];
		fread(pTmpData,fh.FileLen[i],1,pCAB);
		//只取文件名,不要生成文件的路径名
		char tmpFileName[MAX_PATH];
		char *ptmpC = fh.FileName[i] + strlen(fh.FileName[i]);
		while( '\\' != *ptmpC)
		{
			ptmpC--;
		 }
		memset(tmpFileName,0x0,sizeof(tmpFileName));
		strcpy(tmpFileName,ptmpC);
		//取CAB文件路径
		char tmpPathName[MAX_PATH];
		memset(tmpPathName,0x0,sizeof(tmpPathName));
		strcpy(tmpPathName,path.c_str());
		ptmpC = tmpPathName + strlen(tmpPathName);
		while('\0' != *ptmpC)
		{
			ptmpC--;
		}
		ptmpC++;
		*ptmpC = '\0';
		strcat(tmpPathName,tmpFileName);
		pWork = fopen(tmpPathName,"wb");
		fwrite(pTmpData,fh.FileLen[i],1,pWork);
		fclose(pWork);
		delete [] pTmpData;
	}
	fclose(pCAB);
 }

 //显示打包内文件信息
 void MyCab::printCAB()
 {
	cout<<"文件内信息如下:"<<endl;
	cout<<"文件总数:"<<fh.FileCount<<endl;
	for ( int i = 0 ; i < fh.FileCount ; i++ )
	{
		cout<<fh.FileName[i]<<"\t\t\t\t"<<fh.FileLen[i]<<"字节"<<endl;
	}
 }

