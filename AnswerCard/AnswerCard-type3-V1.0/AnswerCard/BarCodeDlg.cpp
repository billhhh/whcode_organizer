#include "BarCodeDlg.h"
#include "ui_BarCodeDlg.h"
#include "AnswerCardDlg3.h"

BarCodeDlg::BarCodeDlg(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::BarCodeDlg();
	ui->setupUi(this);
	connect(ui->codebarList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(showClicked(QListWidgetItem*)));
}

BarCodeDlg::~BarCodeDlg()
{
	delete ui;
}

void BarCodeDlg::initialization()
{
	setProcessing(false);
	ui->codebarList->clear();
	ui->confirmBtn->setEnabled(false);
	ui->addBtn->setText(tr("框选条形码"));
	this->setEnabled(false);
}

void BarCodeDlg::setProcessing(bool b)
{
	ui->typeCmb->setEnabled(!b);
	ui->deleteBtn->setEnabled(!b);
	ui->codebarList->setEnabled(!b);
}

void BarCodeDlg::setAddBtnText(const QString& str)
{
	ui->addBtn->setText(str);
}

void BarCodeDlg::setConfirmBtnEnabled(bool b)
{
	ui->confirmBtn->setEnabled(b);
}

void BarCodeDlg::on_addBtn_clicked()
{
	//点击完未确定状态，此时舍弃绘制重新框选
	if (theApp.m_group_state == BarCodeState && theApp.m_state == BaseRelease)
	{
		//触发重绘
		theApp.is_synchronous = false;
		ui->addBtn->setText(tr("取消"));
		ui->confirmBtn->setEnabled(false);
	}
	else if (theApp.m_group_state == BarCodeState && theApp.m_state == BaseBegin)
	{
		theApp.m_state = BaseInitial;
		ui->confirmBtn->setEnabled(false);
		ui->typeCmb->setEnabled(true);
		setProcessing(false);
		ui->addBtn->setText(tr("框选条形码"));
		emit barCodeDone();
		return;
	}
	else
	{
		int type = ui->typeCmb->currentIndex();

		//判断是否存在
		int foundIdx = -1;

		for (ushort i = 0; i < theApp.barGroup.size(); i++)
		{
			if (theApp.barGroup[i].barType == type)
			{
				foundIdx = i;
			}
		}

		if (foundIdx != -1)
		{
			//已存在该组条形码
			if (QMessageBox::No == QMessageBox::information(NULL, 
				tr("条形码存在"), 
				tr("该类型条形码已经存在，是否覆盖原来选择？"),
				QMessageBox::Yes | QMessageBox::No,
				QMessageBox::Yes))
			{
				return;
			}
			else
			{
				ui->codebarList->takeItem(foundIdx);
				theApp.barGroup.erase(theApp.barGroup.begin() + foundIdx);

				//触发重绘
				theApp.is_synchronous = false;
			}
		}
		ui->addBtn->setText(tr("取消"));
		ui->typeCmb->setEnabled(false);
		setProcessing(true);
		emit barCodeBegin();
	}

	//状态控制
	theApp.m_group_state = BarCodeState;
	theApp.m_state = BaseBegin;
}

void BarCodeDlg::on_confirmBtn_clicked()
{
	if (theApp.m_group_state != BarCodeState || theApp.m_state != BaseRelease)
	{
		QMessageBox::information(NULL, tr(" "),tr("请先框选条形码"));
		return;
	}

	int type = ui->typeCmb->currentIndex();
	QString name = ui->typeCmb->currentText();
	
	Bar_info bar;
	bar.barType = (BarType)type;
	bar.pos = cv::Rect(theApp.cfp_tmpRect);
	theApp.barGroup.push_back(bar);

	//更新listbox
	QString itemStr;
	itemStr = QString("%1").arg(name);
	ui->codebarList->addItem(itemStr);

	//状态控制
	theApp.m_group_state = BarCodeState;
	theApp.m_state = BaseEnd;

	//界面控制
	ui->addBtn->setText(tr("框选条形码"));
	ui->confirmBtn->setEnabled(false);
	ui->typeCmb->setEnabled(true);
	theApp.is_synchronous = false;
	setProcessing(false);

	emit barCodeDone();
}

void BarCodeDlg::on_deleteBtn_clicked()
{
	//界面控制
	int idx = ui->codebarList->currentRow();

	if (idx > -1)
	{
		ui->codebarList->takeItem(idx);
		theApp.barGroup.erase(theApp.barGroup.begin() + idx);

		//触发重绘
		theApp.is_synchronous = false;
		emit barCodeDelete();
	}
}

void BarCodeDlg::showClicked(QListWidgetItem* item)
{
	int idx = ui->codebarList->currentRow();

	if (idx > -1)
	{
		theApp.is_synchronous = false;
		theApp.Redraw3();

		rectangle(theApp.img_show, theApp.barGroup[idx].pos, 
			theApp.barcodeClicked_color, theApp.barcodeClicked_thickness);

		theApp.m_group_state = BarCodeState;
		theApp.m_state = BaseEnd;
		emit barCodeClicked(idx);
	}
}

int BarCodeDlg::resume()
{
	initialization();

	if (theApp.barGroup.size() > 0)
	{
		vector<Bar_info>::iterator iter;
		for (iter = theApp.barGroup.begin(); 
			iter != theApp.barGroup.end(); ++iter)
		{
			QString str = ui->typeCmb->itemText((int)(iter->barType));
			QString itemStr;
			itemStr = QString("%1").arg(str);
			ui->codebarList->addItem(itemStr);
		}

		return 1;
	}

	return -1;
}