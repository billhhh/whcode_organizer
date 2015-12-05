#include "AnchorDlg.h"
#include "AnswerCard.h"
#include "ui_AnchorDlg.h"

AnchorDlg::AnchorDlg(QWidget *parent)
	: QDialog(parent),done(false)
{
	ui = new Ui::AnchorDlg();
	ui->setupUi(this);
}

AnchorDlg::~AnchorDlg()
{
	delete ui;
}

void AnchorDlg::initialization()
{
	done = false;
	this->setEnabled(false);
}

void AnchorDlg::on_anchorLTBtn_clicked()
{
	//已经点击过？询问覆盖
	if (theApp.anchorPoints[0].width>0)
	{
		if (QMessageBox::No == QMessageBox::information(NULL, 
			tr("重新选择"), 
			tr("已经点选左上角定位点，继续操作将覆盖原来选择\n确定要继续吗？"),
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::Yes))
		{
			return;
		}
		else
		{
			theApp.is_synchronous =false;
			theApp.anchorPoints[0] = cv::Rect();
			done = false;
		}
	}

	theApp.m_group_state = AnchorState;
	theApp.m_state = LTBegin;
}

void AnchorDlg::on_anchorRTBtn_clicked()
{
	//已经点击过？询问覆盖
	if (theApp.anchorPoints[1].width>0)
	{
		if (QMessageBox::No == QMessageBox::information(NULL, 
			tr("重新选择"), 
			tr("已经点选左上角定位点，继续操作将覆盖原来选择\n确定要继续吗？"),
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::Yes))
		{
			return;
		}
		else
		{
			theApp.is_synchronous =false;
			theApp.anchorPoints[1] = cv::Rect();
			done = false;
		}
	}

	theApp.m_group_state = AnchorState;
	theApp.m_state = RTBegin;
}

void AnchorDlg::on_anchorLBBtn_clicked()
{
	//已经点击过？询问覆盖
	if (theApp.anchorPoints[2].width>0)
	{
		if (QMessageBox::No == QMessageBox::information(NULL, 
			tr("重新选择"), 
			tr("已经点选左上角定位点，继续操作将覆盖原来选择\n确定要继续吗？"),
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::Yes))
		{
			return;
		}
		else
		{
			theApp.is_synchronous =false;
			theApp.anchorPoints[2] = cv::Rect();
			done = false;
		}
	}

	theApp.m_group_state = AnchorState;
	theApp.m_state = LBBegin;
}

void AnchorDlg::on_anchorRBBtn_clicked()
{
	//已经点击过？询问覆盖
	if (theApp.anchorPoints[3].width>0)
	{
		if (QMessageBox::No == QMessageBox::information(NULL, 
			tr("重新选择"), 
			tr("已经点选左上角定位点，继续操作将覆盖原来选择\n确定要继续吗？"),
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::Yes))
		{
			return;
		}
		else
		{
			theApp.is_synchronous =false;
			theApp.anchorPoints[3] = cv::Rect();
			done = false;
		}
	}

	theApp.m_group_state = AnchorState;
	theApp.m_state = RBBegin;
}

void AnchorDlg::on_confirmBtn_clicked()
{
	Mat tmp;
	double angle;
	int count = 0;

	for (int i = 0; i < 4; ++i)
	{
		if (theApp.anchorPoints[i].width > 0)
		{
			++count;
		}
	}

	if (count < 3)
	{
		QMessageBox::information(this, " ",
			tr("倾斜校正失败\n请确认已标定不少于三个的定位点"));

		return;
	}

	theApp.anchor_type = TiltCorrection(theApp.img_raw, tmp, theApp.anchorPoints, angle);

	if (theApp.anchor_type < 0)
	{
		theApp.anchor_type = 0;
		QMessageBox::information(NULL, " ",
			tr("倾斜校正失败\n请确认已标定不少于三个的定位点"));

		return;
	}

	theApp.img_raw = tmp;

	//重新计算灰度图像及二值图像
	cvtColor(theApp.img_raw, theApp.img_gray, CV_RGB2GRAY);
	threshold(theApp.img_gray, theApp.img_bw, 128, 255, THRESH_BINARY_INV);

	for (int i=0; i < 4; i++)
	{
		if (theApp.anchorPoints[i].width != 0)
		{
			theApp.GetArchorPointRect(
				QPoint(theApp.anchorPoints[i].x + theApp.anchorPoints[i].width / 2,
				theApp.anchorPoints[i].y + theApp.anchorPoints[i].height / 2), i);
		}
	}

	theApp.is_synchronous =false;
	theApp.m_state = RBEnd;
	done = true;
	emit anchorDone();
}

int AnchorDlg::resume()
{
	if (theApp.anchor_type <= 0)
	{
		theApp.anchor_type = 0;
		return -1;
	}

	return 1;
}