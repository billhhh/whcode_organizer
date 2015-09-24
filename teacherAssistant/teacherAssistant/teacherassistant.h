#ifndef TEACHERASSISTANT_H
#define TEACHERASSISTANT_H

#include <QtGui/QMainWindow>
#include "ui_teacherassistant.h"

#include <iostream>
#include <vector>
#include <string>
#include <QFileDialog>

class teacherAssistant : public QMainWindow
{
	Q_OBJECT

public:
	teacherAssistant(QWidget *parent = 0, Qt::WFlags flags = 0);
	~teacherAssistant();

	QString excelPath;
	QString homeworkPath;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_submitBtn_clicked();

private:
	Ui::teacherAssistantClass ui;
	std::vector<std::string> stuNames;
};

#endif // TEACHERASSISTANT_H
