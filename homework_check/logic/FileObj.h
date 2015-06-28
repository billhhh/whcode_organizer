/**
 * 文件实体类
 * 
 * @author Bill Wang
 * 
 */
#ifndef FILEOBJ_H
#define FILEOBJ_H

#include <iostream>
using namespace std;

class FileObj
{
public:
	//getter、setter方法
	string getFileName();
	void setFileName(string fileName);
	string getFileType();
	void setFileType(string fileType);
	string getContent();
	void setContent(string content);
private:
	string fileName;
	string fileType;
	string content;
};

#endif
