/**
 * 控制器类，收集students信息，调用xmlReader，传递给算法检测
 * 
 * @author Bill Wang
 * 
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include "StudentObj.h"
#include "Tools.h"
#include "studentMap.h"
#include "StringCompare.h"
#include "../mainwindow.h"

using namespace std;

class Controller
{
public:
	StudentObj checkStudent;  //待检测的学生
	vector <StudentObj> otherStudents;  //除了待检测的其他学生
	vector <StudentObj> allStudents;  //所有学生info

	bool startCheck(Ui::MainWindow *ui,string homeworkPath,string batch,string batchPath,
		vector <studentMap> stuMap);//与界面直接接触，接受作业批次和待检测学生学号
	
private:
	string homeworkPath;
	string batchPath;
	string studentPath;
	string batch;  //作业批次
	vector <studentMap> stuMap;
	bool runPreprocess(string batchPath);
	void fillStudents();  //对应map填满学生信息【姓名】
	void sendToCompare(Ui::MainWindow *ui); //送去算法检测
};

#endif