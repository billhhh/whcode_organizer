#include "PagePointDlg.h"
#include "ui_PagePointDlg.h"

PagePointDlg::PagePointDlg(QWidget *parent)
	: QDialog(parent),index(1)
{
	ui = new Ui::PagePointDlg();
	ui->setupUi(this);

	connect(ui->idPointList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(showClicked(QListWidgetItem*)));
}

PagePointDlg::~PagePointDlg()
{
	delete ui;
}

void PagePointDlg::initialization()
{
	setProcessing(false);
	ui->idPointList->clear();
	ui->confirmBtn->setEnabled(false);
	ui->addBtn->setText(tr("添加页码标识"));
	this->setEnabled(false);
}

void PagePointDlg::setProcessing(bool b)
{
	ui->idPointList->setEnabled(!b);
	ui->deleteBtn->setEnabled(!b);
}

void PagePointDlg::setAddBtnText(const QString& str)
{
	ui->addBtn->setText(str);
}

void PagePointDlg::setConfirmBtnEnabled(bool b)
{
	ui->confirmBtn->setEnabled(b);
}

void PagePointDlg::on_addBtn_clicked()
{
		//点击完未确定状态，此时舍弃绘制重新框选
	if (theApp.m_group_state == PagePointState && theApp.m_state == BaseRelease)
	{
		theApp.pagePoint.pop_back();

		//触发重绘
		theApp.is_synchronous = false;
		ui->addBtn->setText(tr("取消"));
		ui->confirmBtn->setEnabled(false);
	}
	else if (theApp.m_group_state == PagePointState && theApp.m_state == BaseBegin)
	{
		theApp.m_state = BaseInitial;
		ui->confirmBtn->setEnabled(false);
		setProcessing(false);
		ui->addBtn->setText(tr("添加页码标识"));
		emit pagePointDone();
		return;
	}
	else
	{

		ui->addBtn->setText(tr("取消"));
		setProcessing(true);
		emit pagePointBegin();
	}

	//状态控制
	theApp.m_group_state = PagePointState;
	theApp.m_state = BaseBegin;
}

void PagePointDlg::on_confirmBtn_clicked()
{
	//状态控制
	theApp.m_group_state = PagePointState;
	theApp.m_state = BaseEnd;


	//更新listbox
	QString itemStr;
	itemStr = QString("页码标识%1").arg(index++);
	ui->idPointList->addItem(itemStr);

	//界面控制
	ui->addBtn->setText(tr("添加页码标识"));
	ui->confirmBtn->setEnabled(false);
	setProcessing(false);

	emit pagePointDone();
}

void PagePointDlg::on_deleteBtn_clicked()
{
	//界面控制
	int idx = ui->idPointList->currentRow();

	if (idx > -1)
	{
		ui->idPointList->takeItem(idx);
		theApp.pagePoint.erase(theApp.pagePoint.begin() + idx);

		//触发重绘
		theApp.is_synchronous = false;
		emit pagePointDelete();
	}
}

void PagePointDlg::showClicked(QListWidgetItem* item)
{
	int idx = ui->idPointList->currentRow();

	if (idx > -1)
	{
		theApp.is_synchronous = false;
		theApp.Redraw3();

		vector<cv::Rect>::iterator iter= theApp.pagePoint.begin() + idx;

		rectangle(theApp.img_show,*iter,theApp.pagePointClicked_color,theApp.pagePointClicked_thickness);

		emit pagePointClicked(idx);
	}
}

int PagePointDlg::resume()
{
	initialization();
	index=1;
	vector<cv::Rect>::iterator iter;
	for (iter = theApp.pagePoint.begin(); 
			iter != theApp.pagePoint.end(); ++iter)
	{
		//更新listbox
		QString itemStr;
		itemStr = QString("页码标识%1").arg(index++);
		ui->idPointList->addItem(itemStr);
	}

	return 1;
}