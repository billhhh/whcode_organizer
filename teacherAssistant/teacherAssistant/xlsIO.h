/*
 *
 * funtion:对excel文件进行IO操作
 *
 *    Author: Bill Wang
 */

#ifndef _XLSIO_H_
#define _XLSIO_H_

#include <iostream>
#include <vector>
#include <string>
#include <QtGui/QApplication>


class XlsIO
{
public:
	bool xlsReader(QString excelPath,std::vector<std::string> &stuNames); //读取所有学生名字，存入vector
	bool xlsWriter(QString excelPath,int row);

private:
};

#endif