#ifndef ACSAVEDLG_H
#define ACSAVEDLG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
namespace Ui {class ACSaveDlg;};

class ACSaveDlg : public QDialog
{
	Q_OBJECT

public:
	ACSaveDlg(QWidget *parent = 0);
	~ACSaveDlg();

private:
	Ui::ACSaveDlg *ui;

protected slots:
	void on_okBtn_clicked();
};

#endif // ACSAVEDLG_H
