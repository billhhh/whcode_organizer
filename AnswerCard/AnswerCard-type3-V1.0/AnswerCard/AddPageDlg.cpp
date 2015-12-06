#include "AddPageDlg.h"
#include "ui_AddPageDlg.h"
#include "qmessagebox.h"
#include "qfiledialog.h"

AddPageDlg::AddPageDlg(QWidget *parent)
	: QDialog(parent), m_hasBackPage(false)
{
	ui = new Ui::AddPageDlg();
	ui->setupUi(this);
	this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);

	connect(ui->cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
	QRegExp reg("[1-9][0-9] + $");
	QRegExpValidator *validator = new QRegExpValidator(reg);
	ui->idEdit->setValidator(validator);
}

AddPageDlg::~AddPageDlg()
{
	delete ui;
}

void AddPageDlg::on_okBtn_clicked()
{
	if (ui->idEdit->text() == "")
	{
		QMessageBox::information(this," ",tr("第几张还没填！"));
		return;
	}

	if (ui->pathEdit->text() == "")
	{
		QMessageBox::information(this," ",tr("正面答题卷还没添加！"));
		return;
	}

	accept();
}


bool AddPageDlg::hasBackPage() const
{
	return m_hasBackPage;
}

QString AddPageDlg::getFrontPagePath() const
{
	return ui->pathEdit->text();
}

QString AddPageDlg::getBackPagePath() const
{
	return ui->backPathEdit->text();
}

QString AddPageDlg::getPageId() const
{
	return ui->idEdit->text();
}

void AddPageDlg::on_addFrontPageBtn_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(
	this, tr("添加正面答题卷"),
    ".",
    "Image files (*.bmp *.jpg *.tiff *.tif);;JPEG(*.jpg);;BMP(*.bmp);;TIFF(*.tiff *.tif)");

	if (fileName != "")
	{
		ui->pathEdit->setText(fileName);
		ui->addBackPageBtn->setEnabled(true);
		ui->backPathEdit->setEnabled(true);
	}
}

void AddPageDlg::on_addBackPageBtn_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(
	this, tr("添加反面答题卷"),
    ".",
    "Image files (*.bmp *.jpg *.tiff *.tif);;JPEG(*.jpg);;BMP(*.bmp);;TIFF(*.tiff *.tif)");

	if (fileName != "")
	{
		ui->backPathEdit->setText(fileName);
		m_hasBackPage = true;
	}
}