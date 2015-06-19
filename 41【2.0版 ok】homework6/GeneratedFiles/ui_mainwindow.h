/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Mar 12 10:03:35 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *HwNumLabel;
    QComboBox *HwNumComboBox;
    QPushButton *submitBtn;
    QPushButton *cancelBtn;
    QLabel *StudentNameLabel;
    QComboBox *StudentNameComboBox;
    QLabel *StudentNumLabel;
    QLabel *StudentNumLabel2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QGroupBox *groupBox_2;
    QTreeWidget *rltTreeWidget;
    QGroupBox *groupBox;
    QListWidget *listWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(955, 480);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        HwNumLabel = new QLabel(centralWidget);
        HwNumLabel->setObjectName(QString::fromUtf8("HwNumLabel"));
        HwNumLabel->setGeometry(QRect(20, 110, 101, 22));
        HwNumLabel->setAlignment(Qt::AlignCenter);
        HwNumComboBox = new QComboBox(centralWidget);
        HwNumComboBox->setObjectName(QString::fromUtf8("HwNumComboBox"));
        HwNumComboBox->setGeometry(QRect(20, 140, 111, 31));
        submitBtn = new QPushButton(centralWidget);
        submitBtn->setObjectName(QString::fromUtf8("submitBtn"));
        submitBtn->setGeometry(QRect(30, 400, 85, 22));
        cancelBtn = new QPushButton(centralWidget);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setGeometry(QRect(30, 430, 85, 22));
        StudentNameLabel = new QLabel(centralWidget);
        StudentNameLabel->setObjectName(QString::fromUtf8("StudentNameLabel"));
        StudentNameLabel->setGeometry(QRect(20, 190, 101, 22));
        StudentNameLabel->setAlignment(Qt::AlignCenter);
        StudentNameComboBox = new QComboBox(centralWidget);
        StudentNameComboBox->setObjectName(QString::fromUtf8("StudentNameComboBox"));
        StudentNameComboBox->setGeometry(QRect(20, 220, 111, 31));
        StudentNumLabel = new QLabel(centralWidget);
        StudentNumLabel->setObjectName(QString::fromUtf8("StudentNumLabel"));
        StudentNumLabel->setGeometry(QRect(30, 270, 85, 22));
        StudentNumLabel->setAlignment(Qt::AlignCenter);
        StudentNumLabel2 = new QLabel(centralWidget);
        StudentNumLabel2->setObjectName(QString::fromUtf8("StudentNumLabel2"));
        StudentNumLabel2->setGeometry(QRect(30, 300, 85, 22));
        StudentNumLabel2->setFrameShape(QFrame::Panel);
        StudentNumLabel2->setFrameShadow(QFrame::Sunken);
        StudentNumLabel2->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 20, 131, 31));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 60, 131, 31));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(409, 21, 531, 439));
        rltTreeWidget = new QTreeWidget(groupBox_2);
        rltTreeWidget->setObjectName(QString::fromUtf8("rltTreeWidget"));
        rltTreeWidget->setGeometry(QRect(20, 30, 491, 391));
        rltTreeWidget->setLayoutDirection(Qt::LeftToRight);
        rltTreeWidget->setAutoFillBackground(false);
        rltTreeWidget->setColumnCount(3);
        rltTreeWidget->header()->setVisible(true);
        rltTreeWidget->header()->setCascadingSectionResizes(true);
        rltTreeWidget->header()->setDefaultSectionSize(190);
        rltTreeWidget->header()->setHighlightSections(false);
        rltTreeWidget->header()->setProperty("showSortIndicator", QVariant(false));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(161, 21, 251, 439));
        listWidget = new QListWidget(groupBox);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(20, 30, 211, 391));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(cancelBtn, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\344\275\234\344\270\232\346\237\245\351\207\215\350\275\257\344\273\266", 0, QApplication::UnicodeUTF8));
        HwNumLabel->setText(QApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251\344\275\234\344\270\232\346\211\271\346\254\241\357\274\232", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        HwNumComboBox->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        submitBtn->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        cancelBtn->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
        StudentNameLabel->setText(QApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251\346\237\245\351\207\215\345\255\246\347\224\237\357\274\232", 0, QApplication::UnicodeUTF8));
        StudentNumLabel->setText(QApplication::translate("MainWindow", "\346\237\245\351\207\215\345\255\246\347\224\237\345\255\246\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        StudentNumLabel2->setText(QString());
        pushButton->setText(QApplication::translate("MainWindow", "\345\257\274\345\205\245\345\255\246\347\224\237\344\277\241\346\201\257...", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\344\275\234\344\270\232\345\255\230\346\224\276\344\275\215\347\275\256...", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\346\237\245\351\207\215\347\273\223\346\236\234\346\230\276\347\244\272\345\214\272", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = rltTreeWidget->headerItem();
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "\347\233\270\344\274\274\345\272\246", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "\350\242\253\346\237\245\351\207\215\347\232\204\345\257\271\350\261\2412", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "\350\242\253\346\237\245\351\207\215\347\232\204\345\257\271\350\261\241", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "\350\242\253\346\237\245\351\207\215\345\257\271\350\261\241\346\230\276\347\244\272\345\214\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
