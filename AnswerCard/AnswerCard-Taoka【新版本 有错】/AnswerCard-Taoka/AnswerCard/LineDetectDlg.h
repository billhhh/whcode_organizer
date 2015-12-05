#ifndef LINEDETECTDLG_H
#define LINEDETECTDLG_H

#include <QDialog>
namespace Ui {class LineDetectDlg;};

class LineDetectDlg : public QDialog
{
	Q_OBJECT

public:
	LineDetectDlg(QWidget *parent = 0);
	~LineDetectDlg();

	void setWhiteLineBtnText(const QString& str);
	void setBlackLineBtnText(const QString& str);
	void initialization();
	void setProcessing(bool);
	void resume();

private:
	Ui::LineDetectDlg *ui;

signals:
	void lineDone();
	void lineBegin();

protected slots:
	void on_blackLineBtn_clicked();
	void on_whiteLineBtn_clicked();
};

#endif // LINEDETECTDLG_H
