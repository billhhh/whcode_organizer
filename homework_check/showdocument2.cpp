#include "showdocument.h"
#include "ui_showdocument.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>
ShowDocument::ShowDocument(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowDocument)
{
    ui->setupUi(this);
}


ShowDocument::ShowDocument(QWidget *parent,QString fileName_1,QString fileName_2,QString text_1,QString text_2,QString filePath) :
    QWidget(parent),
    ui(new Ui::ShowDocument)
{
    ui->setupUi(this);
    ui->label_1->setText(fileName_1);
    ui->label_2->setText(fileName_2);
    setTextContent(ui->textEdit_1,ui->textEdit_2,text_1,text_2,filePath);
}

void ShowDocument::setTextContent(QTextEdit *&textEdit,QTextEdit *&textEdit_2,QString text_1,QString text_2,QString filePath)
{

    //获取光标
    QTextCursor cursor=textEdit->textCursor();
    QTextCursor cursor_2=textEdit_2->textCursor();
    //设置输出颜色
    QTextCharFormat charFormat_red;
    charFormat_red.setForeground(Qt::red);

    QTextCharFormat charFormat_black;
    charFormat_black.setForeground(Qt::black);

    QList<QString> list;
    //打开三元组文件
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        return;
    QTextStream in(&file);
    //读取三元组
	QString line=in.readLine();
    while(!in.atEnd())
    {
        QString line=in.readLine();
        list.append(line);
    }

    //文本字符串当前下标
    int currentIndex=0;
    int currentIndex_2=0;
    for(int i=0;i<list.size();i++)
    {
        //解析三元组
        QStringList tempList=list.at(i).split("-",QString::SkipEmptyParts);
        int length=0;
        if(tempList.at(2)!=NULL)
           length=tempList.at(2).toInt();
        else
            return;

        //处理第一个文件
        if(tempList.at(0)!=NULL)
        {
            int &index=currentIndex;
            int temp=tempList.at(0).toInt();

            cursor.setCharFormat(charFormat_black);
            //从当前位置输出到匹配串位置
            for(;index<temp;index++)
            {
                if(QString(text_1.at(index))=="⊙")
                    cursor.insertText("\n");
                else if(QString(text_1.at(index))=="|")
                {

                }
                else
                   cursor.insertText(text_1.at(index));
            }
            //设置颜色输出匹配串
            cursor.setCharFormat(charFormat_red);
            for(;index<temp+length;index++)
            {
                if(QString(text_1.at(index))=="⊙")
                    cursor.insertText("\n");
                else if(QString(text_1.at(index))=="|")
                {

				}
                else
                   cursor.insertText(text_1.at(index));
            }
        }
        else
            return;


        //处理第二个文件文本
        if(tempList.at(1)!=NULL)
        {
            int &index=currentIndex_2;
            int temp=tempList.at(1).toInt();

            cursor_2.setCharFormat(charFormat_black);
            for(;index<temp;index++)
            {
                if(QString(text_2.at(index))=="⊙")
                    cursor_2.insertText("\n");
                else if(QString(text_2.at(index))=="|")
                {

				}
                else
                   cursor_2.insertText(text_2.at(index));
            }
            cursor_2.setCharFormat(charFormat_red);
            for(;index<temp+length;index++)
            {
                if(QString(text_2.at(index))=="⊙")
                    cursor_2.insertText("\n");
                else if(QString(text_2.at(index))=="|")
                {

                }
                else
                   cursor_2.insertText(text_2.at(index));
            }
        }
        else
            return;
    }


    //输出剩下的文本
    cursor.setCharFormat(charFormat_black);
    cursor_2.setCharFormat(charFormat_black);
    for(int i=currentIndex;i<text_1.size();i++)
    {
        if(QString(text_1.at(i))=="⊙")
            cursor.insertText("\n");
        else if(QString(text_1.at(i))=="|")
        {

		}
        else
           cursor.insertText(text_1.at(i));
    }
    for(int j=currentIndex_2;j<text_2.size();j++)
    {
        if(QString(text_2.at(j))=="⊙")
            cursor_2.insertText("\n");
        else if(QString(text_2.at(j))=="|")
        {

        }
        else
           cursor_2.insertText(text_2.at(j));
    }

    file.close();
}


ShowDocument::~ShowDocument()
{
    delete ui;
}
