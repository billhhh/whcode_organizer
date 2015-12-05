#ifndef ANSWERCARDDLG_H
#define ANSWERCARDDLG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QScrollBar>
#include <QCloseEvent>
#include "qlayout.h"
#include "DataIO.h"
#include "AnswerCard.h"
#include "AnchorDlg.h"
#include "MarkerDlg.h"
#include "BarCodeDlg.h"
#include "ClipDlg.h"
#include "ACSaveDlg.h"
#include "FillPointDlg.h"
#include "LineDetectDlg.h"
#include "IdPointDlg.h"
#include "IsFrontDlg.h"
#include "qpushbutton.h"

namespace Ui {class AnswerCardDlg;};

#define TOP_LEFT 0            //左上
#define TOP_RIGHT 1           //右上
#define BOTTOM_RIGHT 2
#define BOTTOM_LEFT 3
#define LEFT 4
#define TOP 5
#define RIGHT 6
#define BOTTOM 7
#define CENTER 8
#define CTRL_POINT_LENGTH 8     //控制点边长
#define CTRL_RECT_MIN_LENGTH 12 //选择框最小边长

class AnswerCardDlg : public QDialog
{
	Q_OBJECT

public:
	AnswerCardDlg(QString pathPrefix = "");
	~AnswerCardDlg();

	//将Mat格式的图片转为QImage输出
	static QImage mat2QImage(const cv::Mat &mat);

	//将QImage格式的图片转为Mat
	static cv::Mat qImage2Mat(const QImage &img);

	//设置数据资源
	int setDataSource(const QString& filePath); 

protected:
	void keyPressEvent(QKeyEvent *event);

	//重绘事件
	void paintEvent(QPaintEvent *);

	//初始化窗口部件
	void initialization();

	//重载退出程序的函数
	void closeEvent(QCloseEvent *event);

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

	void anchorProcessingOnMouseUp(const QPoint &pos);
	void markerProcessingOnMouseUp(const QPoint &pos);
	void barcodeProcessingOnMouseUp(const QPoint &pos);
	void fillPointProcessingOnMouseUp(const QPoint &pos);
	void clipProcessingOnMouseUp(const QPoint &pos);
	void questionProcessingOnMouseUp(const QPoint &pos);
	void whiteLineProcessingOnMouseUp(const QPoint &pos);
	void blackLineProcessingOnMouseUp(const QPoint &pos);
	void idPointProcessingOnMouseUp(const QPoint &pos);

	void markerProcessingOnMouseMove(const QPoint &pos);
	void barcodeProcessingOnMouseMove(const QPoint &pos);
	void fillPointProcessingOnMouseMove(const QPoint &pos);
	void clipProcessingOnMouseMove(const QPoint &pos);
	void questionProcessingOnMouseMove(const QPoint &pos);
	void whiteLineProcessingOnMouseMove(const QPoint &pos);
	void blackLineProcessingOnMouseMove(const QPoint &pos);
	void idPointProcessingOnMouseMove(const QPoint &pos);

	//文件保存
	void saveDataSource();

protected:
	QPoint m_mouseDownPoint;    //鼠标按下坐标
	QRect m_picRect;            //图像区域大小	
	short m_hmarkers_num;       //水平标记点数量	
	short m_vmarkers_num;       //垂直标记点数量		
	QString m_dataPath;         //文件路径
	QString m_dataPathPrefix;   //文件路径前缀
	bool m_isSaved;             //是否已保存
	bool m_isFront;             //是否为正面
	static Mat m_imgTmp; 
	bool m_isZooming;           //是否正在缩放框选区域
	int m_zoomingIndex;         //记录正拖动框选框的哪个点，左上、右上、左下等

	QRect m_controlPoint[9];    //选取框的九个控制点
	cv::Rect m_controlRect;     //选取框区域
	int m_ctrlPointIndex;       //正拖曳的控制点
	
	Ui::AnswerCardDlg *ui;

	AnchorDlg *m_anchorDlg;               //定位点窗口
	MarkerDlg *m_markerDlg;               //标记点窗口
	BarCodeDlg *m_barcodeDlg;             //条形码窗口
	ClipDlg *m_clipDlg;                   //裁切窗口
	FillPointDlg *m_fillPointDlg;         //填涂点窗口
	IsFrontDlg *m_isFrontDlg;
	LineDetectDlg * m_lineDetectDlg;
	IdPointDlg *m_idPointDlg;

	QPushButton *m_clearBtn;             //清除卡格式数据
	QPushButton *m_changePicBtn;            //替换卡格式图片

protected slots:
	
	void on_backBtn_clicked();

	//处理窗口激活与关闭
	void anchorDone();
	void markerDone();	
	void enableDlg();
	void barCodeBegin();
	void fillPointBegin();
	void clipBegin();
	void deleteBtnClicked();
	void lineDetectBegin();
	void lineDetectDone();
	void idPointBegin();
	void clipClicked(int idx);
	void barCodeClicked(int idx);
	void fillPointClicked(int idx);
	void idPointClicked(int idx);
	void pageChanged(int idx);
	void on_clearBtn_clicked();
	void on_changePicBtn_clicked();
};

#endif // ANSWERCARDDLG_H
