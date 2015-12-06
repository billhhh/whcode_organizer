#include "AnswerCardDlg3.h"
#include "ui_AnswerCardDlg3.h"
#include "DataIO.h"
#include "qdir.h"
#include "Zip\ACZip.h"
#include "XmlIO\XmlIO.h"
#pragma comment(lib,"XmlIoDll.lib")


AnswerCardDlg3::AnswerCardDlg3(QApplication &app, int type)
	: QDialog(0),
	m_mouseDownPoint(0,0), 
	m_picRect(),
	m_hmarkers_num(0),
	m_vmarkers_num(0),
	m_controlRect(),
	m_isZooming(false),
	m_zoomingIndex(0),
	m_cardType(type),
	m_cardPath("")
{
	QDir dir;
	bool exist = dir.exists("tmp");
	if (!exist)
	{
		//创建tmp文件夹
		dir.mkdir("tmp");
	}

	ui = new Ui::AnswerCardDlg3();
	ui->setupUi(this); 

	//初始化控制点
	for (int i = 0; i < 9; ++i)
	{
		m_controlPoint[i] = QRect(0, 0, CTRL_POINT_LENGTH, CTRL_POINT_LENGTH);
	}

	//设置对话框的最小最大化按钮
	this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
	this->setWindowFlags(windowFlags()|Qt::WindowMinimizeButtonHint);
	this->setWindowFlags(windowFlags()|Qt::WindowMaximizeButtonHint);
	
///////////////////////////标签第三页//////////////////////////////////
	ui->stepWidget->setCurrentIndex(2);
	QWidget *tab = ui->stepWidget->currentWidget();
	//将条形码定位窗口嵌入选卡部件的第二页
	m_barcodeDlg = new BarCodeDlg(tab);
	m_barcodeDlg->setWindowFlags(Qt::Widget);
	ui->secWidgetLayout->addWidget(m_barcodeDlg);
	m_barcodeDlg->show();

	m_fillPointDlg = new FillPointDlg(tab);
	m_fillPointDlg->setWindowFlags(Qt::Widget);
	ui->secWidgetLayout->addWidget(m_fillPointDlg);
	m_fillPointDlg->show();

	//将裁切区域定位窗口嵌入选卡部件的第二页
	m_clipDlg = new ClipDlg(tab);
	m_clipDlg->setWindowFlags(Qt::Widget);
	ui->secWidgetLayout->addWidget(m_clipDlg);
	m_clipDlg->show();

///////////////////////////标签第二页/////////////////////////////////
	ui->stepWidget->setCurrentIndex(1);
	tab = ui->stepWidget->currentWidget();

	//定位点定位窗口	
	m_anchorDlg = new AnchorDlg(tab);
	m_anchorDlg->setWindowFlags(Qt::Widget);
	ui->firstWidgetLayout->addWidget(m_anchorDlg,1,0);
	m_anchorDlg->show();

	m_anchorRectDlg = new AnchorRectDlg(tab);
	m_anchorRectDlg->setWindowFlags(Qt::Widget);
	ui->firstWidgetLayout->addWidget(m_anchorRectDlg,1,0);
	m_anchorRectDlg->show();

	//类型3显示定位点，类型四显示定位框
	if (m_cardType == 3)
	{
		m_anchorDlg->setVisible(true);
		m_anchorRectDlg->setVisible(false);
	}
	else
	{
		m_anchorDlg->setVisible(false);
		m_anchorRectDlg->setVisible(true);
	}

	//虚拟定位点
	m_lineDetectDlg = new LineDetectDlg(tab);
	m_lineDetectDlg->setWindowFlags(Qt::Widget);
	ui->firstWidgetLayout->addWidget(m_lineDetectDlg,2,0);
	m_lineDetectDlg->show();

	//页码标识
	m_pagePointDlg = new PagePointDlg(tab);
	m_pagePointDlg->setWindowFlags(Qt::Widget);
	ui->firstWidgetLayout->addWidget(m_pagePointDlg,3,0);
	m_pagePointDlg->show();

	//标记点定位窗口
	m_markerMakeDlg = new MarkerMakeDlg(tab);
	m_markerMakeDlg->setWindowFlags(Qt::Widget);
	ui->firstWidgetLayout->addWidget(m_markerMakeDlg,4,0);
	m_markerMakeDlg->show();

///////////////////////////标签第一页/////////////////////////////////
	ui->stepWidget->setCurrentIndex(0);
	tab = ui->stepWidget->currentWidget();

	//套卡信息窗口
	m_cardSetDlg = new CardSetDlg(tab,type);
	m_cardSetDlg->setWindowFlags(Qt::Widget);
	ui->cardWidgetLayout->addWidget(m_cardSetDlg,1,0);
	m_cardSetDlg->show();

	//卡格式清除
	m_clearDlg = new ClearDlg(tab);
	m_clearDlg->setWindowFlags(Qt::Widget);
	ui->cardWidgetLayout->addWidget(m_clearDlg,2,0);
	m_clearDlg->show();

	m_verticalSpacer = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);
	ui->cardWidgetLayout->addItem(m_verticalSpacer,3,0);
////////////////////////////////////////////////////////////////////////////////////
	//注册监视对象
    ui->imageLabel->installEventFilter(this);
	ui->imageWidget->installEventFilter(this);
	ui->imageLabel->setMouseTracking(true);
	ui->imageWidget->setMouseTracking(true);

	//连接信号和槽
	connect(m_anchorDlg, SIGNAL(anchorDone()), this, SLOT(anchorDone()));
	connect(m_anchorRectDlg, SIGNAL(anchorDone()), this, SLOT(anchorDone()));
	connect(m_markerMakeDlg, SIGNAL(MarkerMakeDone()), this, SLOT(markerDone()));
	connect(m_markerMakeDlg, SIGNAL(MarkerMakeBegin()), this, SLOT(markerMakeBegin()));
	connect(m_markerMakeDlg, SIGNAL(MarkerMakeDelete()), this, SLOT(markerMakeDelete()));
	connect(m_barcodeDlg, SIGNAL(barCodeBegin()), this, SLOT(barCodeBegin()));
	connect(m_barcodeDlg, SIGNAL(barCodeDone()), this, SLOT(enableDlg()));
	connect(m_fillPointDlg, SIGNAL(fillPointBegin()), this, SLOT(fillPointBegin()));
	connect(m_fillPointDlg, SIGNAL(fillPointDone()), this, SLOT(enableDlg()));
	connect(m_fillPointDlg, SIGNAL(fillPointClicked()), this, SLOT(fillPointClicked()));
	connect(m_clipDlg, SIGNAL(clipBegin()), this, SLOT(clipBegin()));
	connect(m_clipDlg, SIGNAL(clipDone()), this, SLOT(enableDlg()));
	connect(m_clipDlg, SIGNAL(clipClicked(int)), this, SLOT(clipClicked(int)));
	connect(m_lineDetectDlg, SIGNAL(lineBegin()), this, SLOT(lineDetectBegin()));
	connect(m_lineDetectDlg, SIGNAL(lineDone()), this, SLOT(lineDetectDone()));
	connect(m_barcodeDlg, SIGNAL(barCodeClicked(int)), this, SLOT(barCodeClicked(int)));
	connect(m_markerMakeDlg, SIGNAL(MarkerMakeClicked()), this, SLOT(markerMakeClicked()));
	connect(m_cardSetDlg, SIGNAL(edit(QString)), this, SLOT(editCard(QString)));
	connect(m_cardSetDlg, SIGNAL(deleteCard(QString)), this, SLOT(deleteCard(QString)));
	connect(m_pagePointDlg, SIGNAL(pagePointDone()), this, SLOT(enableDlg()));
	connect(m_pagePointDlg, SIGNAL(pagePointBegin()), this, SLOT(pagePointBegin()));
	connect(m_pagePointDlg, SIGNAL(pagePointClicked()), this, SLOT(fillPointClicked()));
	connect(m_cardSetDlg, SIGNAL(save()), this, SLOT(on_saveFileBtn_clicked()));
	connect(m_cardSetDlg, SIGNAL(import()), this, SLOT(on_importXMLBtn_clicked()));
	connect(m_clearDlg, SIGNAL(clearCard()), this, SLOT(on_clearBtn_clicked()));
	connect(m_clearDlg, SIGNAL(changePic()), this, SLOT(on_changePicBtn_clicked()));

	//初始化对话框
	initialization();

	m_cardSetDlg->setEnabled(false);
	m_clearDlg->setEnabled(false);
}

AnswerCardDlg3::~AnswerCardDlg3()
{
	QDir dir;
	bool exist = dir.exists("tmp");

	if (exist)
	{
		QDir dirTmp("tmp//");
		QFileInfoList list = dirTmp.entryInfoList();

		//遍历删除目录下的文件
		for (int i = 0; i < list.size(); ++i)
		{
			if(list.at(i).fileName() == "." || list.at(i).fileName() == "..")
			{
				continue;
			}

			dirTmp.remove(list.at(i).fileName());
		}

		//删除tmp文件夹
		dir.rmdir("tmp");
	}

	delete m_anchorDlg;
	delete m_anchorRectDlg;
	delete m_barcodeDlg;
	delete m_fillPointDlg;
	delete m_clipDlg;
	delete m_markerMakeDlg;
	delete m_lineDetectDlg;
	delete m_pagePointDlg;
	delete m_cardSetDlg;
	delete m_clearDlg;
//	delete m_isFrontDlg;
	delete ui;
}

//答题卡格式清理
void AnswerCardDlg3::on_clearBtn_clicked()
{
	if (m_cardPath == "")
	{
		return;
	}

	initialization();
	m_anchorDlg->setEnabled(true);
	m_anchorRectDlg->setEnabled(true);
	m_lineDetectDlg->setEnabled(true);
	m_barcodeDlg->setEnabled(true);
	m_clipDlg->setEnabled(true);
	m_fillPointDlg->setEnabled(true);
	theApp.is_synchronous = false;
	update();
}

void AnswerCardDlg3::on_changePicBtn_clicked()
{
	if (m_cardPath == "")
	{
		return;
	}

	QString fileName = QFileDialog::getOpenFileName(
	this, tr("重新指定图片"),
    ".",
    "Image files (*.bmp *.jpg *.tiff *.tif);;JPEG(*.jpg);;BMP(*.bmp);;TIFF(*.tiff *.tif)");

	if (fileName != "")
	{
		Mat tmp = imread(fileName.toStdString());
		theApp.img_raw = tmp;
		cvtColor(theApp.img_raw,theApp.img_gray,CV_RGB2GRAY);
		threshold(theApp.img_gray,theApp.img_bw,128,255,THRESH_BINARY_INV);
		initialization();
		m_anchorDlg->setEnabled(true);
		m_anchorRectDlg->setEnabled(true);
		m_lineDetectDlg->setEnabled(true);
		m_barcodeDlg->setEnabled(true);
		m_clipDlg->setEnabled(true);
		m_fillPointDlg->setEnabled(true);
		theApp.is_synchronous = false;
		update();
	}	
	
}
//////////////////////////////////子窗口激活关闭/////////////////////////////////
//初始化各个子窗口
void AnswerCardDlg3::initialization()
{
	if (m_cardType == 3)
	{
		m_anchorDlg->initialization();
	}
	else
	{
		m_anchorRectDlg->initialization();
	}

	m_lineDetectDlg->initialization();
	m_barcodeDlg->initialization();
	m_fillPointDlg->initialization();
	m_clipDlg->initialization();
	m_markerMakeDlg->initialization();
	m_pagePointDlg->initialization();
	ui->stepWidget->setCurrentIndex(0);
	theApp.clear();
	theApp.clearACInfo3();
}

//激活标记点窗口
void AnswerCardDlg3::anchorDone()
{
	m_markerMakeDlg->setEnabled(true);
	m_fillPointDlg->setEnabled(true);
	m_pagePointDlg->setEnabled(true);
	if (m_isZooming == true)
	{
		m_isZooming = false;
		theApp.is_synchronous = false;
	}
}

//激活tabWidget的第二个页面
void AnswerCardDlg3::markerDone()
{
	enableDlg();
	m_fillPointDlg->updateMarkerGroupId();

	if (m_markerMakeDlg->isEditing())
	{
		//ui->importXMLBtn->setEnabled(false);
		//ui->saveFileBtn->setEnabled(false);
	}
}

//激活所有窗口
void AnswerCardDlg3::enableDlg()
{
	m_anchorDlg->setEnabled(true);
	m_anchorRectDlg->setEnabled(true);
	m_markerMakeDlg->setEnabled(true);
	m_barcodeDlg->setEnabled(true);
	m_fillPointDlg->setEnabled(true);
	m_clipDlg->setEnabled(true);
	m_lineDetectDlg->setEnabled(true);
	m_pagePointDlg->setEnabled(true);

	if ((theApp.anchor_type == 0 && m_cardType == 3) 
		|| (theApp.anchor_type == -1) && m_cardType != 3)
	{
		m_markerMakeDlg->setEnabled(false);
		m_pagePointDlg->setEnabled(false);
	}


	if (m_isZooming == true)
	{
		m_isZooming = false;
		theApp.is_synchronous = false;
	}
}

void AnswerCardDlg3::barCodeBegin()
{
	m_anchorDlg->setEnabled(false);
	m_anchorRectDlg->setEnabled(false);
	m_markerMakeDlg->setEnabled(false);
	m_barcodeDlg->setEnabled(true);
	m_fillPointDlg->setEnabled(false);
	m_clipDlg->setEnabled(false);
	m_lineDetectDlg->setEnabled(false);
	m_pagePointDlg->setEnabled(false);

	if (m_isZooming == true)
	{
		m_isZooming = false;
		theApp.is_synchronous = false;
	}
}

void AnswerCardDlg3::fillPointBegin()
{
	m_anchorDlg->setEnabled(false);
	m_anchorRectDlg->setEnabled(false);
	m_markerMakeDlg->setEnabled(false);
	m_barcodeDlg->setEnabled(false);
	m_fillPointDlg->setEnabled(true);
	m_clipDlg->setEnabled(false);
	m_lineDetectDlg->setEnabled(false);
	m_pagePointDlg->setEnabled(false);

	if (m_isZooming == true)
	{
		m_isZooming = false;
		theApp.is_synchronous = false;
	}
}

void AnswerCardDlg3::clipBegin()
{
	m_anchorDlg->setEnabled(false);
	m_anchorRectDlg->setEnabled(false);
	m_markerMakeDlg->setEnabled(false);
	m_barcodeDlg->setEnabled(false);
	m_fillPointDlg->setEnabled(false);
	m_clipDlg->setEnabled(true);
	m_lineDetectDlg->setEnabled(false);
	m_pagePointDlg->setEnabled(false);

	if (m_isZooming == true)
	{
		m_isZooming = false;
		theApp.is_synchronous = false;
	}
}

void AnswerCardDlg3::markerMakeBegin()
{
	m_anchorDlg->setEnabled(false);
	m_anchorRectDlg->setEnabled(false);
	m_markerMakeDlg->setEnabled(true);
	m_barcodeDlg->setEnabled(false);
	m_fillPointDlg->setEnabled(false);
	m_clipDlg->setEnabled(false);
	m_lineDetectDlg->setEnabled(false);
	m_pagePointDlg->setEnabled(false);

	if (m_isZooming == true)
	{
		m_isZooming = false;
		theApp.is_synchronous = false;
	}
}

void AnswerCardDlg3::lineDetectBegin()
{
	m_anchorDlg->setEnabled(false);
	m_anchorRectDlg->setEnabled(false);
	m_markerMakeDlg->setEnabled(false);
	m_barcodeDlg->setEnabled(false);
	m_fillPointDlg->setEnabled(false);
	m_clipDlg->setEnabled(false);
	m_lineDetectDlg->setEnabled(true);
	m_pagePointDlg->setEnabled(false);

	if (m_isZooming == true)
	{
		m_isZooming = false;
		theApp.is_synchronous = false;
	}
}

void AnswerCardDlg3::pagePointBegin()
{
	m_anchorDlg->setEnabled(false);
	m_anchorRectDlg->setEnabled(false);
	m_markerMakeDlg->setEnabled(false);
	m_barcodeDlg->setEnabled(false);
	m_fillPointDlg->setEnabled(false);
	m_clipDlg->setEnabled(false);
	m_lineDetectDlg->setEnabled(false);
	m_pagePointDlg->setEnabled(true);

	if (m_isZooming == true)
	{
		m_isZooming = false;
		theApp.is_synchronous = false;
	}
}

void AnswerCardDlg3::lineDetectDone()
{
	enableDlg();

	if (m_isZooming == true)
	{
		m_isZooming = false;
		theApp.is_synchronous = false;
	}
}

void AnswerCardDlg3::markerMakeDelete()
{
	if (theApp.markers.size() <= 0)
	{
		m_fillPointDlg->setEnabled(false);
	}

	m_fillPointDlg->updateMarkerGroupId();

	if (m_isZooming == true)
	{
		m_isZooming = false;
		theApp.is_synchronous = false;
	}
}


void AnswerCardDlg3::clipClicked(int idx)
{
	//绘制控制区域
	m_controlRect = theApp.cropAreas.at(idx).pos;		

	//计算控制点位置
	computeCtrlPointPos();

	//绘制控制点
	for (int i = 0; i < 9; ++i)
	{
		drawControlPoint(m_controlPoint[i].center(), CTRL_POINT_LENGTH, theApp.cropAreaClicked_color, theApp.cropAreaClicked_thickness);
	}

	m_zoomingIndex = idx;
	m_isZooming = true;
	update();
}

void AnswerCardDlg3::barCodeClicked(int idx)
{
	//绘制控制区域
	m_controlRect = theApp.barGroup.at(idx).pos;		

	//计算控制点位置
	computeCtrlPointPos();

	//绘制控制点
	for (int i = 0; i < 9; ++i)
	{
		drawControlPoint(m_controlPoint[i].center(), CTRL_POINT_LENGTH, theApp.barcodeClicked_color, theApp.barcodeClicked_thickness);
	}

	m_zoomingIndex = idx;
	m_isZooming = true;
	update();
}

void AnswerCardDlg3::fillPointClicked()
{
	if (m_isZooming == true)
	{
		m_isZooming = false;
	}
	
	update();
}

void AnswerCardDlg3::markerMakeClicked()
{
	if (m_isZooming == true)
	{
		m_isZooming = false;
	}

	update();
}


/////////////////////////////////图像绘制////////////////////////////////////////////
void AnswerCardDlg3::paintEvent(QPaintEvent *e)
{
	if (theApp.m_state != 0 || theApp.m_group_state != 0)
	{
		if (!theApp.is_synchronous)
		{
			theApp.Redraw3();
		}

		QImage img = mat2QImage(theApp.img_show);
		m_picRect = img.rect();
		ui->imageLabel->setPixmap(QPixmap::fromImage(img));

	}
}

//将Mat格式的图片转为QImage输出
QImage AnswerCardDlg3::mat2QImage(const cv::Mat &mat)
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

Mat AnswerCardDlg3::qImage2Mat(const QImage& qimage) 
{ 
    cv::Mat mat = cv::Mat(qimage.height(), qimage.width(), CV_8UC4, 
		(uchar*)qimage.bits(), qimage.bytesPerLine()); 
    cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 ); 
    int from_to[] = { 0,0, 1,1, 2,2 }; 
    cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 ); 

    return mat2; 
}; 

// 计算客户区的一个点在图像中的位置
QPoint AnswerCardDlg3::GetImgPosFromClient(const QPoint &clientPos)
{	
	QPoint pos(clientPos);

	if (pos.x() < 0)
	{
		pos.setX(0);
	}	
	else if (pos.x() > m_picRect.width())
	{
		pos.setX(m_picRect.width());
	}
	
	if (pos.y() < 0)
	{
		pos.setY(0);
	}
	else if (pos.y() > m_picRect.height())
	{
		pos.setY(m_picRect.height());
	}

	return QPoint(pos.x(), pos.y());
}

/////////////////////////////////鼠标控制模块/////////////////////////////////////////
bool AnswerCardDlg3::eventFilter(QObject *target, QEvent *e)
{
	if (target == ui->imageLabel)
    {
		if (e->type() == QEvent::MouseMove)
		{
			QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(e);
			QPoint point(mouseEvent->x(), mouseEvent->y());

			//鼠标按住左键拖动
			if(mouseEvent->buttons() & Qt::LeftButton)
			{
				mouseMove(point);
			}
			else
			{
				changeMouseCursor(point);
			}

			 return true;
		}
		else if (e->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(e);
			QPoint point(mouseEvent->x(), mouseEvent->y());
			mouseLeftButtonPress(point);

			return true;
		}
		else if (e->type() == QEvent::MouseButtonRelease)
		{
			QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(e);
			QPoint point(mouseEvent->x(), mouseEvent->y());
			mouseLeftButtonRelease(point);

			return true;
		}
		else if (e->type() == QEvent::Enter)
		{
			ui->imageScrollArea->setFocus();
			return true;
		}
		else if (e->type() == QEvent::Leave)
		{
			ui->imageScrollArea->clearFocus();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return QDialog::eventFilter(target, e);
	}
}

//鼠标左键按下,处理事件
void AnswerCardDlg3::mouseLeftButtonPress(const QPoint &pos)
{
	switch (theApp.m_group_state)
	{
	//条形码模块
	case BarCodeState:
		switch (theApp.m_state)
		{
		case BaseBegin:
			theApp.img_show.copyTo(theApp.img_bk);		//备份当前图像
			m_mouseDownPoint = GetImgPosFromClient(pos);	//获得相对图像位置
			theApp.m_state++;							//改变状态
			break;

		case BaseRelease:
			{
				QPoint pt = GetImgPosFromClient(pos);
				m_ctrlPointIndex = -1;

				for (int i = 0; i < 9; ++i)
				{
					if (m_controlPoint[i].contains(pt.x(), pt.y()))
					{
						m_ctrlPointIndex = i;
						break;
					}
				}

				break;
			}
		case BaseEnd:
			if (m_isZooming == true)
			{
				QPoint pt = GetImgPosFromClient(pos);
				m_ctrlPointIndex = -1;

				for (int i = 0; i < 9; ++i)
				{
					if (m_controlPoint[i].contains(pt.x(), pt.y()))
					{
						m_ctrlPointIndex = i;
						if (theApp.barGroup.at(m_zoomingIndex).pos.width > 0)
						{
							theApp.barGroup.at(m_zoomingIndex).pos = cv::Rect();
							theApp.Redraw3();
						}

						theApp.img_show.copyTo(theApp.img_bk);		//备份当前图像

						rectangle(theApp.img_show, m_controlRect, 
							theApp.barcode_color, theApp.barcode_thickness);

						computeCtrlPointPos();

						//绘制控制点
						for (int i = 0; i < 9; ++i)
						{
							drawControlPoint(m_controlPoint[i].center(), CTRL_POINT_LENGTH,theApp.barcode_color, theApp.barcode_thickness);
						}
						break;
					}
				}
			}
			break;
		}//switch (theApp.m_state)
		break;

	//自定义填涂点模块
	case FillPointState:
		switch (theApp.m_state)
		{
		case BaseBegin:
			theApp.img_show.copyTo(theApp.img_bk);		//备份当前图像
			m_mouseDownPoint = GetImgPosFromClient(pos);	//获得相对图像位置
			theApp.m_state++;							//改变状态
			break;
		}
		break;

	//裁切区域模块
	case ClipState:
		switch (theApp.m_state)
		{
		case BaseBegin:
			theApp.img_show.copyTo(theApp.img_bk);		//备份当前图像
			m_mouseDownPoint = GetImgPosFromClient(pos);	//获得相对图像位置
			theApp.m_state++;							//改变状态
			break;

		case BaseRelease:
			{
				QPoint pt = GetImgPosFromClient(pos);
				m_ctrlPointIndex = -1;

				for (int i = 0; i < 9; ++i)
				{
					if (m_controlPoint[i].contains(pt.x(), pt.y()))
					{
						m_ctrlPointIndex = i;
						break;
					}
				}

				break;
			}
		case BaseEnd:
			if (m_isZooming == true)
			{
				QPoint pt = GetImgPosFromClient(pos);
				m_ctrlPointIndex = -1;

				for (int i = 0; i < 9; ++i)
				{
					if (m_controlPoint[i].contains(pt.x(), pt.y()))
					{
						m_ctrlPointIndex = i;
						if (theApp.cropAreas.at(m_zoomingIndex).pos.width > 0)
						{
							theApp.cropAreas.at(m_zoomingIndex).pos = cv::Rect();
							theApp.Redraw3();
						}

						theApp.img_show.copyTo(theApp.img_bk);		//备份当前图像

						rectangle(theApp.img_show, m_controlRect, 
							theApp.cropArea_color, theApp.cropArea_thickness);

						computeCtrlPointPos();

						//绘制控制点
						for (int i = 0; i < 9; ++i)
						{
							drawControlPoint(m_controlPoint[i].center(), CTRL_POINT_LENGTH,theApp.cropArea_color, theApp.cropArea_thickness);
						}			
					
						break;
					}
				}
			}
			break;
		}//switch (theApp.m_state)

		break;

	//答案信息模块
	case QuestionState:
		switch (theApp.m_state)
		{
		case SingleBegin:
		case MultiBegin:
			theApp.img_show.copyTo(theApp.img_bk);		//备份当前图像
			m_mouseDownPoint = GetImgPosFromClient(pos);	//获得相对图像位置
			theApp.m_state++;							//改变状态
			break;
		}
		break;

	//标记点拖曳操作
	case MarkerState:
		switch (theApp.m_state)
		{
		case RowBegin:
		case ColBegin:
			theApp.img_show.copyTo(theApp.img_bk);		//备份当前图像
			m_mouseDownPoint = GetImgPosFromClient(pos);	//获得相对图像位置
			theApp.m_state++;							//改变状态
			break;
		}
		break;

	case MarkerMakeState:
		switch (theApp.m_state)
		{
		case SizeBegin:
			theApp.img_show.copyTo(theApp.img_bk);		//备份当前图像
			m_mouseDownPoint = GetImgPosFromClient(pos);	//获得相对图像位置
			theApp.m_state++;							//改变状态
			break;

		case MarkerFirstBegin:
			{
				theApp.img_show.copyTo(theApp.img_bk);		//备份当前图像
				m_mouseDownPoint = GetImgPosFromClient(pos);	//获得相对图像位置

				bool rst = m_markerMakeDlg->addMarker(m_mouseDownPoint);
				if (rst)
				{
					theApp.m_state++;							//改变状态
					m_markerMakeDlg->drawMarkers();
					ui->imageLabel->setCursor(Qt::SizeAllCursor);			
				}
				else
				{
					QMessageBox::information(this, " ", 
						tr("不能再此位置绘制标记点！"));
				}
			}
			break;

		case MarkerSecondBegin:
			{
				theApp.img_show.copyTo(theApp.img_bk);		//备份当前图像
				m_mouseDownPoint = GetImgPosFromClient(pos);	//获得相对图像位置

				int num = m_markerMakeDlg->getInputNumber();
				bool rst = true;

				for (int i = 0; i < num - 1; ++i)
				{
					rst = m_markerMakeDlg->addMarker(m_mouseDownPoint);

					if (rst == false)
					{
						break;
					}
				}
			
				if (rst)
				{
					theApp.m_state++;							//改变状态
					m_markerMakeDlg->computeMarkerPos(m_mouseDownPoint);
					m_markerMakeDlg->drawMarkers();
					ui->imageLabel->setCursor(Qt::SizeAllCursor);
				}
				else
				{
					QMessageBox::information(this, " ", 
						tr("不能再此位置绘制标记点！"));
				}
				break;
			}
		}
		break;

	case WhiteLineState:
		switch (theApp.m_state)
		{
		case BaseBegin:
			theApp.img_show.copyTo(theApp.img_bk);		//备份当前图像
			m_mouseDownPoint = GetImgPosFromClient(pos);	//获得相对图像位置
			theApp.m_state++;							//改变状态
			break;
		}
		break;

	case BlackLineState:
		switch (theApp.m_state)
		{
		case BaseBegin:
			theApp.img_show.copyTo(theApp.img_bk);		//备份当前图像
			m_mouseDownPoint = GetImgPosFromClient(pos);	//获得相对图像位置
			theApp.m_state++;							//改变状态
			break;
		}
		break;
	case AnchorRectState:
		switch (theApp.m_state)
		{
		case BaseBegin:
			theApp.img_show.copyTo(theApp.img_bk);		//备份当前图像
			m_mouseDownPoint = GetImgPosFromClient(pos);	//获得相对图像位置
			theApp.m_state++;							//改变状态
			break;
		}
		break;

	case PagePointState:
		switch (theApp.m_state)
		{
		case BaseBegin:
			theApp.img_show.copyTo(theApp.img_bk);		//备份当前图像
			m_mouseDownPoint = GetImgPosFromClient(pos);	//获得相对图像位置
			theApp.m_state++;							//改变状态
			break;
		}
		break;
	default:
		break;
	}
}

//鼠标左键弹起,处理事件
void AnswerCardDlg3::mouseLeftButtonRelease(const QPoint &pos)
{
	switch (theApp.m_group_state)
	{
	case AnchorState:
		anchorProcessingOnMouseUp(pos);
		break;

	case BarCodeState:
		barcodeProcessingOnMouseUp(pos);
		break;

	case FillPointState:
		fillPointProcessingOnMouseUp(pos);
		break;

	case ClipState:
		clipProcessingOnMouseUp(pos);
		break;

	case QuestionState:
		questionProcessingOnMouseUp(pos);
		break;

	case MarkerState:
		markerProcessingOnMouseUp(pos);
		break;

	case MarkerMakeState:
		makerMakeProcessingOnMouseUp(pos);
		break;

	case WhiteLineState:
		whiteLineProcessingOnMouseUp(pos);
		break;

	case BlackLineState:
		blackLineProcessingOnMouseUp(pos);
		break;

	case AnchorRectState:
		anchorRectProcessingOnMouseUp(pos);
		break;

	case PagePointState:
		pagePointProcessingOnMouseUp(pos);
		break;
	default:
		break;
	}
}

//鼠标移动,处理事件
void AnswerCardDlg3::mouseMove(const QPoint &pos)
{
	//根据状态处理
	switch (theApp.m_group_state)
	{
	case BarCodeState:
		barcodeProcessingOnMouseMove(pos);
		break;

	case MarkerState:
		markerProcessingOnMouseMove(pos);
		break;

	case FillPointState:
		fillPointProcessingOnMouseMove(pos);
		break;

	case ClipState:
		clipProcessingOnMouseMove(pos);
		break;

	case QuestionState:
		questionProcessingOnMouseMove(pos);
		break;

	case MarkerMakeState:
		makerMakeProcessingOnMouseMove(pos);
		break;

	case WhiteLineState:
		whiteLineProcessingOnMouseMove(pos);
		break;

	case BlackLineState:
		blackLineProcessingOnMouseMove(pos);
		break;
		
	case AnchorRectState:
		anchorRectProcessingOnMouseMove(pos);
		break;
	case PagePointState:
		pagePointProcessingOnMouseMove(pos);
		break;
	default:
		break;
	}

	//控制滚动条
	QPoint scrollPoint = ui->imageLabel->mapTo(ui->imageScrollArea, pos);

	if (scrollPoint.x() > ui->imageScrollArea->width())
	{
		QScrollBar *horBar = ui->imageScrollArea->horizontalScrollBar();
		horBar->setValue(horBar->value() + 30);
	}
	else if (scrollPoint.x() <= 0)
	{
		QScrollBar *horBar = ui->imageScrollArea->horizontalScrollBar();
		horBar->setValue(horBar->value() - 30);
	}

	if (scrollPoint.y() > ui->imageScrollArea->height())
	{
		QScrollBar *verBar = ui->imageScrollArea->verticalScrollBar();
		verBar->setValue(verBar->value() + 30);
	}
	else if (scrollPoint.y() <= 0)
	{
		QScrollBar *verBar = ui->imageScrollArea->verticalScrollBar();
		verBar->setValue(verBar->value() - 30);
	}
}

//更改鼠标光标
void AnswerCardDlg3::changeMouseCursor(const QPoint &pos)
{
	switch (theApp.m_group_state)
	{
	case AnchorState:
		switch (theApp.m_state)
		{
		case LTBegin:
		case RTBegin:
		case LBBegin:
		case RBBegin:
			ui->imageLabel->setCursor(Qt::CrossCursor);
			break;
		default:
			ui->imageLabel->setCursor(Qt::ArrowCursor);
			break;
		}
		break;

	case FillPointState:
	case WhiteLineState:
	case BlackLineState:
	case AnchorRectState:
	case PagePointState:
		switch (theApp.m_state)
		{
		case BaseBegin:
		case BasePress:
			ui->imageLabel->setCursor(Qt::CrossCursor);
			break;
		default:
			ui->imageLabel->setCursor(Qt::ArrowCursor);
			break;
		}

		break;
	case BarCodeState:
	case ClipState:
		switch (theApp.m_state)
		{
		case BaseBegin:
		case BasePress:
			ui->imageLabel->setCursor(Qt::CrossCursor);
			break;
		case BaseRelease:
			{
				QPoint pt = GetImgPosFromClient(pos);
				m_ctrlPointIndex = -1;

				for (int i = 0; i < 9; ++i)
				{
					if (m_controlPoint[i].contains(pt.x(), pt.y()))
					{
						m_ctrlPointIndex = i;
						break;
					}
				}

				switch (m_ctrlPointIndex)
				{
				case TOP_LEFT:
				case BOTTOM_RIGHT:
					ui->imageLabel->setCursor(Qt::SizeFDiagCursor);
					break;
				case TOP_RIGHT:
				case BOTTOM_LEFT:
					ui->imageLabel->setCursor(Qt::SizeBDiagCursor);
					break;
				case LEFT:
				case RIGHT:
					ui->imageLabel->setCursor(Qt::SizeHorCursor);
					break;
				case TOP:
				case BOTTOM:
					ui->imageLabel->setCursor(Qt::SizeVerCursor);
					break;
				case CENTER:
					ui->imageLabel->setCursor(Qt::SizeAllCursor);
					break;
				default:
					ui->imageLabel->setCursor(Qt::ArrowCursor);
					break;
				}//switch (m_ctrlPointIndex)
				break;
			}//case 3
		case BaseEnd:
			{
				if (m_isZooming)
				{
					QPoint pt = GetImgPosFromClient(pos);
					m_ctrlPointIndex = -1;

					for (int i = 0; i < 9; ++i)
					{
						if (m_controlPoint[i].contains(pt.x(), pt.y()))
						{
							m_ctrlPointIndex = i;
							break;
						}
					}

					switch (m_ctrlPointIndex)
					{
					case TOP_LEFT:
					case BOTTOM_RIGHT:
						ui->imageLabel->setCursor(Qt::SizeFDiagCursor);
						break;
					case TOP_RIGHT:
					case BOTTOM_LEFT:
						ui->imageLabel->setCursor(Qt::SizeBDiagCursor);
						break;
					case LEFT:
					case RIGHT:
						ui->imageLabel->setCursor(Qt::SizeHorCursor);
						break;
					case TOP:
					case BOTTOM:
						ui->imageLabel->setCursor(Qt::SizeVerCursor);
						break;
					case CENTER:
						ui->imageLabel->setCursor(Qt::SizeAllCursor);
						break;
					default:
						ui->imageLabel->setCursor(Qt::ArrowCursor);
						break;
					}//switch (m_ctrlPointIndex)
				}
				else
				{
					ui->imageLabel->setCursor(Qt::ArrowCursor);
				}
			break;
			}
		default:
			ui->imageLabel->setCursor(Qt::ArrowCursor);
			break;
		}//case 6
		break;
	case QuestionState:
		switch (theApp.m_state)
		{
		case SingleBegin:
		case SinglePress:
		case MultiBegin:
		case MultiPress:
			ui->imageLabel->setCursor(Qt::CrossCursor);
			break;
		default:
			ui->imageLabel->setCursor(Qt::ArrowCursor);
			break;
		}
		break;

	case MarkerState:
		switch (theApp.m_state)
		{
		case RowBegin:
		case RowPress:
		case ColBegin:
		case ColPress:
			ui->imageLabel->setCursor(Qt::CrossCursor);
			break;
		default:
			ui->imageLabel->setCursor(Qt::ArrowCursor);
			break;
		}
		break;

	case MarkerMakeState:
		switch (theApp.m_state)
		{
		case SizeBegin:
		case SizePress:
		case MarkerFirstBegin:
		case MarkerSecondBegin:
			ui->imageLabel->setCursor(Qt::CrossCursor);
			break;

		case MarkerFirstPress:
		case MarkerSecondPress:
			ui->imageLabel->setCursor(Qt::SizeAllCursor);
			break;

		default:
			ui->imageLabel->setCursor(Qt::ArrowCursor);
			break;
		}
		break;

	default:
		ui->imageLabel->setCursor(Qt::ArrowCursor);
		break;
	}
}

void AnswerCardDlg3::anchorProcessingOnMouseUp(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case LTBegin:	
		{
			QPoint img_pos = GetImgPosFromClient(pos);    //获得相对图像位置

			if (!theApp.GetArchorPointRect(img_pos, 0))   //获得定位点矩形并绘制
			{
				QMessageBox::information(NULL, " ", tr("请点击黑色定位点"));
				break;
			}

			update();			
			theApp.m_state = LTEnd;
			break;
		}

	case RTBegin:
		{
			QPoint img_pos = GetImgPosFromClient(pos);

			if (!theApp.GetArchorPointRect(img_pos, 1))			
			{
				QMessageBox::information(NULL, " ", tr("请点击黑色定位点"));
				break;
			}

			update();			
			theApp.m_state = RTEnd;
			break;
		}

	case LBBegin:
		{
			QPoint img_pos = GetImgPosFromClient(pos);

			if (!theApp.GetArchorPointRect(img_pos, 2))			
			{
				QMessageBox::information(NULL, " ", tr("请点击黑色定位点"));
				break;
			}

			update();		
			theApp.m_state = LBEnd;
			break;
		}

	case RBBegin:
		{
			QPoint img_pos = GetImgPosFromClient(pos);

			if (!theApp.GetArchorPointRect(img_pos, 3))			
			{
				QMessageBox::information(NULL, " ", tr("请点击黑色定位点"));
				break;
			}
		
			update();
			theApp.m_state = RBEnd;
			break;
		}
	}//switch (theApp.m_state)
}

void AnswerCardDlg3::barcodeProcessingOnMouseUp(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case BasePress:
		{
			theApp.img_bk.copyTo(theApp.img_show);
			QPoint pt = GetImgPosFromClient(pos);
			cv::Rect rect = cv::Rect(
				cv::Point(m_mouseDownPoint.x(), m_mouseDownPoint.y()),
				cv::Point(pt.x(),pt.y()));

			//绘制控制区域
			m_controlRect = cv::Rect(rect);		
			rectangle(theApp.img_show, m_controlRect, 
				theApp.barcode_color, theApp.barcode_thickness);

			//计算控制点位置
			computeCtrlPointPos();

			//绘制控制点
			for (int i = 0; i < 9; ++i)
			{
				drawControlPoint(m_controlPoint[i].center(), CTRL_POINT_LENGTH,
					theApp.barcode_color, theApp.barcode_thickness);
			}

			theApp.cfp_tmpRect = cv::Rect(m_controlRect);		
			m_barcodeDlg->setAddBtnText(tr("重新框选条形码"));
			m_barcodeDlg->setConfirmBtnEnabled(true);
			theApp.m_state++;
			update();
//			theApp.img_bk.release();
			break;
		}
	case BaseRelease:
		{
			theApp.cfp_tmpRect = cv::Rect(m_controlRect);
			break;
		}
case BaseEnd:
		{
			if (m_isZooming == true)
			{
				theApp.barGroup.at(m_zoomingIndex).pos = m_controlRect;
			}
			break;
		}
	}
}

void AnswerCardDlg3::fillPointProcessingOnMouseUp(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case BasePress:
		{
			//鼠标拖动绘制矩形
			QPoint pt = GetImgPosFromClient(pos);
			cv::Point lt, rb;
			if (pt.x() > m_mouseDownPoint.x())
			{
				if (pt.y() > m_mouseDownPoint.y())
				{
					lt.x = m_mouseDownPoint.x();
					lt.y = m_mouseDownPoint.y();
					rb.x = pt.x();
					rb.y = pt.y();
				}
				else
				{
					lt.x = m_mouseDownPoint.x();
					lt.y = pt.y();
					rb.x = pt.x();
					rb.y = m_mouseDownPoint.y();
				}
			}
			else
			{
				if (pt.y() > m_mouseDownPoint.y())
				{
					lt.x = pt.x();
					lt.y = m_mouseDownPoint.y();
					rb.x = m_mouseDownPoint.x();
					rb.y = pt.y();
				}
				else
				{
					lt.x = pt.x();
					lt.y = pt.y();
					rb.x = m_mouseDownPoint.x();
					rb.y = m_mouseDownPoint.y();
				}
			}

			if (m_fillPointDlg->getFillPointType() == ReferPoint)
			{
				cv::Rect rt = cv::Rect(lt,rb);

				if (rt.width <= 0 || rt.height <=0)
				{
					QMessageBox::information(this," ",tr("请框选识别参考点！"));
					theApp.is_synchronous=false;
					theApp.m_state = BaseBegin;
					return;
				}

				Mat srcGray;
				Mat src;
				theApp.img_raw.copyTo(src);
				if (src.channels()!=1)
				{
					cvtColor(src,srcGray,CV_BGR2GRAY);
				}else
					srcGray=src;

				Mat roi_img=srcGray(rt).clone();
				Mat bw;
				double rectThresh=0.6;//去除干扰轮廓的阈值
				double thresh = threshold(roi_img,bw,100,255,THRESH_BINARY|THRESH_OTSU);
				bw=255-bw;

				vector<vector<Point> > contours;
				findContours(bw,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );

				if (contours.size()==0)
				{
					QMessageBox::information(this," ",tr("请框选识别参考点！"));
					theApp.is_synchronous=false;
					theApp.m_state = BaseBegin;
					return;
				}
				else
				{
					//获取contour
					cv::Rect contourRect = boundingRect(contours.at(0));
					contourRect.x += m_mouseDownPoint.x();
					contourRect.y += m_mouseDownPoint.y();
					theApp.referPoint.push_back(cv::Rect(contourRect));
				}
			}
			else
			{

				int count = m_fillPointDlg->getOptionCount();
				cv::Range range = m_fillPointDlg->getOptionRange();
				bool isHorizontal = m_fillPointDlg->isCrossWise();
				bool isSingleChoice = m_fillPointDlg->isSingleChecked();
				int cSpace = m_fillPointDlg->getCSpace();
				int rSpace = m_fillPointDlg->getRSpace();
				string name = m_fillPointDlg->getFillPointName();
				FillingPointsType type = m_fillPointDlg->getFillPointType();
				int numberOfRect = 0;
				int numberOfOption = 0;

				if (isHorizontal)
				{
					numberOfRect = (range.start - 1) * cSpace + range.start;
					numberOfOption = (count - 1) * rSpace + count;
				}
				else
				{
					numberOfRect = (range.start - 1) * rSpace + range.start;
					numberOfOption = (count - 1) * cSpace + count;
				}

				theApp.AddFillPoint(name, type, isHorizontal, isSingleChoice, 
					numberOfRect, cSpace, rSpace, lt, rb, numberOfOption);
			}
			theApp.m_state++;
			theApp.img_bk.release();

			//控制自定义窗口按钮
			m_fillPointDlg->setAddBtnText(tr("重新框选填涂点"));
			m_fillPointDlg->setConfirmBtnEnabled(true);
			break;
		}
	}
}

void AnswerCardDlg3::clipProcessingOnMouseUp(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case BasePress:
		{
			theApp.img_bk.copyTo(theApp.img_show);
			QPoint pt = GetImgPosFromClient(pos);
			cv::Rect rect = cv::Rect(
				cv::Point(m_mouseDownPoint.x(), m_mouseDownPoint.y()),
				cv::Point(pt.x(),pt.y()));

			//绘制控制区域
			m_controlRect = cv::Rect(rect);		
			rectangle(theApp.img_show, m_controlRect, 
				theApp.cropArea_color, theApp.cropArea_thickness);

			//计算控制点位置
			computeCtrlPointPos();

			//绘制控制点
			for (int i = 0; i < 9; ++i)
			{
				drawControlPoint(m_controlPoint[i].center(), CTRL_POINT_LENGTH,
					theApp.cropArea_color, theApp.cropArea_thickness);
			}

			theApp.cfp_tmpRect = cv::Rect(m_controlRect);		
			m_clipDlg->setConfirmBtnEnabled(true);
			theApp.m_state++;
			update();
//			theApp.img_bk.release();
			break;
		}
	case BaseRelease:
		{
			theApp.cfp_tmpRect = cv::Rect(m_controlRect);
			break;
		}
	case BaseEnd:
		{
			if (m_isZooming == true)
			{
				theApp.cropAreas.at(m_zoomingIndex).pos = m_controlRect;
			}
			break;
		}
	}
}

void AnswerCardDlg3::questionProcessingOnMouseUp(const QPoint &pos)
{
	if (theApp.m_state != SinglePress && theApp.m_state != MultiPress)
	{
		return;
	}

	QPoint pt = GetImgPosFromClient(pos);//转换到图像坐标
	int idx_l, idx_r, idx_t, idx_b;      //计算对应标记点
	int markerId = m_fillPointDlg->getMarkerId();

	if (pt.x() > m_mouseDownPoint.x())
	{
		if (pt.y() > m_mouseDownPoint.y())
		{
			idx_l = theApp.markersTable[markerId].GetNearestLBoundary(m_mouseDownPoint.x());
			idx_t = theApp.markersTable[markerId].GetNearestTBoundary(m_mouseDownPoint.y());
			idx_r = theApp.markersTable[markerId].GetNearestRBoundary(pt.x());
			idx_r = idx_r < idx_l ? idx_l : idx_r;
			idx_b = theApp.markersTable[markerId].GetNearestBBoundary(pt.y());
			idx_b = idx_b < idx_t ? idx_t : idx_b;
		}
		else
		{
			idx_l = theApp.markersTable[markerId].GetNearestLBoundary(m_mouseDownPoint.x());
			idx_t = theApp.markersTable[markerId].GetNearestTBoundary(pt.y());
			idx_r = theApp.markersTable[markerId].GetNearestRBoundary(pt.x());
			idx_r = idx_r < idx_l ? idx_l : idx_r;
			idx_b = theApp.markersTable[markerId].GetNearestBBoundary(m_mouseDownPoint.y());
			idx_b = idx_b < idx_t ? idx_t : idx_b;
		}
	}//if (pt.x() > m_mouseDownPoint.x())
	else
	{
		if (pt.y() > m_mouseDownPoint.y())
		{
			idx_l = theApp.markersTable[markerId].GetNearestLBoundary(pt.x());
			idx_t = theApp.markersTable[markerId].GetNearestTBoundary(m_mouseDownPoint.y());
			idx_r = theApp.markersTable[markerId].GetNearestRBoundary(m_mouseDownPoint.x());
			idx_r = idx_r < idx_l ? idx_l : idx_r;
			idx_b = theApp.markersTable[markerId].GetNearestBBoundary(pt.y());
			idx_b = idx_b < idx_t ? idx_t : idx_b;
		}
		else
		{
			idx_l = theApp.markersTable[markerId].GetNearestLBoundary(pt.x());
			idx_t = theApp.markersTable[markerId].GetNearestTBoundary(pt.y());
			idx_r = theApp.markersTable[markerId].GetNearestRBoundary(m_mouseDownPoint.x());
			idx_r = idx_r < idx_l ? idx_l : idx_r;
			idx_b = theApp.markersTable[markerId].GetNearestBBoundary(m_mouseDownPoint.y());
			idx_b = idx_b < idx_t ? idx_t : idx_b;
		}
	}//else if(pt.x() <= m_mouseDownPoint.x())

	int count = m_fillPointDlg->getOptionCount();
	cv::Range range = m_fillPointDlg->getOptionRange();
	bool isHorizontal = m_fillPointDlg->isCrossWise();
	int cSpace = m_fillPointDlg->getCSpace();
	int rSpace = m_fillPointDlg->getRSpace();

	if (isHorizontal)
	{
		if (idx_b - idx_t != range.size() * (cSpace + 1))
		{
			if (theApp.m_state == SinglePress)
			{
				QMessageBox::information(NULL, " ", 
					tr("框选错误，一个横向选择题只能对应一行！"));
				theApp.m_state = SingleBegin;
			}
			else if(theApp.m_state == MultiPress)
			{
				QMessageBox::information(NULL, " ", 
					tr("框选错误，题数与输入题号范围不对应！"));
				theApp.m_state = MultiBegin;
			}
			theApp.is_synchronous = false;
			update();
			return;
		}
		else if (idx_r - idx_l != (count - 1) * rSpace + count - 1)
		{
			if (theApp.m_state == SinglePress)
			{
				theApp.m_state = SingleBegin;
			}
			else if(theApp.m_state == MultiPress)
			{
				theApp.m_state = MultiBegin;
			}	

			QMessageBox::information(NULL, " ", 
				tr("框选错误，选项数量不对应！"));
			theApp.is_synchronous = false;
			update();
			return;
		}
	}//if (isHorizontal)
	else
	{
		if (idx_r - idx_l != range.size() * (rSpace + 1))
		{
			if (theApp.m_state == SinglePress)
			{
				QMessageBox::information(NULL, " ", 
						tr("框选错误，一个纵向选择题只能对应一列！"));
				theApp.m_state = SingleBegin;
			}
			else if (theApp.m_state == MultiPress)
			{
				QMessageBox::information(NULL, " ", 
					tr("框选错误，题数与输入题号范围不对应！"));
				theApp.m_state = MultiBegin;
			}
			
			theApp.is_synchronous = false;
			update();
			return;
		}
		else if (idx_b - idx_t != (count - 1) * cSpace + count - 1)
		{
			if (theApp.m_state == SinglePress)
			{
				theApp.m_state = SingleBegin;
			}
			else if (theApp.m_state == MultiPress)
			{
				theApp.m_state = MultiBegin;
			}

			QMessageBox::information(NULL, " ", 
					tr("框选错误，选项数量不对应！"));
			theApp.is_synchronous = false;
			update();
			return;
		}
	}

	m_fillPointDlg->setIdx_l(idx_l);
	m_fillPointDlg->setIdx_r(idx_r);
	m_fillPointDlg->setIdx_b(idx_b);
	m_fillPointDlg->setIdx_t(idx_t);

	if (isHorizontal)
	{
		int space = m_fillPointDlg->getCSpace();
		int rspace = m_fillPointDlg->getRSpace();
		int rowId = idx_t;
		ushort markerId = m_fillPointDlg->getMarkerId();

		for (int i = idx_t; rowId <= idx_b; i++)
		{
			theApp.AddQuestion(
				m_fillPointDlg->getOptionRange().start + i - idx_t, 
				markerId,
				m_fillPointDlg->isCrossWise(), 
				m_fillPointDlg->isSingleChecked(),
				rspace,
				rowId, idx_l, idx_r);

			rowId += space + 1;
		}
	}
	else
	{
		int space = m_fillPointDlg->getRSpace();
		int cspace = m_fillPointDlg->getCSpace();
		int columnId = idx_l;
		ushort markerId = m_fillPointDlg->getMarkerId();

		for (int i = idx_l; columnId <= idx_r; i++)
		{
			theApp.AddQuestion(
				m_fillPointDlg->getOptionRange().start + i - idx_l, 
				markerId,
				m_fillPointDlg->isCrossWise(), 
				m_fillPointDlg->isSingleChecked(),
				cspace,
				columnId, idx_t, idx_b);

			columnId += space + 1;
		}
	}

	//控制状态
	theApp.m_state++;
	theApp.is_synchronous = false;
	m_fillPointDlg->setAddBtnText(tr("重新框选填涂区域"));
	m_fillPointDlg->setConfirmBtnEnabled(true);
}

void AnswerCardDlg3::whiteLineProcessingOnMouseUp(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case BasePress:
		{
			QPoint img_pos = GetImgPosFromClient(pos);
			cv::Rect rect = cv::Rect(cv::Point(m_mouseDownPoint.x(),m_mouseDownPoint.y()),
				cv::Point(img_pos.x(),img_pos.y()));

			theApp.whiteLineRect = cv::Rect(rect);
			m_lineDetectDlg->setWhiteLineBtnText(tr("重新框选白检测线"));
			m_lineDetectDlg->setProcessing(false);
			lineDetectDone();

			theApp.m_state++;
			theApp.img_bk.release();
			break;
		}
	}//switch (theApp.m_state)
}

void AnswerCardDlg3::blackLineProcessingOnMouseUp(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case BasePress:
		{
			QPoint img_pos = GetImgPosFromClient(pos);
			cv::Rect rect = cv::Rect(cv::Point(m_mouseDownPoint.x(),m_mouseDownPoint.y()),
				cv::Point(img_pos.x(),img_pos.y()));

			Mat srcGray;
			Mat src;
			theApp.img_raw.copyTo(src);
			if (src.channels()!=1)
			{
				cvtColor(src,srcGray,CV_BGR2GRAY);
			}else
				srcGray=src;

			Mat roi_img=srcGray(rect).clone();
			Mat bw;
			double rectThresh=0.6;//去除干扰轮廓的阈值
			double thresh = threshold(roi_img,bw,100,255,THRESH_BINARY|THRESH_OTSU);
			bw=255-bw;

			vector<vector<Point> > contours;
			findContours(bw,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );
			if (contours.size()==0)
			{
				QMessageBox::information(this," ",tr("请框选黑检测线！"));
				theApp.is_synchronous=false;
				theApp.m_state = BaseBegin;
				return;
			}
			else
			{
				//获取contour
				cv::Rect contourRect = boundingRect(contours.at(0));
				contourRect.x += m_mouseDownPoint.x();
				contourRect.y += m_mouseDownPoint.y();
				theApp.blackLineRect = cv::Rect(contourRect);
			}
			
			m_lineDetectDlg->setBlackLineBtnText(tr("重新框选黑检测线"));
			m_lineDetectDlg->setProcessing(false);
			lineDetectDone();
			theApp.is_synchronous = false;
			theApp.m_state++;
			theApp.img_bk.release();
			break;
		}
	}//switch (theApp.m_state)
}

void AnswerCardDlg3::makerMakeProcessingOnMouseUp(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case SizePress:
		{
			theApp.img_bk.copyTo(theApp.img_show);
			QPoint pt = GetImgPosFromClient(pos);
			cv::Rect rect = cv::Rect(
				cv::Point(m_mouseDownPoint.x(), m_mouseDownPoint.y()),
				cv::Point(pt.x(),pt.y()));

			if (rect.width <= 0 || rect.height <= 0)
			{
				QMessageBox::information(this, tr(" "),
					tr("标记点的宽或高不能为零，请重新拖曳！"));

				theApp.m_state = SizeBegin;
				break;
			}
			m_markerMakeDlg->setMarkerSize(rect.size());
			m_markerMakeDlg->setSizeEditText(QString("(%1, %2)")
				.arg(rect.size().width).arg(rect.size().height));
			m_markerMakeDlg->setSizeBtnText(tr("拖曳大小"));
			m_markerMakeDlg->setProcessing(false);

			theApp.img_bk.release();
			theApp.m_state++;
			ui->imageLabel->setCursor(Qt::ArrowCursor);

			if (m_markerMakeDlg->isEditing() == false)
			{
				enableDlg();
			}
			else
			{
				m_markerMakeDlg->setDelBtnEnabled(false);
				m_markerMakeDlg->setEditBtnEnabled(false);
				m_markerMakeDlg->setListEnabled(false);
			}

			update();

			break;
		}
	case MarkerFirstPress:
		{
			if (m_markerMakeDlg->getInputNumber() > 1)
			{
				theApp.m_state = MarkerSecondBegin;
			}
			else
			{
				m_markerMakeDlg->setHorBtnText(tr("绘制"));
				m_markerMakeDlg->setVerBtnText(tr("绘制"));
				m_markerMakeDlg->setProcessing(false);

				if (m_markerMakeDlg->isEditing() == false)
				{
					enableDlg();
				}
				else
				{
					m_markerMakeDlg->setDelBtnEnabled(false);
					m_markerMakeDlg->setEditBtnEnabled(false);
					m_markerMakeDlg->setListEnabled(false);
				}

				m_markerMakeDlg->updatePerMarker();
				theApp.m_state = MarkerFirstRelease;
				ui->imageLabel->setCursor(Qt::ArrowCursor);
				theApp.is_synchronous = false;
			}

			theApp.img_bk.release();
			//enableDlg();
			update();
			break;
		}

	case MarkerSecondPress:
		{
			theApp.m_state++;
			ui->imageLabel->setCursor(Qt::ArrowCursor);
			m_markerMakeDlg->setHorBtnText(tr("绘制"));
			m_markerMakeDlg->setVerBtnText(tr("绘制"));
			m_markerMakeDlg->setProcessing(false);
			m_markerMakeDlg->updatePerMarker();
			theApp.img_bk.release();
			theApp.is_synchronous = false;

			if (m_markerMakeDlg->isEditing() == false)
			{
				enableDlg();
			}
			else
			{
				m_markerMakeDlg->setDelBtnEnabled(false);
				m_markerMakeDlg->setEditBtnEnabled(false);
				m_markerMakeDlg->setListEnabled(false);
			}

			update();
			break;
		}
	}
}

void AnswerCardDlg3::anchorRectProcessingOnMouseUp(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case BasePress:
		{
			QPoint img_pos = GetImgPosFromClient(pos);
			cv::Rect rect = cv::Rect(cv::Point(m_mouseDownPoint.x(),m_mouseDownPoint.y()),
				cv::Point(img_pos.x(),img_pos.y()));

			if (rect.width <= 0 || rect.height <= 0)
			{
				QMessageBox::information(this," ",tr("请重新框选定位框！"));
				theApp.m_state = BaseBegin;
				return;
			}

			theApp.anchorRect = cv::Rect(rect);
			m_anchorRectDlg->setAnchorBtnText(tr("重新框选定位框"));

			theApp.m_state++;
			theApp.img_bk.release();
			break;
		}
	}//switch (theApp.m_state)
}

void AnswerCardDlg3::pagePointProcessingOnMouseUp(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case BasePress:
		{
			QPoint img_pos = GetImgPosFromClient(pos);
			cv::Rect rect = cv::Rect(cv::Point(m_mouseDownPoint.x(),m_mouseDownPoint.y()),
				cv::Point(img_pos.x(),img_pos.y()));

			Mat srcGray;
			Mat src;
			theApp.img_raw.copyTo(src);
			if (src.channels()!=1)
			{
				cvtColor(src,srcGray,CV_BGR2GRAY);
			}else
				srcGray=src;

			Mat roi_img=srcGray(rect).clone();
			Mat bw;
			double rectThresh=0.6;//去除干扰轮廓的阈值
			double thresh = threshold(roi_img,bw,100,255,THRESH_BINARY|THRESH_OTSU);
			bw=255-bw;

			vector<vector<Point> > contours;
			findContours(bw,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE );

			if (contours.size()==0)
			{
				QMessageBox::information(this," ",tr("请框选页码标识！"));
				theApp.is_synchronous=false;
				theApp.m_state = BaseBegin;
				return;
			}
			else
			{
				//获取contour
				cv::Rect contourRect = boundingRect(contours.at(0));
				contourRect.x += m_mouseDownPoint.x();
				contourRect.y += m_mouseDownPoint.y();
				theApp.pagePoint.push_back(contourRect);
			}

			m_pagePointDlg->setAddBtnText(tr("重新框选"));
			m_pagePointDlg->setConfirmBtnEnabled(true);
			theApp.is_synchronous = false;
			theApp.img_bk.release();
			theApp.m_state++;
			break;
		}
	}//switch (theApp.m_state)
}

void AnswerCardDlg3::markerProcessingOnMouseUp(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case RowPress:
		{
			QPoint img_pos = GetImgPosFromClient(pos);
			theApp.markersRect[0] = cv::Rect(
				cv::Point(m_mouseDownPoint.x(), m_mouseDownPoint.y()),
				cv::Point(img_pos.x(),img_pos.y()));
		
			if (theApp.markersRect[0].width == 0)
			{
				QMessageBox::information(NULL, " ", tr("选择区域中没有检测到标记点\n请重新选择"));
				theApp.m_state = RowBegin;
				theApp.is_synchronous = false;
				update();
				return;
			}
			else
			{
				//计算标记点数量
				vector<cv::Rect> hmarkers = theApp.GetMarkersNum(theApp.img_bw(theApp.markersRect[0]));

				if (hmarkers.size()==0)
				{
					QMessageBox::information(NULL, " ", tr("选择区域中没有检测到标记点\n请重新选择"));
					theApp.m_state = RowBegin;
					theApp.is_synchronous = false;
					update();
					return;
				}
				else
				{
					//加上偏移值
					for (int i = hmarkers.size()-1; i>=0; i--)
					{
						hmarkers.at(i).x += m_mouseDownPoint.x();
						hmarkers.at(i).y += m_mouseDownPoint.y();
					}

					theApp.hmarkers = hmarkers;
					theApp.SortMarkers(true);

					m_markerMakeDlg->setProcessing(false);
					m_markerMakeDlg->updatePerMarker();
					m_markerMakeDlg->setHDragBtnText(tr("拖曳"));
					theApp.img_bk.release();
					theApp.is_synchronous = false;

					if (m_markerMakeDlg->isEditing() == false)
					{
						enableDlg();
					}
					else
					{
						m_markerMakeDlg->setDelBtnEnabled(false);
						m_markerMakeDlg->setEditBtnEnabled(false);
						m_markerMakeDlg->setListEnabled(false);
					}

					theApp.is_synchronous = false;
					theApp.m_state = RowRelease;
					update();
				}
			}
			break;
		}

	case ColPress:
		{
			QPoint img_pos = GetImgPosFromClient(pos);
			theApp.markersRect[1] = cv::Rect(
				cv::Point(m_mouseDownPoint.x(),m_mouseDownPoint.y()),
				cv::Point(img_pos.x(),img_pos.y()));

			if (theApp.markersRect[1].width == 0)
			{
				QMessageBox::information(NULL, " ", tr("选择区域中没有检测到标记点\n请重新选择"));
				theApp.m_state = ColBegin;
				theApp.is_synchronous = false;
				update();
				return;
			}
			else
			{
				//计算标记点数量
				vector<cv::Rect> vmarkers = theApp.GetMarkersNum(theApp.img_bw(theApp.markersRect[1]));

				if (vmarkers.size()==0)
				{
					QMessageBox::information(NULL, " ", tr("选择区域中没有检测到标记点\n请重新选择"));
					theApp.m_state = ColBegin;
					theApp.is_synchronous = false;
					update();
					return;
				}
				else
				{

					//加上偏移值
					for (int i = vmarkers.size()-1; i>=0; i--)
					{
						vmarkers.at(i).x += m_mouseDownPoint.x();
						vmarkers.at(i).y += m_mouseDownPoint.y();
					}

					theApp.vmarkers = vmarkers;
					theApp.SortMarkers(false);

					m_markerMakeDlg->setProcessing(false);
					m_markerMakeDlg->updatePerMarker();
					m_markerMakeDlg->setVDragBtnText(tr("拖曳"));
					theApp.img_bk.release();
					theApp.is_synchronous = false;

					if (m_markerMakeDlg->isEditing() == false)
					{
						enableDlg();
					}
					else
					{
						m_markerMakeDlg->setDelBtnEnabled(false);
						m_markerMakeDlg->setEditBtnEnabled(false);
						m_markerMakeDlg->setListEnabled(false);
					}
					update();
					theApp.m_state = ColRelease;
				}
			}		
			break;
		}
	
	}
}

void AnswerCardDlg3::barcodeProcessingOnMouseMove(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case BasePress:
		{
			//鼠标拖动绘制矩形
			QPoint pt = GetImgPosFromClient(pos);
			cv::Rect rt(cv::Point(m_mouseDownPoint.x(), m_mouseDownPoint.y()),
				cv::Point(pt.x(),pt.y()));
			theApp.img_bk.copyTo(theApp.img_show);
			rectangle(theApp.img_show, rt, theApp.barcode_color, theApp.barcode_thickness);

			update();
			break;
		}
		break;
		
	//处于自由变换控制区域状态
	case BaseRelease:
		{
			//如果鼠标没有击中控制点，则返回
			if (m_ctrlPointIndex == -1)
			{
				break;
			}
			else
			{
				QPoint pt = GetImgPosFromClient(pos);

				//恢复图像
				theApp.img_bk.copyTo(theApp.img_show);

				//重绘控制区域，计算控制点位置
				dragMarquee(pt, m_ctrlPointIndex);
				rectangle(theApp.img_show, m_controlRect, theApp.barcode_color, theApp.barcode_thickness);

				computeCtrlPointPos();

				//绘制控制点
				for (int i = 0; i < 9; ++i)
				{
					drawControlPoint(m_controlPoint[i].center(), CTRL_POINT_LENGTH, 
						theApp.barcode_color, theApp.barcode_thickness);
				}

				//更新到视图上
				update();
			}			
		}
		break;
	case BaseEnd:
		{
			if (m_isZooming == true)
			{
				//如果鼠标没有击中控制点，则返回
				if (m_ctrlPointIndex == -1)
				{
					break;
				}
				else
				{
					QPoint pt = GetImgPosFromClient(pos);

					//恢复图像
					theApp.img_bk.copyTo(theApp.img_show);

					//重绘控制区域，计算控制点位置
					dragMarquee(pt, m_ctrlPointIndex);
					//theApp.barGroup.at(m_zoomingIndex).pos = m_controlRect;
					
					rectangle(theApp.img_show, m_controlRect, 
						theApp.barcode_color, theApp.barcode_thickness);
					//update();

					computeCtrlPointPos();

					//绘制控制点
					for (int i = 0; i < 9; ++i)
					{
						drawControlPoint(m_controlPoint[i].center(), CTRL_POINT_LENGTH,theApp.barcode_color, theApp.barcode_thickness);
					}

					//更新到视图上
					update();
				}	
			}
		}
		break;
	}
}

void AnswerCardDlg3::fillPointProcessingOnMouseMove(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case BasePress:
		{
			//鼠标拖动绘制矩形
			QPoint pt = GetImgPosFromClient(pos);
			cv::Point lt, rb;
			if (pt.x() > m_mouseDownPoint.x())
			{
				if (pt.y() > m_mouseDownPoint.y())
				{
					lt.x = m_mouseDownPoint.x();
					lt.y = m_mouseDownPoint.y();
					rb.x = pt.x();
					rb.y = pt.y();
				}
				else
				{
					lt.x = m_mouseDownPoint.x();
					lt.y = pt.y();
					rb.x = pt.x();
					rb.y = m_mouseDownPoint.y();
				}
			}
			else
			{
				if (pt.y() > m_mouseDownPoint.y())
				{
					lt.x = pt.x();
					lt.y = m_mouseDownPoint.y();
					rb.x = m_mouseDownPoint.x();
					rb.y = pt.y();
				}
				else
				{
					lt.x = pt.x();
					lt.y = pt.y();
					rb.x = m_mouseDownPoint.x();
					rb.y = m_mouseDownPoint.y();
				}
			}

			if (m_fillPointDlg->getFillPointType() == ReferPoint)
			{
				theApp.img_bk.copyTo(theApp.img_show);
				rectangle(theApp.img_show, lt,rb, theApp.cfp_color, theApp.cfp_thickness);
			}
			else
			{
				int optionCount = m_fillPointDlg->getOptionCount();
				cv::Range range = m_fillPointDlg->getOptionRange();
				bool isHorizontal = m_fillPointDlg->isCrossWise();
				int cSpace = m_fillPointDlg->getCSpace();
				int rSpace = m_fillPointDlg->getRSpace();
				theApp.img_bk.copyTo(theApp.img_show);

				if (isHorizontal)
				{
					int number = (range.start - 1) * cSpace + range.start;
					int option = (optionCount - 1) * rSpace + optionCount;
					int horSpace = (rb.x - lt.x) / option;
					int verSpace = (rb.y - lt.y) / number;
					rb.x = lt.x + option * horSpace;
					rb.y = lt.y + number * verSpace;

					for (int i = 0; i < number + 1; ++i)
					{
						cv::Point start(lt.x, lt.y + verSpace * i);
						cv::Point end(rb.x, lt.y + verSpace * i);
						line(theApp.img_show, start, end,theApp.cfp_color, theApp.cfp_thickness);
					}

					for (int i = 0; i < option + 1; ++i)
					{
						cv::Point start(lt.x + horSpace * i, lt.y);
						cv::Point end(lt.x + horSpace * i, rb.y);
						line(theApp.img_show, start, end,theApp.cfp_color, theApp.cfp_thickness);
					}
				}
				else
				{
					int number = (range.start - 1) * rSpace + range.start;
					int option = (optionCount - 1) * cSpace + optionCount;
					int horSpace = (rb.x - lt.x) / number;
					int verSpace = (rb.y - lt.y) / option;
					rb.x = lt.x + horSpace * number;
					rb.y = lt.y + verSpace * option;

					for (int i = 0; i < option + 1; ++i)
					{
						cv::Point start(lt.x, lt.y + verSpace * i);
						cv::Point end(rb.x, lt.y + verSpace * i);
						line(theApp.img_show, start, end,theApp.cfp_color, theApp.cfp_thickness);
					}

					for (int i = 0; i < number + 1; ++i)
					{
						cv::Point start(lt.x + horSpace * i, lt.y);
						cv::Point end(lt.x + horSpace * i, rb.y);
						line(theApp.img_show, start, end,theApp.cfp_color, theApp.cfp_thickness);
					}
				}
			}
			update();
			break;
		}
	}
}

void AnswerCardDlg3::clipProcessingOnMouseMove(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case BasePress:
		{
			//鼠标拖动绘制矩形
			QPoint pt = GetImgPosFromClient(pos);
			cv::Rect rt(cv::Point(m_mouseDownPoint.x(), m_mouseDownPoint.y()),
				cv::Point(pt.x(),pt.y()));
			theApp.img_bk.copyTo(theApp.img_show);
			rectangle(theApp.img_show, rt, theApp.cropArea_color, 
				theApp.cropArea_thickness);

			update();
			break;
		}
		break;
		
	//处于自由变换控制区域状态
	case BaseRelease:
		{
			//如果鼠标没有击中控制点，则返回
			if (m_ctrlPointIndex == -1)
			{
				break;
			}
			else
			{
				QPoint pt = GetImgPosFromClient(pos);

				//恢复图像
				theApp.img_bk.copyTo(theApp.img_show);

				//重绘控制区域，计算控制点位置
				dragMarquee(pt, m_ctrlPointIndex);
				rectangle(theApp.img_show, m_controlRect, theApp.cropArea_color, theApp.cropArea_thickness);

				computeCtrlPointPos();

				//绘制控制点
				for (int i = 0; i < 9; ++i)
				{
					drawControlPoint(m_controlPoint[i].center(), CTRL_POINT_LENGTH, 
						theApp.cropArea_color, theApp.cropArea_thickness);
				}

				//更新到视图上
				update();
			}			
		}
		break;
	case BaseEnd:
		{
			if (m_isZooming == true)
			{
				//如果鼠标没有击中控制点，则返回
				if (m_ctrlPointIndex == -1)
				{
					break;
				}
				else
				{
					QPoint pt = GetImgPosFromClient(pos);
					

					//恢复图像
					//theApp.img_bk.copyTo(theApp.img_show);

					//重绘控制区域，计算控制点位置
					dragMarquee(pt, m_ctrlPointIndex);
					theApp.img_bk.copyTo(theApp.img_show);
					rectangle(theApp.img_show, m_controlRect, 
						theApp.cropArea_color, theApp.cropArea_thickness);

					computeCtrlPointPos();

					//绘制控制点
					for (int i = 0; i < 9; ++i)
					{
						drawControlPoint(m_controlPoint[i].center(), CTRL_POINT_LENGTH,theApp.cropArea_color, theApp.cropArea_thickness);
					}

					//更新到视图上
					update();
				}	
			}
		}
		break;
	}
}

void AnswerCardDlg3::questionProcessingOnMouseMove(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case SinglePress:
	case MultiPress:
		{
			//鼠标拖动绘制矩形
			QPoint pt = GetImgPosFromClient(pos);
			cv::Point lt, rb;
			int markerId = m_fillPointDlg->getMarkerId();

			if (pt.x() > m_mouseDownPoint.x())
			{
				if (pt.y() > m_mouseDownPoint.y())
				{
					int idx_l = theApp.markersTable[markerId].GetNearestLBoundary(m_mouseDownPoint.x());
					int idx_t = theApp.markersTable[markerId].GetNearestTBoundary(m_mouseDownPoint.y());
					int idx_r = theApp.markersTable[markerId].GetNearestRBoundary(pt.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					int idx_b = theApp.markersTable[markerId].GetNearestBBoundary(pt.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
					lt.x = theApp.markersTable[markerId].GetLBoundary(idx_l);
					lt.y = theApp.markersTable[markerId].GetTBoundary(idx_t);
					rb.x = theApp.markersTable[markerId].GetRBoundary(idx_r);
					rb.y = theApp.markersTable[markerId].GetBBoundary(idx_b);
				}
				else
				{
					int idx_l = theApp.markersTable[markerId].GetNearestLBoundary(m_mouseDownPoint.x());
					int idx_t = theApp.markersTable[markerId].GetNearestTBoundary(pt.y());
					int idx_r = theApp.markersTable[markerId].GetNearestRBoundary(pt.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					int idx_b = theApp.markerBT.GetNearestBBoundary(m_mouseDownPoint.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
					lt.x = theApp.markersTable[markerId].GetLBoundary(idx_l);
					lt.y = theApp.markersTable[markerId].GetTBoundary(idx_t);
					rb.x = theApp.markersTable[markerId].GetRBoundary(idx_r);
					rb.y = theApp.markersTable[markerId].GetBBoundary(idx_b);
				}
			}
			else
			{
				if (pt.y() > m_mouseDownPoint.y())
				{
					int idx_l = theApp.markersTable[markerId].GetNearestLBoundary(pt.x());
					int idx_t = theApp.markersTable[markerId].GetNearestTBoundary(m_mouseDownPoint.y());
					int idx_r = theApp.markersTable[markerId].GetNearestRBoundary(m_mouseDownPoint.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					int idx_b = theApp.markerBT.GetNearestBBoundary(pt.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
					lt.x = theApp.markersTable[markerId].GetLBoundary(idx_l);
					lt.y = theApp.markersTable[markerId].GetTBoundary(idx_t);
					rb.x = theApp.markersTable[markerId].GetRBoundary(idx_r);
					rb.y = theApp.markersTable[markerId].GetBBoundary(idx_b);
				}
				else
				{
					int idx_l = theApp.markersTable[markerId].GetNearestLBoundary(pt.x());
					int idx_t = theApp.markersTable[markerId].GetNearestTBoundary(pt.y());
					int idx_r = theApp.markersTable[markerId].GetNearestRBoundary(m_mouseDownPoint.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					int idx_b = theApp.markerBT.GetNearestBBoundary(m_mouseDownPoint.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
					lt.x = theApp.markersTable[markerId].GetLBoundary(idx_l);
					lt.y = theApp.markersTable[markerId].GetTBoundary(idx_t);
					rb.x = theApp.markersTable[markerId].GetRBoundary(idx_r);
					rb.y = theApp.markersTable[markerId].GetBBoundary(idx_b);
				}
			}

			theApp.img_bk.copyTo(theApp.img_show);
			rectangle(theApp.img_show, lt, rb,theApp.cfp_color, theApp.cfp_thickness);

			update();
			break;
		}
	}
}

void AnswerCardDlg3::makerMakeProcessingOnMouseMove(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case SizePress:
		{
			//鼠标拖动绘制矩形
			QPoint pt = GetImgPosFromClient(pos);
			cv::Rect rt(cv::Point(m_mouseDownPoint.x(), m_mouseDownPoint.y()),
				cv::Point(pt.x(),pt.y()));
			m_markerMakeDlg->setSizeEditText(QString("(%1, %2)")
				.arg(rt.size().width).arg(rt.size().height));
			theApp.img_bk.copyTo(theApp.img_show);
			rectangle(theApp.img_show, rt, theApp.markers_point_color, 
				theApp.markers_point_thickness);

			update();
			break;
		}

	case MarkerFirstPress:
		{
			theApp.img_bk.copyTo(theApp.img_show);
			QPoint pt = GetImgPosFromClient(pos);
			m_markerMakeDlg->dragLastMarker(pt);
			m_markerMakeDlg->drawMarkers();

			update();
			break;
		}

	case MarkerSecondPress:
		{
			theApp.img_bk.copyTo(theApp.img_show);
			QPoint pt = GetImgPosFromClient(pos);
			m_markerMakeDlg->computeMarkerPos(pt);
			m_markerMakeDlg->drawMarkers();

			update();
			break;
		}
	}
}

void AnswerCardDlg3::whiteLineProcessingOnMouseMove(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case BasePress:
		{
			//鼠标拖动绘制矩形
			QPoint pt = GetImgPosFromClient(pos);
			cv::Rect rt(cv::Point(m_mouseDownPoint.x(),m_mouseDownPoint.y()),
				cv::Point(pt.x(),pt.y()));
			theApp.img_bk.copyTo(theApp.img_show);
			rectangle(theApp.img_show, rt, theApp.whiteLine_color, theApp.whiteLine_thickness);

			update();
			break;
		}
	}
}

void AnswerCardDlg3::blackLineProcessingOnMouseMove(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case BasePress:
		{
			//鼠标拖动绘制矩形
			QPoint pt = GetImgPosFromClient(pos);
			cv::Rect rt(cv::Point(m_mouseDownPoint.x(),m_mouseDownPoint.y()),
				cv::Point(pt.x(),pt.y()));
			theApp.img_bk.copyTo(theApp.img_show);
			rectangle(theApp.img_show, rt, theApp.blackLine_color, theApp.blackLine_thickness);

			update();
			break;
		}
	}
}

void AnswerCardDlg3::anchorRectProcessingOnMouseMove(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case BasePress:
		{
			//鼠标拖动绘制矩形
			QPoint pt = GetImgPosFromClient(pos);
			cv::Rect rt(cv::Point(m_mouseDownPoint.x(),m_mouseDownPoint.y()),
				cv::Point(pt.x(),pt.y()));
			theApp.img_bk.copyTo(theApp.img_show);
			rectangle(theApp.img_show, rt, theApp.anchor_point_color, theApp.anchor_point_thickness);

			update();
			break;
		}
	}
}

void AnswerCardDlg3::pagePointProcessingOnMouseMove(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case BasePress:
		{
			//鼠标拖动绘制矩形
			QPoint pt = GetImgPosFromClient(pos);
			cv::Rect rt(cv::Point(m_mouseDownPoint.x(),m_mouseDownPoint.y()),
				cv::Point(pt.x(),pt.y()));
			theApp.img_bk.copyTo(theApp.img_show);
			rectangle(theApp.img_show, rt, theApp.pagePoint_color, theApp.pagePoint_thickness);

			update();
			break;
		}
	}
}

void AnswerCardDlg3::markerProcessingOnMouseMove(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case RowPress:
	case ColPress:
		{
			//鼠标拖动绘制矩形
			QPoint pt = GetImgPosFromClient(pos);
			cv::Rect rt(cv::Point(m_mouseDownPoint.x(), m_mouseDownPoint.y()), 
				cv::Point(pt.x(), pt.y()));
			theApp.img_bk.copyTo(theApp.img_show);
			rectangle(theApp.img_show, rt, theApp.markers_point_color, 
				theApp.markers_point_thickness);
				
			update();				
			break;
		}
	}
}


//在输入的位置上绘制一个控制点
void AnswerCardDlg3::drawControlPoint(const QPoint &centerPos, int length, cv::Scalar scalar, ushort thickness)
{
	int cut = length / 2;
	QPoint pos = QPoint(centerPos);
	
	if (pos.x() - cut < 0)
	{
		pos.setX(cut);
	}
	else if (pos.x() + cut > m_picRect.width())
	{
		pos.setX(m_picRect.width() - cut);
	}

	if (pos.y() - cut < 0)
	{
		pos.setY(cut);
	}
	else if (pos.y() + cut > m_picRect.height())
	{
		pos.setY(m_picRect.height() - cut);
	}

	QPoint topLeft = QPoint(pos.x() - cut, pos.y() - cut);
	QPoint bottomRight = QPoint(pos.x() + cut, pos.y() + cut);

	cv::Rect rt(cv::Point(topLeft.x(), topLeft.y()),
				cv::Point(bottomRight.x(), bottomRight.y()));

	rectangle(theApp.img_show, rt, scalar, thickness);
}

//重新计算九个控制点的位置
void AnswerCardDlg3::computeCtrlPointPos()
{
	m_controlPoint[TOP_LEFT].moveCenter(
		QPoint(m_controlRect.tl().x, m_controlRect.tl().y));

	m_controlPoint[TOP_RIGHT].moveCenter(
		QPoint(m_controlRect.br().x, m_controlRect.tl().y));

	m_controlPoint[BOTTOM_LEFT].moveCenter(
		QPoint(m_controlRect.tl().x, m_controlRect.br().y));

	m_controlPoint[BOTTOM_RIGHT].moveCenter(
		QPoint(m_controlRect.br().x, m_controlRect.br().y));

	m_controlPoint[LEFT].moveCenter(QPoint(m_controlRect.tl().x,
		(m_controlRect.tl().y + m_controlRect.br().y) / 2));

	m_controlPoint[TOP].moveCenter(QPoint(
		(m_controlRect.tl().x + m_controlRect.br().x) / 2, m_controlRect.tl().y));

	m_controlPoint[RIGHT].moveCenter(QPoint(m_controlRect.br().x,
		(m_controlRect.tl().y + m_controlRect.br().y) / 2));

	m_controlPoint[BOTTOM].moveCenter(QPoint(
		(m_controlRect.tl().x + m_controlRect.br().x) / 2, m_controlRect.br().y));

	m_controlPoint[CENTER].moveCenter(QPoint(
		(m_controlRect.tl().x + m_controlRect.br().x) / 2, 
		(m_controlRect.tl().y + m_controlRect.br().y) / 2));
}

//拖曳选取区域并重绘
void AnswerCardDlg3::dragMarquee(const QPoint &imgPos, int ctlPointIndex)
{
	int index = ctlPointIndex;
	QPoint pos = imgPos;

	switch (index)
	{
	case TOP_LEFT:
		{
			cv::Point tl(pos.x(), pos.y());
			cv::Point br(m_controlRect.br());

			if (tl.x + CTRL_RECT_MIN_LENGTH > br.x)
			{
				tl = cv::Point(br.x - CTRL_RECT_MIN_LENGTH, tl.y);
			}

			if (tl.y + CTRL_RECT_MIN_LENGTH > br.y)
			{
				tl = cv::Point(tl.x, br.y - CTRL_RECT_MIN_LENGTH);
			}

			m_controlRect = cv::Rect(tl, br);
			break;
		}

	case TOP_RIGHT:
		{
			cv::Point tl(m_controlRect.tl().x, pos.y());
			cv::Point br(pos.x(), m_controlRect.br().y);

			if (tl.x + CTRL_RECT_MIN_LENGTH > br.x)
			{
				br = cv::Point(tl.x + CTRL_RECT_MIN_LENGTH, m_controlRect.br().y);
			}

			if (tl.y + CTRL_RECT_MIN_LENGTH > br.y)
			{
				tl = cv::Point(m_controlRect.tl().x, br.y - CTRL_RECT_MIN_LENGTH);
			}

			m_controlRect = cv::Rect(tl, br);
			break;
		}

	case BOTTOM_RIGHT:
		{
			cv::Point tl(m_controlRect.tl());
			cv::Point br(pos.x(), pos.y());

			if (tl.x + CTRL_RECT_MIN_LENGTH > br.x)
			{
				br = cv::Point(tl.x + CTRL_RECT_MIN_LENGTH, br.y);
			}

			if (tl.y + CTRL_RECT_MIN_LENGTH > br.y)
			{
				br = cv::Point(br.x, tl.y + CTRL_RECT_MIN_LENGTH);
			}

			m_controlRect = cv::Rect(tl, br);
			break;
		}

	case BOTTOM_LEFT:
		{
			cv::Point tl(pos.x(), m_controlRect.tl().y);
			cv::Point br(m_controlRect.br().x, pos.y());

			if (tl.x + CTRL_RECT_MIN_LENGTH > br.x)
			{
				tl = cv::Point(br.x - CTRL_RECT_MIN_LENGTH, tl.y);
			}

			if (tl.y + CTRL_RECT_MIN_LENGTH > br.y)
			{
				br = cv::Point(br.x, tl.y + CTRL_RECT_MIN_LENGTH);
			}

			m_controlRect = cv::Rect(tl, br);
			break;
		}

	case LEFT:
		{
			cv::Point tl(pos.x(), m_controlRect.tl().y);
			cv::Point br(m_controlRect.br());

			if (tl.x + CTRL_RECT_MIN_LENGTH > br.x)
			{
				tl = cv::Point(br.x - CTRL_RECT_MIN_LENGTH, tl.y);
			}

			m_controlRect = cv::Rect(tl, br);
			break;
		}

	case TOP:
		{
			cv::Point tl(m_controlRect.tl().x, pos.y());
			cv::Point br(m_controlRect.br());

			if (tl.y + CTRL_RECT_MIN_LENGTH > br.y)
			{
				tl = cv::Point(tl.x, br.y - CTRL_RECT_MIN_LENGTH);
			}

			m_controlRect = cv::Rect(tl, br);
			break;
		}

	case RIGHT:
		{
			cv::Point tl(m_controlRect.tl());
			cv::Point br(pos.x(), m_controlRect.br().y);

			if (tl.x + CTRL_RECT_MIN_LENGTH > br.x)
			{
				br = cv::Point(tl.x + CTRL_RECT_MIN_LENGTH, br.y);
			}

			m_controlRect = cv::Rect(tl, br);
			break;
		}
		
	case BOTTOM:
		{
			cv::Point tl(m_controlRect.tl());
			cv::Point br(m_controlRect.br().x, pos.y());

			if (tl.y + CTRL_RECT_MIN_LENGTH > br.y)
			{
				br = cv::Point(br.x, tl.y + CTRL_RECT_MIN_LENGTH);
			}

			m_controlRect = cv::Rect(tl, br);
			break;
		}

	case CENTER:
		{
			int width = m_controlRect.width / 2;
			int height = m_controlRect.height / 2;

			if (pos.x() - width < 0)
			{
				pos.setX(width);
			}
			else if (pos.x() + width > m_picRect.width())
			{
				pos.setX(m_picRect.width() - width);
			}

			if (pos.y() - height < 0)
			{
				pos.setY(height);
			}
			else if (pos.y() + height > m_picRect.height())
			{
				pos.setY(m_picRect.height() - height);
			}

			cv::Point tl(pos.x() - width, pos.y() - height);
			cv::Point br(pos.x() + width, pos.y() + height);
			m_controlRect = cv::Rect(tl, br);
			break;
		}
	default:
		break;
	}


}


//答题卡切换
void AnswerCardDlg3::editCard(QString path)
{
	if (m_cardPath == "")
	{
		m_cardPath = path;
		setDataSource(path);
	}
	else
	{
		saveDataSource(m_cardPath);
		m_cardPath = path;
		setDataSource(path);
	}
}

//答题卡删除
void AnswerCardDlg3::deleteCard(QString path)
{
	if (m_cardPath == path)
	{
		m_cardPath = "";
		initialization();
		theApp.img_show = cv::Mat();
		//theApp.is_synchronous = false;
		update();
	}
}

//新建套卡
void AnswerCardDlg3::on_newCardBtn_clicked()
{

	CreateCardDlg dlg;
	if (dlg.exec() == QDialog::Accepted)
	{
		m_cardSetDlg->setDpi(dlg.getDpi());
		QDir dir;
		bool exist = dir.exists("tmp");

		if (exist)
		{
			QDir dirTmp("tmp//");
			QFileInfoList list = dirTmp.entryInfoList();

			//遍历删除目录下的文件
			for (int i = 0; i < list.size(); ++i)
			{
				if(list.at(i).fileName() == "." || list.at(i).fileName() == "..")
				{
					continue;
				}

				dirTmp.remove(list.at(i).fileName());
			}
		}
		else
		{
			//创建tmp文件夹
			dir.mkdir("tmp");
		}
		m_cardPath = "";
		initialization();
		ui->stepWidget->setCurrentIndex(0);
		m_cardSetDlg->setEnabled(true);
		m_clearDlg->setEnabled(true);
		m_cardSetDlg->clear();
		theApp.is_synchronous = true;
		theApp.img_show = cv::Mat();
		update();
	}
}

//打开导出xml的对话框
void AnswerCardDlg3::on_importXMLBtn_clicked()
{

	if (m_cardSetDlg->getCard().size() <= 0)
	{
		return;
	}

	QString fileName = QFileDialog::getSaveFileName(this, 
		tr("输出XML"), tr(""), tr("XML (*.xml)"));

	if (!fileName.isNull())  
	{
		TK_info3 tkInfo;
		vector<PerAC_info3> perInfo;
		
		theApp.clearACInfo3();
		int currentTab = ui->stepWidget->currentIndex();

		if (m_cardPath != "")
		{
			saveDataSource(m_cardPath);
		}

		int dpi = m_cardSetDlg->getDpi();

		vector<Card> card = m_cardSetDlg->getCard();
		for (int i = 0; i < card.size(); ++i)
		{
			vector<AC_info3> info;
			theApp.clearACInfo3();
			int page = card.at(i).pageId;
			QString str = tr("tmp\\%1-%2.tmp").arg(card.at(i).pageId).arg(card.at(i).isFront);
			setDataSource(str);
			theApp.TransToOutputStruct3();
			theApp.acinfo3.ac_type = m_cardType == 3 ? 3 : 4;
			theApp.acinfo3.ac_id = QString(tr("%1").arg(card.at(i).pageId)).toStdString();
			theApp.acinfo3.dpi = dpi;
			info.push_back(theApp.acinfo3);

			if (i + 1 < card.size())
			{
				if (card.at(i).pageId == card.at(i+1).pageId)
				{
					theApp.clearACInfo3();
					QString str = tr("tmp\\%1-%2.tmp").arg(card.at(i+1).pageId).arg(card.at(i+1).isFront);
					setDataSource(str);
					theApp.TransToOutputStruct3();
					theApp.acinfo3.ac_type = m_cardType == 3 ? 3 : 4;
					theApp.acinfo3.ac_id = QString(tr("%1").arg(card.at(i+1).pageId)).toStdString();
					theApp.acinfo3.dpi = dpi;
					info.push_back(theApp.acinfo3);

					i++;
				}
			}
			PerAC_info3 per;
			per.pageId = page;
			per.acinfo = info;
			perInfo.push_back(per);

		}

		if (m_cardPath != "")
		{
			setDataSource(m_cardPath);
			ui->stepWidget->setCurrentIndex(currentTab);
		}
		else
		{
			this->initialization();
			theApp.img_show = cv::Mat();
			theApp.is_synchronous = true;
			update();
		}

		tkInfo.tkinfo = perInfo;

		XmlIo io;
		io.Write(fileName.toStdString(), tkInfo);
			
		QMessageBox::information(this, "  ", tr("答题卡描述文件输出成功"));
	}
}

void AnswerCardDlg3::on_saveFileBtn_clicked()
{
	if (m_cardSetDlg->getCard().size() <= 0)
	{
		return;
	}

	QString fileName = QFileDialog::getSaveFileName(this, 
		tr("输出保存文件"), tr(""), tr("AC3PROJ (*.ac3proj)"));

	if (fileName != "")  
	{
		if (m_cardPath != "")
		{
			saveDataSource(m_cardPath);
		}

		vector<string> files;
		files.push_back("tmp\\relation.dat");
		vector<Card> card = m_cardSetDlg->getCard();

		for (int i = 0; i < card.size(); ++i)
		{
			QString str = tr("tmp\\%1-%2.tmp").arg(card.at(i).pageId).arg(card.at(i).isFront);
			files.push_back(str.toStdString());
		}

		ACZip(files, fileName.toStdString());
		
		QMessageBox::information(this, " ", tr("保存文件成功!!"));
	}
}

void AnswerCardDlg3::saveDataSource(const QString &path)
{
	DataInfo3 info;
	info.hasQuestion = theApp.m_hasQuestions;
	info.isFront = theApp.m_isFront;
	info.image = mat2QImage(theApp.img_raw);
	info.anchorRect = theApp.anchorRect;
	info.oriPoint = theApp.originalPoint;
	info.hasAnchorRect = m_cardType == 3 ? false : true;
	info.anchorType = theApp.anchor_type;
	info.markerSize = m_markerMakeDlg->getMarkerSize();
	info.markerDone = m_markerMakeDlg->isDone();
	info.barGroup = theApp.barGroup;
	info.fillingPointGroup = theApp.cfp_group3;
	info.cropAreaInfo = theApp.cropAreas;
	info.questioninfo = theApp.questionInfo;
	info.markersInfo.xMarker = theApp.hmarkers;
	info.markersInfo.yMarker = theApp.vmarkers;
	info.markers = theApp.markers;
	info.whiteLineRect = theApp.whiteLineRect;
	info.blackeLineRect = theApp.blackLineRect;
	info.referPoint = theApp.referPoint;
	info.pagePoint = theApp.pagePoint;
	info.questionType = theApp.questionType;

	for (int i = 0; i < 4; ++i)
	{
		info.anchorPoints[i] = theApp.anchorPoints[i];
	}

	DataIO io(path, DATA_WRITE);
	io.writeToDat(info);
}

int AnswerCardDlg3::setDataSource(const QString &path)
{
	if (path == "")
	{
		return 0;
	}

	//界面控制、清除数据
	initialization();
	theApp.is_synchronous = false;

	DataInfo3 info;
	DataIO io(path);
	if (io.readFromDat(info) != TYPE_TWO)
	{
		return 0;
	}

	//导入图像
	theApp.img_raw = qImage2Mat(info.image);

	//计算灰度图像及二值图像
	cvtColor(theApp.img_raw,theApp.img_gray,CV_RGB2GRAY);
	threshold(theApp.img_gray,theApp.img_bw,128,255,THRESH_BINARY_INV);

	//导入各种定位信息
	theApp.m_hasQuestions = info.hasQuestion;
	theApp.m_isFront = info.isFront;
	theApp.anchorRect = info.anchorRect;	
	theApp.originalPoint = info.oriPoint;
	theApp.anchorPoints[0] = info.anchorPoints[0];
	theApp.anchorPoints[1] = info.anchorPoints[1];
	theApp.anchorPoints[2] = info.anchorPoints[2];
	theApp.anchorPoints[3] = info.anchorPoints[3];

	theApp.cfp_group3 = info.fillingPointGroup;
	theApp.barGroup = info.barGroup;
	theApp.cropAreas = info.cropAreaInfo;
	theApp.questionInfo = info.questioninfo;
	
	theApp.anchor_type = info.anchorType;
	theApp.whiteLineRect = info.whiteLineRect;
	theApp.blackLineRect = info.blackeLineRect;
	theApp.pagePoint = info.pagePoint;
	theApp.referPoint = info.referPoint;
	theApp.questionType = info.questionType;
	
	bool done = info.markerDone;
	m_markerMakeDlg->setDone(info.markerDone);
	theApp.markers = info.markers;
	theApp.hmarkers = info.markersInfo.xMarker;
	theApp.vmarkers = info.markersInfo.yMarker;
	cv::Size markerSize = info.markerSize;

	//DataIO io(path);
	//int rst = io.readFileHead();
	//	
	//if (rst != TYPE_TWO)
	//{
	//	return 0;
	//}

	//bool hasQuestion;
	//bool isFront;
	//io.readHasQuestion(hasQuestion);
	//io.readIsFront(isFront);

	////导入图像
	//QImage img;
	//io.readImage(img);
	//
	//cv::Rect anchorRect;
	//bool hasRect;
	//cv::Point point;

	//io.readAnchorRectInfo(anchorRect, hasRect, point);

	////界面控制、清除数据
	//initialization();

	//theApp.m_hasQuestions = hasQuestion;
	//theApp.m_isFront = isFront;
	//theApp.anchorRect = anchorRect;	
	//theApp.originalPoint = point;

	//计算灰度图像及二值图像
	//theApp.img_raw = qImage2Mat(img);
	//cvtColor(theApp.img_raw,theApp.img_gray,CV_RGB2GRAY);
	//threshold(theApp.img_gray,theApp.img_bw,128,255,THRESH_BINARY_INV);

	////导入定位点等信息
	//io.readAnchorInfo(theApp.anchorPoints, theApp.anchor_type);

	//theApp.is_synchronous = false;

	//bool done = false;
	//cv::Size markerSize;
	//Marker_info3 markerInfo;
	//io.readMarkerInfo(markerSize, markerInfo, theApp.markers, done);
	//theApp.hmarkers = markerInfo.xMarker;
	//theApp.vmarkers = markerInfo.yMarker;

	//io.readBarCodeInfo(theApp.barGroup);
	//io.readQuestionInfo(theApp.questionInfo,theApp.questionType);
	//io.readFillPointInfo(theApp.cfp_group3);
	//io.readCropAreaInfo(theApp.cropAreas);
	//io.readWhiteLineData(theApp.whiteLineRect);
	//io.readBlackLineData(theApp.blackLineRect);
	//io.readReferPointInfo(theApp.referPoint);
	//io.readPagePointInfo(theApp.pagePoint);
	
	//窗口数据恢复
	if (m_cardType == 3)
	{
		m_anchorDlg->setEnabled(true);
	}
	else
	{
		m_anchorRectDlg->setEnabled(true);
		m_anchorRectDlg->resume();
	}

	m_markerMakeDlg->setDone(done);

	if ((theApp.anchor_type > 0 && m_cardType == 3) 
		|| (theApp.anchor_type >= 0 && m_cardType != 3 && theApp.anchorRect.width > 0))
	{
		m_markerMakeDlg->resume(markerSize, done);					
		m_pagePointDlg->resume();
		m_pagePointDlg->setEnabled(true);
		markerDone();

	}

	m_fillPointDlg->resume3();	
	m_lineDetectDlg->resume();
	m_barcodeDlg->resume();
	m_clipDlg->resume();
	
	m_clipDlg->setEnabled(true);
	m_fillPointDlg->setEnabled(true);
	m_barcodeDlg->setEnabled(true);
	m_lineDetectDlg->setEnabled(true);
	theApp.m_group_state = AnchorState;
	theApp.m_state = AnchorInitial;
	m_fillPointDlg->updateMarkerGroupId();
	return 1;
}


void AnswerCardDlg3::on_openFileBtn_clicked()
{
	 QString fileName = QFileDialog::getOpenFileName(
                this, tr("打开文件"),
                ".",
                "AC3PROJ (*.ac3proj)");
    if(fileName != "")
	{
		QDir dir;
		bool exist = dir.exists("tmp1");
		if (!exist)
		{
			//创建tmp文件夹
			dir.mkdir("tmp1");
		}

		try
		{
			ACUnZip(fileName.toStdString(), "tmp1\\");

			if (QFile::exists("tmp1\\relation.dat"))
			{
				int rst = m_cardSetDlg->resume();

				if (rst == 0)
				{
					QMessageBox::information(this," ",tr("该文件不可识别！！"));
				}
				else
				{
					QDir dirTmp("tmp//");
					QFileInfoList list = dirTmp.entryInfoList();

					//遍历删除目录下的文件
					for (int i = 0; i < list.size(); ++i)
					{
						if(list.at(i).fileName() == "." || list.at(i).fileName() == "..")
						{
							continue;
						}

						dirTmp.remove(list.at(i).fileName());
					}

					ACUnZip(fileName.toStdString(), "tmp\\");
					initialization();
					ui->stepWidget->setCurrentIndex(0);
					m_cardSetDlg->setEnabled(true);
					m_clearDlg->setEnabled(true);
					m_cardPath = "";
					theApp.is_synchronous = true;
					theApp.img_show = cv::Mat();
					update();
				}
			}
			else
			{
				QMessageBox::information(this," ",tr("该文件不可识别！！"));
			}
		}
		catch(exception &e)
		{
			cerr<<e.what()<<endl;
			QMessageBox::information(this," ",tr("该文件不可识别！！"));
		}

		QDir dir1;
		exist = dir1.exists("tmp1");

		if (exist)
		{
			QDir dirTmp1("tmp1//");
			QFileInfoList list1 = dirTmp1.entryInfoList();

			//遍历删除目录下的文件
			for (int i = 0; i < list1.size(); ++i)
			{
				if(list1.at(i).fileName() == "." || list1.at(i).fileName() == "..")
				{
					continue;
				}

				dirTmp1.remove(list1.at(i).fileName());
			}

			//删除tmp文件夹
			dir1.rmdir("tmp1");
		}
		
	}
}