#include "AnswerCardDlg3.h"
#include <QtGui/QApplication>
#include <QTextCodec>
#include <qtranslator.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec* codec =QTextCodec::codecForName("System");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);
	QTranslator oTranslator;
    oTranslator.load(":/qt_zh_CN"); 
	a.installTranslator(&oTranslator);

	int type = 4;
	if (argc == 2)
	{
		char* tmp = argv[1];
		if (strcmp(tmp,"3") == 0)
		{
			type = 3;
		}
	}

	AnswerCardDlg3 w(a, type);
	w.show();
	return a.exec();
}
