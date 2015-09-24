#include "xlsIO.h"
#include <ActiveQt/QAxWidget>
#include <ActiveQt/QAxObject>
#include <QVariant>
#include <QFileDialog>
#include <QMainWindow>
#include <QTextCodec>
#include <QMessageBox>
#include <qDebug>
#include <vector>
#include "ui_teacherassistant.h"

using namespace std;

bool XlsIO::xlsReader(QString excelPath,vector<string> &stuNames)
{
	QAxObject excel("Excel.Application");
	excel.setProperty("Visible", false);
	QAxObject *work_books = excel.querySubObject("WorkBooks");
	work_books->dynamicCall("Open (const QString&)", excelPath);
	QAxObject *work_book = excel.querySubObject("ActiveWorkBook");
	QAxObject *work_sheets = work_book->querySubObject("Sheets");  //Sheets也可换用WorkSheets
	int sheet_count = work_sheets->property("Count").toInt();  //获取工作表数目

	if(sheet_count > 0)
	{
		QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", 1);
		QAxObject *used_range = work_sheet->querySubObject("UsedRange");
		QAxObject *rows = used_range->querySubObject("Rows");
		//QAxObject *columns = used_range->querySubObject("Columns");
		int row_start = used_range->property("Row").toInt();  //获取起始行:1
		//int column_start = used_range->property("Column").toInt();  //获取起始列
		int row_count = rows->property("Count").toInt();  //获取行数
		//int column_count = columns->property("Count").toInt();  //获取列数

		QString StudentName;
		for(int i=row_start+4; i<=row_count;i++)
		{
			QAxObject *cell = work_sheet->querySubObject("Cells(int,int)", i, 3);
			StudentName = cell->dynamicCall("Value2()").toString();//获取单元格内容

			stuNames.push_back(StudentName.toStdString());
		}
	}

	work_books->dynamicCall("Close()");//关闭工作簿
	excel.dynamicCall("Quit()");//关闭excel

	return true;
}


bool XlsIO::xlsWriter(QString excelPath,int row)
{
	QAxObject excel("Excel.Application");
	excel.setProperty("Visible", false);
	QAxObject *work_books = excel.querySubObject("WorkBooks");
	work_books->dynamicCall("Open (const QString&)", excelPath);
	QAxObject *work_book = excel.querySubObject("ActiveWorkBook");
	QAxObject *work_sheets = work_book->querySubObject("Sheets");  //Sheets也可换用WorkSheets
	int sheet_count = work_sheets->property("Count").toInt();  //获取工作表数目

	if(sheet_count > 0)
	{
		QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", 1);
		QAxObject *cell = work_sheet->querySubObject("Cells(int,int)", row+5, 9);

		cell->setProperty("Value","V");
	}

	work_book->dynamicCall("Save()");  //保存文件
	work_books->dynamicCall("Close()");//关闭工作簿
	excel.dynamicCall("Quit(void)");//关闭excel

	return true;
}