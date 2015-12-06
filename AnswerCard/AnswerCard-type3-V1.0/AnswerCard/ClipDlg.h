#ifndef CLIPDLG_H
#define CLIPDLG_H

#include <QDialog>
#include <QMessageBox>
#include "qlistwidget.h"

namespace Ui {class ClipDlg;};

class ClipDlg : public QDialog
{
	Q_OBJECT

public:
	ClipDlg(QWidget *parent = 0);
	~ClipDlg();

	void setConfirmBtnEnabled(bool);
	void initialization();//初始化

	int resume();        //根据数据恢复窗口信息
private:
	Ui::ClipDlg *ui;
	bool isSecretClicked;  //是否为保密属性

	void setProcessing(bool);

signals:
	void clipBegin();   //裁切开始
	void clipDone();    //裁切结束
	void clipDelete();
	void clipClicked(int);

protected slots:
	void on_addBtn_clicked();//点击添加裁切区域的按钮
	void on_confirmBtn_clicked();//确认裁切区域
	void on_deleteBtn_clicked();//删除裁切区域
	void on_secretCheckBox_toggled();
	void showClicked(QListWidgetItem* item);
};

#endif // CLIPDLG_H
