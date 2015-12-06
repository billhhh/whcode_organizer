#include "FillPointPlusDlg.h"
#include "ui_FillPointPlusDlg.h"

FillPointPlusDlg::FillPointPlusDlg(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::FillPointPlusDlg();
	ui->setupUi(this);
}

FillPointPlusDlg::~FillPointPlusDlg()
{
	delete ui;
}

