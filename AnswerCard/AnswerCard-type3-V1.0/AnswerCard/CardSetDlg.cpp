#include "CardSetDlg.h"
#include "ui_CardSetDlg.h"
#include "qdir.h"
#include "qmessagebox.h"

CardSetDlg::CardSetDlg(QWidget *parent,int cardType)
	: QDialog(parent),m_cardType(cardType)
{
	ui = new Ui::CardSetDlg();
	ui->setupUi(this);
}

CardSetDlg::~CardSetDlg()
{
	delete ui;
}

Mat CardSetDlg::qImage2Mat(const QImage& qimage) 
{ 
    cv::Mat mat = cv::Mat(qimage.height(), qimage.width(), CV_8UC4, 
		(uchar*)qimage.bits(), qimage.bytesPerLine()); 
    cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 ); 
    int from_to[] = { 0,0, 1,1, 2,2 }; 
    cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 ); 

    return mat2; 
}; 

QImage CardSetDlg::mat2QImage(const cv::Mat &mat)
{
    QImage img;
    if(mat.channels()==3)
    {
        cvtColor(mat,m_imgTmp,CV_BGR2RGB);
        img =QImage((const unsigned char*)(m_imgTmp.data),
                    m_imgTmp.cols, m_imgTmp.rows,
					m_imgTmp.cols * m_imgTmp.channels(),
                    QImage::Format_RGB888);
    }
    else
    {
        img =QImage((const unsigned char*)(mat.data),
                    mat.cols, mat.rows,
                    mat.cols * mat.channels(),
                    QImage::Format_RGB888);
    }
    return img;
}

void CardSetDlg::on_addBtn_clicked()
{
	AddPageDlg dlg;
	if (dlg.exec() == QDialog::Accepted)
	{
		QString id = dlg.getPageId();
		for (int i = 0; i < m_card.size(); ++i)
		{
			if (id.toInt() == m_card.at(i).pageId)
			{
				QMessageBox::information(this, tr(" "),tr("该张数已存在！"));
				return;
			}
		}

		//添加正面试卷
		QString frontFileName = dlg.getFrontPagePath();
		Mat tmp = imread(frontFileName.toStdString());
		QImage img = mat2QImage(tmp);

		DataInfo3 info;
		info.image = img;
		info.isFront = true;
		info.markerDone = false;
		info.hasAnchorRect = m_cardType == 3 ? false : true;
		info.anchorType = -1;

		//获取临时文件路径
		DataIO io(QObject::tr("tmp\\%1-1.tmp").arg(id), DATA_WRITE);
		io.writeToDat(info);

		Card card = {id.toInt(),true};
		m_card.push_back(card);

		//将文件信息输出到界面上
		int currentRow = ui->tableWidget->rowCount();
		ui->tableWidget->insertRow(currentRow);
		ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(id));
		ui->tableWidget->setItem(currentRow, 1, new QTableWidgetItem(tr("正面")));

		//添加反面试卷
		if (dlg.hasBackPage() == true)
		{		
			QString frontFileName1 = dlg.getBackPagePath();
			Mat tmp1 = imread(frontFileName1.toStdString());
			QImage img1 = mat2QImage(tmp1);

			DataInfo3 info1;
			info1.image = img1;
			info1.isFront = false;
			info1.markerDone = false;
			info1.hasAnchorRect = m_cardType == 3 ? false : true;
			info1.anchorType = -1;

			//获取临时文件路径
			DataIO io1(QObject::tr("tmp\\%1-0.tmp").arg(id), DATA_WRITE);
			io1.writeToDat(info1);

			//将文件信息输出到界面上
			int currentRow = ui->tableWidget->rowCount();
			ui->tableWidget->insertRow(currentRow);
			ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(id));
			ui->tableWidget->setItem(currentRow, 1, new QTableWidgetItem(tr("反面")));

			Card card = {id.toInt(),false};
			m_card.push_back(card);
		}


	}

}

void CardSetDlg::on_deleteBtn_clicked()
{
	int idx = ui->tableWidget->currentIndex().row();
	if (idx < 0)
	{
		QMessageBox::information(this, tr(" "),tr("还没选择哪张试卷！"));
		return;
	}

	QString dataPath = tr("tmp\\%1-%2.tmp").arg(m_card.at(idx).pageId).arg(m_card.at(idx).isFront);
	QFile file(dataPath);
	if (file.exists())
	{
		//删除临时文件
		file.remove();
	}
	ui->tableWidget->removeRow(idx);
	m_card.erase(m_card.begin() + idx);
	emit deleteCard(dataPath);
}

void CardSetDlg::on_editBtn_clicked()
{
	int idx = ui->tableWidget->currentIndex().row();
	if (idx < 0)
	{
		QMessageBox::information(this, tr(" "),tr("还没选择哪张试卷！"));
		return;
	}

	QString dataPath = tr("tmp\\%1-%2.tmp").arg(m_card.at(idx).pageId).arg(m_card.at(idx).isFront);
	emit edit(dataPath);
}

void CardSetDlg::clear()
{
	ui->tableWidget->clearContents();
	ui->tableWidget->setRowCount(0);
	m_card.clear();
}

int CardSetDlg::resume()
{
	QFile file("tmp1\\relation.dat");

	if(!file.exists())
	{
		return 0;
	}

	if (!file.open(QIODevice::ReadOnly))
	{
		file.close();
		return 0;
	}

	QDataStream data;
	data.setDevice(&file);
	data.setVersion(QDataStream::Qt_4_8);

	quint32 magic;
	data >> magic;

	//判断是否为可识别格式
	if (magic != (quint32)PAPERSET_MAGIC_NUM)
	{
		file.close();
		return 0;
	}

	quint32 version;
	data >> version;

	//判断是否为可识别版本
	if (version != (quint32)VERSION)
	{
		file.close();
		return 0;
	}

	int type;
	data >> type;

	if (type != m_cardType)
	{
		return 0;
	}

	QList<int> pageId;
	QList<bool> isFront;

	data>>m_cardDpi>>pageId>>isFront;

	clear();

	for (int i = 0; i < pageId.size() && i < isFront.size(); ++i)
	{
		Card c;
		c.pageId = pageId.at(i);
		c.isFront = isFront.at(i);

		m_card.push_back(c);

		//将文件信息输出到界面上
		int currentRow = ui->tableWidget->rowCount();
		ui->tableWidget->insertRow(currentRow);
		ui->tableWidget->setItem(currentRow, 0, new QTableWidgetItem(QString(tr("%1").arg(c.pageId))));
		if (c.isFront == true)
		{
			ui->tableWidget->setItem(currentRow, 1, new QTableWidgetItem(tr("正面")));
		}
		else
		{
			ui->tableWidget->setItem(currentRow, 1, new QTableWidgetItem(tr("反面")));
		}
	}

	return 1;
}

void CardSetDlg::on_saveFileBtn_clicked()
{
	QFile file("tmp\\relation.dat");

	if(file.exists())
	{
		file.remove();
	}

	if (!file.open(QIODevice::WriteOnly))
	{
		QMessageBox::information(this," ","无法保存!");
		return;
	}


	QList<int> pageId;
	QList<bool> isFront;

	for (int i = 0; i < m_card.size(); ++i)
	{
		pageId.push_back(m_card.at(i).pageId);
		isFront.push_back(m_card.at(i).isFront);
	}

	QDataStream data;
	data.setDevice(&file);
	data.setVersion(QDataStream::Qt_4_8);

	//输出试卷关系信息
	data << quint32(PAPERSET_MAGIC_NUM) << quint32(VERSION) 
		 << m_cardType <<m_cardDpi<<pageId<<isFront;

	
	if (file.isOpen())
	{
		file.close();
	}

	emit save();
}

void CardSetDlg::on_importXMLBtn_clicked()
{
	emit import();
}


