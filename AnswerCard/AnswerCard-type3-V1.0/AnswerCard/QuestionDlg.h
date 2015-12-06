#ifndef QUESTIONDLG_H
#define QUESTIONDLG_H

#include <QDialog>
#include <QMessageBox>
#include "AnswerCard.h"

namespace Ui {class QuestionDlg;};

class QuestionDlg : public QDialog
{
	Q_OBJECT

public:
	QuestionDlg(QWidget *parent = 0);
	~QuestionDlg();

	cv::Range getQuestionRange() const {return m_question_id_range;}
	bool isSingleRadioChecked() const {return m_singleRadioChecked;}

	void setQuestionEditStr(const QString &str);
	void setQuestionEditEnable(bool);
	void setAddBtnText(const QString &str);
	
	// 插入题目信息字符串到列表控件
	void addQuestionStrToList(int id, bool isCrosswise,
		bool isSingleChoice, int num, int idx = -1);
	void initialization();

private:
	Ui::QuestionDlg *ui;
	cv::Range m_question_id_range;//题号范围
	bool m_singleRadioChecked;

signals:
	void imageUpdated();

protected slots:
	void on_addBtn_clicked();
	void on_deleteBtn_clicked();
	void on_horRadioBtn_clicked();
	void on_verRadioBtn_clicked();
	void on_singleRadioBtn_clicked();
	void on_multiRadioBtn_clicked();
};

#endif // QUESTIONDLG_H
