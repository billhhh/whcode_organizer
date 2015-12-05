#include "AddCourseDlg.h"
#include "ui_AddCourseDlg.h"
#include "qmessagebox.h"

AddCourseDlg::AddCourseDlg(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::AddCourseDlg();
	ui->setupUi(this);
}

AddCourseDlg::~AddCourseDlg()
{
	delete ui;
}

QString AddCourseDlg::getCourseName()
{
	return ui->courseEdit->text();
}

void AddCourseDlg::on_okBtn_clicked()
{
	if (ui->courseEdit->text() == "")
	{
		QMessageBox::information(this,"  ",tr("输入不能为空!"));
		return;
	}

	accept();
}

void AddCourseDlg::on_cancelBtn_clicked()
{
	this->close();
}