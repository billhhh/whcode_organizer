/********************************************************************************
** Form generated from reading UI file 'AnswerCardDlg.ui'
**
** Created: Mon Jun 30 09:41:38 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANSWERCARDDLG_H
#define UI_ANSWERCARDDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AnswerCardDlg
{
public:
    QGridLayout *gridLayout;
    QGridLayout *btnGridLayout;
    QPushButton *backBtn;
    QScrollArea *imageScrollArea;
    QWidget *imageWidget;
    QGridLayout *imageGridLayout;
    QLabel *imageLabel;
    QTabWidget *stepWidget;
    QWidget *firstWidget;
    QGridLayout *firstWidgetLayout;
    QWidget *secondWidget;
    QGridLayout *secWidgetLayout;

    void setupUi(QDialog *AnswerCardDlg)
    {
        if (AnswerCardDlg->objectName().isEmpty())
            AnswerCardDlg->setObjectName(QString::fromUtf8("AnswerCardDlg"));
        AnswerCardDlg->resize(1050, 730);
        AnswerCardDlg->setMinimumSize(QSize(0, 730));
        gridLayout = new QGridLayout(AnswerCardDlg);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btnGridLayout = new QGridLayout();
        btnGridLayout->setSpacing(6);
        btnGridLayout->setObjectName(QString::fromUtf8("btnGridLayout"));
        backBtn = new QPushButton(AnswerCardDlg);
        backBtn->setObjectName(QString::fromUtf8("backBtn"));
        backBtn->setMinimumSize(QSize(0, 26));
        backBtn->setMaximumSize(QSize(16777215, 30));

        btnGridLayout->addWidget(backBtn, 0, 0, 1, 1);


        gridLayout->addLayout(btnGridLayout, 0, 0, 1, 1);

        imageScrollArea = new QScrollArea(AnswerCardDlg);
        imageScrollArea->setObjectName(QString::fromUtf8("imageScrollArea"));
        imageScrollArea->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ArrowCursor)));
        imageScrollArea->setMouseTracking(false);
        imageScrollArea->setFocusPolicy(Qt::StrongFocus);
        imageScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        imageScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        imageScrollArea->setWidgetResizable(true);
        imageWidget = new QWidget();
        imageWidget->setObjectName(QString::fromUtf8("imageWidget"));
        imageWidget->setGeometry(QRect(0, 0, 737, 693));
        imageWidget->setMouseTracking(true);
        imageWidget->setFocusPolicy(Qt::StrongFocus);
        imageGridLayout = new QGridLayout(imageWidget);
        imageGridLayout->setSpacing(6);
        imageGridLayout->setContentsMargins(0, 0, 0, 0);
        imageGridLayout->setObjectName(QString::fromUtf8("imageGridLayout"));
        imageGridLayout->setHorizontalSpacing(0);
        imageLabel = new QLabel(imageWidget);
        imageLabel->setObjectName(QString::fromUtf8("imageLabel"));
        imageLabel->setMouseTracking(true);
        imageLabel->setFocusPolicy(Qt::StrongFocus);

        imageGridLayout->addWidget(imageLabel, 0, 0, 1, 1);

        imageScrollArea->setWidget(imageWidget);

        gridLayout->addWidget(imageScrollArea, 0, 1, 2, 1);

        stepWidget = new QTabWidget(AnswerCardDlg);
        stepWidget->setObjectName(QString::fromUtf8("stepWidget"));
        stepWidget->setMinimumSize(QSize(270, 600));
        stepWidget->setMaximumSize(QSize(270, 16777215));
        stepWidget->setTabPosition(QTabWidget::North);
        stepWidget->setTabShape(QTabWidget::Rounded);
        stepWidget->setElideMode(Qt::ElideNone);
        stepWidget->setUsesScrollButtons(true);
        stepWidget->setDocumentMode(false);
        firstWidget = new QWidget();
        firstWidget->setObjectName(QString::fromUtf8("firstWidget"));
        firstWidgetLayout = new QGridLayout(firstWidget);
        firstWidgetLayout->setSpacing(0);
        firstWidgetLayout->setContentsMargins(11, 11, 11, 11);
        firstWidgetLayout->setObjectName(QString::fromUtf8("firstWidgetLayout"));
        firstWidgetLayout->setContentsMargins(0, 6, 0, 0);
        stepWidget->addTab(firstWidget, QString());
        secondWidget = new QWidget();
        secondWidget->setObjectName(QString::fromUtf8("secondWidget"));
        secWidgetLayout = new QGridLayout(secondWidget);
        secWidgetLayout->setSpacing(0);
        secWidgetLayout->setContentsMargins(11, 11, 11, 11);
        secWidgetLayout->setObjectName(QString::fromUtf8("secWidgetLayout"));
        secWidgetLayout->setSizeConstraint(QLayout::SetNoConstraint);
        secWidgetLayout->setContentsMargins(0, 6, 0, 0);
        stepWidget->addTab(secondWidget, QString());

        gridLayout->addWidget(stepWidget, 1, 0, 1, 1);

        QWidget::setTabOrder(backBtn, stepWidget);

        retranslateUi(AnswerCardDlg);

        stepWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AnswerCardDlg);
    } // setupUi

    void retranslateUi(QDialog *AnswerCardDlg)
    {
        AnswerCardDlg->setWindowTitle(QApplication::translate("AnswerCardDlg", "\347\255\224\351\242\230\345\215\241\346\240\274\345\274\217\346\217\217\350\277\260\346\226\207\344\273\266\345\210\266\344\275\234\350\275\257\344\273\266", 0, QApplication::UnicodeUTF8));
        backBtn->setText(QApplication::translate("AnswerCardDlg", "\350\277\224\345\233\236", 0, QApplication::UnicodeUTF8));
        imageLabel->setText(QString());
        stepWidget->setTabText(stepWidget->indexOf(firstWidget), QApplication::translate("AnswerCardDlg", "\346\255\245\351\252\244\344\270\200", 0, QApplication::UnicodeUTF8));
        stepWidget->setTabText(stepWidget->indexOf(secondWidget), QApplication::translate("AnswerCardDlg", "\346\255\245\351\252\244\344\272\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AnswerCardDlg: public Ui_AnswerCardDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANSWERCARDDLG_H
