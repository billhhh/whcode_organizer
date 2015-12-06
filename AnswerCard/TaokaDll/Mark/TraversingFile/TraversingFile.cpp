#include "stdafx.h"
#include "TraversingFile.h"
#include <iterator>
#include <algorithm>
TraversingFile::TraversingFile(void)
{
	FindData;
	hError;
	FileCount = 0;
}


TraversingFile::~TraversingFile(void)
{
}
//含有特殊字符
bool IsNumOrChar(char ch)
{
	if ((ch>='0'&&ch<='9')||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
	{
		return true;
	}else
		return false;
}

// 初始化，传入要遍历的目录
int TraversingFile::Init(string path,string suffix)
{
	//后缀名合法性判断
	string::iterator first;
	first = find_if_not(suffix.begin(),suffix.end(),IsNumOrChar);
	if (first != suffix.end())
	{
		//后缀名中含有非法字符
		return -1;
	}
	//构造文件名
	strcpy_s(FilePathName, path.c_str());
	if (path[path.length()-1] != '\\'&&path[path.length()-1] != '/')
	{
		strcat_s(FilePathName, "\\*.");
	}else
	{
		strcat_s(FilePathName, "*.");
		path = path.substr(0,path.length()-1);
	}
	strcat_s(FilePathName, suffix.c_str());
	this->path = path;
	this->suffix = suffix;
	return 0;
}


// 获得要遍历路径下的一个文件名
int TraversingFile::GetFileName(string& filename)
{
	//未初始化？
	if (suffix.length() == 0)
	{
		return -1;
	}
	//第一个文件?
	if (FileCount == 0)
	{
		hError = FindFirstFile(FilePathName, &FindData);
		if (hError == INVALID_HANDLE_VALUE)
		{
			return -2;
		}
	}else{
		if (::FindNextFile(hError, &FindData))
		{
			// 过虑.和..
			if (strcmp(FindData.cFileName, ".") == 0 || strcmp(FindData.cFileName, "..") == 0 )
			{
				return GetFileName(filename);
			}
		}else
		{
			//遍历完毕
			return 1;
		}
	}
	// 构造完整路径
//	wsprintf(FullPathName, "%s\\%s", path.c_str(),FindData.cFileName);
	string pahta(path.c_str());
	string pathb(FindData.cFileName);
	filename = pahta+"\\"+pathb;
	FileCount++;
	return 0;
}
// 文件数量计数器
int TraversingFile::GetFileCounter(void)
{
	return FileCount;
}