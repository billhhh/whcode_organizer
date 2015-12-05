#include "CardSet\\CardSetDlg.h"
#include <QtGui/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec* codec =QTextCodec::codecForName("System");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);

	int type = 1;
	if (argc == 2)
	{
		char* tmp = argv[1];
		if (strcmp(tmp,"1") == 0)
		{
			type = 1;
		}
		else if(strcmp(tmp,"2") == 0)
		{
			type = 2;
		}
	}

	CardSetDlg w(a,type);
	w.show();
	return a.exec();
}
