/********************************************************************************
** Form generated from reading UI file 'AnswerCardDlg3.ui'
**
** Created: Mon Apr 14 15:53:49 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANSWERCARDDLG3_H
#define UI_ANSWERCARDDLG3_H

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

class Ui_AnswerCardDlg3
{
public:
    QGridLayout *gridLayout;
    QGridLayout *btnGridLayout;
    QPushButton *newCardBtn;
    QPushButton *openFileBtn;
    QScrollArea *imageScrollArea;
    QWidget *imageWidget;
    QGridLayout *imageGridLayout;
    QLabel *imageLabel;
    QTabWidget *stepWidget;
    QWidget *cardWidget;
    QGridLayout *cardWidgetLayout;
    QWidget *firstWidget;
    QGridLayout *firstWidgetLayout;
    QWidget *secondWidget;
    QGridLayout *secWidgetLayout;

    void setupUi(QDialog *AnswerCardDlg3)
    {
        if (AnswerCardDlg3->objectName().isEmpty())
            AnswerCardDlg3->setObjectName(QString::fromUtf8("AnswerCardDlg3"));
        AnswerCardDlg3->resize(1030, 730);
        AnswerCardDlg3->setMinimumSize(QSize(0, 700));
        gridLayout = new QGridLayout(AnswerCardDlg3);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btnGridLayout = new QGridLayout();
        btnGridLayout->setSpacing(6);
        btnGridLayout->setObjectName(QString::fromUtf8("btnGridLayout"));
        newCardBtn = new QPushButton(AnswerCardDlg3);
        newCardBtn->setObjectName(QString::fromUtf8("newCardBtn"));
        newCardBtn->setMinimumSize(QSize(0, 23));
        newCardBtn->setMaximumSize(QSize(16777215, 28));

        btnGridLayout->addWidget(newCardBtn, 0, 0, 1, 1);

        openFileBtn = new QPushButton(AnswerCardDlg3);
        openFileBtn->setObjectName(QString::fromUtf8("openFileBtn"));
        openFileBtn->setMinimumSize(QSize(0, 23));
        openFileBtn->setMaximumSize(QSize(16777215, 28));

        btnGridLayout->addWidget(openFileBtn, 0, 2, 1, 1);


        gridLayout->addLayout(btnGridLayout, 0, 0, 1, 1);

        imageScrollArea = new QScrollArea(AnswerCardDlg3);
        imageScrollArea->setObjectName(QString::fromUtf8("imageScrollArea"));
        imageScrollArea->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ArrowCursor)));
        imageScrollArea->setMouseTracking(false);
        imageScrollArea->setFocusPolicy(Qt::StrongFocus);
        imageScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        imageScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        imageScrollArea->setWidgetResizable(true);
        imageWidget = new QWidget();
        imageWidget->setObjectName(QString::fromUtf8("imageWidget"));
        imageWidget->setGeometry(QRect(0, 0, 707, 693));
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

        gridLayout->addWidget(imageScrollArea, 0, 1, 3, 1);

        stepWidget = new QTabWidget(AnswerCardDlg3);
        stepWidget->setObjectName(QString::fromUtf8("stepWidget"));
        stepWidget->setMinimumSize(QSize(280, 600));
        stepWidget->setMaximumSize(QSize(280, 16777215));
        stepWidget->setTabPosition(QTabWidget::North);
        stepWidget->setTabShape(QTabWidget::Rounded);
        stepWidget->setElideMode(Qt::ElideNone);
        stepWidget->setUsesScrollButtons(true);
        stepWidget->setDocumentMode(false);
        cardWidget = new QWidget();
        cardWidget->setObjectName(QString::fromUtf8("cardWidget"));
        cardWidgetLayout = new QGridLayout(cardWidget);
        cardWidgetLayout->setSpacing(0);
        cardWidgetLayout->setContentsMargins(11, 11, 11, 11);
        cardWidgetLayout->setObjectName(QString::fromUtf8("cardWidgetLayout"));
        cardWidgetLayout->setContentsMargins(0, 5, 0, 0);
        stepWidget->addTab(cardWidget, QString());
        firstWidget = new QWidget();
        firstWidget->setObjectName(QString::fromUtf8("firstWidget"));
        firstWidgetLayout = new QGridLayout(firstWidget);
        firstWidgetLayout->setSpacing(0);
        firstWidgetLayout->setContentsMargins(11, 11, 11, 11);
        firstWidgetLayout->setObjectName(QString::fromUtf8("firstWidgetLayout"));
        firstWidgetLayout->setContentsMargins(0, 5, 0, 0);
        stepWidget->addTab(firstWidget, QString());
        secondWidget = new QWidget();
        secondWidget->setObjectName(QString::fromUtf8("secondWidget"));
        secWidgetLayout = new QGridLayout(secondWidget);
        secWidgetLayout->setSpacing(0);
        secWidgetLayout->setContentsMargins(11, 11, 11, 11);
        secWidgetLayout->setObjectName(QString::fromUtf8("secWidgetLayout"));
        secWidgetLayout->setSizeConstraint(QLayout::SetNoConstraint);
        secWidgetLayout->setContentsMargins(0, 5, 0, 0);
        stepWidget->addTab(secondWidget, QString());

        gridLayout->addWidget(stepWidget, 1, 0, 1, 1);

        QWidget::setTabOrder(newCardBtn, openFileBtn);
        QWidget::setTabOrder(openFileBtn, stepWidget);

        retranslateUi(AnswerCardDlg3);

        stepWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AnswerCardDlg3);
    } // setupUi

    void retranslateUi(QDialog *AnswerCardDlg3)
    {
        AnswerCardDlg3->setWindowTitle(QApplication::translate("AnswerCardDlg3", "\347\255\224\351\242\230\345\215\241\346\240\274\345\274\217\346\217\217\350\277\260\346\226\207\344\273\266\345\210\266\344\275\234\350\275\257\344\273\266", 0, QApplication::UnicodeUTF8));
        newCardBtn->setText(QApplication::translate("AnswerCardDlg3", "\346\226\260\345\273\272\345\245\227\345\215\241", 0, QApplication::UnicodeUTF8));
        openFileBtn->setText(QApplication::translate("AnswerCardDlg3", "\346\211\223\345\274\200\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        imageLabel->setText(QString());
        stepWidget->setTabText(stepWidget->indexOf(cardWidget), QApplication::translate("AnswerCardDlg3", "\345\245\227\345\215\241\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
        stepWidget->setTabText(stepWidget->indexOf(firstWidget), QApplication::translate("AnswerCardDlg3", "\346\255\245\351\252\244\344\270\200", 0, QApplication::UnicodeUTF8));
        stepWidget->setTabText(stepWidget->indexOf(secondWidget), QApplication::translate("AnswerCardDlg3", "\346\255\245\351\252\244\344\272\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AnswerCardDlg3: public Ui_AnswerCardDlg3 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANSWERCARDDLG3_H
