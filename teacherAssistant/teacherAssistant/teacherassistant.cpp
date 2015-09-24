#include "teacherassistant.h"
#include <iostream>
#include <vector>
#include <string>
#include <QMessageBox>
#include "xlsIO.h"
#include "Controller.h"

using namespace std;

teacherAssistant::teacherAssistant(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
}

teacherAssistant::~teacherAssistant()
{

}


//导入excel信息
void teacherAssistant::on_pushButton_clicked()
{
	excelPath = QFileDialog::getOpenFileName(this,tr("选择打开的文件"),".",tr("Excel Files(*.xlsx *.xls)"));
	if(excelPath.size()==0)
		return;
	
	cout<<"excelPath == "<<excelPath.toStdString()<<"\n";

	XlsIO xlsio;
	xlsio.xlsReader(excelPath,stuNames);

// 	for (int i=0;i<stuNames.size();i++)
// 		cout<<stuNames.at(i)<<endl;

	cout<<"stuNames.size == "<<stuNames.size()<<"\n";
}


void teacherAssistant::on_pushButton_2_clicked()
{
	homeworkPath = QFileDialog::getExistingDirectory(this,tr("选择作业存放位置"),".");
	if(homeworkPath.size()==0)
		return;
	QMessageBox::information(NULL, tr("Path"), tr("You selected ") + homeworkPath);
}


//最终的“确定”按钮，开始查重
void teacherAssistant::on_submitBtn_clicked()
{
	if (excelPath.size()==0)
	{
		QMessageBox::information(NULL, tr("警告"), tr("未指定学生【花名册】"));
		return;
	}

	if(homeworkPath.size()==0)
	{
		QMessageBox::information(NULL, tr("警告"), tr("未选择【作业路径】"));
		return;
	}

	Controller ctrl;
	ctrl.startCheck(excelPath,homeworkPath.toStdString(),stuNames);
}