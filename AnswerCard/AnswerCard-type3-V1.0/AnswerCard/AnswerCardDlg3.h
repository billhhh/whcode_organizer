#ifndef AnswerCardDlg3_H
#define AnswerCardDlg3_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QScrollBar>
#include "qlayout.h"
#include "../XmlIO/ACStructs.h"
#include "AnswerCard.h"
#include "AnchorDlg.h"
#include "BarCodeDlg.h"
#include "ClipDlg.h"
#include "QuestionDlg.h"
#include "ACSaveDlg.h"
#include "FillPointDlg.h"
#include "MarkerMakeDlg.h"
#include "LineDetectDlg.h"
#include "IsFrontDlg.h"
#include "AnchorRectDlg.h"
#include "CardSetDlg.h"
#include "PagePointDlg.h"
#include "ClearDlg.h"
#include "CreateCardDlg.h"

namespace Ui {class AnswerCardDlg3;};

#define TOP_LEFT 0
#define TOP_RIGHT 1
#define BOTTOM_RIGHT 2
#define BOTTOM_LEFT 3
#define LEFT 4
#define TOP 5
#define RIGHT 6
#define BOTTOM 7
#define CENTER 8
#define CTRL_POINT_LENGTH 8     //控制点边长
#define CTRL_RECT_MIN_LENGTH 12 //选择框最小边长

class AnswerCardDlg3 : public QDialog
{
	Q_OBJECT

public:
	AnswerCardDlg3(QApplication &app, int type = 4);
	~AnswerCardDlg3();

	//将Mat格式的图片转为QImage输出
	QImage mat2QImage(const cv::Mat &mat);

	//将QImage格式的图片转为Mat
	cv::Mat qImage2Mat(const QImage &img);

protected:
	int setDataSource(const QString &path);
	void saveDataSource(const QString &path);

	//重绘事件
	void paintEvent(QPaintEvent *);

	//初始化窗口部件
	void initialization();

	// 计算客户区的一个点在图像中的位置
	QPoint GetImgPosFromClient(const QPoint &clientPos);

	//事件过滤
	bool eventFilter(QObject *, QEvent *);

	//鼠标左键按下
	void mouseLeftButtonPress(const QPoint &pos);

	//鼠标左键弹起
	void mouseLeftButtonRelease(const QPoint &pos);

	//鼠标移动
	void mouseMove(const QPoint &pos);

	//更改鼠标光标
	void changeMouseCursor(const QPoint &pos);

	//拖曳选取框并重绘
	void dragMarquee(const QPoint &newPos, int ctlPointIndex);

	//绘制控制点
	void drawControlPoint(const QPoint &centerPos, int length, cv::Scalar scalar, ushort thickness);

	//重新计算九个控制点的位置
	void computeCtrlPointPos();

	void anchorProcessingOnMouseUp(const QPoint &pos);      //处理定位模块的鼠标点击释放事件
	void barcodeProcessingOnMouseUp(const QPoint &pos);     //处理条形码模块的鼠标点击释放事件
	void fillPointProcessingOnMouseUp(const QPoint &pos);
	void clipProcessingOnMouseUp(const QPoint &pos);
	void questionProcessingOnMouseUp(const QPoint &pos);
	void whiteLineProcessingOnMouseUp(const QPoint &pos);
	void blackLineProcessingOnMouseUp(const QPoint &pos);
	void makerMakeProcessingOnMouseUp(const QPoint &pos);
	void anchorRectProcessingOnMouseUp(const QPoint &pos);
	void pagePointProcessingOnMouseUp(const QPoint &pos);
	void markerProcessingOnMouseUp(const QPoint &pos);

	void barcodeProcessingOnMouseMove(const QPoint &pos);
	void fillPointProcessingOnMouseMove(const QPoint &pos);
	void clipProcessingOnMouseMove(const QPoint &pos);
	void questionProcessingOnMouseMove(const QPoint &pos);
	void whiteLineProcessingOnMouseMove(const QPoint &pos);
	void blackLineProcessingOnMouseMove(const QPoint &pos);
	void makerMakeProcessingOnMouseMove(const QPoint &pos);
	void anchorRectProcessingOnMouseMove(const QPoint &pos);
	void pagePointProcessingOnMouseMove(const QPoint &pos);
	void markerProcessingOnMouseMove(const QPoint &pos);

protected:
	QString m_cardPath;			//当前答题卡文件路径
	QPoint m_mouseDownPoint;    //鼠标按下坐标
	QRect m_picRect;            //图像区域大小	
	short m_hmarkers_num;       //水平标记点数量	
	short m_vmarkers_num;       //垂直标记点数量		
	Mat m_imgTmp;
	bool m_isZooming;
	int m_zoomingIndex;

	QRect m_controlPoint[9];    //选取框的九个控制点
	cv::Rect m_controlRect;     //选取框区域
	int m_ctrlPointIndex;       //正拖曳的控制点
	
	Ui::AnswerCardDlg3 *ui;
	AnchorDlg *m_anchorDlg;               //定位点窗口
	BarCodeDlg *m_barcodeDlg;             //条形码窗口
	ClipDlg *m_clipDlg;                   //裁切窗口
	FillPointDlg *m_fillPointDlg;         //填涂点窗口
	MarkerMakeDlg *m_markerMakeDlg;       //虚拟标记点制作窗口
	LineDetectDlg * m_lineDetectDlg;      //黑白线窗口
	PagePointDlg *m_pagePointDlg;         //页码标识窗口
	CardSetDlg * m_cardSetDlg;			  //套卡管理窗口
	ClearDlg *m_clearDlg;
//	IsFrontDlg *m_isFrontDlg;
	AnchorRectDlg *m_anchorRectDlg;       //定位框窗口
	QSpacerItem *m_verticalSpacer;        //占位符控件
	QPushButton *m_clearBtn;              //卡格式清除按钮
	QPushButton *m_changePicBtn;          //重新指定试卷图片按钮
	int m_cardType;

protected slots:
	//创建新的套卡
	void on_newCardBtn_clicked();
	////输出XML文件
	void on_importXMLBtn_clicked();
	//保存文件
	void on_saveFileBtn_clicked();
	//读取文件
	void on_openFileBtn_clicked();

	//定位结束
	void anchorDone();
	//标记点结束
	void markerDone();
	//使所有子窗口可编辑
	void enableDlg();
	//开始条形码框选
	void barCodeBegin();
	void fillPointBegin();
	void clipBegin();
	void markerMakeBegin();
	void lineDetectBegin();
	void lineDetectDone();
	void pagePointBegin();
	void markerMakeDelete();

	//裁切区域点击
	void clipClicked(int idx);
	void barCodeClicked(int idx);
	void fillPointClicked();
	void markerMakeClicked();

	void editCard(QString);
	void deleteCard(QString);
	void on_clearBtn_clicked();
	void on_changePicBtn_clicked();
};

#endif // AnswerCardDlg3_H
