#include "BlackLineDetectDlg.h"
#include "ui_BlackLineDetectDlg.h"
#include "AnswerCardDlg.h"

BlackLineDetectDlg::BlackLineDetectDlg(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::BlackLineDetectDlg();
	ui->setupUi(this);
}

BlackLineDetectDlg::~BlackLineDetectDlg()
{
	delete ui;
}

void BlackLineDetectDlg::initialization()
{
	ui->confirmBtn->setEnabled(false);
	ui->addBtn->setText(tr("添加"));
	ui->list->clear();
	ui->nameEdit->clear();
	this->setEnabled(false);
}

void BlackLineDetectDlg::setProcessing(bool b)
{
	ui->nameEdit->setEnabled(!b);
	ui->deleteBtn->setEnabled(!b);
}

void BlackLineDetectDlg::setAddBtnText(const QString& str)
{
	ui->addBtn->setText(str);
}

void BlackLineDetectDlg::setConfirmBtnEnabled(bool b)
{
	ui->confirmBtn->setEnabled(b);
}

void BlackLineDetectDlg::on_addBtn_clicked()
{
	//点击完未确定状态，此时舍弃绘制重新框选
	if (theApp.m_group_state == BlackLineState && theApp.m_state == BaseRelease)
	{
		//触发重绘
		theApp.is_synchronous = false;
		ui->addBtn->setText(tr("取消"));
		ui->confirmBtn->setEnabled(false);
	}
	else if (theApp.m_group_state == BlackLineState && theApp.m_state == BaseBegin)
	{
		theApp.m_state = BaseInitial;
		ui->confirmBtn->setEnabled(false);
		ui->nameEdit->setEnabled(true);
		setProcessing(false);
		ui->addBtn->setText(tr("添加"));
		emit BlackLineDone();
		return;
	}
	else
	{
		QString name = ui->nameEdit->text();

		//判断是否存在
		int foundIdx = -1;

		for (ushort i = 0; i < theApp.blackLineGroup.size(); i++)
		{
			if (theApp.blackLineGroup[i].name == name.toStdString())
			{
				foundIdx = i;
			}
		}

		if (foundIdx != -1)
		{
			//已存在该名字
			QMessageBox::information(this, 
				tr("重名"), 
				tr("该名称已存在！"));
			return;
		}

		ui->addBtn->setText(tr("取消"));
		ui->nameEdit->setEnabled(false);
		setProcessing(true);
		emit BlackLinebegin();
	}

	//状态控制
	theApp.m_group_state = BlackLineState;
	theApp.m_state = BaseBegin;
}

void BlackLineDetectDlg::on_confirmBtn_clicked()
{
	if (theApp.m_group_state != BlackLineState || theApp.m_state != BaseRelease)
	{
		QMessageBox::information(this, tr(" "),tr("名称不能为空"));
		return;
	}

	QString name = ui->nameEdit->text();
	
	BlackLine_info info;
	info.name = name.toStdString();
	info.pos = cv::Rect(theApp.cfp_tmpRect);
	theApp.blackLineGroup.push_back(info);

	//更新listbox
	QString itemStr;
	itemStr = QString("%1").arg(name);
	ui->list->addItem(itemStr);

	//状态控制
	theApp.m_group_state = BlackLineState;
	theApp.m_state = BaseEnd;

	//界面控制
	ui->addBtn->setText(tr("添加"));
	ui->confirmBtn->setEnabled(false);
	ui->nameEdit->setEnabled(true);
	setProcessing(false);

	emit BlackLineDone();
}

void BlackLineDetectDlg::on_deleteBtn_clicked()
{
	//界面控制
	int idx = ui->list->currentRow();

	if (idx > -1)
	{
		ui->list->takeItem(idx);
		theApp.blackLineGroup.erase(theApp.blackLineGroup.begin() + idx);

		//触发重绘
		theApp.is_synchronous = false;
		emit BlackLineDelete();
	}
}