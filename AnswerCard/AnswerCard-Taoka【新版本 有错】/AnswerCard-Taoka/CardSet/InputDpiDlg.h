#ifndef INPUTDPIDLG_H
#define INPUTDPIDLG_H

#include <QDialog>
namespace Ui {class InputDpiDlg;};

class InputDpiDlg : public QDialog
{
	Q_OBJECT

public:
	InputDpiDlg(QWidget *parent = 0);
	~InputDpiDlg();

	int getDpi();
private:
	Ui::InputDpiDlg *ui;

protected slots:
	void on_okBtn_clicked();
	//void on_cancelBtn_clicked();
};

#endif // INPUTDPIDLG_H
