#ifndef CUSTOMIZEFILLPOINTDLG_H
#define CUSTOMIZEFILLPOINTDLG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {class CustomizeFillPointDlg;};

class CustomizeFillPointDlg : public QDialog
{
	Q_OBJECT

public:
	CustomizeFillPointDlg(QWidget *parent = 0);
	~CustomizeFillPointDlg();

	void setAddBtnText(const QString& str);
	void setConfirmBtnEnabled(bool);

	void initialization();
private:
	Ui::CustomizeFillPointDlg *ui;

signals:
	void imageUpdated();

protected slots:
	void on_addBtn_clicked();
	void on_confirmBtn_clicked();
	void on_deleteBtn_clicked();
};

#endif // CUSTOMIZEFILLPOINTDLG_H
