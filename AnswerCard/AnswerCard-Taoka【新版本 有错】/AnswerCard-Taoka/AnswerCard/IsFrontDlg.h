#ifndef ISFRONTDLG_H
#define ISFRONTDLG_H

#include <QDialog>
namespace Ui {class IsFrontDlg;};

class IsFrontDlg : public QDialog
{
	Q_OBJECT

public:
	IsFrontDlg(QWidget *parent = 0);
	~IsFrontDlg();

	void resume();
	void initialization();
	void setCurrentIndex(int idx);
	int getCurrentIndex();

private:
	Ui::IsFrontDlg *ui;
	int m_currentIndex;

signals:
	void indexChanged(int);

protected slots:
	void on_typeCbx_currentIndexChanged(QString);
};

#endif // ISFRONTDLG_H
