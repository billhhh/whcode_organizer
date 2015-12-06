#include "WhiteDetectLineDlg.h"
#include "ui_WhiteDetectLineDlg.h"
#include "AnswerCardDlg.h"

WhiteDetectLineDlg::WhiteDetectLineDlg(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::WhiteDetectLineDlg();
	ui->setupUi(this);
}

WhiteDetectLineDlg::~WhiteDetectLineDlg()
{
	delete ui;
}

void WhiteDetectLineDlg::initialization()
{
	ui->confirmBtn->setEnabled(false);
	ui->addBtn->setText(tr("添加"));
	ui->list->clear();
	ui->nameEdit->clear();
	this->setEnabled(false);
}

void WhiteDetectLineDlg::setProcessing(bool b)
{
	ui->nameEdit->setEnabled(!b);
	ui->deleteBtn->setEnabled(!b);
}

void WhiteDetectLineDlg::setAddBtnText(const QString& str)
{
	ui->addBtn->setText(str);
}

void WhiteDetectLineDlg::setConfirmBtnEnabled(bool b)
{
	ui->confirmBtn->setEnabled(b);
}

void WhiteDetectLineDlg::on_addBtn_clicked()
{
	//点击完未确定状态，此时舍弃绘制重新框选
	if (theApp.m_group_state == WhiteLineState && theApp.m_state == BaseRelease)
	{
		//触发重绘
		theApp.is_synchronous = false;
		ui->addBtn->setText(tr("取消"));
		ui->confirmBtn->setEnabled(false);
	}
	else if (theApp.m_group_state == WhiteLineState && theApp.m_state == BaseBegin)
	{
		theApp.m_state = BaseInitial;
		ui->confirmBtn->setEnabled(false);
		ui->nameEdit->setEnabled(true);
		setProcessing(false);
		ui->addBtn->setText(tr("添加"));
		emit whiteLineDone();
		return;
	}
	else
	{
		QString name = ui->nameEdit->text();

		//判断是否存在
		int foundIdx = -1;

		for (ushort i = 0; i < theApp.whiteLineGroup.size(); i++)
		{
			if (theApp.whiteLineGroup[i].name == name.toStdString())
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
		emit whiteLinebegin();
	}

	//状态控制
	theApp.m_group_state = WhiteLineState;
	theApp.m_state = BaseBegin;
}

void WhiteDetectLineDlg::on_confirmBtn_clicked()
{
	if (theApp.m_group_state != WhiteLineState || theApp.m_state != BaseRelease)
	{
		QMessageBox::information(this, tr(" "),tr("名称不能为空"));
		return;
	}

	QString name = ui->nameEdit->text();
	
	WhiteLine_info info;
	info.name = name.toStdString();
	info.pos = cv::Rect(theApp.cfp_tmpRect);
	theApp.whiteLineGroup.push_back(info);

	//更新listbox
	QString itemStr;
	itemStr = QString("%1").arg(name);
	ui->list->addItem(itemStr);

	//状态控制
	theApp.m_group_state = WhiteLineState;
	theApp.m_state = BaseEnd;

	//界面控制
	ui->addBtn->setText(tr("添加"));
	ui->confirmBtn->setEnabled(false);
	ui->nameEdit->setEnabled(true);
	setProcessing(false);

	emit whiteLineDone();
}

void WhiteDetectLineDlg::on_deleteBtn_clicked()
{
	//界面控制
	int idx = ui->list->currentRow();

	if (idx > -1)
	{
		ui->list->takeItem(idx);
		theApp.whiteLineGroup.erase(theApp.whiteLineGroup.begin() + idx);

		//触发重绘
		theApp.is_synchronous = false;
		emit whiteLineDelete();
	}
}