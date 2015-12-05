#include "LineDetectDlg.h"
#include "ui_LineDetectDlg.h"
#include "AnswerCard.h"
#include "qmessagebox.h"

LineDetectDlg::LineDetectDlg(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::LineDetectDlg();
	ui->setupUi(this);
}

LineDetectDlg::~LineDetectDlg()
{
	delete ui;
}

void LineDetectDlg::setWhiteLineBtnText(const QString& str)
{
	ui->whiteLineBtn->setText(str);
}

void LineDetectDlg::setBlackLineBtnText(const QString& str)
{
	ui->blackLineBtn->setText(str);
}

void LineDetectDlg::initialization()
{
	setProcessing(false);
	this->setEnabled(false);
	ui->whiteLineBtn->setText(tr("框选白检测线"));
	ui->blackLineBtn->setText(tr("框选黑检测线"));
}

void LineDetectDlg::setProcessing(bool b)
{
	ui->whiteLineBtn->setEnabled(!b);
	ui->blackLineBtn->setEnabled(!b);
}

void LineDetectDlg::on_blackLineBtn_clicked()
{
	if (theApp.blackLineRect.width > 0)
	{
		if (QMessageBox::No == QMessageBox::information(this, 
				tr(" "), 
				tr("黑检测线已经存在，是否覆盖原来框选？"),
				QMessageBox::Yes | QMessageBox::No,
				QMessageBox::Yes))
		{
			return;
		}

		theApp.blackLineRect = cv::Rect();

		//触发重绘
		theApp.is_synchronous = false;
	}

	if (theApp.m_group_state == BlackLineState && theApp.m_state == BaseBegin)
	{
		theApp.m_state = BaseInitial;
		ui->blackLineBtn->setText(tr("框选黑检测线"));
		setProcessing(false);
		emit lineDone();
		return;
	}

	setProcessing(true);
	ui->blackLineBtn->setEnabled(true);
	ui->blackLineBtn->setText(tr("取消"));

	//状态控制
	theApp.m_group_state = BlackLineState;
	theApp.m_state = BaseBegin;
	
	emit lineBegin();
}

void LineDetectDlg::on_whiteLineBtn_clicked()
{
	if (theApp.whiteLineRect.width > 0)
	{
		if (QMessageBox::No == QMessageBox::information(this, 
				tr(" "), 
				tr("白检测线已经存在，是否覆盖原来框选？"),
				QMessageBox::Yes | QMessageBox::No,
				QMessageBox::Yes))
		{
			return;
		}

		theApp.whiteLineRect = cv::Rect();

		//触发重绘
		theApp.is_synchronous = false;
	}

	if (theApp.m_group_state == WhiteLineState && theApp.m_state == BaseBegin)
	{
		theApp.m_state = BaseInitial;
		ui->whiteLineBtn->setText(tr("框选白检测线"));
		setProcessing(false);
		emit lineDone();
		return;
	}

	setProcessing(true);
	ui->whiteLineBtn->setEnabled(true);
	ui->whiteLineBtn->setText(tr("取消"));

	//状态控制
	theApp.m_group_state = WhiteLineState;
	theApp.m_state = BaseBegin;
	
	emit lineBegin();
}

void LineDetectDlg::resume()
{
	if (theApp.whiteLineRect.width > 0)
	{
		ui->whiteLineBtn->setText(tr("重新框选白检测线"));
	}

	if (theApp.blackLineRect.width > 0)
	{
		ui->blackLineBtn->setText(tr("重新框选黑检测线"));
	}
}