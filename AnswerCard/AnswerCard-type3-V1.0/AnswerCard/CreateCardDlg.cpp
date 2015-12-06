#include "CreateCardDlg.h"
#include "ui_CreateCardDlg.h"
#include "qmessagebox.h"

CreateCardDlg::CreateCardDlg(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::CreateCardDlg();
	ui->setupUi(this);

	QRegExp reg("[1-9][0-9][0-9][0-9][0-9][0-9] + $");
	QRegExpValidator *validator = new QRegExpValidator(reg);
	ui->dpiEdit->setValidator(validator);
}

CreateCardDlg::~CreateCardDlg()
{
	delete ui;
}

int CreateCardDlg::getDpi()
{
	return ui->dpiEdit->text().toInt();
}

void CreateCardDlg::on_okBtn_clicked()
{
	if (ui->dpiEdit->text() == "")
	{
		QMessageBox::information(this," ","dpi²»ÄÜÎª¿Õ");
		return;
	}
	accept();
}