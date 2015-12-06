#include "QuestionDlg.h"
#include "ui_QuestionDlg.h"


QuestionDlg::QuestionDlg(QWidget *parent)
	: QDialog(parent),m_question_id_range()
{
	ui = new Ui::QuestionDlg();
	ui->setupUi(this);

	//正则表达式
	QRegExp rx("-?\\d{1,3}--?\\d{1,3}");
    QValidator *validator = new QRegExpValidator(rx, this);
	ui->questionEdit->setValidator(validator);
}

QuestionDlg::~QuestionDlg()
{
	delete ui;
}

void QuestionDlg::initialization()
{
	ui->addBtn->setText(tr("框选位置"));
	ui->questionList->clear();
	ui->questionEdit->clear();
	this->setEnabled(false);
}

//设置文本编辑框的内容
void QuestionDlg::setQuestionEditStr(const QString &str)
{
	ui->questionEdit->setText(str);
}

void QuestionDlg::setQuestionEditEnable(bool b)
{
	ui->questionEdit->setEnabled(b);
}

void QuestionDlg::setAddBtnText(const QString &str)
{
	ui->addBtn->setText(str);
}

// 插入题目信息字符串到列表控件
void QuestionDlg::addQuestionStrToList(int id, bool isCrosswise,
	bool isSingleChoice, int num, int idx)
{
	QString strW ;
	
	if (idx == -1)
	{
		if (isCrosswise)
		{
			if (isSingleChoice)
			{
				strW = QString(tr("题%1|横排|单选|%2个选项").arg(id).arg(num));
			}
			else
			{
				strW = QString(tr("题%1|横排|多选|%2个选项").arg(id).arg(num));
			}
		}
		else
		{
			if (isSingleChoice)
			{
				strW = QString(tr("题%1|竖排|单选|%2个选项").arg(id).arg(num));
			}
			else
			{
				strW = QString(tr("题%1|竖排|多选|%2个选项").arg(id).arg(num));
			}
		}

		ui->questionList->addItem(strW);
	}
	else
	{
		ui->questionList->insertItem(idx, strW);
	}
}

void QuestionDlg::on_addBtn_clicked()
{
	//已经处于框选状态
	if (theApp.m_group_state == 7 && (theApp.m_state == 1 || theApp.m_state == 5))
	{
		//启用输入控件
		setQuestionEditEnable(true);

		//更改按钮文字
		setAddBtnText(tr("框选位置"));

		//控制状态
		theApp.m_group_state =7;
		theApp.m_state = 0;

		return ;
	}

	QString edit_questions_id = ui->questionEdit->text();

	if (edit_questions_id == "")
	{
		QMessageBox::information(NULL, tr(" "),tr("请输入题号"));
		return ;
	}

	//禁用输入控件
	setQuestionEditEnable(false);

	//更改按钮文字
	setAddBtnText(tr("取消"));

	//判断输入是否是题号范围
	int idx = edit_questions_id.indexOf('-');

	if (-1 == idx)			//输入单个题号
	{
		m_question_id_range.end = m_question_id_range.start = edit_questions_id.toInt();
		theApp.m_group_state = 7;
		theApp.m_state = 1;
	}
	else					//输入题号范围
	{
		QString start,end;
		start = edit_questions_id.left(idx);
		end = edit_questions_id.right(edit_questions_id.length() - idx - 1);
		m_question_id_range.start = start.toInt();
		m_question_id_range.end = end.toInt();
		theApp.m_group_state = 7;
		theApp.m_state = 5;
	}
}

void QuestionDlg::on_deleteBtn_clicked()
{
	int idx = ui->questionList->currentRow();

	if (idx > -1)
	{
		ui->questionList->takeItem(idx);
		theApp.questionInfo.erase(theApp.questionInfo.begin()+idx);
		theApp.is_synchronous = false;
	}
}

void QuestionDlg::on_horRadioBtn_clicked()
{
	theApp.isHorizontal = true;
}

void QuestionDlg::on_verRadioBtn_clicked()
{
	theApp.isHorizontal = false;
}

void QuestionDlg::on_singleRadioBtn_clicked()
{
	m_singleRadioChecked = true;
}

void QuestionDlg::on_multiRadioBtn_clicked()
{
	m_singleRadioChecked = false;
}