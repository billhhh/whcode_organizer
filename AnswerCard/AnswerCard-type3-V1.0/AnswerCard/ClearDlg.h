#ifndef CLEARDLG_H
#define CLEARDLG_H

#include <QDialog>
namespace Ui {class ClearDlg;};

class ClearDlg : public QDialog
{
	Q_OBJECT

public:
	ClearDlg(QWidget *parent = 0);
	~ClearDlg();

private:
	Ui::ClearDlg *ui;
signals:
	void changePic();
	void clearCard();

protected slots:
	void on_clearBtn_clicked();
	void on_changePicBtn_clicked();
};

#endif // CLEARDLG_H
