#ifndef INPUTNUMBERDLG_H
#define INPUTNUMBERDLG_H

#include <QDialog>
#include "qmessagebox.h"
#include "qcheckbox.h"
namespace Ui {class InputNumberDlg;};

//输入要制作的标记点的个数的窗口
class InputNumberDlg : public QDialog
{
	Q_OBJECT

public:
	InputNumberDlg(QWidget *parent = 0);
	~InputNumberDlg();

	int getInputNumber();

private:
	Ui::InputNumberDlg *ui;

protected slots:
	void on_okBtn_clicked();
	void on_cancelBtn_clicked();
};


class TipMsgBox : public QMessageBox
{
	 Q_OBJECT

public:
	explicit TipMsgBox(QWidget *parent, const QString& title, 
		const QString &msg, QMessageBox::Icon icon = QMessageBox::Information);
	bool isShowAgain() const;

protected:
    virtual void paintEvent(QPaintEvent *paintevent);

private:
	QCheckBox *m_checkBox;

};

#endif // INPUTNUMBERDLG_H
