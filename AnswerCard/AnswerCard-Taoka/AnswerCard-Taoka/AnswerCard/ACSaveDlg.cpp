#include "ACSaveDlg.h"
#include "ui_ACSaveDlg.h"
#include "XmlIO\XmlIO.h"
#include "AnswerCard.h"

ACSaveDlg::ACSaveDlg(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::ACSaveDlg();
	ui->setupUi(this);
}

ACSaveDlg::~ACSaveDlg()
{
	delete ui;
}

void ACSaveDlg::on_okBtn_clicked()
{
	theApp.clearACInfo();

	int rst = theApp.TransToOutputStruct();
	if (rst < 0)
	{
		QMessageBox::information(NULL, "  ", tr("选择题信息还没框选"));
		return;
	}

//	theApp.acinfo.ac_id = ui->idEdit->text().toAscii().data();
	//theApp.acinfo.dpi = ui->dpiEdit->text().toInt();

	//QString fileName = QFileDialog::getSaveFileName(this, 
	//	tr("输出XML"), tr(""), tr("XML (*.xml)"));

	//if (!fileName.isNull())  
	//{
	//	XmlIo io;
	//	io.Write(fileName.toAscii().data(), theApp.acinfo);
	//	this->close();
	//	QMessageBox::information(this, "  ", tr("答题卡描述文件输出成功"));
	//	return;
 //   }
}

