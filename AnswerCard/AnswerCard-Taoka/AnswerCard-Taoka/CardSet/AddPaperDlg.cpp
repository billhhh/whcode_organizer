#include "AddPaperDlg.h"
#include "ui_AddPaperDlg.h"
#include "qmessagebox.h"

AddPaperDlg::AddPaperDlg(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::AddPaperDlg();
	ui->setupUi(this);
	this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
	connect(ui->cancelBtn, SIGNAL(clicked()), this, SLOT(close()));

	QRegExp reg("[1-9][0-9]+$");
	QRegExpValidator *validator = new QRegExpValidator(reg);
	ui->numEdit->setValidator(validator);
	ui->dpiEdit->setValidator(validator);
}

AddPaperDlg::~AddPaperDlg()
{
	delete ui;
}

QString AddPaperDlg::getPaperSetId() const
{
	return ui->numEdit->text();
}

QString AddPaperDlg::getPaperDpi() const
{
	return ui->dpiEdit->text();
}

void AddPaperDlg::on_okBtn_clicked()
{
	if (ui->numEdit->text() == "")
	{
		QMessageBox::information(this," ",tr("套卡号不能为空"));
		return;
	}

	if (ui->dpiEdit->text() == "")
	{
		QMessageBox::information(this," ",tr("分辨率不能为空"));
		return;
	}

	accept();
}

