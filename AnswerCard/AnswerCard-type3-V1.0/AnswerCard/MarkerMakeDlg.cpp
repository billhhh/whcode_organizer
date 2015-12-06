#include "MarkerMakeDlg.h"
#include "ui_MarkerMakeDlg.h"


MarkerMakeDlg::MarkerMakeDlg(QWidget *parent)
	: QDialog(parent),
	m_markerSize(),
	m_isHorizontal(true),
	m_inputNumber(0),
	m_isDone(false),
	m_editMode(false),
	m_editingIndex(-1)
{
	ui = new Ui::MarkerMakeDlg();
	ui->setupUi(this);

	m_tipMsgBox = new TipMsgBox(this, tr("虚拟标记点定位"), 
		tr("先点击第一个标记点的位置，接着点击最后一个标记点的位置"));

	connect(ui->list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(showClicked(QListWidgetItem*)));
}

MarkerMakeDlg::~MarkerMakeDlg()
{
	delete m_tipMsgBox;
	delete ui;
}

void MarkerMakeDlg::initialization()
{
	m_markerSize = cv::Size();
	m_editingIndex = -1;
	m_editMode = false;
	m_isDone = false;
	setProcessing(false);
	ui->sizeEdit->clear();
	ui->verEdit->setText("0");
	ui->horEdit->setText("0");
	ui->groupEdit->setText("1");
	ui->sizeBtn->setText(tr("拖曳大小"));
	ui->horBtn->setText(tr("绘制"));
	ui->verBtn->setText(tr("绘制"));
	ui->list->clear();
	this->setEnabled(false);
	m_markerRects.clear();
	ui->subList->clear();
}

void MarkerMakeDlg::setProcessing(bool b)
{
	ui->addBtn->setEnabled(!b);
	ui->cancelBtn->setEnabled(!b);
	ui->horBtn->setEnabled(!b);
	ui->sizeBtn->setEnabled(!b);
	ui->verBtn->setEnabled(!b);
	ui->list->setEnabled(!b);
	ui->deleteBtn->setEnabled(!b);
	ui->groupEdit->setEnabled(!b);
	ui->deleteMarkerBtn->setEnabled(!b);
	ui->editBtn->setEnabled(!b);
	ui->subList->setEnabled(!b);
	ui->vDragBtn->setEnabled(!b);
	ui->hDragBtn->setEnabled(!b);
}

void MarkerMakeDlg::setMarkerSize(cv::Size size)
{
	m_markerSize = cv::Size(size);
}

cv::Size MarkerMakeDlg::getMarkerSize() const
{
	return m_markerSize;
}

void MarkerMakeDlg::setSizeEditText(const QString& str)
{
	ui->sizeEdit->setText(str);
}

void MarkerMakeDlg::setSizeBtnText(const QString& str)
{
	ui->sizeBtn->setText(str);
}

void MarkerMakeDlg::setHorBtnText(const QString& str)
{
	ui->horBtn->setText(str);
}

void MarkerMakeDlg::setVerBtnText(const QString& str)
{
	ui->verBtn->setText(str);
}

void MarkerMakeDlg::setHDragBtnText(const QString& str)
{
	ui->hDragBtn->setText(str);
}

void MarkerMakeDlg::setVDragBtnText(const QString& str)
{
	ui->vDragBtn->setText(str);
}

bool MarkerMakeDlg::isHorizontal() const
{
	return m_isHorizontal;
}

int MarkerMakeDlg::getInputNumber() const
{
	return m_inputNumber;
}

void MarkerMakeDlg::setListEnabled(bool b)
{
	ui->list->setEnabled(b);
}

void MarkerMakeDlg::setDelBtnEnabled(bool b)
{
	ui->deleteBtn->setEnabled(b);
}

void MarkerMakeDlg::setEditBtnEnabled(bool b)
{
	ui->editBtn->setEnabled(b);
}

void MarkerMakeDlg::on_vDragBtn_clicked()
{
	if (theApp.m_group_state == MarkerState 
		&& theApp.m_state == ColBegin)
	{
		ui->vDragBtn->setText(tr("拖曳"));
		setProcessing(false);

		if (m_editMode == true)
		{
			ui->list->setEnabled(false);
			ui->deleteBtn->setEnabled(false);
			ui->editBtn->setEnabled(false);
		}

		theApp.m_state = MarkerInitial;
		emit MarkerMakeDone();
		return;
	}

	if (theApp.vmarkers.size() >0)
	{
		if (QMessageBox::No == QMessageBox::information(this, 
			tr(" "), 
			tr("是否覆盖原来的标记点？\n垂直标记点组将会重置"),
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::Yes))
		{
			return;
		}
	}

	setProcessing(true);
	ui->vDragBtn->setText(tr("取消"));
	ui->vDragBtn->setEnabled(true);

	theApp.m_group_state = MarkerState;
	theApp.m_state = ColBegin;

	emit MarkerMakeBegin();
}

void MarkerMakeDlg::on_hDragBtn_clicked()
{
	if (theApp.m_group_state == MarkerState 
		&& theApp.m_state == RowBegin)
	{
		ui->hDragBtn->setText(tr("拖曳"));
		setProcessing(false);

		if (m_editMode == true)
		{
			ui->list->setEnabled(false);
			ui->deleteBtn->setEnabled(false);
			ui->editBtn->setEnabled(false);
		}

		theApp.m_state = MarkerInitial;
		emit MarkerMakeDone();
		return;
	}

	if (theApp.hmarkers.size() >0)
	{
		if (QMessageBox::No == QMessageBox::information(this, 
			tr(" "), 
			tr("是否覆盖原来的标记点？\n水平标记点组将会重置"),
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::Yes))
		{
			return;
		}
	}

	setProcessing(true);
	ui->hDragBtn->setText(tr("取消"));
	ui->hDragBtn->setEnabled(true);

	theApp.m_group_state = MarkerState;
	theApp.m_state = RowBegin;

	emit MarkerMakeBegin();
}

void MarkerMakeDlg::on_sizeBtn_clicked()
{

	if (theApp.m_group_state == MarkerMakeState && theApp.m_state == SizeBegin)
	{
		ui->sizeBtn->setText(tr("拖曳大小"));
		setProcessing(false);

		if (m_editMode == true)
		{
			ui->list->setEnabled(false);
			ui->deleteBtn->setEnabled(false);
			ui->editBtn->setEnabled(false);
		}

		theApp.is_synchronous = false;
		theApp.m_state = MarkerMakeInitial;
		emit MarkerMakeDone();
		return;
	}
	
	if (m_markerSize.width > 0)
	{
		if (QMessageBox::No == QMessageBox::information(this, 
			tr(" "), 
			tr("大小已经存在，是否覆盖原来大小？\n水平垂直序号组将会重置"),
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::Yes))
		{
			return;
		}
		else
		{
			m_markerSize = cv::Size();
			ui->sizeEdit->clear();
			theApp.vmarkers.clear();
			theApp.hmarkers.clear();
			ui->verEdit->setText("0");
			ui->horEdit->setText("0");
			ui->subList->clear();
			theApp.is_synchronous = false;
		}
	}

	setProcessing(true);
	ui->sizeBtn->setText(tr("取消"));
	ui->sizeBtn->setEnabled(true);

	theApp.m_group_state = MarkerMakeState;
	theApp.m_state = SizeBegin;

	emit MarkerMakeBegin();
}

void MarkerMakeDlg::on_horBtn_clicked()
{
	if (m_markerSize.width <= 0)
	{
		QMessageBox::information(this, tr(" "),
			tr("请先框选标记点大小！！"));
		return;
	}

	if (theApp.m_group_state == MarkerMakeState 
		&& theApp.m_state == MarkerFirstBegin)
	{
		ui->horBtn->setText(tr("绘制"));
		setProcessing(false);

		if (m_editMode == true)
		{
			ui->list->setEnabled(false);
			ui->deleteBtn->setEnabled(false);
			ui->editBtn->setEnabled(false);
		}

		theApp.m_state = MarkerMakeInitial;
		emit MarkerMakeDone();
		return;
	}
	else if (theApp.m_group_state == MarkerMakeState 
		&& theApp.m_state == MarkerSecondBegin)
	{
		ui->horBtn->setText(tr("绘制"));
		setProcessing(false);

		if (m_editMode == true)
		{
			ui->list->setEnabled(false);
			ui->deleteBtn->setEnabled(false);
			ui->editBtn->setEnabled(false);
		}

		theApp.hmarkers.pop_back();
		ui->horEdit->setText(tr("%1").arg(theApp.hmarkers.size()));
		theApp.m_state = MarkerMakeInitial;
		theApp.is_synchronous = false;
		emit MarkerMakeDone();
		return;
	}

	InputNumberDlg dlg;

	if (dlg.exec() == QDialog::Accepted)
	{
		m_inputNumber = dlg.getInputNumber();

		if (m_inputNumber > 1)
		{
			if (m_tipMsgBox->isShowAgain())
			{
				m_tipMsgBox->exec();
			}

			//QMessageBox::information(this, tr(" "),
			//	tr("先点击第一个标记点的位置，接着点击最后一个标记点的位置"));
		}

		setProcessing(true);
		ui->horBtn->setText(tr("取消"));
		ui->horBtn->setEnabled(true);

		m_isHorizontal = true;
		theApp.m_group_state = MarkerMakeState;
		theApp.m_state = MarkerFirstBegin;

		emit MarkerMakeBegin();
	}
}

void MarkerMakeDlg::on_verBtn_clicked()
{
	if (m_markerSize.width <= 0)
	{
		QMessageBox::information(this, tr(" "),
			tr("请先框选标记点大小！！"));
		return;
	}

	if (theApp.m_group_state == MarkerMakeState 
		&& theApp.m_state == MarkerFirstBegin)
	{
		ui->verBtn->setText(tr("绘制"));
		setProcessing(false);

		if (m_editMode == true)
		{
			ui->list->setEnabled(false);
			ui->deleteBtn->setEnabled(false);
			ui->editBtn->setEnabled(false);
		}

		theApp.m_state = MarkerMakeInitial;
		emit MarkerMakeDone();
		return;
	}
	else if (theApp.m_group_state == MarkerMakeState 
		&& theApp.m_state == MarkerSecondBegin)
	{
		ui->verBtn->setText(tr("绘制"));
		setProcessing(false);

		if (m_editMode == true)
		{
			ui->list->setEnabled(false);
			ui->deleteBtn->setEnabled(false);
			ui->editBtn->setEnabled(false);
		}

		theApp.vmarkers.pop_back();
		ui->verEdit->setText(tr("%1").arg(theApp.vmarkers.size()));
		theApp.m_state = MarkerMakeInitial;
		theApp.is_synchronous = false;
		emit MarkerMakeDone();
		return;
	}

	InputNumberDlg dlg;

	if (dlg.exec() == QDialog::Accepted)
	{
		m_inputNumber = dlg.getInputNumber();

		if (m_inputNumber > 1)
		{
			if (m_tipMsgBox->isShowAgain())
			{
				m_tipMsgBox->exec();
			}
		}

		setProcessing(true);
		ui->verBtn->setText(tr("取消"));
		ui->verBtn->setEnabled(true);

		m_isHorizontal = false;
		theApp.m_group_state = MarkerMakeState;
		theApp.m_state = MarkerFirstBegin;

		emit MarkerMakeBegin();
	}
}

void MarkerMakeDlg::on_addBtn_clicked()
{
	if (ui->groupEdit->text() == "")
	{
		QMessageBox::information(this, tr(" "),
			tr("请输入标记点组号！"));
		return;
	}

	vector<Marker_info3>::iterator iter = theApp.markers.begin();

	//查找是否存在该组号
	for (; iter != theApp.markers.end(); ++iter)
	{
		if (iter->id == ui->groupEdit->text().toInt())
		{
			if (!(m_editMode = true && m_groupIdTmp == ui->groupEdit->text().toInt()))
			{
				QMessageBox::information(this, tr(" "),
					tr("该组号已存在！"));
				return;
			}
		}
	}

	//判断是否已经完成水平垂直标记点的绘制
	if (theApp.hmarkers.size() <=0 || theApp.vmarkers.size() <= 0)
	{
		QMessageBox::information(this, tr(" "),
			tr("请确认已框选了水平标记点组和垂直标记点组！"));
		return;
	}

	QString w_str;
	w_str = QString(tr("水平标记点有%1个，垂直方向标记点有%2个\n确认？")
		.arg(theApp.hmarkers.size()).arg(theApp.vmarkers.size()));

	if (QMessageBox::No == QMessageBox::information(this, 
			tr("确认标记点数量？"), 
			w_str,
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::Yes))
	{
		return;
	}

	//对标记点进行排序
	theApp.SortMarkers(true);
	theApp.SortMarkers(false);
	
	Marker_info3 marker;
	marker.id = ui->groupEdit->text().toInt();
	marker.xMarker = theApp.hmarkers;
	marker.yMarker = theApp.vmarkers;

	if (m_editMode == false)
	{
		//添加一组标记点
		theApp.markers.push_back(marker);
		m_markerRects.push_back(computeRectFromMarker());

		theApp.markerBT.InitMarkersBoundaryTable(theApp.hmarkers,theApp.vmarkers);
		MarkersBoundaryTable tmp;
		tmp.InitMarkersBoundaryTable(theApp.hmarkers,theApp.vmarkers);
		theApp.markersTable.insert(map<ushort,MarkersBoundaryTable>::value_type(marker.id, tmp));

		//添加到list上
		ui->list->addItem(tr("组%1| 水平%2个| 垂直%3个")
			.arg(ui->groupEdit->text())
			.arg(ui->horEdit->text())
			.arg(ui->verEdit->text()));

		m_isDone = true;
	}
	else
	{
		theApp.markers.at(m_editingIndex) = marker;
		m_markerRects.at(m_editingIndex) = computeRectFromMarker();
		theApp.markerBT.InitMarkersBoundaryTable(theApp.hmarkers,theApp.vmarkers);
		theApp.markersTable.at(marker.id).InitMarkersBoundaryTable(theApp.hmarkers,theApp.vmarkers);

		ui->list->clear();
		vector<Marker_info3>::iterator iter = theApp.markers.begin();
		for (; iter != theApp.markers.end(); ++iter)
		{
			ui->list->addItem(tr("组%1| 水平%2个| 垂直%3个")
				.arg(iter->id)
				.arg(iter->xMarker.size())
				.arg(iter->yMarker.size()));
		}

		m_hmarkersTmp.clear();
		m_vmarkersTmp.clear();
		m_markerSizeTmp = cv::Size();
		m_groupIdTmp = -1;
		setProcessing(false);
		m_editMode = false;
		theApp.is_synchronous = false;
	}

	//清空数据
	theApp.hmarkers.clear();
	theApp.vmarkers.clear();

	ui->verEdit->setText("0");
	ui->horEdit->setText("0");
	ui->subList->clear();
	ui->groupEdit->setText(tr("%1").arg(ui->groupEdit->text().toInt() + 1));

	theApp.m_group_state = MarkerMakeState;
	theApp.m_state = MarkerMakeEnd;
	
	emit MarkerMakeDone();
}

void MarkerMakeDlg::updatePerMarker()
{
	ui->subList->clear();
	ui->horEdit->setText(tr("%1").arg(theApp.hmarkers.size()));
	ui->verEdit->setText(tr("%1").arg(theApp.vmarkers.size()));
	for (int i = 0; i < theApp.hmarkers.size(); ++i)
	{
		ui->subList->addItem(QString("水平%1").arg(i+1));
	}

	for (int i = 0; i < theApp.vmarkers.size(); ++i)
	{
		ui->subList->addItem(QString("垂直%1").arg(i+1));
	}
}

void MarkerMakeDlg::on_deleteMarkerBtn_clicked()
{
	int idx = ui->subList->currentRow();

	if (idx > -1)
	{
		if (idx < theApp.hmarkers.size())
		{
			theApp.hmarkers.erase(theApp.hmarkers.begin() + idx);
			ui->horEdit->setText(QString("%1").arg(theApp.hmarkers.size()));
		}
		else
		{
			idx -= theApp.hmarkers.size();
			theApp.vmarkers.erase(theApp.vmarkers.begin() + idx);
			ui->verEdit->setText(QString("%1").arg(theApp.vmarkers.size()));
		}

		updatePerMarker();	
		theApp.is_synchronous = false;
	}
}

void MarkerMakeDlg::on_editBtn_clicked()
{
	int idx = ui->list->currentRow();

	if (idx > -1)
	{
		ushort groupId = theApp.markers.at(idx).id;

		//检测该组标记点是否已被使用
		vector<QustionItemPos>::iterator itemIter = theApp.questionInfo.begin();
		for (; itemIter != theApp.questionInfo.end(); ++itemIter)
		{
			if (itemIter->mark_id == groupId)
			{
				QMessageBox::information(this, tr(" "),
					tr("该组标记点已被使用，无法修改！"));
				return;
			}
		}

		m_editMode = true;
		m_editingIndex = idx;

		vector<Marker_info3>::iterator iter =  theApp.markers.begin() + idx;
		theApp.hmarkers = iter->xMarker;
		theApp.vmarkers = iter->yMarker;
		m_hmarkersTmp = iter->xMarker;
		m_vmarkersTmp = iter->yMarker;
		m_markerSizeTmp = iter->xMarker.at(0).size();
		m_groupIdTmp = iter->id;

		iter->xMarker.clear();
		iter->yMarker.clear();
		m_markerSize = theApp.hmarkers.at(0).size();
		m_markerRects.at(idx) = QRect();

		//设置外观
		ui->sizeEdit->setText(QString("(%1, %2)")
			.arg(m_markerSize.width).arg(m_markerSize.height));
		ui->horEdit->setText(QString("%1").arg(theApp.hmarkers.size()));
		ui->verEdit->setText(QString("%1").arg(theApp.vmarkers.size()));
		ui->groupEdit->setText(QString("%1").arg(iter->id));
		updatePerMarker();		
		ui->list->setEnabled(false);
		ui->deleteBtn->setEnabled(false);
		ui->editBtn->setEnabled(false);

		theApp.is_synchronous = false;
		emit MarkerMakeBegin();
	}
}

void MarkerMakeDlg::on_deleteBtn_clicked()
{
	int idx = ui->list->currentRow();

	if (idx > -1)
	{
		ushort groupId = theApp.markers.at(idx).id;

		//检测该组标记点是否已被使用
		vector<QustionItemPos>::iterator itemIter = theApp.questionInfo.begin();
		for (; itemIter != theApp.questionInfo.end(); ++itemIter)
		{
			if (itemIter->mark_id == groupId)
			{
				QMessageBox::information(this, tr(" "),
					tr("该组标记点已被使用，删除失败！"));
				return;
			}
		}

		map<ushort, MarkersBoundaryTable>::iterator iter;
		iter = theApp.markersTable.find(groupId);

		m_markerRects.erase(m_markerRects.begin() + idx);

		//删除对应的边界表
		if (iter != theApp.markersTable.end())
		{
			theApp.markersTable.erase(iter);
		}

		//删除标记点
		theApp.markers.erase(theApp.markers.begin() + idx);

		//删除列表控件的记录
		ui->list->takeItem(idx);

		if (theApp.markers.size() <= 0)
		{
			m_isDone = false;
		}

		//触发重绘
		theApp.is_synchronous = false;
		emit MarkerMakeDelete();
	}
}

void MarkerMakeDlg::on_cancelBtn_clicked()
{
	if (m_editMode == true)
	{
		theApp.hmarkers = m_hmarkersTmp;
		theApp.vmarkers = m_vmarkersTmp;

		//设置外观
		ui->sizeEdit->setText(QString("(%1, %2)")
			.arg(m_markerSizeTmp.width).arg(m_markerSizeTmp.height));
		ui->horEdit->setText(QString("%1").arg(theApp.hmarkers.size()));
		ui->verEdit->setText(QString("%1").arg(theApp.vmarkers.size()));
		ui->groupEdit->setText(QString("%1").arg(m_groupIdTmp));
		updatePerMarker();		
	}
	else
	{
		m_markerSize = cv::Size();
		theApp.hmarkers.clear();
		theApp.vmarkers.clear();

		ui->verEdit->setText("0");
		ui->horEdit->setText("0");
		ui->sizeEdit->clear();		
		ui->subList->clear();
		emit MarkerMakeDone();
	}

	theApp.is_synchronous = false;

	if (theApp.markers.size() > 0)
	{
		m_isDone = true;
	}
	else
	{
		m_isDone = false;
	}
}

void MarkerMakeDlg::on_subList_itemClicked(QListWidgetItem*)
{
	int idx = ui->subList->currentRow();

	if (idx > -1)
	{
		theApp.is_synchronous = false;
		theApp.Redraw3();

		vector<cv::Rect>::iterator iter;

		if (idx < theApp.hmarkers.size())
		{
			iter = theApp.hmarkers.begin() + idx;

		}
		else
		{
			idx -= theApp.hmarkers.size();
			iter = theApp.vmarkers.begin() + idx;
		}

		rectangle(theApp.img_show, (*iter), 
			theApp.markerClicked_color, CV_FILLED);

		emit MarkerMakeClicked();
	}
}

void MarkerMakeDlg::showClicked(QListWidgetItem*)
{
	int idx = ui->list->currentRow();

	if (idx > -1)
	{
		theApp.is_synchronous = false;
		theApp.Redraw3();

		vector<Marker_info3>::iterator iter = theApp.markers.begin() + idx;

		vector<cv::Rect>::iterator xiter = iter->xMarker.begin();

		for (; xiter != iter->xMarker.end(); ++xiter)
		{
			rectangle(theApp.img_show, (*xiter), 
				theApp.markerClicked_color, theApp.markerClicked_thickness);
		}

		vector<cv::Rect>::iterator yiter = iter->yMarker.begin();

		for (; yiter != iter->yMarker.end(); ++yiter)
		{
			rectangle(theApp.img_show, (*yiter), 
				theApp.markerClicked_color, theApp.markerClicked_thickness);
		}

		emit MarkerMakeClicked();
	}
}

QRect MarkerMakeDlg::computeRectFromMarker()
{
	int width, height;
	int x, y;

	theApp.SortMarkers(true);
	theApp.SortMarkers(false);

	width = (theApp.hmarkers.end() - 1)->x + m_markerSize.width - theApp.hmarkers.begin()->x;
	height = (theApp.vmarkers.end() - 1)->y + m_markerSize.height - theApp.vmarkers.begin()->y;

	x = theApp.hmarkers.begin()->x;
	y = theApp.vmarkers.begin()->y;

	return QRect(x, y, width, height);
}

QRect MarkerMakeDlg::computeRectFromMarker(vector<cv::Rect> xMarker, vector<cv::Rect> yMarker)
{
	int xMin, xMax, yMin, yMax;
	int width, height;
	int x, y;

	xMin = xMarker[0].x;
	xMax = xMarker[0].x;
	for (int i = 1; i < xMarker.size(); ++i)
	{
		if (xMin > xMarker[i].x)
		{
			xMin = xMarker[i].x;
		}

		if (xMax < xMarker[i].x)
		{
			xMax = xMarker[i].x;
		}
	}

	yMin = yMarker[0].y;
	yMax = yMarker[0].y;
	for (int i = 1; i < yMarker.size(); ++i)
	{
		if (yMin > yMarker[i].y)
		{
			yMin = yMarker[i].y;
		}

		if (yMax < yMarker[i].y)
		{
			yMax = yMarker[i].y;
		}
	}

	width = xMax + xMarker.begin()->width - xMin;
	height = yMax + yMarker.begin()->height - yMin;

	return QRect(xMin, yMin, width, height);
}

bool MarkerMakeDlg::addMarker(const QPoint& position)
{
	cv::Point pos;
	int x = position.x() - (m_markerSize.width / 2);
	int y = position.y() - (m_markerSize.height / 2);

	if (x < 0)
	{
		x = 0;
	}

	if (y < 0)
	{
		y = 0;
	}

	pos = cv::Point(x, y);

	if (m_isHorizontal)
	{
		//判断是否为该分组下的第一个标记点
		if (theApp.hmarkers.size() <= 0)
		{
			//判断是否为所有分组下的第一个标记点
			if (theApp.markers.size() == 0)
			{
				cv::Rect rect(pos, m_markerSize);
				theApp.hmarkers.push_back(rect);
			}
			else
			{
				//判断垂直标记点是否已经添加了
				if (theApp.vmarkers.size() == 0)
				{
					//判断该标记点是否在其他Rect里面
					for (int i = 0; i < m_markerRects.size(); ++i)
					{
						if (m_markerRects[i].intersects(
							QRect(pos.x, pos.y, m_markerSize.width, m_markerSize.height)))
						{
							return false;
						}
					}

					cv::Rect rect(pos, m_markerSize);
					theApp.hmarkers.push_back(rect);
				}
				else
				{
					cv::Rect rect(pos, m_markerSize);
					theApp.hmarkers.push_back(rect);
					QRect qrect = computeRectFromMarker(theApp.hmarkers, theApp.vmarkers);

					//判断当前标记点Rect是否与其他标记点Rect相交
					for (int i = 0; i < m_markerRects.size(); ++i)
					{
						if (m_markerRects[i].intersects(qrect))
						{
							theApp.hmarkers.pop_back();
							return false;
						}
					}

				}
			}
		}
		else
		{
			if (theApp.markers.size() == 0)
			{
				cv::Rect rect(cv::Point(pos.x, theApp.hmarkers.at(0).y), m_markerSize);
				theApp.hmarkers.push_back(rect);
			}
			else
			{
				if (theApp.vmarkers.size() == 0)
				{
					for (int i = 0; i < m_markerRects.size(); ++i)
					{
						if (m_markerRects[i].intersects(
							QRect(pos.x, theApp.hmarkers.at(0).y, m_markerSize.width, m_markerSize.height)))
						{
							return false;
						}
					}

					cv::Rect rect(cv::Point(pos.x, theApp.hmarkers.at(0).y), m_markerSize);
					theApp.hmarkers.push_back(rect);
				}
				else
				{
					cv::Rect rect(cv::Point(pos.x, theApp.hmarkers.at(0).y), m_markerSize);
					theApp.hmarkers.push_back(rect);
					QRect qrect = computeRectFromMarker(theApp.hmarkers, theApp.vmarkers);

					for (int i = 0; i < m_markerRects.size(); ++i)
					{
						if (m_markerRects[i].intersects(qrect))
						{
							theApp.hmarkers.pop_back();
							return false;
						}
					}
				}
			}
		}
		ui->horEdit->setText(tr("%1").arg(theApp.hmarkers.size()));
		return true;
	}
	else
	{
		if (theApp.vmarkers.size() <= 0)
		{
			if (theApp.markers.size() == 0)
			{
				cv::Rect rect(pos, m_markerSize);
				theApp.vmarkers.push_back(rect);
			}
			else
			{
				if (theApp.hmarkers.size() == 0)
				{
					for (int i = 0; i < m_markerRects.size(); ++i)
					{
						if (m_markerRects[i].intersects(
							QRect(pos.x, pos.y, m_markerSize.width, m_markerSize.height)))
						{
							return false;
						}
					}
					cv::Rect rect(pos, m_markerSize);
					theApp.vmarkers.push_back(rect);
				}
				else
				{
					cv::Rect rect(pos, m_markerSize);
					theApp.vmarkers.push_back(rect);
					QRect qrect = computeRectFromMarker(theApp.hmarkers, theApp.vmarkers);

					for (int i = 0; i < m_markerRects.size(); ++i)
					{
						if (m_markerRects[i].intersects(qrect))
						{
							theApp.vmarkers.pop_back();
							return false;
						}
					}
				}
			}
		}
		else
		{
			if (theApp.markers.size() == 0)
			{
				cv::Rect rect(cv::Point(theApp.vmarkers.at(0).x, pos.y), m_markerSize);
				theApp.vmarkers.push_back(rect);
			}
			else
			{
				if (theApp.hmarkers.size() == 0)
				{
					for (int i = 0; i < m_markerRects.size(); ++i)
					{
						if (m_markerRects[i].intersects(
							QRect(theApp.vmarkers.at(0).x, pos.y, m_markerSize.width, m_markerSize.height)))
						{
							return false;
						}
					}

					cv::Rect rect(cv::Point(theApp.vmarkers.at(0).x, pos.y), m_markerSize);
					theApp.vmarkers.push_back(rect);
				}
				else
				{
					cv::Rect rect(cv::Point(theApp.vmarkers.at(0).x, pos.y), m_markerSize);
					theApp.vmarkers.push_back(rect);
					QRect qrect = computeRectFromMarker(theApp.hmarkers, theApp.vmarkers);

					for (int i = 0; i < m_markerRects.size(); ++i)
					{
						if (m_markerRects[i].intersects(qrect))
						{
							theApp.vmarkers.pop_back();
							return false;
						}
					}
				}
			}
		}
		ui->verEdit->setText(tr("%1").arg(theApp.vmarkers.size()));
		return true;
	}
}

void MarkerMakeDlg::dragLastMarker(const QPoint& position)
{
	int x = position.x() - (m_markerSize.width / 2);
	int y = position.y() - (m_markerSize.height / 2);

	if (x < 0)
	{
		x = 0;
	}

	if (y < 0)
	{
		y = 0;
	}

	if (m_isHorizontal)
	{
		if (theApp.hmarkers.size() <= 0)
		{
			return;
		}
		
		vector<cv::Rect>::iterator iter = theApp.hmarkers.end() - 1;

		if (theApp.hmarkers.size() == 1)
		{
			if (theApp.markers.size() == 0)
			{
				(*iter) = cv::Rect(x, y, m_markerSize.width, m_markerSize.height);
			}
			else
			{
				if (theApp.vmarkers.size() == 0)
				{
					for (int i = 0; i < m_markerRects.size(); ++i)
					{
						if (m_markerRects[i].intersects(
							QRect(x, y, m_markerSize.width, m_markerSize.height)))
						{
							return;
						}
					}
					(*iter) = cv::Rect(x, y, m_markerSize.width, m_markerSize.height);
				}
				else
				{
					int xOrigin = iter->x;
					int yOrigin = iter->y;
					(*iter) = cv::Rect(x, y, m_markerSize.width, m_markerSize.height);
					QRect qrect = computeRectFromMarker(theApp.hmarkers, theApp.vmarkers);

					//判断当前标记点Rect是否与其他标记点Rect相交
					for (int i = 0; i < m_markerRects.size(); ++i)
					{
						if (m_markerRects[i].intersects(qrect))
						{
							(*iter) = cv::Rect(xOrigin, yOrigin, m_markerSize.width, m_markerSize.height);
							return ;
						}
					}
				}
			}
		}
		else
		{
			int rect_y = iter->y;

			if (theApp.markers.size() == 0)
			{		
				(*iter) = cv::Rect(x, rect_y, m_markerSize.width, m_markerSize.height);
			}
			else
			{
				if (theApp.vmarkers.size() == 0)
				{
					for (int i = 0; i < m_markerRects.size(); ++i)
					{
						if (m_markerRects[i].intersects(
							QRect(x, rect_y, m_markerSize.width, m_markerSize.height)))
						{
							return;
						}
					}
					(*iter) = cv::Rect(x, rect_y, m_markerSize.width, m_markerSize.height);
				}
				else
				{
					int xOrigin = iter->x;
					int yOrigin = iter->y;
					(*iter) = cv::Rect(x, rect_y, m_markerSize.width, m_markerSize.height);
					QRect qrect = computeRectFromMarker(theApp.hmarkers, theApp.vmarkers);

					//判断当前标记点Rect是否与其他标记点Rect相交
					for (int i = 0; i < m_markerRects.size(); ++i)
					{
						if (m_markerRects[i].intersects(qrect))
						{
							(*iter) = cv::Rect(xOrigin, yOrigin, m_markerSize.width, m_markerSize.height);
							return ;
						}
					}
				}
			}
		}
	}
	else
	{
		if (theApp.vmarkers.size() <= 0)
		{
			return;
		}
		
		vector<cv::Rect>::iterator iter = theApp.vmarkers.end() - 1;
		if (theApp.vmarkers.size() == 1)
		{
			if (theApp.markers.size() == 0)
			{
				(*iter) = cv::Rect(x, y, m_markerSize.width, m_markerSize.height);
			}
			else
			{
				if (theApp.hmarkers.size() == 0)
				{
					for (int i = 0; i < m_markerRects.size(); ++i)
					{
						if (m_markerRects[i].intersects(
							QRect(x, y, m_markerSize.width, m_markerSize.height)))
						{
							return;
						}
					}
					(*iter) = cv::Rect(x, y, m_markerSize.width, m_markerSize.height);
				}
				else
				{
					int xOrigin = iter->x;
					int yOrigin = iter->y;
					(*iter) = cv::Rect(x, y, m_markerSize.width, m_markerSize.height);
					QRect qrect = computeRectFromMarker(theApp.hmarkers, theApp.vmarkers);

					//判断当前标记点Rect是否与其他标记点Rect相交
					for (int i = 0; i < m_markerRects.size(); ++i)
					{
						if (m_markerRects[i].intersects(qrect))
						{
							(*iter) = cv::Rect(xOrigin, yOrigin, m_markerSize.width, m_markerSize.height);
							return ;
						}
					}
				}
			}
		}
		else
		{
			int rect_x = iter->x;
			
			if (theApp.markers.size() == 0)
			{		
				(*iter) = cv::Rect(rect_x, y, m_markerSize.width, m_markerSize.height);
			}
			else
			{
				if (theApp.hmarkers.size() == 0)
				{
					for (int i = 0; i < m_markerRects.size(); ++i)
					{
						if (m_markerRects[i].intersects(
							QRect(rect_x, y, m_markerSize.width, m_markerSize.height)))
						{
							return;
						}
					}
					(*iter) = cv::Rect(rect_x, y, m_markerSize.width, m_markerSize.height);
				}
				else
				{
					int xOrigin = iter->x;
					int yOrigin = iter->y;
					(*iter) = cv::Rect(rect_x, y, m_markerSize.width, m_markerSize.height);
					QRect qrect = computeRectFromMarker(theApp.hmarkers, theApp.vmarkers);

					//判断当前标记点Rect是否与其他标记点Rect相交
					for (int i = 0; i < m_markerRects.size(); ++i)
					{
						if (m_markerRects[i].intersects(qrect))
						{
							(*iter) = cv::Rect(xOrigin, yOrigin, m_markerSize.width, m_markerSize.height);
							return ;
						}
					}
				}
			}
		}
	}
}


void MarkerMakeDlg::drawMarkers()
{
	if (theApp.m_group_state == MarkerMakeState && theApp.m_state == MarkerFirstPress)
	{
		if (m_isHorizontal)
		{
			if (theApp.hmarkers.size() > 0)
			{
				vector<cv::Rect>::iterator iter = theApp.hmarkers.end() - 1;
				rectangle(theApp.img_show, (*iter), theApp.marker_color, CV_FILLED);

				int height = theApp.img_show.size().height;
				line(theApp.img_show, cv::Point(iter->tl().x, 0), cv::Point(iter->tl().x, height), theApp.marker_color, 1);
				line(theApp.img_show, cv::Point(iter->br().x, 0), cv::Point(iter->br().x, height), theApp.marker_color, 1);
				
			}
		}
		else
		{
			if (theApp.vmarkers.size() > 0)
			{
				vector<cv::Rect>::iterator iter = theApp.vmarkers.end() - 1;
				rectangle(theApp.img_show, (*iter), theApp.marker_color, CV_FILLED);

				int width = theApp.img_show.size().width;
				line(theApp.img_show, cv::Point(0, iter->tl().y), cv::Point(width, iter->tl().y), theApp.marker_color, 1);
				line(theApp.img_show, cv::Point(0, iter->br().y), cv::Point(width, iter->br().y), theApp.marker_color, 1);
			}
		}
	}
	else if (theApp.m_group_state == MarkerMakeState && theApp.m_state == MarkerSecondPress)
	{
		if (m_isHorizontal)
		{
			if (theApp.hmarkers.size() > 0)
			{
				vector<cv::Rect>::iterator iter = theApp.hmarkers.end() - m_inputNumber;

				for (;iter != theApp.hmarkers.end(); ++iter)
				{
					rectangle(theApp.img_show, (*iter), theApp.marker_color, CV_FILLED);
				}

				iter = theApp.hmarkers.end() - 1;
				int height = theApp.img_show.size().height;
				line(theApp.img_show, cv::Point(iter->tl().x, 0), cv::Point(iter->tl().x, height), theApp.marker_color, 1);
				line(theApp.img_show, cv::Point(iter->br().x, 0), cv::Point(iter->br().x, height), theApp.marker_color, 1);

			}
		}
		else
		{
			if (theApp.vmarkers.size() > 0)
			{
				vector<cv::Rect>::iterator iter = theApp.vmarkers.end() - m_inputNumber;

				for (;iter != theApp.vmarkers.end(); ++iter)
				{
					rectangle(theApp.img_show, (*iter), theApp.marker_color, CV_FILLED);
				}

				iter = theApp.vmarkers.end() - 1;
				int width = theApp.img_show.size().width;
				line(theApp.img_show, cv::Point(0, iter->tl().y), cv::Point(width, iter->tl().y), theApp.marker_color, 1);
				line(theApp.img_show, cv::Point(0, iter->br().y), cv::Point(width, iter->br().y), theApp.marker_color, 1);
			}
		}
	}
}

void MarkerMakeDlg::computeMarkerPos(const QPoint& pos)
{
	if (m_isHorizontal)
	{
		dragLastMarker(pos);
		vector<cv::Rect>::iterator iterStart = theApp.hmarkers.end() - m_inputNumber;
		vector<cv::Rect>::iterator iterEnd = theApp.hmarkers.end() - 1;
		double length = iterEnd->x - iterStart->x;
		double space = length / double(m_inputNumber - 1);
		
		vector<cv::Rect>::iterator iter = theApp.hmarkers.end() - m_inputNumber + 1;
		for (; iter != theApp.hmarkers.end(); ++iter)
		{
			(*iter) = cv::Rect(double((iter - 1)->x) + space, (iter - 1)->y,
				m_markerSize.width, m_markerSize.height);
		}
	}
	else
	{
		dragLastMarker(pos);
		vector<cv::Rect>::iterator iterStart = theApp.vmarkers.end() - m_inputNumber;
		vector<cv::Rect>::iterator iterEnd = theApp.vmarkers.end() - 1;
		double length = iterEnd->y - iterStart->y;
		double space = length / double(m_inputNumber - 1);
		
		vector<cv::Rect>::iterator iter = theApp.vmarkers.end() - m_inputNumber + 1;
		for (; iter != theApp.vmarkers.end(); ++iter)
		{
			(*iter) = cv::Rect((iter - 1)->x, double((iter - 1)->y + space),
				m_markerSize.width, m_markerSize.height);
		}
	}
}

int MarkerMakeDlg::resume(cv::Size markerSize, bool isDone)
{
	initialization();
	m_markerSize = cv::Size(markerSize);
	m_isDone = isDone;

	if (theApp.markers.size() > 0)
	{
		vector<Marker_info3>::iterator iter = theApp.markers.begin();
		for (; iter != theApp.markers.end(); ++iter)
		{
			ui->list->addItem(tr("组%1| 水平%2个| 垂直%3个")
				.arg(iter->id)
				.arg(iter->xMarker.size())
				.arg(iter->yMarker.size()));

			MarkersBoundaryTable tmp;
			tmp.InitMarkersBoundaryTable(iter->xMarker,iter->yMarker);
			theApp.markersTable.insert(map<ushort,MarkersBoundaryTable>::value_type(iter->id, tmp));
			m_markerRects.push_back(computeRectFromMarker(iter->xMarker,iter->yMarker));
		}

		ui->groupEdit->setText(tr("%1").arg((theApp.markers.end() - 1)->id + 1));
	}

	if (m_markerSize.width > 0 && m_markerSize.height > 0)
	{
		ui->sizeEdit->setText(tr("(%1, %2)").arg(m_markerSize.width).arg(m_markerSize.height));
		ui->horEdit->setText(tr("%1").arg(theApp.hmarkers.size()));
		ui->verEdit->setText(tr("%1").arg(theApp.vmarkers.size()));

		//if (isDone == true && theApp.hmarkers.size() > 0 && theApp.vmarkers.size() > 0)
		//{
		//	theApp.markerBT.InitMarkersBoundaryTable(theApp.hmarkers,theApp.vmarkers);
		//}
		updatePerMarker();
		emit MarkerMakeBegin();
	}
	else
	{
		emit MarkerMakeDone();
	}

	return 1;
}