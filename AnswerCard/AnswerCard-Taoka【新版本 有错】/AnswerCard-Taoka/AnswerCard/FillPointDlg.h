#ifndef FILLPOINTDLG_H
#define FILLPOINTDLG_H

#include <QDialog>
#include <QMessageBox>
#include "AnswerCard.h"
#include "qlistwidget.h"

namespace Ui {class FillPointDlg;};

#define QUESTION 0

class FillPointDlg : public QDialog
{
	Q_OBJECT

public:
	FillPointDlg(QWidget *parent = 0);
	~FillPointDlg();

	void initialization();
	int resume();

	FillingPointsType getFillPointType();
	string getFillPointName() const;
	int getCSpace() const;
	int getRSpace() const;

	void setAddBtnText(const QString &str);
	void setConfirmBtnEnabled(bool);

	cv::Range getOptionRange() const {return m_optionRange;}
	int getOptionCount() const       {return m_optionCount;}
	bool isCrossWise() const         {return m_isCrosswise;}
	bool isSingleChecked() const     {return m_singleRadioChecked;}
	void setIdx_l(int i)             {m_idx_l = i;}
	void setIdx_r(int i)             {m_idx_r = i;}
	void setIdx_t(int i)             {m_idx_t = i;}
	void setIdx_b(int i)             {m_idx_b = i;}

private:
	void setProcessing(bool);
	QString fillPointTypeToString(int idx);

	Ui::FillPointDlg *ui;

	int m_idx_l, m_idx_r;            //计算对应标记点
	int m_idx_t, m_idx_b;            //计算对应标记点
	int m_optionCount;               //选项数量
	cv::Range m_optionRange;         //选项范围
	bool m_singleRadioChecked;       //是否单选
	bool m_isCrosswise;              //是否横向排布
	int count[12];                  

	// 插入题目信息字符串到列表控件
	void addQuestionStrToList(int id, bool isCrosswise,
		bool isSingleChoice, int num, int idx = -1);

signals:
	void fillPointBegin();
	void fillPointDone();
	void fillPointDelete();
	void fillPointClicked(int);

protected slots:
	void on_addBtn_clicked();
	void on_confirmBtn_clicked();
	void on_deleteBtn_clicked();
	void on_horRadioBtn_clicked();
	void on_verRadioBtn_clicked();
	void on_singleRadioBtn_clicked();
	void on_multiRadioBtn_clicked();
	void on_typeCmb_currentIndexChanged(int);
	void showClicked(QListWidgetItem* item);
};

#endif // FILLPOINTDLG_H
