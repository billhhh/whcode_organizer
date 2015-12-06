#include "CustomizeFillPointDlg.h"
#include "ui_CustomizeFillPointDlg.h"
#include "AnswerCard.h"

CustomizeFillPointDlg::CustomizeFillPointDlg(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::CustomizeFillPointDlg();
	ui->setupUi(this);	
}

CustomizeFillPointDlg::~CustomizeFillPointDlg()
{
	delete ui;
}

void CustomizeFillPointDlg::initialization()
{
	ui->confirmBtn->setEnabled(false);
	ui->addBtn->setText(tr("添加填涂点"));
	ui->list->clear();
	this->setEnabled(false);
}

void CustomizeFillPointDlg::setAddBtnText(const QString& str)
{
	ui->addBtn->setText(str);
}

void CustomizeFillPointDlg::setConfirmBtnEnabled(bool b)
{
	ui->confirmBtn->setEnabled(b);
}

void CustomizeFillPointDlg::on_addBtn_clicked()
{
	//是否已打开图像
	if (theApp.m_group_state == 0 && theApp.m_state == 0)
	{
		QMessageBox::critical(NULL, tr("错误"),tr("请先打开图像"));
		return;
	}

	//点击完未确定状态，此时舍弃绘制重新框选
	if (theApp.m_group_state == 5 && theApp.m_state == 3)
	{
		//触发重绘
		theApp.is_synchronous = false;
		ui->addBtn->setText(tr("取消"));
		ui->confirmBtn->setEnabled(false);
		emit imageUpdated();
	}
	else if (theApp.m_group_state == 5 && theApp.m_state == 1)
	{
		theApp.m_state = 0;
		ui->confirmBtn->setEnabled(false);
		ui->addBtn->setText(tr("添加填涂点"));
		return;
	}
	else
	{
		ui->addBtn->setText(tr("取消"));
	}

	//状态控制
	theApp.m_group_state = 5;
	theApp.m_state = 1;
}

void CustomizeFillPointDlg::on_confirmBtn_clicked()
{
	//是否已打开图像
	if (theApp.m_group_state == 0 && theApp.m_state == 0)
	{
		QMessageBox::critical(NULL, tr("错误"),tr("请先打开图像"));
		return;
	}

	if (theApp.m_group_state != 5 || theApp.m_state != 3)
	{
		QMessageBox::information(NULL, tr(" "),tr("请先框选区域"));
		return;
	}

	QString type = ui->typeComboBox->currentText();
	string tmpName(type.toAscii().data());

	//判断是否存在
	int foundIdx = -1;

	for (ushort i = 0; i < theApp.cfp_group.size(); i++)
	{
		if (theApp.cfp_group[i].name == tmpName)
		{
			foundIdx = i;
		}
	}

	if (foundIdx != -1)
	{
		//已存在该组名->合并组
		if (QMessageBox::No == QMessageBox::information(NULL, 
			tr("合并到组？"), 
			tr("该组名已经存在，是否加入该组吗？"),
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::Yes))
		{
			return;
		}
		else
		{
			theApp.cfp_group[foundIdx].fillingPoints.push_back(theApp.cfp_tmpRect);

			//更新listbox
			QString itemStr;
			itemStr = QString("%1| %2个区域|")
				.arg(type).arg(theApp.cfp_group[foundIdx].fillingPoints.size());

			ui->list->takeItem(foundIdx);
			ui->list->insertItem(foundIdx, itemStr);
		}
	
	}//if (foundIdx != -1)
	else
	{
		//未存在，新组名->新建组
		CustomFillingPoints_info cfp;
		cfp.name = tmpName;
		cfp.fillingPoints.push_back(theApp.cfp_tmpRect);
		theApp.cfp_group.push_back(cfp);

		//更新listbox
		QString itemStr;
		itemStr = QString("%1| %2个区域|")
			.arg(type).arg(cfp.fillingPoints.size());

		ui->list->addItem(itemStr);
	}//else if(foundIdx == -1)

	//状态控制
	theApp.m_group_state = 5;
	theApp.m_state = 5;

	//界面控制
	ui->addBtn->setText(tr("添加填涂点"));
	ui->confirmBtn->setEnabled(false);
}

void CustomizeFillPointDlg::on_deleteBtn_clicked()
{
	//界面控制
	int idx = ui->list->currentRow();

	if (idx > -1)
	{
		ui->list->takeItem(idx);
		theApp.cfp_group.erase(theApp.cfp_group.begin()+idx);

		//触发重绘
		theApp.is_synchronous = false;
		emit imageUpdated();
	}
}