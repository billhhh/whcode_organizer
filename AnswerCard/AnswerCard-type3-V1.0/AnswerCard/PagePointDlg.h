#ifndef PAGEPOINTDLG_H
#define PAGEPOINTDLG_H

#include <QDialog>
#include "qlistwidget.h"
#include "AnswerCard.h"
namespace Ui {class PagePointDlg;};

class PagePointDlg : public QDialog
{
	Q_OBJECT

public:
	PagePointDlg(QWidget *parent = 0);
	~PagePointDlg();

	void setAddBtnText(const QString& str);
	void setConfirmBtnEnabled(bool);

	void initialization();

	int resume();

private:
	void setProcessing(bool);
	Ui::PagePointDlg *ui;

	int index;

signals:
	void pagePointBegin();
	void pagePointDone();
	void pagePointDelete();
	void pagePointClicked(int);

protected slots:
	void on_addBtn_clicked();
	void on_confirmBtn_clicked();
	void on_deleteBtn_clicked();
	void showClicked(QListWidgetItem* item);
};

#endif // IDPOINTDLG_H
