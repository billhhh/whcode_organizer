#ifndef WHITEDETECTLINEDLG_H
#define WHITEDETECTLINEDLG_H

#include <QDialog>
#include <QMessageBox>
namespace Ui {class WhiteDetectLineDlg;};

class WhiteDetectLineDlg : public QDialog
{
	Q_OBJECT

public:
	WhiteDetectLineDlg(QWidget *parent = 0);
	~WhiteDetectLineDlg();

	void setAddBtnText(const QString& str);
	void setConfirmBtnEnabled(bool);

	void initialization();

private:
	Ui::WhiteDetectLineDlg *ui;

	void setProcessing(bool);

signals:
	void whiteLineDone();
	void whiteLinebegin();
	void whiteLineDelete();

protected slots:
	void on_addBtn_clicked();
	void on_confirmBtn_clicked();
	void on_deleteBtn_clicked();
};

#endif // WHITEDETECTLINEDLG_H
