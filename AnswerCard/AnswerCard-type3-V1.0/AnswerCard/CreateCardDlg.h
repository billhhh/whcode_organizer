#ifndef CREATECARDDLG_H
#define CREATECARDDLG_H

#include <QDialog>
namespace Ui {class CreateCardDlg;};

class CreateCardDlg : public QDialog
{
	Q_OBJECT

public:
	CreateCardDlg(QWidget *parent = 0);
	~CreateCardDlg();
	int getDpi();
private:
	Ui::CreateCardDlg *ui;

protected slots:
	void on_okBtn_clicked();
};

#endif // CREATECARDDLG_H
