#include "ACSaveDlg.h"
#include "ui_ACSaveDlg.h"


ACSaveDlg::ACSaveDlg(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::ACSaveDlg();
	ui->setupUi(this);
}

ACSaveDlg::~ACSaveDlg()
{
	delete ui;
}

void ACSaveDlg::on_okBtn_clicked()
{
	accept();
}

QString ACSaveDlg::getIdNumber()
{
	return ui->idEdit->text();
}

QString ACSaveDlg::getDpi()
{
	return ui->dpiEdit->text();
}