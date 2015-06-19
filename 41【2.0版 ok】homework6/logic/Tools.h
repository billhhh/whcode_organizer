/**
 * 工具类
 * 
 * @author Bill Wang
 * 
 */
#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include <io.h>
#include "StudentObj.h"
#include "XmlReader.h"

class Tools
{
public:
	bool getStudents(string batch,StudentObj &checkStu,vector <StudentObj> &otherStu);//传入path和待检测学生，返回待检测学生信息和其他学生信息
	string findXmlPath(string batch);  //合成XML的绝对路径，传给xmlReader，获得student对象
	bool getDirFilesPath(string path, vector<string>& files ,vector <string> &stuId);   //获得某文件夹下的所有文件的绝对路径，和文件夹下所有学生学号
	bool getAllStudentsNum(string batch,vector <StudentObj> &allStudents); //【2.0版本新增】获得所有学生num info

private:
	
};

#endif