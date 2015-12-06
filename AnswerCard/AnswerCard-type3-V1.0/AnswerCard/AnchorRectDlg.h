#ifndef ANCHORRECTDLG_H
#define ANCHORRECTDLG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {class AnchorRectDlg;};

class AnchorRectDlg : public QDialog
{
	Q_OBJECT

public:
	AnchorRectDlg(QWidget *parent = 0);
	~AnchorRectDlg();

	void initialization();
	int resume();
	bool isDone() const {return m_done;}
	void setAnchorBtnText(QString str);

private:
	Ui::AnchorRectDlg *ui;
	bool m_done;

signals:
	void anchorDone();

protected slots:
	void on_anchorBtn_clicked();
	void on_confirmBtn_clicked();
};

#endif // ANCHORRECTDLG_H
