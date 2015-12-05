#ifndef IDPOINTDLG_H
#define IDPOINTDLG_H

#include <QDialog>
#include "qlistwidget.h"
#include "AnswerCard.h"
namespace Ui {class IdPointDlg;};

class IdPointDlg : public QDialog
{
	Q_OBJECT

public:
	IdPointDlg(QWidget *parent = 0);
	~IdPointDlg();

	void setAddBtnText(const QString& str);
	void setConfirmBtnEnabled(bool);

	void initialization();

	int resume();

private:
	void setProcessing(bool);
	Ui::IdPointDlg *ui;

signals:
	void idPointBegin();
	void idPointDone();
	void idPointDelete();
	void idPointClicked(int);

protected slots:
	void on_addBtn_clicked();
	void on_confirmBtn_clicked();
	void on_deleteBtn_clicked();
	void showClicked(QListWidgetItem* item);
};

#endif // IDPOINTDLG_H
