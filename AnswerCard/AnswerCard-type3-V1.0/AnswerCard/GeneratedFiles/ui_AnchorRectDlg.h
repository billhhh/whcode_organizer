/********************************************************************************
** Form generated from reading UI file 'AnchorRectDlg.ui'
**
** Created: Mon Apr 14 15:53:52 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANCHORRECTDLG_H
#define UI_ANCHORRECTDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AnchorRectDlg
{
public:
    QGridLayout *mainGridLayout;
    QGroupBox *anchorGroupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *anchorBtn;
    QPushButton *confirmBtn;

    void setupUi(QDialog *AnchorRectDlg)
    {
        if (AnchorRectDlg->objectName().isEmpty())
            AnchorRectDlg->setObjectName(QString::fromUtf8("AnchorRectDlg"));
        AnchorRectDlg->resize(242, 119);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AnchorRectDlg->sizePolicy().hasHeightForWidth());
        AnchorRectDlg->setSizePolicy(sizePolicy);
        mainGridLayout = new QGridLayout(AnchorRectDlg);
        mainGridLayout->setSpacing(6);
        mainGridLayout->setContentsMargins(11, 11, 11, 11);
        mainGridLayout->setObjectName(QString::fromUtf8("mainGridLayout"));
        mainGridLayout->setContentsMargins(-1, 3, -1, 5);
        anchorGroupBox = new QGroupBox(AnchorRectDlg);
        anchorGroupBox->setObjectName(QString::fromUtf8("anchorGroupBox"));
        anchorGroupBox->setEnabled(true);
        anchorGroupBox->setBaseSize(QSize(0, 0));
        anchorGroupBox->setAutoFillBackground(false);
        anchorGroupBox->setFlat(false);
        anchorGroupBox->setCheckable(false);
        gridLayout = new QGridLayout(anchorGroupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(anchorGroupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        anchorBtn = new QPushButton(anchorGroupBox);
        anchorBtn->setObjectName(QString::fromUtf8("anchorBtn"));
        anchorBtn->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(anchorBtn, 1, 0, 1, 1);

        confirmBtn = new QPushButton(anchorGroupBox);
        confirmBtn->setObjectName(QString::fromUtf8("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(0, 28));

        gridLayout->addWidget(confirmBtn, 2, 0, 1, 1);


        mainGridLayout->addWidget(anchorGroupBox, 0, 0, 1, 1);


        retranslateUi(AnchorRectDlg);

        QMetaObject::connectSlotsByName(AnchorRectDlg);
    } // setupUi

    void retranslateUi(QDialog *AnchorRectDlg)
    {
        AnchorRectDlg->setWindowTitle(QApplication::translate("AnchorRectDlg", "\345\256\232\344\275\215\347\202\271\345\256\232\344\275\215", 0, QApplication::UnicodeUTF8));
        anchorGroupBox->setTitle(QApplication::translate("AnchorRectDlg", "\345\256\232\344\275\215\346\241\206\345\256\232\344\275\215", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AnchorRectDlg", "<html><head/><body><p>\347\202\271\345\207\273\344\270\213\351\235\242\347\232\204\346\214\211\351\222\256\345\274\200\345\247\213\346\241\206\351\200\211\345\256\232\344\275\215\346\241\206</p></body></html>", 0, QApplication::UnicodeUTF8));
        anchorBtn->setText(QApplication::translate("AnchorRectDlg", "\346\241\206\351\200\211\345\256\232\344\275\215\346\241\206", 0, QApplication::UnicodeUTF8));
        confirmBtn->setText(QApplication::translate("AnchorRectDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AnchorRectDlg: public Ui_AnchorRectDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANCHORRECTDLG_H
