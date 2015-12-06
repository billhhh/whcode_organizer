#ifndef FILLPOINTPLUSDLG_H
#define FILLPOINTPLUSDLG_H

#include <QDialog>
namespace Ui {class FillPointPlusDlg;};

class FillPointPlusDlg : public QDialog
{
	Q_OBJECT

public:
	FillPointPlusDlg(QWidget *parent = 0);
	~FillPointPlusDlg();

private:
	Ui::FillPointPlusDlg *ui;
};

#endif // FILLPOINTPLUSDLG_H
