#ifndef ADDPAGEDLG_H
#define ADDPAGEDLG_H

#include <QDialog>
#include "qstring.h"
namespace Ui {class AddPageDlg;};

class AddPageDlg : public QDialog
{
	Q_OBJECT

public:
	AddPageDlg(QWidget *parent = 0);
	~AddPageDlg();

	QString getPageNumber() const;
	QString getFrontPagePath() const;
	QString getBackPagePath() const;

	bool hasBackPage() const;

private:
	Ui::AddPageDlg *ui;
	bool m_hasBackPage;

protected slots:
	void on_okBtn_clicked();
	void on_addFrontPageBtn_clicked();
	void on_addBackPageBtn_clicked();
};

#endif // ADDPAGEDLG_H
