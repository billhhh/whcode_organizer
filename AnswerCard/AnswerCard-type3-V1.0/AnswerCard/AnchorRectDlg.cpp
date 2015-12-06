#include "AnchorRectDlg.h"
#include "ui_AnchorRectDlg.h"
#include "AnswerCard.h"

AnchorRectDlg::AnchorRectDlg(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::AnchorRectDlg();
	ui->setupUi(this);
}

AnchorRectDlg::~AnchorRectDlg()
{
	delete ui;
}

void AnchorRectDlg::initialization()
{
	m_done = false;
	this->setEnabled(false);
	ui->anchorBtn->setText(tr("框选定位框"));
}

void AnchorRectDlg::setAnchorBtnText(QString str)
{
	ui->anchorBtn->setText(str);
}

void AnchorRectDlg::on_anchorBtn_clicked()
{
	if (theApp.anchorRect.width > 0)
	{
		if (QMessageBox::No == QMessageBox::information(this, 
				tr(" "), 
				tr("定位框已经存在，是否覆盖原来框选？"),
				QMessageBox::Yes | QMessageBox::No,
				QMessageBox::Yes))
		{
			return;
		}

		theApp.anchorRect = cv::Rect();
		theApp.anchor_type = 0;
		m_done = false;

		//触发重绘
		theApp.is_synchronous = false;
	}

	if (theApp.m_group_state == AnchorRectState && theApp.m_state == BaseBegin)
	{
		theApp.m_state = BaseInitial;
		ui->anchorBtn->setText(tr("框选定位框"));
		return;
	}

	ui->anchorBtn->setText(tr("取消"));

	//状态控制
	theApp.m_group_state = AnchorRectState;
	theApp.m_state = BaseBegin;
}

void AnchorRectDlg::on_confirmBtn_clicked()
{
	if (theApp.anchorRect.width <= 0)
	{
		QMessageBox::information(this, " ",
			tr("请框选定位框!"));
	}

	Mat tmp;
	double angle;
	Point point;
	cv::Rect rect = theApp.anchorRect;
	theApp.anchor_type = TiltCorrection(theApp.img_raw, tmp, rect, point, angle);

	theApp.anchorRect=rect;
	theApp.originalPoint = point;
	if (theApp.anchor_type < 0)
	{
		theApp.anchor_type = 0;
		QMessageBox::information(this, " ",
			tr("倾斜校正失败!"));

		return;
	}

	theApp.img_raw = tmp;

	//重新计算灰度图像及二值图像
	cvtColor(theApp.img_raw, theApp.img_gray, CV_RGB2GRAY);
	threshold(theApp.img_gray, theApp.img_bw, 128, 255, THRESH_BINARY_INV);

	//for (int i=0; i < 4; i++)
	//{
	//	if (theApp.anchorPoints[i].width != 0)
	//	{
	//		theApp.GetArchorPointRect(
	//			QPoint(theApp.anchorPoints[i].x + theApp.anchorPoints[i].width / 2,
	//			theApp.anchorPoints[i].y + theApp.anchorPoints[i].height / 2), i);
	//	}
	//}

	theApp.is_synchronous =false;
	theApp.m_state = BaseEnd;
	m_done = true;
	emit anchorDone();
}

int AnchorRectDlg::resume()
{
	if (theApp.anchorRect.width > 0)
	{
		ui->anchorBtn->setText(tr("重新框选定位框"));
	}
	else
	{
		ui->anchorBtn->setText(tr("框选定位框"));
	}

	//if (theApp.anchor_type <= 0)
	//{
	//	theApp.anchor_type = 0;
	//	return -1;
	//}
	

	return 1;
}