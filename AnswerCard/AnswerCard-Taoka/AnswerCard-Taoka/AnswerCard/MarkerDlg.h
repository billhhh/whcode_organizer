#ifndef MARKERDLG_H
#define MARKERDLG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {class MarkerDlg;};

class MarkerDlg : public QDialog
{
	Q_OBJECT

public:
	MarkerDlg(QWidget *parent = 0);
	~MarkerDlg();

	void setHorEditEnabled(bool isEnable);
	void setVerEditEnabled(bool isEnable);
	void setHorEditNum(short num);
	void setVerEditNum(short num);

	void initialization();
	int resume(bool isDone);
	bool isDone() const {return m_done;}
	void setDone(bool b) {m_done = b;}
private:
	Ui::MarkerDlg *ui;

	// 水平标记点数量
	short m_hmarkers_num;
	// 垂直标记点数量
	short m_vmarkers_num;

	bool m_done;
signals:
	void markerDone();

protected slots:
	void on_horMarkersBtn_clicked();
	void on_verMarkersBtn_clicked();
	void on_confirmBtn_clicked();

};

#endif // MARKERDLG_H
