/********************************************************************************
** Form generated from reading UI file 'teacherassistant.ui'
**
** Created: Sun Apr 5 16:24:49 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEACHERASSISTANT_H
#define UI_TEACHERASSISTANT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_teacherAssistantClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *submitBtn;
    QPushButton *cancelBtn;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *teacherAssistantClass)
    {
        if (teacherAssistantClass->objectName().isEmpty())
            teacherAssistantClass->setObjectName(QString::fromUtf8("teacherAssistantClass"));
        teacherAssistantClass->resize(455, 386);
        centralWidget = new QWidget(teacherAssistantClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(150, 40, 131, 31));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(150, 100, 131, 31));
        submitBtn = new QPushButton(centralWidget);
        submitBtn->setObjectName(QString::fromUtf8("submitBtn"));
        submitBtn->setGeometry(QRect(170, 210, 85, 22));
        cancelBtn = new QPushButton(centralWidget);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setGeometry(QRect(170, 250, 85, 22));
        teacherAssistantClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(teacherAssistantClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        teacherAssistantClass->setStatusBar(statusBar);

        retranslateUi(teacherAssistantClass);
        QObject::connect(cancelBtn, SIGNAL(clicked()), teacherAssistantClass, SLOT(close()));

        QMetaObject::connectSlotsByName(teacherAssistantClass);
    } // setupUi

    void retranslateUi(QMainWindow *teacherAssistantClass)
    {
        teacherAssistantClass->setWindowTitle(QApplication::translate("teacherAssistantClass", "teacherAssistant", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("teacherAssistantClass", "\345\257\274\345\205\245\345\255\246\347\224\237\344\277\241\346\201\257...", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("teacherAssistantClass", "\346\211\223\345\274\200\344\275\234\344\270\232\345\255\230\346\224\276\344\275\215\347\275\256...", 0, QApplication::UnicodeUTF8));
        submitBtn->setText(QApplication::translate("teacherAssistantClass", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        cancelBtn->setText(QApplication::translate("teacherAssistantClass", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class teacherAssistantClass: public Ui_teacherAssistantClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEACHERASSISTANT_H
