#ifndef SHOWDOCUMENT_H
#define SHOWDOCUMENT_H
#include<QTextEdit>
#include <QWidget>
#include <string>
#include "../logic/match.h"
using namespace std;

namespace Ui {
    class ShowDocument;
}

class ShowDocument : public QWidget
{
    Q_OBJECT

public:
    explicit ShowDocument(QWidget *parent = 0);
    explicit ShowDocument(QWidget *parent = 0,QString fileName_1="a.doc",QString fileName_2="b.doc",string text_1="込込",string text_2="最最",QString filePath="F:/test/in.txt");
    void setTextContent(QTextEdit *&textEdit,QTextEdit *&textEdit_2,string text_1,string text_2,QString filePath);
    ~ShowDocument();

private:
    Ui::ShowDocument *ui;
};

#endif // SHOWDOCUMENT_H
