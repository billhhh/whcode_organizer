#ifndef ANCHORDLG_H
#define ANCHORDLG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {class AnchorDlg;};

class AnchorDlg : public QDialog
{
	Q_OBJECT

public:
	AnchorDlg(QWidget *parent = 0);
	~AnchorDlg();

	void initialization();
	int resume();
	bool isDone() const {return done;}
private:
	Ui::AnchorDlg *ui;
	bool done;

signals:
	void anchorDone();
	

protected slots:
	void on_anchorLTBtn_clicked();
	void on_anchorRTBtn_clicked();
	void on_anchorLBBtn_clicked();
	void on_anchorRBBtn_clicked();
	void on_confirmBtn_clicked();
};

#endif // ANCHORDLG_H
