/**
 * 读取xml的工具类
 * 
 * @author Bill Wang
 * 
 */
#ifndef XMLREADER_H
#define XMLREADER_H

#include <iostream>
#include <vector>
#include<QDomDocument>
#include <QFile>
#include <QDebug>
#include <QTextCodec>
#include "StudentObj.h"
#include "FileObj.h"

using namespace std;

class XmlReader
{
public:
	void test();
	bool XmlIO(string path,vector<FileObj> &fileList); //返回成功与否
	bool XmlIO(string stuName,string stuId,string path,StudentObj &stu); //重载的方法，可以传入学生ID和姓名
	bool XmlIO(string path,StudentObj &stu); //重载的方法，可传入已有ID和姓名的学生，直接获得完整的学生对象

private:
	bool getFileList(string path,vector<FileObj> &fileList);  //得到fileList，方便赋值给stu
};

#endif