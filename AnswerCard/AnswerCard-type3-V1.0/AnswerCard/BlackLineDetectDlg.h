#ifndef BLACKLINEDETECTDLG_H
#define BLACKLINEDETECTDLG_H

#include <QDialog>
namespace Ui {class BlackLineDetectDlg;};

class BlackLineDetectDlg : public QDialog
{
	Q_OBJECT

public:
	BlackLineDetectDlg(QWidget *parent = 0);
	~BlackLineDetectDlg();
	void setAddBtnText(const QString& str);
	void setConfirmBtnEnabled(bool);

	void initialization();

private:
	Ui::BlackLineDetectDlg *ui;
	void setProcessing(bool);

signals:
	void BlackLineDone();
	void BlackLinebegin();
	void BlackLineDelete();

protected slots:
	void on_addBtn_clicked();
	void on_confirmBtn_clicked();
	void on_deleteBtn_clicked();
};

#endif // BLACKLINEDETECTDLG_H
