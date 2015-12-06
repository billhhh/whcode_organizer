#include "ClearDlg.h"
#include "ui_ClearDlg.h"

ClearDlg::ClearDlg(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::ClearDlg();
	ui->setupUi(this);
}

ClearDlg::~ClearDlg()
{
	delete ui;
}

void ClearDlg::on_clearBtn_clicked()
{
	emit clearCard();
}

void ClearDlg::on_changePicBtn_clicked()
{
	emit changePic();
}