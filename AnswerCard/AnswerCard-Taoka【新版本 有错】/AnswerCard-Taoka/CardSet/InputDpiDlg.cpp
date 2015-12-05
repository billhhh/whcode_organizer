#include "InputDpiDlg.h"
#include "ui_InputDpiDlg.h"
#include "qmessagebox.h"

InputDpiDlg::InputDpiDlg(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::InputDpiDlg();
	ui->setupUi(this);
}

InputDpiDlg::~InputDpiDlg()
{
	delete ui;
}

int InputDpiDlg::getDpi()
{
	return ui->dpiEdit->text().toInt();
}

void InputDpiDlg::on_okBtn_clicked()
{
	if (ui->dpiEdit->text() == "")
	{
		QMessageBox::information(this," ","输入不能为空!");
	}

	accept();
}