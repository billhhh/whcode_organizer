#include "CardSetDlg.h"
#include "qmessagebox.h"
#include "../XmlIO/XmlIO.h"
#include "qfile.h"
#include "../AnswerCard/DataIO.h"
#include "InputDpiDlg.h"
#include "AddCourseDlg.h"

#pragma comment(lib,"XmlIoDll.lib")

CardSetDlg::CardSetDlg(QApplication &app, int type)
	: QDialog(0),m_cardDoc(type)
{
	ui.setupUi(this);

	//设置对话框的最小最大化按钮
	this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
	this->setWindowFlags(windowFlags()|Qt::WindowMinimizeButtonHint);
	this->setWindowFlags(windowFlags()|Qt::WindowMaximizeButtonHint);

	m_type = type;
	//m_cardDoc = CardDoc(m_type);
	connect(ui.paperSetTable, SIGNAL(cellClicked(int , int)),
		this, SLOT(updatePageDetails(int, int)));

	ui.gridLayout_2->removeWidget(ui.comboBox);
	delete ui.comboBox;
	ui.comboBox = new QComboBox(this);
    ui.comboBox->setObjectName(QString::fromUtf8("comboBox"));
    ui.comboBox->setMinimumSize(QSize(150, 0));

    ui.gridLayout_2->addWidget(ui.comboBox, 0, 1, 1, 1);
	connect(ui.comboBox, SIGNAL(currentIndexChanged(int)),
	this, SLOT(courseChanged(int)));
}

CardSetDlg::~CardSetDlg()
{
}

//添加科目
void CardSetDlg::on_addCourseBtn_clicked()
{
	AddCourseDlg dlg;

	while (dlg.exec() == QDialog::Accepted)
	{
		QString course = dlg.getCourseName();

		if (m_cardDoc.isCourseExist(course) != -1)
		{
			QMessageBox::information(this, tr(" "),tr("该科目已存在，请重新输入！")); 
		}
		else
		{
			ui.comboBox->addItem(dlg.getCourseName());
			m_cardDoc.createCourse(dlg.getCourseName());
			break;
		}
	}
}

//移除科目及其试卷
void CardSetDlg::on_deleteCourseBtn_clicked()
{
	if (ui.comboBox->count() <= 0)
	{
		return;
	}

	int courseIdx = ui.comboBox->currentIndex();
	
	
	m_cardDoc.removeCourse(courseIdx);

	ui.comboBox->removeItem(courseIdx);

	if (ui.comboBox->count() > 0)
	{
		ui.comboBox->setCurrentIndex(0);
		courseChanged(0);
	}
	else
	{
		//清空子视图
		ui.subTable->clearContents();
		ui.subTable->setRowCount(0);

		//清空试卷集视图
		ui.paperSetTable->clearContents();
		ui.paperSetTable->setRowCount(0);
	}
}

//根据当前选择的科目更改显示的试卷套内容
void CardSetDlg::courseChanged(int index)
{
	if (index < 0)
	{
		return;
	}

	//清空子视图
	ui.subTable->clearContents();
	ui.subTable->setRowCount(0);

	//清空试卷集视图
	ui.paperSetTable->clearContents();
	ui.paperSetTable->setRowCount(0);

	for (int i = 0; i < m_cardDoc.getSetCountOfCourse(index); ++i)
	{
		PaperSet set = m_cardDoc.getPageSetDetail(index, i);

		//更新数据到视图界面
		int currentRow = ui.paperSetTable->rowCount();
		ui.paperSetTable->insertRow(currentRow);
		ui.paperSetTable->setItem(currentRow, 0, new QTableWidgetItem(set.setId));

		//该试卷套的试卷数量
		int count = 0;

		vector<PaperPage>::iterator iter = set.page.begin();

		for (; iter != set.page.end(); ++iter)
		{
			if (iter->isPositive == true)
			{
				++count;
			}
		}

		QString countrSt = tr("%1").arg(count);
		ui.paperSetTable->setItem(currentRow, 1, new QTableWidgetItem(countrSt));
	}
}

//添加试卷套
void CardSetDlg::on_addPaperBtn_clicked()
{
	if (ui.comboBox->count() == 0)
	{
		QMessageBox::information(this, tr(" "),tr("请先添加科目！"));
		return;
	}

	AddPaperDlg dlg;
	//打开添加试卷套的对话框
	while (dlg.exec() == QDialog::Accepted)
	{
		QString number = dlg.getPaperSetId();
		int dpi = dlg.getPaperDpi().toInt();

		if (m_cardDoc.isPaperSetIdExist(ui.comboBox->currentIndex(), number) > -1)
		{
			QMessageBox::information(this, tr(" "),tr("该试卷编号已存在，请重新输入！"));
			continue;
		}

		m_cardDoc.createPaperSet(ui.comboBox->currentIndex(), number, dpi);

		//将文件信息输出到界面上
		int currentRow = ui.paperSetTable->rowCount();
		ui.paperSetTable->insertRow(currentRow);
		ui.paperSetTable->setItem(currentRow, 0, new QTableWidgetItem(number));
		ui.paperSetTable->setItem(currentRow, 1, new QTableWidgetItem(tr("0")));
		//ui.paperSetTable->setItem(currentRow, 2, new QTableWidgetItem(name));
		break;
	}
}

//删除试卷套
void CardSetDlg::on_deletePaperBtn_clicked()
{
	if (ui.comboBox->count() == 0)
	{
		QMessageBox::information(this, tr(" "),tr("请先添加科目！"));
		return;
	}

	if (ui.paperSetTable->currentIndex().row() >= 0)
	{
		int idx = ui.paperSetTable->currentItem()->row();
		ui.paperSetTable->removeRow(idx);
		m_cardDoc.removePaperSet(ui.comboBox->currentIndex(), idx);

		ui.subTable->clearContents();
		ui.subTable->setRowCount(0);
		ui.paperSetTable->clearSelection();
		//updatePageDetails(ui.paperSetTable->rowCount() - 1, 0);
	}
	else
	{
		QMessageBox::information(this, tr(" "),tr("还没选择哪套试卷！"));
	}
}


//添加一张试卷
void CardSetDlg::on_addPageBtn_clicked()
{
	if (ui.paperSetTable->currentIndex().row() < 0)
	{
		QMessageBox::information(this, tr(" "),tr("还没选择哪套试卷！"));
		return;
	}

	AddPageDlg dlg;
	int setIdx = ui.paperSetTable->currentItem()->row();	

	while (dlg.exec() == QDialog::Accepted)
	{
		QString number = dlg.getPageNumber();

		if (m_cardDoc.isPageIdOfSetExist(ui.comboBox->currentIndex(), setIdx, number) > -1)
		{
			QMessageBox::information(this, tr(" "),tr("该编号已存在，请重新输入！"));
			continue;
		}

		//添加正面试卷
		QString frontFileName = dlg.getFrontPagePath();
		Mat tmp = imread(frontFileName.toStdString());
		QImage img = AnswerCardDlg::mat2QImage(tmp);

		PaperPage page;
		page.pageId = number;
		page.isPositive = true;
		m_cardDoc.insertPaperPage(ui.comboBox->currentIndex(), setIdx, page, img);

		//将文件信息输出到界面上
		int currentRow = ui.subTable->rowCount();
		ui.subTable->insertRow(currentRow);
		ui.subTable->setItem(currentRow, 0, new QTableWidgetItem(number));
		ui.subTable->setItem(currentRow, 1, new QTableWidgetItem("正面"));

		//添加反面试卷
		if (dlg.hasBackPage() == true)
		{
			QString backFileName = dlg.getBackPagePath();
			Mat backTmp = imread(backFileName.toStdString());
			QImage backImg = AnswerCardDlg::mat2QImage(backTmp);

			PaperPage backPage;
			backPage.pageId = number;
			backPage.isPositive = false;
			m_cardDoc.insertPaperPage(ui.comboBox->currentIndex(), setIdx, backPage, backImg);
		}

		//int count = m_cardDoc.getCountOfPage(setIdx);
		int count = ui.subTable->rowCount();
		ui.paperSetTable->setItem(setIdx, 1, new QTableWidgetItem(QString(tr("%1").arg(count))));

		break;
	}

}

//移除一张试卷
void CardSetDlg::on_deletePageBtn_clicked()
{
	if (ui.paperSetTable->currentIndex().row() < 0)
	{
		QMessageBox::information(this, tr(" "),tr("还没选择哪套试卷！"));
		return;
	}

	if (ui.subTable->currentIndex().row() < 0)
	{
		QMessageBox::information(this, tr(" "),tr("还没选择哪张试卷！"));
		return;
	}
	
	QString pageId = ui.subTable->currentItem()->text();
	int currentRow = ui.subTable->currentItem()->row();
	int setIdx = ui.paperSetTable->currentItem()->row();

	int pageIdx = m_cardDoc.isPageIdOfSetExist(ui.comboBox->currentIndex(), setIdx, pageId);
	m_cardDoc.removePaperPage(ui.comboBox->currentIndex(), setIdx, pageIdx);
	ui.subTable->removeRow(currentRow);

	if (m_cardDoc.getPageCountOfSet(ui.comboBox->currentIndex(), setIdx) > 0
		&& m_cardDoc.getPageCountOfSet(ui.comboBox->currentIndex(), setIdx) > pageIdx
		&& m_cardDoc.getPageDetail(ui.comboBox->currentIndex(), setIdx, pageIdx).isPositive == false
		&& m_cardDoc.getPageDetail(ui.comboBox->currentIndex(), setIdx, pageIdx).pageId == pageId)
	{
		m_cardDoc.removePaperPage(ui.comboBox->currentIndex(), setIdx, pageIdx);
	}

	ui.subTable->clearSelection();

	//更新试卷集视图
	int count = ui.subTable->rowCount();
	ui.paperSetTable->setItem(setIdx, 1, new QTableWidgetItem(QString(tr("%1").arg(count))));
}

//当点中某试卷套后，更新其试卷信息
void CardSetDlg::updatePageDetails(int row, int column)
{
	if (row > -1)
	{
		ui.subTable->clearContents();
		ui.subTable->setRowCount(0);

		int count = m_cardDoc.getPageCountOfSet(ui.comboBox->currentIndex(), row);

		for (int i = 0; i < count; ++i)
		{
			PaperPage page = m_cardDoc.getPageDetail(ui.comboBox->currentIndex(), row, i);
			
			if (page.isPositive == true)
			{
				//将文件信息输出到界面上
				int currentRow = ui.subTable->rowCount();
				ui.subTable->insertRow(currentRow);
				ui.subTable->setItem(currentRow, 0, new QTableWidgetItem(page.pageId));				
			}
		}
	}
}

//编辑所选试卷
void CardSetDlg::on_editPageBtn_clicked()
{
	int setIdx = ui.paperSetTable->currentIndex().row();

	if (setIdx < 0)
	{
		QMessageBox::information(this, tr(" "),tr("还没选择哪套试卷！"));
		return;
	}

	if (ui.subTable->currentIndex().row() < 0)
	{
		QMessageBox::information(this, tr(" "),tr("还没选择哪张试卷！"));
		return;
	}

	QString pageId = ui.subTable->currentItem()->text();
	int pageIdx = m_cardDoc.isPageIdOfSetExist(ui.comboBox->currentIndex(), setIdx, pageId);

	QString dataPath = QString(tr("tmp\\%1-%2-%3-%4.dat")
		.arg(ui.comboBox->currentText())
		.arg(m_cardDoc.getPageSetDetail(ui.comboBox->currentIndex(), setIdx).setId)
		.arg(m_cardDoc.getPageDetail(ui.comboBox->currentIndex(), setIdx, pageIdx).pageId)
		.arg((int)(m_cardDoc.getPageDetail(ui.comboBox->currentIndex(), setIdx, pageIdx).isPositive)));

	QString pre = QString(tr("tmp\\%1-%2-%3")
		.arg(ui.comboBox->currentText())
		.arg(m_cardDoc.getPageSetDetail(ui.comboBox->currentIndex(), setIdx).setId)
		.arg(m_cardDoc.getPageDetail(ui.comboBox->currentIndex(), setIdx, pageIdx).pageId));

	AnswerCardDlg dlg(pre);
	dlg.setDataSource(dataPath);
	dlg.exec();
}

//////////////////////////////////文件输入输出////////////////////////////////////
void CardSetDlg::on_savePaperBtn_clicked()
{
	if (ui.comboBox->count() <= 0 || m_cardDoc.getSetCountOfCourse(ui.comboBox->currentIndex()) <= 0)
	{
//		QMessageBox::information(NULL, tr("失败"),tr("文件不能为空！"));
		return;
	}

	QString fileName = QFileDialog::getSaveFileName(this, 
		tr("保存当前科目下套卡信息"), tr(""), tr("ACPROJ (*.acproj)"));

	if (fileName != "")
	{
		int rst = m_cardDoc.zipPaperSetInfo(ui.comboBox->currentIndex(), fileName);

		if (rst >= 0)
		{
			QMessageBox::information(NULL, tr("成功"),tr("保存成功！"));
		}
		else
		{
			QMessageBox::information(NULL, tr("失败"),tr("保存失败！"));
		}
	}
}

void CardSetDlg::on_openPaperBtn_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(
                this, tr("打开ACPROJ文件"),
                ".",
				tr("ACPROJ (*.acproj)"));

	if (fileName != "")
	{
		int currentIdx = ui.comboBox->currentIndex();
		int courseCount = m_cardDoc.getCourse().size();

		int rst = m_cardDoc.resumeDataFromZip(fileName);

		if (rst == 0)
		{
			QMessageBox::information(this," ","文件无法打开");
			return;
		}

		if (courseCount < m_cardDoc.getCourse().size())
		{
			ui.comboBox->addItem(m_cardDoc.getCourse().rbegin()->courseName);
		}

		if (currentIdx == -1)
		{
			this->courseChanged(0);
		}
		else
		{
			this->courseChanged(currentIdx);
		}
	}
}

void CardSetDlg::on_importPaperBtn_clicked()
{
	if (ui.comboBox->count() <= 0 || m_cardDoc.getSetCountOfCourse(ui.comboBox->currentIndex()) <= 0)
	{
//		QMessageBox::information(NULL, tr("失败"),tr("文件不能为空！"));
		return;
	}

	QString fileName = QFileDialog::getSaveFileName(this, 
		tr("导出当前科目下套卡XML文件"), tr(""), tr("XML(*.xml)"));

	if (fileName != "")
	{
		vector<PaperSet> paperSet = m_cardDoc.getPaperSet(ui.comboBox->currentIndex());
		TK_info tkInfo;

		for (int i = 0; i < paperSet.size(); ++i)
		{
			for (int j = 0; j < paperSet.at(i).page.size(); ++j)
			{
				PerAC_info perInfo;
				perInfo.tkId = paperSet.at(i).setId.toInt();			
				perInfo.pageId = paperSet.at(i).page.at(j).pageId.toInt();

				QString dataPath = QString(tr("tmp\\%1-%2-%3-%4.dat")
					.arg(ui.comboBox->currentText())
					.arg(paperSet.at(i).setId)
					.arg(paperSet.at(i).page.at(j).pageId)
					.arg((int)(paperSet.at(i).page.at(j).isPositive)));

				QString pre = QString(tr("tmp\\%1-%2-%3")
					.arg(ui.comboBox->currentText())
					.arg(paperSet.at(i).setId)
					.arg(paperSet.at(i).page.at(j).pageId));

				AnswerCardDlg dlg(pre);
				dlg.setDataSource(dataPath);
				theApp.TransToOutputStruct();

				theApp.acinfo.ac_type = m_cardDoc.getAcType();
				theApp.acinfo.dpi =  paperSet.at(i).dpi;
				theApp.acinfo.isFront = paperSet.at(i).page.at(j).isPositive;
				perInfo.acinfo.push_back(theApp.acinfo);

				if (j + 1 < paperSet.at(i).page.size())
				{
					if (paperSet.at(i).page.at(j).pageId == paperSet.at(i).page.at(j + 1).pageId)
					{
						QString dataPath = QString(tr("tmp\\%1-%2-%3-%4.dat")
							.arg(ui.comboBox->currentText())
							.arg(paperSet.at(i).setId)
							.arg(paperSet.at(i).page.at(j+1).pageId)
							.arg((int)(paperSet.at(i).page.at(j+1).isPositive)));
						AnswerCardDlg dlg1(pre);
						dlg1.setDataSource(dataPath);
						theApp.TransToOutputStruct();

						theApp.acinfo.ac_type = m_cardDoc.getAcType();
						theApp.acinfo.dpi = paperSet.at(i).dpi;
						theApp.acinfo.isFront = paperSet.at(i).page.at(j+1).isPositive;
						perInfo.acinfo.push_back(theApp.acinfo);

						++j;
					}
				}

				tkInfo.tkinfo.push_back(perInfo);
			}
		}

		XmlIo io;		
		//tkInfo.tkinfo
		io.Write(fileName.toStdString(), tkInfo);
		QMessageBox::information(this, "  ", tr("答题卡描述文件输出成功"));
	}
}