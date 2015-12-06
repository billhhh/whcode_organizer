#include "ClipDlg.h"
#include "ui_ClipDlg.h"
#include "AnswerCard.h"

ClipDlg::ClipDlg(QWidget *parent)
	: QDialog(parent),
	isSecretClicked(false)
{
	ui = new Ui::ClipDlg();
	ui->setupUi(this);
	connect(ui->clipList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(showClicked(QListWidgetItem*)));
}

ClipDlg::~ClipDlg()
{
	delete ui;
}

//初始化裁切对话框中的控件
void ClipDlg::initialization()
{
	setProcessing(false);
	isSecretClicked = false;
	ui->cropAreaEdit->clear();
	ui->addBtn->setText(tr("添加裁切区域"));
	ui->secretCheckBox->setChecked(false);
	ui->confirmBtn->setEnabled(false);
	ui->clipList->clear();
	ui->groupEdit->setText("0");
	this->setEnabled(false);
}

//设置裁切是否在执行中
void ClipDlg::setProcessing(bool b)
{
	ui->cropAreaEdit->setEnabled(!b);
	ui->groupEdit->setEnabled(!b);
	ui->secretCheckBox->setEnabled(!b);
	ui->deleteBtn->setEnabled(!b);
	ui->clipList->setEnabled(!b);
}

void ClipDlg::setConfirmBtnEnabled(bool b)
{
	ui->confirmBtn->setEnabled(b);
}

//添加裁切区域
void ClipDlg::on_addBtn_clicked()
{
	if (ui->cropAreaEdit->text() == "")
	{
		QMessageBox::information(NULL, tr(" "),tr("请输入裁切名"));
		return;
	}

	//放弃已绘制的区域
	if (theApp.m_group_state == ClipState 
		&& (theApp.m_state == BaseBegin || theApp.m_state == BaseRelease))
	{
		//触发重绘
		theApp.is_synchronous = false;
		ui->addBtn->setText(tr("添加裁切区域"));
		ui->confirmBtn->setEnabled(false);
		theApp.m_state = BaseInitial;

		setProcessing(false);
		emit clipDone();
		return;
	}
	else
	{
		//判断是否存在
		int foundIdx = -1;
		string name = ui->cropAreaEdit->text().toAscii().data();

		for (ushort i = 0; i < theApp.cropAreas.size(); i++)
		{
			if (theApp.cropAreas[i].name == name)
			{
				foundIdx = i;
			}
		}

		if (foundIdx != -1)
		{
			QMessageBox::information(this, 
				tr("重名"), 
				tr("裁切名字已存在！"));
			return;
		}

		ui->addBtn->setText(tr("取消"));
		setProcessing(true);
		emit clipBegin();
	}

	//状态控制
	theApp.m_group_state = ClipState;
	theApp.m_state = BaseBegin;
}

//确认裁切区域
void ClipDlg::on_confirmBtn_clicked()
{
	if (theApp.m_group_state != ClipState || theApp.m_state != BaseRelease)
	{
		QMessageBox::information(NULL, tr(" "),tr("请先框选区域"));
		return;
	}

	CropArea_info area;
	string clipName(ui->cropAreaEdit->text().toAscii().data());
	area.name = clipName;
	area.pos = cv::Rect(theApp.cfp_tmpRect);

	if (ui->groupEdit->text() == "")
	{
		area.groupNum = 0;
	}
	else
	{
		area.groupNum = ui->groupEdit->text().toInt();
	}

	area.isSecret = isSecretClicked;
	theApp.cropAreas.push_back(area);

	QString secretChoice;

	if (isSecretClicked)
	{
		secretChoice = QString(tr("保密"));
	}
	else
	{
		secretChoice = QString(tr("公开"));
	}

	//更新listbox
	QString itemStr;
	if (area.groupNum > 0)
	{
		itemStr = QString("%1| %2组| %3|")
			.arg(ui->cropAreaEdit->text())
			.arg(area.groupNum)
			.arg(secretChoice);
	}
	else
	{
		itemStr = QString("%1| 不分组| %2|")
			.arg(ui->cropAreaEdit->text())
			.arg(secretChoice);
	}

	ui->clipList->addItem(itemStr);

	//状态控制
	theApp.m_group_state = ClipState;
	theApp.m_state = BaseEnd;

	//界面控制
	ui->addBtn->setText(tr("添加裁切区域"));
	theApp.is_synchronous = false;
	setProcessing(false);
	ui->confirmBtn->setEnabled(false);

	//发送信号
	emit clipDone();
}

void ClipDlg::on_deleteBtn_clicked()
{
	int idx = ui->clipList->currentRow();

	if (idx > -1)
	{
		ui->clipList->takeItem(idx);
		theApp.cropAreas.erase(theApp.cropAreas.begin()+idx);
		theApp.is_synchronous = false;
		emit clipDelete();
	}
}

void ClipDlg::showClicked(QListWidgetItem* item)
{
	int idx = ui->clipList->currentRow();

	if (idx > -1)
	{
		theApp.is_synchronous = false;
		theApp.Redraw3();

		rectangle(theApp.img_show, theApp.cropAreas[idx].pos, 
			theApp.cropAreaClicked_color, theApp.cropAreaClicked_thickness);

		theApp.m_group_state = ClipState;
		theApp.m_state = BaseEnd;
		emit clipClicked(idx);
	}
}

void ClipDlg::on_secretCheckBox_toggled()
{
	if (ui->secretCheckBox->isChecked())
	{
		isSecretClicked  = true;
	}
	else
	{
		isSecretClicked  = false;
	}
}

int ClipDlg::resume()
{
	initialization();

	if (theApp.cropAreas.size() > 0)
	{
		vector<CropArea_info>::iterator iter;
		for (iter = theApp.cropAreas.begin(); 
			iter != theApp.cropAreas.end(); ++iter)
		{
			QString secret;
			if (iter->isSecret)
			{
				secret = QString(tr("保密"));
			}
			else
			{
				secret = QString(tr("公开"));
			}

			QString itemStr;
			if (iter->groupNum > 0)
			{
				itemStr = QString("%1| %2组| %3|")
					.arg(QString::fromLocal8Bit((iter->name).c_str()))
					.arg(iter->groupNum)
					.arg(secret);
			}
			else
			{
				itemStr = QString("%1| 不分组| %2|")
					.arg(QString::fromLocal8Bit((iter->name).c_str()))
					.arg(secret);
			}

			ui->clipList->addItem(itemStr);
		}

		return 1;
	}

	return -1;
}