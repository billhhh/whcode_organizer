#ifndef BARCODEDLG_H
#define BARCODEDLG_H

#include <QDialog>
#include <QMessageBox>
#include "qlistwidget.h"
namespace Ui {class BarCodeDlg;};

class BarCodeDlg : public QDialog
{
	Q_OBJECT

public:
	BarCodeDlg(QWidget *parent = 0);
	~BarCodeDlg();

	void setAddBtnText(const QString& str);
	void setConfirmBtnEnabled(bool);

	void initialization();

	int resume();
private:
	void setProcessing(bool);

	Ui::BarCodeDlg *ui;

signals:
	void barCodeBegin();
	void barCodeDone();
	void barCodeDelete();
	void barCodeClicked(int);

protected slots:
	void on_addBtn_clicked();
	void on_confirmBtn_clicked();
	void on_deleteBtn_clicked();
	void showClicked(QListWidgetItem* item);
};

#endif // BARCODEDLG_H
