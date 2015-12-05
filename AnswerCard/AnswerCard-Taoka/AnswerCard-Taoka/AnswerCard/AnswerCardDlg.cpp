#include "AnswerCardDlg.h"
#include "ui_AnswerCardDlg.h"
#include "DataIO.h"

Mat AnswerCardDlg::m_imgTmp = Mat();

//构造函数
AnswerCardDlg::AnswerCardDlg(QString pathPrefix)
	: QDialog(0),
	m_mouseDownPoint(0,0), 
	m_picRect(),
	m_hmarkers_num(0),
	m_vmarkers_num(0),
	m_controlRect(),
	m_isSaved(true),
	m_isZooming(false),
	m_zoomingIndex(0),
	m_isFront(true)
{
	ui = new Ui::AnswerCardDlg();
	ui->setupUi(this); 

	m_dataPathPrefix = pathPrefix;

	//初始化控制点
	for (int i = 0; i < 9; ++i)
	{
		m_controlPoint[i] = QRect(0, 0, CTRL_POINT_LENGTH, CTRL_POINT_LENGTH);
	}

	//设置对话框的最小最大化按钮
	this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
	this->setWindowFlags(windowFlags()|Qt::WindowMinimizeButtonHint);
	this->setWindowFlags(windowFlags()|Qt::WindowMaximizeButtonHint);

////////////////////////////标签页第二页/////////////////////////////////////////
	ui->stepWidget->setCurrentIndex(1);
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
	
///////////////////////标签页第一页//////////////////////////////////
	ui->stepWidget->setCurrentIndex(0);
	tab = ui->stepWidget->currentWidget();
	
	QWidget* w = new QWidget(tab);
	m_clearBtn = new QPushButton(w);
	m_clearBtn->setText(tr("清除卡格式 "));
	m_changePicBtn = new QPushButton(w);
	m_changePicBtn->setText(tr("重新指定图片"));
	QHBoxLayout *layout = new QHBoxLayout(w);
	layout->addWidget(m_clearBtn);
	layout->addWidget(m_changePicBtn);
	w->setWindowFlags(Qt::Widget);
	ui->firstWidgetLayout->addWidget(w,0,0);
	w->show();

	//将定位点定位窗口嵌入第一页
	m_isFrontDlg = new IsFrontDlg(tab);
	m_isFrontDlg->setWindowFlags(Qt::Widget);
	ui->firstWidgetLayout->addWidget(m_isFrontDlg,1,0);
	m_isFrontDlg->show();

	//将定位点定位窗口嵌入第一页
	m_anchorDlg = new AnchorDlg(tab);
	m_anchorDlg->setWindowFlags(Qt::Widget);
	ui->firstWidgetLayout->addWidget(m_anchorDlg,2,0);
	m_anchorDlg->show();

	//将虚拟定位点嵌入第一页
	m_lineDetectDlg = new LineDetectDlg(tab);
	m_lineDetectDlg->setWindowFlags(Qt::Widget);
	ui->firstWidgetLayout->addWidget(m_lineDetectDlg,3,0);
	m_lineDetectDlg->show();

	//将标记点定位窗口嵌入第一页
	m_markerDlg = new MarkerDlg(tab);
	m_markerDlg->setWindowFlags(Qt::Widget);
	ui->firstWidgetLayout->addWidget(m_markerDlg,4,0);
	m_markerDlg->show();

	//将标记点定位窗口嵌入第一页
	m_idPointDlg = new IdPointDlg(tab);
	m_idPointDlg->setWindowFlags(Qt::Widget);
	ui->firstWidgetLayout->addWidget(m_idPointDlg,5,0);
	m_idPointDlg->show();

/////////////////////////////////////////////////////////////////////////

	//注册监视对象
    ui->imageLabel->installEventFilter(this);
	ui->imageWidget->installEventFilter(this);
	ui->imageLabel->setMouseTracking(true);
	ui->imageWidget->setMouseTracking(true);

	//连接信号和槽
	connect(m_anchorDlg, SIGNAL(anchorDone()), this, SLOT(anchorDone()));
	connect(m_markerDlg, SIGNAL(markerDone()), this, SLOT(markerDone()));
	connect(m_idPointDlg, SIGNAL(idPointBegin()), this, SLOT(idPointBegin()));
	connect(m_idPointDlg, SIGNAL(idPointDone()), this, SLOT(enableDlg()));
	connect(m_idPointDlg, SIGNAL(idPointDelete()), this, SLOT(deleteBtnClicked()));
	connect(m_barcodeDlg, SIGNAL(barCodeBegin()), this, SLOT(barCodeBegin()));
	connect(m_barcodeDlg, SIGNAL(barCodeDone()), this, SLOT(enableDlg()));
	connect(m_fillPointDlg, SIGNAL(fillPointBegin()), this, SLOT(fillPointBegin()));
	connect(m_fillPointDlg, SIGNAL(fillPointDone()), this, SLOT(enableDlg()));
	connect(m_clipDlg, SIGNAL(clipBegin()), this, SLOT(clipBegin()));
	connect(m_clipDlg, SIGNAL(clipDone()), this, SLOT(enableDlg()));
	connect(m_barcodeDlg, SIGNAL(barCodeDelete()), this, SLOT(deleteBtnClicked()));
	connect(m_clipDlg, SIGNAL(clipDelete()), this, SLOT(deleteBtnClicked()));
	connect(m_fillPointDlg, SIGNAL(fillPointDelete()), this, SLOT(deleteBtnClicked()));
	connect(m_lineDetectDlg, SIGNAL(lineBegin()), this, SLOT(lineDetectBegin()));
	connect(m_lineDetectDlg, SIGNAL(lineDone()), this, SLOT(lineDetectDone()));
	connect(m_clipDlg, SIGNAL(clipClicked(int)), this, SLOT(clipClicked(int)));
	connect(m_fillPointDlg, SIGNAL(fillPointClicked(int)), this, SLOT(fillPointClicked(int)));
	connect(m_barcodeDlg, SIGNAL(barCodeClicked(int)), this, SLOT(barCodeClicked(int)));
	connect(m_idPointDlg, SIGNAL(idPointClicked(int)), this, SLOT(idPointClicked(int)));
	connect(m_isFrontDlg, SIGNAL(indexChanged(int)), this, SLOT(pageChanged(int)));
	connect(m_clearBtn, SIGNAL(clicked()), this, SLOT(on_clearBtn_clicked()));
	connect(m_changePicBtn, SIGNAL(clicked()), this, SLOT(on_changePicBtn_clicked()));

	//初始化对话框
	initialization();
}

AnswerCardDlg::~AnswerCardDlg()
{
	delete m_anchorDlg;
	delete m_markerDlg;
	delete m_barcodeDlg;
	delete m_fillPointDlg;
	delete m_clipDlg;	
	delete m_lineDetectDlg;
	delete m_idPointDlg;
	delete m_isFrontDlg;
	delete ui;
}

int AnswerCardDlg::setDataSource(const QString &path)
{
	if (path == "")
	{
		return 0;
	}

	//界面控制、清除数据
	initialization();
	m_anchorDlg->setEnabled(true);

	theApp.is_synchronous = false;
	m_dataPath = QString(path);

	DataInfo info;
	DataIO io(m_dataPath);

	if (io.readFromDat(info) != TYPE_ONE)
	{
		return 0;
	}

	//导入图像
	theApp.img_raw = qImage2Mat(info.image);

	//计算灰度图像及二值图像
	cvtColor(theApp.img_raw,theApp.img_gray,CV_RGB2GRAY);
	threshold(theApp.img_gray,theApp.img_bw,128,255,THRESH_BINARY_INV);

	//导入各种定位信息
	theApp.cfp_group = info.fillingPointGroup;
	theApp.barGroup = info.barGroup;
	theApp.cropAreas = info.cropAreaInfo;
	theApp.questionInfo = info.questioninfo;
	theApp.markersRect[0] = info.markersRect[0];
	theApp.markersRect[1] = info.markersRect[1];
	theApp.anchor_type = info.anchorType;
	theApp.whiteLineRect = info.whiteLineRect;
	theApp.blackLineRect = info.blackeLineRect;
	theApp.idGroup = info.idPointInfo;
	theApp.referPoint = info.referPoint;
	theApp.questionType = info.questionType;
	m_markerDlg->setDone(info.markerDone);

	for (int i = 0; i < 4; ++i)
	{
		theApp.anchorPoints[i] = info.anchorPoints[i];
	}

	m_clipDlg->resume();
	m_lineDetectDlg->resume();
	m_barcodeDlg->resume();
	m_fillPointDlg->resume();
	m_idPointDlg->resume();

	m_lineDetectDlg->setEnabled(true);
	m_barcodeDlg->setEnabled(true);
	m_clipDlg->setEnabled(true);
	m_fillPointDlg->setEnabled(true);

	//恢复子对话框各种状态
	if (info.anchorType > 0)
	{
		if (info.markerDone == true)
		{		
			m_markerDlg->resume(info.markerDone);
			
			m_fillPointDlg->setEnabled(true);
			m_barcodeDlg->setEnabled(true);
			m_clipDlg->setEnabled(true);
			m_markerDlg->setEnabled(true);
			m_lineDetectDlg->setEnabled(true);
			m_idPointDlg->setEnabled(true);
		}
		else
		{
			m_markerDlg->resume(info.markerDone);
			m_markerDlg->setEnabled(true);
		}
	}


	//状态控制
	theApp.m_group_state = AnchorState;
	theApp.m_state = AnchorInitial;
	return 1;
}

///////////////////////////////////////清除/替换按钮////////////////////////////////////
void AnswerCardDlg::on_clearBtn_clicked()
{
	initialization();
	m_anchorDlg->setEnabled(true);
	m_lineDetectDlg->setEnabled(true);
	m_barcodeDlg->setEnabled(true);
	m_clipDlg->setEnabled(true);
	m_fillPointDlg->setEnabled(true);
	theApp.is_synchronous = false;
	m_isSaved = false;
	update();
}

void AnswerCardDlg::on_changePicBtn_clicked()
{
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
		m_lineDetectDlg->setEnabled(true);
		m_barcodeDlg->setEnabled(true);
		m_clipDlg->setEnabled(true);
		m_fillPointDlg->setEnabled(true);
		theApp.is_synchronous = false;
		m_isSaved = false;
		update();
	}	
	
}


//////////////////////////////////子窗口激活/关闭/////////////////////////////////
//初始化各个子窗口
void AnswerCardDlg::initialization()
{
	m_anchorDlg->initialization();
	m_markerDlg->initialization();
	m_barcodeDlg->initialization();
	m_fillPointDlg->initialization();
	m_clipDlg->initialization();
	m_lineDetectDlg->initialization();
	m_idPointDlg->initialization();

	ui->stepWidget->setCurrentIndex(0);
	theApp.clear();
	theApp.clearACInfo();
}

//激活标记点窗口
void AnswerCardDlg::anchorDone()
{
	m_markerDlg->setEnabled(true);
	m_isSaved = false;

	//如果处于拖选裁切区域或条形码区域则取消拖选状态
	if (m_isZooming == true)
	{
		m_isZooming = false;
		theApp.is_synchronous = false;
	}
}

//激活tabWidget的第二个页面
void AnswerCardDlg::markerDone()
{
	m_fillPointDlg->setEnabled(true);
	m_idPointDlg->setEnabled(true);
	m_isSaved = false;

	if (m_isZooming == true)
	{
		m_isZooming = false;
		theApp.is_synchronous = false;
	}
}

//激活所有窗口
void AnswerCardDlg::enableDlg()
{
	m_anchorDlg->setEnabled(true);
	m_markerDlg->setEnabled(true);
	m_barcodeDlg->setEnabled(true);
	m_fillPointDlg->setEnabled(true);
	m_clipDlg->setEnabled(true);
	m_lineDetectDlg->setEnabled(true);
	m_idPointDlg->setEnabled(true);
	m_isFrontDlg->setEnabled(true);

	if (theApp.anchor_type == 0)
	{
		m_markerDlg->setEnabled(false);
	}

	if (!m_markerDlg->isDone())
	{
		m_idPointDlg->setEnabled(false);
	}

	m_isSaved = false;

	if (m_isZooming == true)
	{
		m_isZooming = false;
		theApp.is_synchronous = false;
	}
}

void AnswerCardDlg::barCodeBegin()
{
	m_anchorDlg->setEnabled(false);
	m_markerDlg->setEnabled(false);
	m_barcodeDlg->setEnabled(true);
	m_fillPointDlg->setEnabled(false);
	m_clipDlg->setEnabled(false);
	m_lineDetectDlg->setEnabled(false);
	m_idPointDlg->setEnabled(false);
	m_isFrontDlg->setEnabled(false);

	if (m_isZooming == true)
	{
		m_isZooming = false;
		theApp.is_synchronous = false;
	}
}

void AnswerCardDlg::idPointBegin()
{
	m_anchorDlg->setEnabled(false);
	m_markerDlg->setEnabled(false);
	m_barcodeDlg->setEnabled(false);
	m_fillPointDlg->setEnabled(false);
	m_clipDlg->setEnabled(false);
	m_lineDetectDlg->setEnabled(false);
	m_idPointDlg->setEnabled(true);
	m_isFrontDlg->setEnabled(false);

	if (m_isZooming == true)
	{
		m_isZooming = false;
		theApp.is_synchronous = false;
	}
}

void AnswerCardDlg::fillPointBegin()
{
	m_anchorDlg->setEnabled(false);
	m_markerDlg->setEnabled(false);
	m_barcodeDlg->setEnabled(false);
	m_fillPointDlg->setEnabled(true);
	m_clipDlg->setEnabled(false);
	m_lineDetectDlg->setEnabled(false);
	m_idPointDlg->setEnabled(false);
	m_isFrontDlg->setEnabled(false);

	if (m_isZooming == true)
	{
		m_isZooming = false;
		theApp.is_synchronous = false;
	}
}

void AnswerCardDlg::clipBegin()
{
	m_anchorDlg->setEnabled(false);
	m_markerDlg->setEnabled(false);
	m_barcodeDlg->setEnabled(false);
	m_fillPointDlg->setEnabled(false);
	m_clipDlg->setEnabled(true);
	m_lineDetectDlg->setEnabled(false);
	m_idPointDlg->setEnabled(false);
	m_isFrontDlg->setEnabled(false);

	if (m_isZooming == true)
	{
		m_isZooming = false;
		theApp.is_synchronous = false;
	}
}

void AnswerCardDlg::deleteBtnClicked()
{
	m_isSaved = false;

	if (m_isZooming == true)
	{
		m_isZooming = false;
		theApp.is_synchronous = false;
	}
}

void AnswerCardDlg::lineDetectBegin()
{
	m_anchorDlg->setEnabled(false);
	m_markerDlg->setEnabled(false);
	m_barcodeDlg->setEnabled(false);
	m_fillPointDlg->setEnabled(false);
	m_clipDlg->setEnabled(false);
	m_lineDetectDlg->setEnabled(true);
	m_idPointDlg->setEnabled(false);
	m_isFrontDlg->setEnabled(false);

	if (m_isZooming == true)
	{
		m_isZooming = false;
		theApp.is_synchronous = false;
	}
}

void AnswerCardDlg::lineDetectDone()
{
	enableDlg();
}

void AnswerCardDlg::pageChanged(int idx)
{
	if (idx == 0)
	{
		if (m_isFront == false)
		{
			saveDataSource();
			m_isFront = true;
		
			m_dataPath = m_dataPathPrefix + tr("-%1.dat").arg((int)(m_isFront));
			setDataSource(m_dataPath);
		}

	}
	else
	{
		if (QFile::exists(m_dataPathPrefix + tr("-%1.dat").arg((int)(false))))
		{
			if (m_isFront == true)
			{
				saveDataSource();
			}

			m_isFront = false;

			m_dataPath = m_dataPathPrefix + tr("-%1.dat").arg((int)(m_isFront));
			setDataSource(m_dataPath);
		}
		else
		{
			m_isFrontDlg->setCurrentIndex(0);
		}
	}
}

//裁切区域选中
void AnswerCardDlg::clipClicked(int idx)
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

//条形码选中
void AnswerCardDlg::barCodeClicked(int idx)
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

//填涂点选中
void AnswerCardDlg::fillPointClicked(int idx)
{
	if (m_isZooming == true)
	{
		m_isZooming = false;
	}
	update();
}

//id点选中
void AnswerCardDlg::idPointClicked(int idx)
{
	if (m_isZooming == true)
	{
		m_isZooming = false;
	}
	update();
}

/////////////////////////////////图像绘制////////////////////////////////////////////
void AnswerCardDlg::paintEvent(QPaintEvent *e)
{
	if (theApp.m_state != InitialState || theApp.m_group_state != InitialState)
	{
		
		if (!theApp.is_synchronous)
		{
			//图像更新
			theApp.Redraw();
		}

		QImage img = mat2QImage(theApp.img_show);
		m_picRect = img.rect();
		ui->imageLabel->setPixmap(QPixmap::fromImage(img));
	}
}

//将Mat格式的图片转为QImage输出
QImage AnswerCardDlg::mat2QImage(const cv::Mat &mat)
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

//将QImage格式转为mat格式
Mat AnswerCardDlg::qImage2Mat(const QImage& qimage) 
{ 
    cv::Mat mat = cv::Mat(qimage.height(), qimage.width(), CV_8UC4, 
		(uchar*)qimage.bits(), qimage.bytesPerLine()); 
    cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 ); 
    int from_to[] = { 0,0, 1,1, 2,2 }; 
    cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 ); 

    return mat2; 
}; 

// 计算客户区的一个点在图像区域中的位置
QPoint AnswerCardDlg::GetImgPosFromClient(const QPoint &clientPos)
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

//////////////////////////////键盘事件//////////////////////////////////////////
void AnswerCardDlg::keyPressEvent(QKeyEvent *event)
{
	switch(event->key())
	{
		//进行界面退出，重写Esc键，保存文件
		//case Qt::Key_Escape:
		//	void saveDataSource();
		//	break;

		default:
			QDialog::keyPressEvent(event);
	}
}

/////////////////////////////////鼠标控制模块/////////////////////////////////////////
bool AnswerCardDlg::eventFilter(QObject *target, QEvent *e)
{
	//目标是图像区域
	if (target == ui->imageLabel)
    {
		//鼠标移动
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
		//鼠标点击
		else if (e->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(e);
			QPoint point(mouseEvent->x(), mouseEvent->y());
			mouseLeftButtonPress(point);

			return true;
		}
		//鼠标点击释放
		else if (e->type() == QEvent::MouseButtonRelease)
		{
			QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(e);
			QPoint point(mouseEvent->x(), mouseEvent->y());
			mouseLeftButtonRelease(point);

			return true;
		}
		//鼠标进入图像区域，将图像区域设为聚焦状态
		else if (e->type() == QEvent::Enter)
		{
			ui->imageScrollArea->setFocus();
			return true;
		}
		//鼠标离开图像区域，取消图像区域聚焦状态
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
void AnswerCardDlg::mouseLeftButtonPress(const QPoint &pos)
{
	switch (theApp.m_group_state)
	{
	//标记点模块
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
		//框选结束
		case BaseEnd:
			//处于缩放状态
			if (m_isZooming == true)
			{
				QPoint pt = GetImgPosFromClient(pos);
				m_ctrlPointIndex = -1;

				//判断鼠标拖动哪个位置
				for (int i = 0; i < 9; ++i)
				{
					if (m_controlPoint[i].contains(pt.x(), pt.y()))
					{
						m_ctrlPointIndex = i;

						//将选中的条形框区域置空
						if (theApp.barGroup.at(m_zoomingIndex).pos.width > 0)
						{
							theApp.barGroup.at(m_zoomingIndex).pos = cv::Rect();
							theApp.Redraw();
						}

						//备份当前条形框区域为空的图像
						theApp.img_show.copyTo(theApp.img_bk);		

						//重新绘制图像
						//m_controlRect在条形框选中时已赋值
						rectangle(theApp.img_show, m_controlRect, 
							theApp.barcode_color, theApp.barcode_thickness);
						computeCtrlPointPos();

						//绘制控制点
						for (int i = 0; i < 9; ++i)
						{
							drawControlPoint(m_controlPoint[i].center(), CTRL_POINT_LENGTH, theApp.barcode_color, theApp.barcode_thickness);
						}						
						break;
					}
				}//for (int i = 0; i < 9; ++i)

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
						//将选中的裁切框区域置空
						if (theApp.cropAreas.at(m_zoomingIndex).pos.width > 0)
						{
							theApp.cropAreas.at(m_zoomingIndex).pos = cv::Rect();
							theApp.Redraw();
						}

						theApp.img_show.copyTo(theApp.img_bk);		//备份当前图像
				
						rectangle(theApp.img_show, m_controlRect, 
							theApp.cropArea_color, theApp.cropArea_thickness);

						//计算控制点位置
						computeCtrlPointPos();

						//绘制控制点
						for (int i = 0; i < 9; ++i)
						{
							drawControlPoint(m_controlPoint[i].center(), CTRL_POINT_LENGTH, theApp.cropArea_color, theApp.cropArea_thickness);
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

	case IdPointState:
		switch (theApp.m_state)
		{
		case BaseBegin:
			theApp.img_show.copyTo(theApp.img_bk);		//备份当前图像
			m_mouseDownPoint = GetImgPosFromClient(pos);	//获得相对图像位置
			theApp.m_state++;							//改变状态
			break;
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
	default:
		break;
	}
}

//鼠标左键弹起,处理事件
void AnswerCardDlg::mouseLeftButtonRelease(const QPoint &pos)
{
	switch (theApp.m_group_state)
	{
	case AnchorState:
		anchorProcessingOnMouseUp(pos);
		break;

	case MarkerState:
		markerProcessingOnMouseUp(pos);
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

	case WhiteLineState:
		whiteLineProcessingOnMouseUp(pos);
		break;

	case BlackLineState:
		blackLineProcessingOnMouseUp(pos);
		break;

	case IdPointState:
		idPointProcessingOnMouseUp(pos);
		break;

	default:
		break;
	}
}

//鼠标移动,处理事件
void AnswerCardDlg::mouseMove(const QPoint &pos)
{
	//根据状态处理
	switch (theApp.m_group_state)
	{
	case MarkerState:
		markerProcessingOnMouseMove(pos);
		break;

	case BarCodeState:
		barcodeProcessingOnMouseMove(pos);
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

	case WhiteLineState:
		whiteLineProcessingOnMouseMove(pos);
		break;

	case BlackLineState:
		blackLineProcessingOnMouseMove(pos);
		break;

	case IdPointState:
		idPointProcessingOnMouseMove(pos);
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
void AnswerCardDlg::changeMouseCursor(const QPoint &pos)
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

	case IdPointState:
	case FillPointState:
	case WhiteLineState:
	case BlackLineState:
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
		}
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

	default:
		ui->imageLabel->setCursor(Qt::ArrowCursor);
		break;
	}
}

//在输入的位置上绘制一个控制点
//点击的位置，边长，填充颜色，填充风格
void AnswerCardDlg::drawControlPoint(const QPoint &centerPos, int length, cv::Scalar scalar, ushort thickness)
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
void AnswerCardDlg::computeCtrlPointPos()
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
//鼠标移动的新位置，拖动的哪个点
void AnswerCardDlg::dragMarquee(const QPoint &imgPos, int ctlPointIndex)
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

void AnswerCardDlg::anchorProcessingOnMouseUp(const QPoint &pos)
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
			m_isSaved = false;
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
			m_isSaved = false;
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
			m_isSaved = false;
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
			m_isSaved = false;
			break;
		}
	}//switch (theApp.m_state)
}

void AnswerCardDlg::markerProcessingOnMouseUp(const QPoint &pos)
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
			}
			else
			{
				//计算标记点数量
				vector<cv::Rect> hmarkers = theApp.GetMarkersNum(theApp.img_bw(theApp.markersRect[0]));
				if (hmarkers.size()==0)
				{
					QMessageBox::information(NULL, " ", tr("选择区域中没有检测到标记点\n请重新选择"));
				}
				else
				{
					m_hmarkers_num = hmarkers.size();
					m_markerDlg->setHorEditNum(m_hmarkers_num);
					m_markerDlg->setHorEditEnabled(true);

					//加上偏移值
					for (int i = hmarkers.size()-1; i>=0; i--)
					{
						hmarkers.at(i).x += m_mouseDownPoint.x();
						hmarkers.at(i).y += m_mouseDownPoint.y();
					}

					theApp.hmarkers = hmarkers;
					theApp.SortMarkers(true);
					theApp.is_synchronous = false;
					update();
				}
			}

			theApp.m_state = RowRelease;
			theApp.img_bk.release();
			m_isSaved = false;
	
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
			}
			else
			{
				//计算标记点数量
				vector<cv::Rect> vmarkers = theApp.GetMarkersNum(theApp.img_bw(theApp.markersRect[1]));

				if (vmarkers.size()==0)
				{
					QMessageBox::information(NULL, " ", tr("选择区域中没有检测到标记点\n请重新选择"));
				}
				else
				{
					m_vmarkers_num = vmarkers.size();
					m_markerDlg->setVerEditNum(m_vmarkers_num);
					m_markerDlg->setVerEditEnabled(true);

					//加上偏移值
					for (int i = vmarkers.size()-1; i>=0; i--)
					{
						vmarkers.at(i).x += m_mouseDownPoint.x();
						vmarkers.at(i).y += m_mouseDownPoint.y();
					}

					theApp.vmarkers = vmarkers;
					theApp.SortMarkers(false);
					theApp.is_synchronous = false;
					update();
				}
			}

			theApp.m_state = ColRelease;
			theApp.img_bk.release();
			m_isSaved = false;
			break;
		}
	}//switch (theApp.m_state)
}

void AnswerCardDlg::markerProcessingOnMouseMove(const QPoint &pos)
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

void AnswerCardDlg::barcodeProcessingOnMouseUp(const QPoint &pos)
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

void AnswerCardDlg::barcodeProcessingOnMouseMove(const QPoint &pos)
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
					m_isSaved = false;

					//恢复图像
					theApp.img_bk.copyTo(theApp.img_show);

					//重绘控制区域，计算控制点位置
					dragMarquee(pt, m_ctrlPointIndex);
					
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

void AnswerCardDlg::fillPointProcessingOnMouseUp(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case BasePress:
		{
			//识别参考点
			if (m_fillPointDlg->getFillPointType() == ReferPoint)
			{
				//鼠标拖动绘制矩形
				QPoint pt = GetImgPosFromClient(pos);
				cv::Rect rt(cv::Point(m_mouseDownPoint.x(), m_mouseDownPoint.y()),
					cv::Point(pt.x(),pt.y()));

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
					theApp.referPoint.push_back(contourRect);
				}
				
				theApp.m_state++;
				theApp.img_bk.release();

				//控制自定义窗口按钮
				m_fillPointDlg->setAddBtnText(tr("重新框选填涂点"));
				m_fillPointDlg->setConfirmBtnEnabled(true);
				theApp.is_synchronous = false;

				return;
			}

			//非识别参考点
			//鼠标拖动绘制矩形
			QPoint pt = GetImgPosFromClient(pos);
			int idx_l, idx_r, idx_t, idx_b;      //计算对应标记点

			if (pt.x() > m_mouseDownPoint.x())
			{
				if (pt.y() > m_mouseDownPoint.y())
				{
					idx_l = theApp.markerBT.GetNearestLBoundary(m_mouseDownPoint.x());
					idx_t = theApp.markerBT.GetNearestTBoundary(m_mouseDownPoint.y());
					idx_r = theApp.markerBT.GetNearestRBoundary(pt.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					idx_b = theApp.markerBT.GetNearestBBoundary(pt.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
				}
				else
				{
					idx_l = theApp.markerBT.GetNearestLBoundary(m_mouseDownPoint.x());
					idx_t = theApp.markerBT.GetNearestTBoundary(pt.y());
					idx_r = theApp.markerBT.GetNearestRBoundary(pt.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					idx_b = theApp.markerBT.GetNearestBBoundary(m_mouseDownPoint.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
				}
			}
			else
			{
				if (pt.y() > m_mouseDownPoint.y())
				{
					idx_l = theApp.markerBT.GetNearestLBoundary(pt.x());
					idx_t = theApp.markerBT.GetNearestTBoundary(m_mouseDownPoint.y());
					idx_r = theApp.markerBT.GetNearestRBoundary(m_mouseDownPoint.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					idx_b = theApp.markerBT.GetNearestBBoundary(pt.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
				}
				else
				{
					idx_l = theApp.markerBT.GetNearestLBoundary(pt.x());
					idx_t = theApp.markerBT.GetNearestTBoundary(pt.y());
					idx_r = theApp.markerBT.GetNearestRBoundary(m_mouseDownPoint.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					idx_b = theApp.markerBT.GetNearestBBoundary(m_mouseDownPoint.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
				}
			}

			int count = m_fillPointDlg->getOptionCount();
			cv::Range range = m_fillPointDlg->getOptionRange();
			bool isHorizontal = m_fillPointDlg->isCrossWise();
			int cSpace = m_fillPointDlg->getCSpace();
			int rSpace = m_fillPointDlg->getRSpace();
			string name = m_fillPointDlg->getFillPointName();
			FillingPointsType type = m_fillPointDlg->getFillPointType();

			if (isHorizontal)
			{
				if (idx_b - idx_t != (range.start - 1) * cSpace + range.start - 1 )
				{
					QMessageBox::information(NULL, " ", 
						tr("框选错误，框选位数不对应！"));
					theApp.m_state = BaseBegin;
					theApp.is_synchronous = false;
					update();
					break;
				}
				else if (idx_r - idx_l != (count - 1) * rSpace + count - 1)
				{
					QMessageBox::information(NULL, " ", 
						tr("框选错误，选项数量不对应！"));
					theApp.m_state = BaseBegin;
					theApp.is_synchronous = false;
					update();
					break;
				}
			}
			else
			{
				if (idx_r - idx_l != (range.start - 1) * rSpace + range.start - 1)
				{
					QMessageBox::information(NULL, " ", 
						tr("框选错误，框选位数不对应！"));
					theApp.is_synchronous = false;
					theApp.m_state = BaseBegin;
					update();
					break;
				}
				else if (idx_b - idx_t != (count - 1) * cSpace + count - 1)
				{
					QMessageBox::information(NULL, " ", 
						tr("框选错误，选项数量不对应！"));
					theApp.m_state = BaseBegin;
					theApp.is_synchronous = false;
					update();
					break;
				}
			}

			theApp.AddFillPoint(name, type, isHorizontal, cSpace,
				rSpace, idx_l, idx_r, idx_t, idx_b);

			m_fillPointDlg->setIdx_l(idx_l);
			m_fillPointDlg->setIdx_r(idx_r);
			m_fillPointDlg->setIdx_b(idx_b);
			m_fillPointDlg->setIdx_t(idx_t);

			theApp.m_state++;
			theApp.img_bk.release();

			//控制自定义窗口按钮
			m_fillPointDlg->setAddBtnText(tr("重新框选填涂点"));
			m_fillPointDlg->setConfirmBtnEnabled(true);
			theApp.is_synchronous = false;
			break;
		}
	}
}

void AnswerCardDlg::fillPointProcessingOnMouseMove(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case BasePress:
		{
			if (m_fillPointDlg->getFillPointType() == ReferPoint)
			{
				//鼠标拖动绘制矩形
				QPoint pt = GetImgPosFromClient(pos);
				cv::Rect rt(cv::Point(m_mouseDownPoint.x(), m_mouseDownPoint.y()),
					cv::Point(pt.x(),pt.y()));
				theApp.img_bk.copyTo(theApp.img_show);
				rectangle(theApp.img_show, rt,theApp.cfp_color, theApp.cfp_thickness);
				update();
				return;
			}

			//鼠标拖动绘制矩形
			QPoint pt = GetImgPosFromClient(pos);
			cv::Point lt, rb;
			if (pt.x() > m_mouseDownPoint.x())
			{
				if (pt.y() > m_mouseDownPoint.y())
				{
					int idx_l = theApp.markerBT.GetNearestLBoundary(m_mouseDownPoint.x());
					int idx_t = theApp.markerBT.GetNearestTBoundary(m_mouseDownPoint.y());
					int idx_r = theApp.markerBT.GetNearestRBoundary(pt.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					int idx_b = theApp.markerBT.GetNearestBBoundary(pt.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
					lt.x = theApp.markerBT.GetLBoundary(idx_l);
					lt.y = theApp.markerBT.GetTBoundary(idx_t);
					rb.x = theApp.markerBT.GetRBoundary(idx_r);
					rb.y = theApp.markerBT.GetBBoundary(idx_b);
				}
				else
				{
					int idx_l = theApp.markerBT.GetNearestLBoundary(m_mouseDownPoint.x());
					int idx_t = theApp.markerBT.GetNearestTBoundary(pt.y());
					int idx_r = theApp.markerBT.GetNearestRBoundary(pt.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					int idx_b = theApp.markerBT.GetNearestBBoundary(m_mouseDownPoint.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
					lt.x = theApp.markerBT.GetLBoundary(idx_l);
					lt.y = theApp.markerBT.GetTBoundary(idx_t);
					rb.x = theApp.markerBT.GetRBoundary(idx_r);
					rb.y = theApp.markerBT.GetBBoundary(idx_b);
				}
			}
			else
			{
				if (pt.y() > m_mouseDownPoint.y())
				{
					int idx_l = theApp.markerBT.GetNearestLBoundary(pt.x());
					int idx_t = theApp.markerBT.GetNearestTBoundary(m_mouseDownPoint.y());
					int idx_r = theApp.markerBT.GetNearestRBoundary(m_mouseDownPoint.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					int idx_b = theApp.markerBT.GetNearestBBoundary(pt.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
					lt.x = theApp.markerBT.GetLBoundary(idx_l);
					lt.y = theApp.markerBT.GetTBoundary(idx_t);
					rb.x = theApp.markerBT.GetRBoundary(idx_r);
					rb.y = theApp.markerBT.GetBBoundary(idx_b);
				}
				else
				{
					int idx_l = theApp.markerBT.GetNearestLBoundary(pt.x());
					int idx_t = theApp.markerBT.GetNearestTBoundary(pt.y());
					int idx_r = theApp.markerBT.GetNearestRBoundary(m_mouseDownPoint.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					int idx_b = theApp.markerBT.GetNearestBBoundary(m_mouseDownPoint.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
					lt.x = theApp.markerBT.GetLBoundary(idx_l);
					lt.y = theApp.markerBT.GetTBoundary(idx_t);
					rb.x = theApp.markerBT.GetRBoundary(idx_r);
					rb.y = theApp.markerBT.GetBBoundary(idx_b);
				}
			}

			theApp.img_bk.copyTo(theApp.img_show);
			rectangle(theApp.img_show, lt, rb,theApp.cfp_color, theApp.cfp_thickness);

			update();
			break;
		}
	}
}

void AnswerCardDlg::clipProcessingOnMouseUp(const QPoint &pos)
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
				drawControlPoint(m_controlPoint[i].center(), CTRL_POINT_LENGTH, theApp.cropArea_color, theApp.cropArea_thickness);
			}

			theApp.cfp_tmpRect = cv::Rect(m_controlRect);		
			m_clipDlg->setConfirmBtnEnabled(true);
			theApp.m_state++;
			update();

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

void AnswerCardDlg::clipProcessingOnMouseMove(const QPoint &pos)
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
					m_isSaved = false;

					//重绘控制区域，计算控制点位置
					dragMarquee(pt, m_ctrlPointIndex);
					
					//update();

					//恢复图像
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

void AnswerCardDlg::questionProcessingOnMouseUp(const QPoint &pos)
{
	if (theApp.m_state != SinglePress && theApp.m_state != MultiPress)
	{
		return;
	}

	QPoint pt = GetImgPosFromClient(pos);//转换到图像坐标
	int idx_l, idx_r, idx_t, idx_b;      //计算对应标记点

	if (pt.x() > m_mouseDownPoint.x())
	{
		if (pt.y() > m_mouseDownPoint.y())
		{
			idx_l = theApp.markerBT.GetNearestLBoundary(m_mouseDownPoint.x());
			idx_t = theApp.markerBT.GetNearestTBoundary(m_mouseDownPoint.y());
			idx_r = theApp.markerBT.GetNearestRBoundary(pt.x());
			idx_r = idx_r < idx_l ? idx_l : idx_r;
			idx_b = theApp.markerBT.GetNearestBBoundary(pt.y());
			idx_b = idx_b < idx_t ? idx_t : idx_b;
		}
		else
		{
			idx_l = theApp.markerBT.GetNearestLBoundary(m_mouseDownPoint.x());
			idx_t = theApp.markerBT.GetNearestTBoundary(pt.y());
			idx_r = theApp.markerBT.GetNearestRBoundary(pt.x());
			idx_r = idx_r < idx_l ? idx_l : idx_r;
			idx_b = theApp.markerBT.GetNearestBBoundary(m_mouseDownPoint.y());
			idx_b = idx_b < idx_t ? idx_t : idx_b;
		}
	}//if (pt.x() > m_mouseDownPoint.x())
	else
	{
		if (pt.y() > m_mouseDownPoint.y())
		{
			idx_l = theApp.markerBT.GetNearestLBoundary(pt.x());
			idx_t = theApp.markerBT.GetNearestTBoundary(m_mouseDownPoint.y());
			idx_r = theApp.markerBT.GetNearestRBoundary(m_mouseDownPoint.x());
			idx_r = idx_r < idx_l ? idx_l : idx_r;
			idx_b = theApp.markerBT.GetNearestBBoundary(pt.y());
			idx_b = idx_b < idx_t ? idx_t : idx_b;
		}
		else
		{
			idx_l = theApp.markerBT.GetNearestLBoundary(pt.x());
			idx_t = theApp.markerBT.GetNearestTBoundary(pt.y());
			idx_r = theApp.markerBT.GetNearestRBoundary(m_mouseDownPoint.x());
			idx_r = idx_r < idx_l ? idx_l : idx_r;
			idx_b = theApp.markerBT.GetNearestBBoundary(m_mouseDownPoint.y());
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

		for (int i = idx_t; rowId <= idx_b; i++)
		{
			theApp.AddQuestion(
				m_fillPointDlg->getOptionRange().start + i - idx_t, 
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

		for (int i = idx_l; columnId <= idx_r; i++)
		{
			theApp.AddQuestion(
				m_fillPointDlg->getOptionRange().start + i - idx_l, 
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

void AnswerCardDlg::questionProcessingOnMouseMove(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case SinglePress:
	case MultiPress:
		{
			//鼠标拖动绘制矩形
			QPoint pt = GetImgPosFromClient(pos);
			cv::Point lt, rb;
			if (pt.x() > m_mouseDownPoint.x())
			{
				if (pt.y() > m_mouseDownPoint.y())
				{
					int idx_l = theApp.markerBT.GetNearestLBoundary(m_mouseDownPoint.x());
					int idx_t = theApp.markerBT.GetNearestTBoundary(m_mouseDownPoint.y());
					int idx_r = theApp.markerBT.GetNearestRBoundary(pt.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					int idx_b = theApp.markerBT.GetNearestBBoundary(pt.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
					lt.x = theApp.markerBT.GetLBoundary(idx_l);
					lt.y = theApp.markerBT.GetTBoundary(idx_t);
					rb.x = theApp.markerBT.GetRBoundary(idx_r);
					rb.y = theApp.markerBT.GetBBoundary(idx_b);
				}
				else
				{
					int idx_l = theApp.markerBT.GetNearestLBoundary(m_mouseDownPoint.x());
					int idx_t = theApp.markerBT.GetNearestTBoundary(pt.y());
					int idx_r = theApp.markerBT.GetNearestRBoundary(pt.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					int idx_b = theApp.markerBT.GetNearestBBoundary(m_mouseDownPoint.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
					lt.x = theApp.markerBT.GetLBoundary(idx_l);
					lt.y = theApp.markerBT.GetTBoundary(idx_t);
					rb.x = theApp.markerBT.GetRBoundary(idx_r);
					rb.y = theApp.markerBT.GetBBoundary(idx_b);
				}
			}
			else
			{
				if (pt.y() > m_mouseDownPoint.y())
				{
					int idx_l = theApp.markerBT.GetNearestLBoundary(pt.x());
					int idx_t = theApp.markerBT.GetNearestTBoundary(m_mouseDownPoint.y());
					int idx_r = theApp.markerBT.GetNearestRBoundary(m_mouseDownPoint.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					int idx_b = theApp.markerBT.GetNearestBBoundary(pt.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
					lt.x = theApp.markerBT.GetLBoundary(idx_l);
					lt.y = theApp.markerBT.GetTBoundary(idx_t);
					rb.x = theApp.markerBT.GetRBoundary(idx_r);
					rb.y = theApp.markerBT.GetBBoundary(idx_b);
				}
				else
				{
					int idx_l = theApp.markerBT.GetNearestLBoundary(pt.x());
					int idx_t = theApp.markerBT.GetNearestTBoundary(pt.y());
					int idx_r = theApp.markerBT.GetNearestRBoundary(m_mouseDownPoint.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					int idx_b = theApp.markerBT.GetNearestBBoundary(m_mouseDownPoint.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
					lt.x = theApp.markerBT.GetLBoundary(idx_l);
					lt.y = theApp.markerBT.GetTBoundary(idx_t);
					rb.x = theApp.markerBT.GetRBoundary(idx_r);
					rb.y = theApp.markerBT.GetBBoundary(idx_b);
				}
			}

			theApp.img_bk.copyTo(theApp.img_show);
			rectangle(theApp.img_show, lt, rb,theApp.cfp_color, theApp.cfp_thickness);

			update();
			break;
		}
	}
}

void AnswerCardDlg::whiteLineProcessingOnMouseUp(const QPoint &pos)
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

void AnswerCardDlg::whiteLineProcessingOnMouseMove(const QPoint &pos)
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

void AnswerCardDlg::blackLineProcessingOnMouseUp(const QPoint &pos)
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
				theApp.is_synchronous = false;
				update();
			}
			
			m_lineDetectDlg->setBlackLineBtnText(tr("重新框选黑检测线"));
			m_lineDetectDlg->setProcessing(false);
			lineDetectDone();

			theApp.m_state++;
			theApp.img_bk.release();
			break;
		}
	}//switch (theApp.m_state)
}

void AnswerCardDlg::blackLineProcessingOnMouseMove(const QPoint &pos)
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

void AnswerCardDlg::idPointProcessingOnMouseUp(const QPoint &pos)
{
	switch (theApp.m_state)
	{
	case BasePress:
		{
			//鼠标拖动绘制矩形
			QPoint pt = GetImgPosFromClient(pos);
			int idx_l, idx_r, idx_t, idx_b;      //计算对应标记点

			if (pt.x() > m_mouseDownPoint.x())
			{
				if (pt.y() > m_mouseDownPoint.y())
				{
					idx_l = theApp.markerBT.GetNearestLBoundary(m_mouseDownPoint.x());
					idx_t = theApp.markerBT.GetNearestTBoundary(m_mouseDownPoint.y());
					idx_r = theApp.markerBT.GetNearestRBoundary(pt.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					idx_b = theApp.markerBT.GetNearestBBoundary(pt.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
				}
				else
				{
					idx_l = theApp.markerBT.GetNearestLBoundary(m_mouseDownPoint.x());
					idx_t = theApp.markerBT.GetNearestTBoundary(pt.y());
					idx_r = theApp.markerBT.GetNearestRBoundary(pt.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					idx_b = theApp.markerBT.GetNearestBBoundary(m_mouseDownPoint.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
				}
			}
			else
			{
				if (pt.y() > m_mouseDownPoint.y())
				{
					idx_l = theApp.markerBT.GetNearestLBoundary(pt.x());
					idx_t = theApp.markerBT.GetNearestTBoundary(m_mouseDownPoint.y());
					idx_r = theApp.markerBT.GetNearestRBoundary(m_mouseDownPoint.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					idx_b = theApp.markerBT.GetNearestBBoundary(pt.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
				}
				else
				{
					idx_l = theApp.markerBT.GetNearestLBoundary(pt.x());
					idx_t = theApp.markerBT.GetNearestTBoundary(pt.y());
					idx_r = theApp.markerBT.GetNearestRBoundary(m_mouseDownPoint.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					idx_b = theApp.markerBT.GetNearestBBoundary(m_mouseDownPoint.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
				}
			}

			int count = 1;
			cv::Range range = cv::Range(1,1);
			bool isHorizontal = true;
			int cSpace = 0;
			int rSpace = 0;

			if (isHorizontal)
			{
				if (idx_b - idx_t != (range.start - 1) * cSpace + range.start - 1 )
				{
					QMessageBox::information(this, " ", 
						tr("框选范围过大！"));
					theApp.m_state = BaseBegin;
					theApp.is_synchronous = false;
					update();
					break;
				}
				else if (idx_r - idx_l != (count - 1) * rSpace + count - 1)
				{
					QMessageBox::information(this, " ", 
						tr("框选范围过大！"));
					theApp.m_state = BaseBegin;
					theApp.is_synchronous = false;
					update();
					break;
				}
			}
			else
			{
				if (idx_r - idx_l != (range.start - 1) * rSpace + range.start - 1)
				{
					QMessageBox::information(this, " ", 
						tr("框选范围过大！"));
					theApp.is_synchronous = false;
					theApp.m_state = BaseBegin;
					update();
					break;
				}
				else if (idx_b - idx_t != (count - 1) * cSpace + count - 1)
				{
					QMessageBox::information(this, " ", 
						tr("框选范围过大！"));
					theApp.m_state = BaseBegin;
					theApp.is_synchronous = false;
					update();
					break;
				}
			}

			int idx = 1;

			if (theApp.idGroup.size() > 0)
			{
				idx = (theApp.idGroup.end() - 1)->id + 1;
			}

			theApp.AddIdPoint(idx, idx_t, idx_l, idx_r);

			theApp.m_state++;
			theApp.img_bk.release();

			//控制自定义窗口按钮
			m_idPointDlg->setAddBtnText(tr("重新添加ID点"));
			m_idPointDlg->setConfirmBtnEnabled(true);
			theApp.is_synchronous = false;
			break;
		}
	}
}

void AnswerCardDlg::idPointProcessingOnMouseMove(const QPoint &pos)
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
					int idx_l = theApp.markerBT.GetNearestLBoundary(m_mouseDownPoint.x());
					int idx_t = theApp.markerBT.GetNearestTBoundary(m_mouseDownPoint.y());
					int idx_r = theApp.markerBT.GetNearestRBoundary(pt.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					int idx_b = theApp.markerBT.GetNearestBBoundary(pt.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
					lt.x = theApp.markerBT.GetLBoundary(idx_l);
					lt.y = theApp.markerBT.GetTBoundary(idx_t);
					rb.x = theApp.markerBT.GetRBoundary(idx_r);
					rb.y = theApp.markerBT.GetBBoundary(idx_b);
				}
				else
				{
					int idx_l = theApp.markerBT.GetNearestLBoundary(m_mouseDownPoint.x());
					int idx_t = theApp.markerBT.GetNearestTBoundary(pt.y());
					int idx_r = theApp.markerBT.GetNearestRBoundary(pt.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					int idx_b = theApp.markerBT.GetNearestBBoundary(m_mouseDownPoint.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
					lt.x = theApp.markerBT.GetLBoundary(idx_l);
					lt.y = theApp.markerBT.GetTBoundary(idx_t);
					rb.x = theApp.markerBT.GetRBoundary(idx_r);
					rb.y = theApp.markerBT.GetBBoundary(idx_b);
				}
			}
			else
			{
				if (pt.y() > m_mouseDownPoint.y())
				{
					int idx_l = theApp.markerBT.GetNearestLBoundary(pt.x());
					int idx_t = theApp.markerBT.GetNearestTBoundary(m_mouseDownPoint.y());
					int idx_r = theApp.markerBT.GetNearestRBoundary(m_mouseDownPoint.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					int idx_b = theApp.markerBT.GetNearestBBoundary(pt.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
					lt.x = theApp.markerBT.GetLBoundary(idx_l);
					lt.y = theApp.markerBT.GetTBoundary(idx_t);
					rb.x = theApp.markerBT.GetRBoundary(idx_r);
					rb.y = theApp.markerBT.GetBBoundary(idx_b);
				}
				else
				{
					int idx_l = theApp.markerBT.GetNearestLBoundary(pt.x());
					int idx_t = theApp.markerBT.GetNearestTBoundary(pt.y());
					int idx_r = theApp.markerBT.GetNearestRBoundary(m_mouseDownPoint.x());
					idx_r = idx_r < idx_l ? idx_l : idx_r;
					int idx_b = theApp.markerBT.GetNearestBBoundary(m_mouseDownPoint.y());
					idx_b = idx_b < idx_t ? idx_t : idx_b;
					lt.x = theApp.markerBT.GetLBoundary(idx_l);
					lt.y = theApp.markerBT.GetTBoundary(idx_t);
					rb.x = theApp.markerBT.GetRBoundary(idx_r);
					rb.y = theApp.markerBT.GetBBoundary(idx_b);
				}
			}

			theApp.img_bk.copyTo(theApp.img_show);
			rectangle(theApp.img_show, lt, rb, theApp.idPoint_color, theApp.idPoint_thickness);

			update();
			break;
		}
	}
}

////////////////////////////////////按钮///////////////////////////////////////

//保存当前project
void AnswerCardDlg::saveDataSource()
{
	if (m_dataPath == "")
	{
		return;
	}

	DataInfo info;
	info.image = mat2QImage(theApp.img_raw);
	info.anchorType = theApp.anchor_type;
	info.markerDone = m_markerDlg->isDone();
	info.barGroup = theApp.barGroup;
	info.fillingPointGroup = theApp.cfp_group;
	info.cropAreaInfo = theApp.cropAreas;
	info.questioninfo = theApp.questionInfo;
	info.markersRect[0] = theApp.markersRect[0];
	info.markersRect[1] = theApp.markersRect[1];
	info.whiteLineRect = theApp.whiteLineRect;
	info.blackeLineRect = theApp.blackLineRect;
	info.idPointInfo = theApp.idGroup;
	info.referPoint = theApp.referPoint;
	info.questionType = theApp.questionType;

	for (int i = 0; i < 4; ++i)
	{
		info.anchorPoints[i] = theApp.anchorPoints[i];
	}
	
	DataIO io(m_dataPath, DATA_WRITE);
	io.writeToDat(info);

	m_isSaved = true;
}

//返回主窗口
void AnswerCardDlg::on_backBtn_clicked()
{
	if (m_isSaved == false)
	{
		saveDataSource();
		m_isSaved = true;
		this->close();

	}
	else
	{
		this->close();
	}
}

//重载退出程序的函数
void AnswerCardDlg::closeEvent(QCloseEvent *event)
{
	if (m_isSaved == false)
	{
		saveDataSource();
		event->accept();
	}
	else
	{
		event->accept();
	}
}

