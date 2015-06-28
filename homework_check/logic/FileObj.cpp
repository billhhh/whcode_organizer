/**
 * file实体类实现
 * 
 * @author Bill Wang
 * 
 */
#include "FileObj.h"

string FileObj::getFileName()
{
	return this->fileName;
}
void FileObj::setFileName(string fileName)
{
	this->fileName = fileName;
}
string FileObj::getFileType()
{
	return this->fileType;
}
void FileObj::setFileType(string fileType)
{
	this->fileType = fileType;
}
string FileObj::getContent()
{
	return this->content;
}
void FileObj::setContent(string content)
{
	this->content = content;
}