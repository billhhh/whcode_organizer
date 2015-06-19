#include "showdocument.h"
#include "ui_showdocument.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>

using namespace std;
bool first(const Match &m1, const Match &m2) { return m1.m < m2.m; }
bool second(const Match &m1, const Match &m2) { return m1.n < m2.n; }
bool three(const Match &m1, const Match &m2) { return m1.len > m2.len; }



ShowDocument::ShowDocument(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowDocument)
{
    ui->setupUi(this);
}


ShowDocument::ShowDocument(QWidget *parent,QString fileName_1,QString fileName_2,string text_1,string text_2,QString filePath) :
    QWidget(parent),
    ui(new Ui::ShowDocument)
{
    ui->setupUi(this);
    ui->label_1->setText(fileName_1);
    ui->label_2->setText(fileName_2);
    setTextContent(ui->textEdit_1,ui->textEdit_2,text_1,text_2,filePath);
}

void ShowDocument::setTextContent(QTextEdit *&textEdit,QTextEdit *&textEdit_2,string text_1,string text_2,QString filePath)
{

    //获取光标
    QTextCursor cursor=textEdit->textCursor();
    QTextCursor cursor_2=textEdit_2->textCursor();
    //设置输出颜色
    QTextCharFormat fmt_red;
    fmt_red.setForeground(Qt::red);

    QTextCharFormat fmt_black;
    fmt_black.setForeground(Qt::black);

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
		if(line.trimmed()!="")
           list.append(line);
    }
	file.close();



	vector <Match> matches;
	//把3原组转化为match对象，并存在vector里
	for(int i=0;i<list.size();i++)
    {
		QStringList tempList=list.at(i).split("-",QString::SkipEmptyParts);
        int length=0;
		int pos_1=0;
		int pos_2=0;
		if(tempList.at(0)!=NULL)
           pos_1=tempList.at(0).toInt();
        else
            continue;
		if(tempList.at(1)!=NULL)
           pos_2=tempList.at(1).toInt();
        else
            continue;
        if(tempList.at(2)!=NULL)
           length=tempList.at(2).toInt();
        else
            continue;

		Match mat(pos_1, pos_2, length);
		matches.push_back(mat);
	}

	
	stable_sort(matches.begin(), matches.end(), three);
	//按第一个文件的字段位置排序
	stable_sort(matches.begin(), matches.end(), first);

	//文本字符串当前下标
    int currentIndex=0;
    int currentIndex_2=0;
    for(int i=0;i<matches.size();i++)
    {
        //取出三元组
		Match mat=matches[i];
		int pos=mat.m;
		int length=mat.len;
     
        //如果下一段要上色的字段在当前位置的后面，则先把中间的文字以黑色字体输出
			if(currentIndex<pos)
			{
				cursor.setCharFormat(fmt_black);
				string temp=text_1.substr(currentIndex,pos-currentIndex);
				QString qstr = QString::fromStdString(temp);
				for(int i=0;i<qstr.size();i++)
                {
                  if(QString(qstr.at(i))=="⊙")
                     cursor.insertText("\n");
                 else if(QString(qstr.at(i))=="|")
                 {

		         }
                 else
                    cursor.insertText(QString(qstr.at(i)));
                }
				currentIndex=pos;
			}
			
			//如果要输出字段已经输出过，则不处理
			if(pos+length<=currentIndex)
				continue;
			
			cursor.setCharFormat(fmt_red);
			//此处防止pos位于当前输出位置之前，计算出真正要输出的字段，过滤已输出字段
			int sub=currentIndex-pos;
			string temp=text_1.substr(currentIndex,length-sub);
		    QString qstr = QString::fromStdString(temp);
				for(int i=0;i<qstr.size();i++)
                {
                  if(QString(qstr.at(i))=="⊙")
                     cursor.insertText("\n");
                 else if(QString(qstr.at(i))=="|")
                 {

		         }
                 else
                    cursor.insertText(QString(qstr.at(i)));
                }
			currentIndex=pos+length;
		


	    }
	       //处理剩余字段
	        cursor.setCharFormat(fmt_black);
			string temp=text_1.substr(currentIndex,text_1.length()-currentIndex);
		    QString qstr = QString::fromStdString(temp);
				for(int i=0;i<qstr.size();i++)
                {
                  if(QString(qstr.at(i))=="⊙")
                     cursor.insertText("\n");
                 else if(QString(qstr.at(i))=="|")
                 {

		         }
                 else
                    cursor.insertText(QString(qstr.at(i)));
                }
		

				//处理第二个文本
    stable_sort(matches.begin(), matches.end(), second);
   for(int i=0;i<matches.size();i++)
    {
        //解析三元组
		Match mat=matches[i];
		int pos=mat.n;
		int length=mat.len;
     
    
			if(currentIndex_2<pos)
			{
				cursor_2.setCharFormat(fmt_black);
				string temp=text_2.substr(currentIndex_2,pos-currentIndex_2);
				QString qstr = QString::fromStdString(temp);
				for(int i=0;i<qstr.size();i++)
                {
                  if(QString(qstr.at(i))=="⊙")
                     cursor_2.insertText("\n");
                 else if(QString(qstr.at(i))=="|")
                 {

		         }
                 else
                    cursor_2.insertText(QString(qstr.at(i)));
                }
				currentIndex_2=pos;
			}
			

			if(pos+length<=currentIndex_2)
				continue;
			cursor_2.setCharFormat(fmt_red);
			int sub=currentIndex_2-pos;
			string temp=text_2.substr(currentIndex_2,length-sub);
		    QString qstr = QString::fromStdString(temp);
				for(int i=0;i<qstr.size();i++)
                {
                  if(QString(qstr.at(i))=="⊙")
                     cursor_2.insertText("\n");
                 else if(QString(qstr.at(i))=="|")
                 {

		         }
                 else
                    cursor_2.insertText(QString(qstr.at(i)));
                }
			currentIndex_2=pos+length;
		


	    }

	        cursor_2.setCharFormat(fmt_black);
			 temp=text_2.substr(currentIndex_2,text_2.length()-currentIndex_2);
		     qstr = QString::fromStdString(temp);
				for(int i=0;i<qstr.size();i++)
                {
                  if(QString(qstr.at(i))=="⊙")
                     cursor_2.insertText("\n");
                 else if(QString(qstr.at(i))=="|")
                 {

		         }
                 else
                    cursor_2.insertText(QString(qstr.at(i)));
                }







	/*
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
	*/
    
}


ShowDocument::~ShowDocument()
{
    delete ui;
}
