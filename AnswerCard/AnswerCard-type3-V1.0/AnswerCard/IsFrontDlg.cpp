#include "IsFrontDlg.h"
#include "ui_IsFrontDlg.h"
#include "AnswerCard.h"

IsFrontDlg::IsFrontDlg(QWidget *parent)
	: QDialog(parent),m_currentIndex(0)
{
	ui = new Ui::IsFrontDlg();
	ui->setupUi(this);
}

IsFrontDlg::~IsFrontDlg()
{
	delete ui;
}

void IsFrontDlg::initialization()
{
	this->setEnabled(false);
}

void IsFrontDlg::setCurrentIndex(int idx)
{
	ui->typeCbx->setCurrentIndex(idx);
}

void IsFrontDlg::on_typeCbx_currentIndexChanged(QString str)
{
	if (str == tr("ÕıÃæ"))
	{
		emit indexChanged(0);
		m_currentIndex = 0;
	}
	else
	{
		emit indexChanged(1);
		m_currentIndex = 1;
	}
}

void IsFrontDlg::resume()
{
	if (theApp.m_isFront)
	{
		ui->typeCbx->setCurrentIndex(0);
	}
	else
	{
		ui->typeCbx->setCurrentIndex(1);
	}
}