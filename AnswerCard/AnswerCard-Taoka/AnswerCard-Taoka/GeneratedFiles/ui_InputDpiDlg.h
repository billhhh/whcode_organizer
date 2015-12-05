/********************************************************************************
** Form generated from reading UI file 'InputDpiDlg.ui'
**
** Created: Mon Jun 30 09:41:39 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTDPIDLG_H
#define UI_INPUTDPIDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_InputDpiDlg
{
public:
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLineEdit *dpiEdit;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *InputDpiDlg)
    {
        if (InputDpiDlg->objectName().isEmpty())
            InputDpiDlg->setObjectName(QString::fromUtf8("InputDpiDlg"));
        InputDpiDlg->resize(342, 67);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(InputDpiDlg->sizePolicy().hasHeightForWidth());
        InputDpiDlg->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(InputDpiDlg);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(InputDpiDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        dpiEdit = new QLineEdit(InputDpiDlg);
        dpiEdit->setObjectName(QString::fromUtf8("dpiEdit"));
        dpiEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(dpiEdit, 0, 1, 1, 2);

        okBtn = new QPushButton(InputDpiDlg);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));

        gridLayout->addWidget(okBtn, 1, 1, 1, 1);

        cancelBtn = new QPushButton(InputDpiDlg);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));

        gridLayout->addWidget(cancelBtn, 1, 2, 1, 1);


        retranslateUi(InputDpiDlg);

        QMetaObject::connectSlotsByName(InputDpiDlg);
    } // setupUi

    void retranslateUi(QDialog *InputDpiDlg)
    {
        InputDpiDlg->setWindowTitle(QApplication::translate("InputDpiDlg", "\350\276\223\345\205\245\345\233\276\345\275\242\345\210\206\350\276\250\347\216\207", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("InputDpiDlg", "\345\233\276\345\275\242\345\210\206\350\276\250\347\216\207\344\270\272\357\274\210\345\215\225\344\275\215\357\274\232dpi\357\274\211\357\274\232", 0, QApplication::UnicodeUTF8));
        dpiEdit->setText(QApplication::translate("InputDpiDlg", "0", 0, QApplication::UnicodeUTF8));
        okBtn->setText(QApplication::translate("InputDpiDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        cancelBtn->setText(QApplication::translate("InputDpiDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class InputDpiDlg: public Ui_InputDpiDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTDPIDLG_H
