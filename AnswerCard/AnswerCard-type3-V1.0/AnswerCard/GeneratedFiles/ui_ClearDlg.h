/********************************************************************************
** Form generated from reading UI file 'ClearDlg.ui'
**
** Created: Mon Apr 14 15:53:52 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLEARDLG_H
#define UI_CLEARDLG_H

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

class Ui_ClearDlg
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QPushButton *changePicBtn;
    QPushButton *clearBtn;
    QLabel *label;

    void setupUi(QDialog *ClearDlg)
    {
        if (ClearDlg->objectName().isEmpty())
            ClearDlg->setObjectName(QString::fromUtf8("ClearDlg"));
        ClearDlg->resize(268, 82);
        gridLayout = new QGridLayout(ClearDlg);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 3, -1, 6);
        groupBox = new QGroupBox(ClearDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        changePicBtn = new QPushButton(groupBox);
        changePicBtn->setObjectName(QString::fromUtf8("changePicBtn"));

        gridLayout_2->addWidget(changePicBtn, 1, 1, 1, 1);

        clearBtn = new QPushButton(groupBox);
        clearBtn->setObjectName(QString::fromUtf8("clearBtn"));

        gridLayout_2->addWidget(clearBtn, 1, 0, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 2);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(ClearDlg);

        QMetaObject::connectSlotsByName(ClearDlg);
    } // setupUi

    void retranslateUi(QDialog *ClearDlg)
    {
        ClearDlg->setWindowTitle(QApplication::translate("ClearDlg", "ClearDlg", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ClearDlg", "\350\257\225\345\215\267\346\240\274\345\274\217\346\270\205\351\231\244", 0, QApplication::UnicodeUTF8));
        changePicBtn->setText(QApplication::translate("ClearDlg", "\351\207\215\346\226\260\345\210\266\345\256\232\345\233\276\347\211\207", 0, QApplication::UnicodeUTF8));
        clearBtn->setText(QApplication::translate("ClearDlg", "\346\270\205\351\231\244\345\215\241\346\240\274\345\274\217", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ClearDlg", "\345\257\271\345\275\223\345\211\215\347\274\226\350\276\221\347\232\204\350\257\225\345\215\267\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ClearDlg: public Ui_ClearDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLEARDLG_H
