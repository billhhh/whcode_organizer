#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "showdocument.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMainWindow>
#include <QTextCodec>
#include <QAxObject>
#include <QAxWidget>
#include <QVariant>
#include <QMessageBox>
#include <qDebug>
#include <vector>
#include "logic/XmlReader.h"
#include "logic/Controller.h"
#include "logic/studentMap.h"
#include "logic/StringCompare.h"
#include "GeneratedFiles/ui_mainwindow.h"

#define HOMEWORKNUM 7

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString excelPath;
    QString homeworkPath;
    QString *StudentName;//StudentName[0]和StudentNum[0]均存的空
    QString *StudentNum;//在学生学号同步学生姓名的过程，防止在这两个数组赋值之前就进行访问（on_StudentNameComboBox_currentIndexChanged(int index)中
	int StuNum;
	vector <studentMap> stuMap;  //学生姓名、学号映射
	void addchild(QTreeWidgetItem *parent, QString studentname1, QString studentname2, QString similarity);
	QTreeWidgetItem *addroot(QString studentname1, QString studentname2, QString similarity);

private slots:

    void on_StudentNameComboBox_currentIndexChanged(int index);
    void on_submitBtn_clicked();
    void on_rltTreeWidget_itemDoubleClicked(QTreeWidgetItem* item, int column);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
