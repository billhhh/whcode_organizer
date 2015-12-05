#include "MarkerDlg.h"
#include "ui_MarkerDlg.h"
#include "AnswerCard.h"

MarkerDlg::MarkerDlg(QWidget *parent)
	: QDialog(parent),
	m_hmarkers_num(0),
	m_vmarkers_num(0),
	m_done(false)
{
	ui = new Ui::MarkerDlg();
	ui->setupUi(this);
}

MarkerDlg::~MarkerDlg()
{
	delete ui;
}

void MarkerDlg::initialization()
{
	m_hmarkers_num = 0;
	m_vmarkers_num = 0;

	ui->horMarkersEdit->setText("0");
	ui->verMarkersEdit->setText("0");
	ui->horMarkersEdit->setEnabled(false);
	ui->verMarkersEdit->setEnabled(false);
	m_done = false;
	this->setEnabled(false);
}

void MarkerDlg::on_horMarkersBtn_clicked()
{
	//已经点击过？询问覆盖
	if (theApp.markersRect[0].width > 0)
	{
		if (theApp.questionInfo.size() > 0 || theApp.cfp_group.size() > 0 || theApp.idGroup.size() > 0)
		{
			QMessageBox::information(this," ","该标记点已被使用，无法修改!");
			return;
		}

		if (QMessageBox::No == QMessageBox::information(this, 
			tr("重新选择"), 
			tr("已经框选水平标记点区域，继续操作将覆盖原来选择\n确定要继续吗"),
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::Yes))
		{
			theApp.is_synchronous = false;
			return;
		}
		else
		{
			theApp.is_synchronous = false;
			setHorEditNum(0);
			theApp.markersRect[0] = cv::Rect();
			m_done = false;
		}
	}
	theApp.m_group_state = MarkerState;
	theApp.m_state = RowBegin;
}

void MarkerDlg::on_verMarkersBtn_clicked()
{
	//已经点击过？询问覆盖
	if (theApp.markersRect[1].width > 0)
	{
		if (theApp.questionInfo.size() > 0 || theApp.cfp_group.size() > 0 || theApp.idGroup.size() > 0)
		{
			QMessageBox::information(this," ","该标记点已被使用，无法修改!");
			return;
		}

		if (QMessageBox::No == QMessageBox::information(NULL, 
			tr("重新选择"), 
			tr("已经框选竖直标记点区域，继续操作将覆盖原来选择\n确定要继续吗"),
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::Yes))
		{
			return;
		}
		else
		{
			theApp.is_synchronous = false;
			setVerEditNum(0);
			theApp.markersRect[1] = cv::Rect();
			m_done = false;
		}
	}
	theApp.m_group_state = MarkerState;
	theApp.m_state = ColBegin;
}

void MarkerDlg::on_confirmBtn_clicked()
{
	if (m_hmarkers_num <=0 || m_vmarkers_num <= 0)
	{
		QMessageBox::information(NULL, tr(" "),
			tr("请确认已框选了水平标记点组和垂直标记点组！"));
		return;
	}

	QString w_str;
	w_str = QString(tr("水平标记点有%1个，垂直方向标记点有%2个\n确认？")
		.arg(m_hmarkers_num).arg(m_vmarkers_num));

	if (QMessageBox::No == QMessageBox::information(NULL, 
			tr("确认标记点数量？"), 
			w_str,
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::Yes))
	{
		return;
	}

	setHorEditEnabled(false);
	setVerEditEnabled(false);

	theApp.markerBT.InitMarkersBoundaryTable(theApp.hmarkers,theApp.vmarkers);

	m_done = true;
	emit markerDone();
}

void MarkerDlg::setHorEditEnabled(bool isEnable)
{
	ui->horMarkersEdit->setEnabled(isEnable);
}

void MarkerDlg::setVerEditEnabled(bool isEnable)
{
	ui->verMarkersEdit->setEnabled(isEnable);
}
	
void MarkerDlg::setHorEditNum(short num)
{
	m_hmarkers_num = num;
	ui->horMarkersEdit->setText(QString("%1").arg(m_hmarkers_num));

}
void MarkerDlg::setVerEditNum(short num)
{
	m_vmarkers_num = num;
	ui->verMarkersEdit->setText(QString("%1").arg(m_vmarkers_num));
}

int MarkerDlg::resume(bool isDone)
{
	initialization();
	if (theApp.markersRect[0].width > 0)
	{
		vector<cv::Rect> hmarkers = theApp.GetMarkersNum(theApp.img_bw(theApp.markersRect[0]));
		m_hmarkers_num = hmarkers.size();
		if (m_hmarkers_num > 0)
		{
			setHorEditNum(m_hmarkers_num);
			for (int i = hmarkers.size()-1; i>=0; i--)
			{
				hmarkers.at(i).x += theApp.markersRect[0].x;
				hmarkers.at(i).y += theApp.markersRect[0].y;
			}
			theApp.hmarkers = hmarkers;
			theApp.SortMarkers(true);

			ui->horMarkersEdit->setText(tr("%1").arg(m_hmarkers_num));
		}
	}

	if (theApp.markersRect[1].width > 0)
	{
		vector<cv::Rect> vmarkers = theApp.GetMarkersNum(theApp.img_bw(theApp.markersRect[1]));
		m_vmarkers_num = vmarkers.size();
		if (m_vmarkers_num > 0)
		{
			setVerEditNum(m_vmarkers_num);
			for (int i = vmarkers.size()-1; i>=0; i--)
			{
				vmarkers.at(i).x += theApp.markersRect[1].x;
				vmarkers.at(i).y += theApp.markersRect[1].y;
			}
			theApp.vmarkers = vmarkers;
			theApp.SortMarkers(true);

			ui->verMarkersEdit->setText(tr("%1").arg(m_vmarkers_num));
		}
	}

	if (theApp.markersRect[1].width > 0 && theApp.markersRect[0].width > 0 && isDone == true)
	{
		theApp.markerBT.InitMarkersBoundaryTable(theApp.hmarkers,theApp.vmarkers);
		m_done = true;
		return 1;
	}

	if (theApp.markersRect[1].width > 0)
	{
		ui->verMarkersEdit->setEnabled(true);
	}

	if (theApp.markersRect[0].width > 0)
	{
		ui->horMarkersEdit->setEnabled(true);
	}

	return -1;
}