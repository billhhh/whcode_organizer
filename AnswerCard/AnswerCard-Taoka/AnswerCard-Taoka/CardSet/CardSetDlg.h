#ifndef CardSetDlg_H
#define CardSetDlg_H

#include <QtGui/QDialog>
#include <QFileDialog>
#include <QList>
#include "ui_CardSetDlg.h"
#include "CardDoc.h"
#include "AddPaperDlg.h"
#include "AddPageDlg.h"
#include "../AnswerCard/AnswerCardDlg.h"


class CardSetDlg : public QDialog
{
	Q_OBJECT

public:
	CardSetDlg(QApplication &app, int type = 1);
	~CardSetDlg();

	//重绘事件,调试用
	//void paintEvent(QPaintEvent *)
	//{
	//	printf("%s\n",m_cardDoc.getCourse().size());
	//};

private:
	Ui::CardCombineClass ui;
	CardDoc m_cardDoc; 
	int m_type;
	 QComboBox* m_combox;

protected slots:
	void on_addPaperBtn_clicked();
	void on_deletePaperBtn_clicked();
	void on_openPaperBtn_clicked();
	void on_savePaperBtn_clicked();
	void on_importPaperBtn_clicked();
	void on_editPageBtn_clicked();
	void on_addPageBtn_clicked();
	void on_deletePageBtn_clicked();
	void updatePageDetails(int, int);
	void on_addCourseBtn_clicked();
	void on_deleteCourseBtn_clicked();
	void courseChanged(int);
};

#endif // CardSetDlg_H
