#ifndef MARKERMAKEDLG_H
#define MARKERMAKEDLG_H

#include <QDialog>
#include "AnswerCard.h"
#include "qmessagebox.h"
#include "qstring.h"
#include "InputNumberDlg.h"
#include "qlistwidget.h"

namespace Ui {class MarkerMakeDlg;};

class MarkerMakeDlg : public QDialog
{
	Q_OBJECT

public:
	MarkerMakeDlg(QWidget *parent = 0);
	~MarkerMakeDlg();

	void initialization();     //初始化
	int resume(cv::Size markerSize, bool isDone);

	void setMarkerSize(cv::Size size);
	cv::Size getMarkerSize() const;
	bool isHorizontal() const;
	void setSizeEditText(const QString& str);
	void setSizeBtnText(const QString& str);
	void setHorBtnText(const QString& str);
	void setVerBtnText(const QString& str);
	void setListEnabled(bool);
	void setDelBtnEnabled(bool);
	void setEditBtnEnabled(bool);
	void setHDragBtnText(const QString& str);
	void setVDragBtnText(const QString& str);

	int getInputNumber() const;
	bool isDone() const {return m_isDone;}
	void setDone(bool done) {m_isDone = done;}

	void setProcessing(bool);
	void dragLastMarker(const QPoint& pos);   //更改最后一个标记点的位置
	bool addMarker(const QPoint& pos);        //添加一个标记点
	void drawMarkers();                       //绘制制作中的标记点
	void computeMarkerPos(const QPoint& pos); //计算制作中的标记点的位置

	QRect computeRectFromMarker();
	QRect computeRectFromMarker(vector<cv::Rect> xMarker, vector<cv::Rect> yMarker);

	bool isEditing() const {return m_editMode;}
	void updatePerMarker();

private:
	Ui::MarkerMakeDlg *ui;
	cv::Size m_markerSize;
	bool m_isHorizontal;     //是否是水平标记点
	int m_inputNumber;       //要制作标记点的数量
	bool m_isDone;           //是否已确认
	vector<QRect> m_markerRects; //每组标记点的区域

	TipMsgBox *m_tipMsgBox;

	bool m_editMode;
	int m_editingIndex;

	//临时记录
	vector<cv::Rect> m_hmarkersTmp;
	vector<cv::Rect> m_vmarkersTmp;
	cv::Size m_markerSizeTmp;
	int m_groupIdTmp;

signals:
	void MarkerMakeBegin();
	void MarkerMakeDone();
	void MarkerMakeDelete();
	void MarkerMakeClicked();
	void rowBegin();
	void colBegin();

protected slots:
	void on_sizeBtn_clicked();
	void on_horBtn_clicked();
	void on_verBtn_clicked();
	void on_addBtn_clicked();
	void on_cancelBtn_clicked();
	void on_deleteBtn_clicked();
	void showClicked(QListWidgetItem*);
	void on_deleteMarkerBtn_clicked();
	void on_editBtn_clicked();
	//void showPerClickd(QListWidgetItem*);
	void on_subList_itemClicked(QListWidgetItem*);

	void on_vDragBtn_clicked();
	void on_hDragBtn_clicked();
};

#endif // MARKERMAKEDLG_H
