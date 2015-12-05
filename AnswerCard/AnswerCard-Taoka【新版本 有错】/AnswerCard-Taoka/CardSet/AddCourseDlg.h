#ifndef ADDCOURSEDLG_H
#define ADDCOURSEDLG_H

#include <QDialog>
namespace Ui {class AddCourseDlg;};

class AddCourseDlg : public QDialog
{
	Q_OBJECT

public:
	AddCourseDlg(QWidget *parent = 0);
	~AddCourseDlg();

	QString getCourseName();
private:
	Ui::AddCourseDlg *ui;

protected slots:
	void on_okBtn_clicked();
	void on_cancelBtn_clicked();
};

#endif // ADDCOURSEDLG_H
