/********************************************************************************
** Form generated from reading UI file 'showdocument.ui'
**
** Created: Thu Mar 12 10:03:36 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWDOCUMENT_H
#define UI_SHOWDOCUMENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowDocument
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QLabel *label_1;
    QTextEdit *textEdit_1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLabel *label_2;
    QTextEdit *textEdit_2;

    void setupUi(QWidget *ShowDocument)
    {
        if (ShowDocument->objectName().isEmpty())
            ShowDocument->setObjectName(QString::fromUtf8("ShowDocument"));
        ShowDocument->resize(642, 527);
        horizontalLayout_3 = new QHBoxLayout(ShowDocument);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 10, -1, 10);
        label_5 = new QLabel(ShowDocument);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        label_1 = new QLabel(ShowDocument);
        label_1->setObjectName(QString::fromUtf8("label_1"));

        horizontalLayout->addWidget(label_1);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout);

        textEdit_1 = new QTextEdit(ShowDocument);
        textEdit_1->setObjectName(QString::fromUtf8("textEdit_1"));

        verticalLayout->addWidget(textEdit_1);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 10, -1, 10);
        label_4 = new QLabel(ShowDocument);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        label_2 = new QLabel(ShowDocument);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 2);

        verticalLayout_2->addLayout(horizontalLayout_2);

        textEdit_2 = new QTextEdit(ShowDocument);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));

        verticalLayout_2->addWidget(textEdit_2);


        horizontalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(ShowDocument);

        QMetaObject::connectSlotsByName(ShowDocument);
    } // setupUi

    void retranslateUi(QWidget *ShowDocument)
    {
        ShowDocument->setWindowTitle(QApplication::translate("ShowDocument", "\346\226\207\344\273\266\346\237\245\347\234\213", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ShowDocument", "\350\242\253\346\237\245\351\207\215\345\257\271\350\261\241", 0, QApplication::UnicodeUTF8));
        label_1->setText(QApplication::translate("ShowDocument", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ShowDocument", "\345\214\271\351\205\215\345\257\271\350\261\241", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ShowDocument", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ShowDocument: public Ui_ShowDocument {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWDOCUMENT_H
