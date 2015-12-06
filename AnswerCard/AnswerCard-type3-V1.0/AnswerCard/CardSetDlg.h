#ifndef CARDSETDLG_H
#define CARDSETDLG_H

#include <QDialog>
#include "AnswerCard.h"
#include "AddPageDlg.h"
#include "DataIO.h"
#include <vector>
using std::vector;

namespace Ui {class CardSetDlg;};

#define PAPERSET_MAGIC_NUM 0x0000CD03
#define VERSION 102
struct Card{
	int pageId;
	bool isFront;
};

class CardSetDlg : public QDialog
{
	Q_OBJECT

public:
	CardSetDlg(QWidget *parent = 0,int cardType=3);
	~CardSetDlg();
	vector<Card> getCard(){return this->m_card;}
	int getDpi() {return this->m_cardDpi;}
	void setDpi(int dpi){this->m_cardDpi = dpi;}
	int resume();
	void clear();
private:
	Ui::CardSetDlg *ui;
	int m_cardDpi;
	int m_cardType;
	Mat m_imgTmp;
	Mat qImage2Mat(const QImage& qimage); 
	QImage mat2QImage(const cv::Mat &mat);

	vector<Card> m_card;
	QString lastEditCard;//记录上次的答题卡
protected slots:
	void on_addBtn_clicked();
	void on_deleteBtn_clicked();
	void on_editBtn_clicked();
	void on_saveFileBtn_clicked();
	void on_importXMLBtn_clicked();

signals:
	void edit(QString);
	void deleteCard(QString);
	void save();
	void import();
};

#endif // CARDSETDLG_H
