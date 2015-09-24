/*
 * 
 * funtion: 工具类，提供如【拿到字符串中中文子串】等工具函数
 *
 *    Author: Bill Wang
 */

#ifndef _TOOLS_H_
#define _TOOLS_H_

#include<iostream>
#include<string>
#include <string>
#include <io.h>
#include <vector>

class Tools
{
public:
	std::string getChinese(std::string inputStr);  //获得中文子串，并返回
	bool getDirFilesPath( std::string folderPath, std::vector<std::string>& files); //获得某文件夹下的所有文件名，包括文件夹名

protected:
private:
};

#endif
