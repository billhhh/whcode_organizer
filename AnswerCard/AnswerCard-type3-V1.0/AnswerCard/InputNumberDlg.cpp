#include "InputNumberDlg.h"
#include "ui_InputNumberDlg.h"
#include "qmessagebox.h"

InputNumberDlg::InputNumberDlg(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::InputNumberDlg();
	ui->setupUi(this);

	QValidator *validator=new QIntValidator(1,10000,this);
	ui->numEdit->setValidator(validator);
}

InputNumberDlg::~InputNumberDlg()
{
	delete ui;
}

void InputNumberDlg::on_okBtn_clicked()
{
	if (ui->numEdit->text() == "")
	{
		QMessageBox::information(this, tr("  "),
			tr("输入不能为空！"));
		return;
	}

	if (ui->numEdit->text() == "0")
	{
		QMessageBox::information(this, tr("  "),
			tr("输入不能为0！"));
		return;
	}
	accept();
}

void InputNumberDlg::on_cancelBtn_clicked()
{
	this->close();
}

int InputNumberDlg::getInputNumber()
{
	return ui->numEdit->text().toInt();
}

TipMsgBox::TipMsgBox(QWidget *parent, const QString& title, 
	const QString &msg, QMessageBox::Icon icon)
	:QMessageBox(icon, title, "", NoButton, parent, Qt::Sheet)
{
	m_checkBox = new QCheckBox(tr("不再提示"), this);
	m_checkBox->setChecked(false);

	QPushButton* pOK = this->addButton(QMessageBox::Ok);
//	pOK->setText(tr("确定"));
	QLabel* pLabel = new QLabel(msg);
    pLabel->setScaledContents(true);
    pLabel->setIndent(20);
	QSpacerItem *pSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

	dynamic_cast< QGridLayout *>(this->layout())->addWidget(pLabel, 0, 1,1,3);
    dynamic_cast< QGridLayout *>(this->layout())->addWidget(m_checkBox, 3, 0,1,2);
	dynamic_cast< QGridLayout *>(this->layout())->addItem(pSpacer, 3, 2);
	dynamic_cast< QGridLayout *>(this->layout())->addWidget(pOK, 3, 3);

	//QVBoxLayout * pLayout = new QVBoxLayout(this);
	//pLayout->addWidget(m_checkBox);
	//dynamic_cast< QGridLayout *>(this->layout())->addWidget(m_checkBox);/*->addLayout(pLayout, 1, 1);*/
}

void TipMsgBox::paintEvent(QPaintEvent *paintevent)
{
	/*this->addButton(m_checkBox, QMessageBox::ButtonRole.*/	
	QMessageBox::paintEvent(paintevent);
}

bool TipMsgBox::isShowAgain() const
{
	return !(m_checkBox->isChecked());
}