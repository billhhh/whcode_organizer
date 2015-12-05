#ifndef ADDPAPERDLG_H
#define ADDPAPERDLG_H

#include <QDialog>
namespace Ui {class AddPaperDlg;};

class AddPaperDlg : public QDialog
{
	Q_OBJECT

public:
	AddPaperDlg(QWidget *parent = 0);
	~AddPaperDlg();

	QString getPaperSetId() const;
	QString getPaperDpi() const;

private:
	Ui::AddPaperDlg *ui;

protected slots:
	void on_okBtn_clicked();
};

#endif // ADDPAPERDLG_H
