/*
 *
 * funtion: 控制整个程序流程
 *
 *    Author: Bill Wang
 */
#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <iostream>
#include <vector>
#include <string>
#include <QtGui/QMainWindow>

class Controller
{
public:
	void startCheck(QString excelPath, std::string homeworkPath, std::vector<std::string> stuNames);

private:
	std::vector<std::string> fileNames,chineseFileNames;
	bool compareName(std::string name1,std::string name2);
};

#endif