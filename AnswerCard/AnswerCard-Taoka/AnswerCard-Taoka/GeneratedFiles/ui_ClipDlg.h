/********************************************************************************
** Form generated from reading UI file 'ClipDlg.ui'
**
** Created: Mon Jun 30 09:41:38 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIPDLG_H
#define UI_CLIPDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ClipDlg
{
public:
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *cropAreaEdit;
    QLabel *label_2;
    QLineEdit *groupEdit;
    QCheckBox *secretCheckBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *addBtn;
    QPushButton *confirmBtn;
    QGridLayout *gridLayout_3;
    QListWidget *clipList;
    QPushButton *deleteBtn;

    void setupUi(QDialog *ClipDlg)
    {
        if (ClipDlg->objectName().isEmpty())
            ClipDlg->setObjectName(QString::fromUtf8("ClipDlg"));
        ClipDlg->setEnabled(true);
        ClipDlg->resize(279, 210);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ClipDlg->sizePolicy().hasHeightForWidth());
        ClipDlg->setSizePolicy(sizePolicy);
        gridLayout_4 = new QGridLayout(ClipDlg);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(-1, 3, -1, 6);
        groupBox = new QGroupBox(ClipDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        cropAreaEdit = new QLineEdit(groupBox);
        cropAreaEdit->setObjectName(QString::fromUtf8("cropAreaEdit"));

        gridLayout->addWidget(cropAreaEdit, 0, 1, 1, 2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        groupEdit = new QLineEdit(groupBox);
        groupEdit->setObjectName(QString::fromUtf8("groupEdit"));

        gridLayout->addWidget(groupEdit, 1, 1, 1, 1);

        secretCheckBox = new QCheckBox(groupBox);
        secretCheckBox->setObjectName(QString::fromUtf8("secretCheckBox"));

        gridLayout->addWidget(secretCheckBox, 1, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        addBtn = new QPushButton(groupBox);
        addBtn->setObjectName(QString::fromUtf8("addBtn"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(addBtn->sizePolicy().hasHeightForWidth());
        addBtn->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(addBtn);

        confirmBtn = new QPushButton(groupBox);
        confirmBtn->setObjectName(QString::fromUtf8("confirmBtn"));
        sizePolicy2.setHeightForWidth(confirmBtn->sizePolicy().hasHeightForWidth());
        confirmBtn->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(confirmBtn);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setVerticalSpacing(2);
        clipList = new QListWidget(groupBox);
        clipList->setObjectName(QString::fromUtf8("clipList"));

        gridLayout_3->addWidget(clipList, 0, 0, 1, 1);

        deleteBtn = new QPushButton(groupBox);
        deleteBtn->setObjectName(QString::fromUtf8("deleteBtn"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(deleteBtn->sizePolicy().hasHeightForWidth());
        deleteBtn->setSizePolicy(sizePolicy3);
        deleteBtn->setMinimumSize(QSize(0, 0));
        deleteBtn->setMaximumSize(QSize(40, 16777215));

        gridLayout_3->addWidget(deleteBtn, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout_3, 2, 0, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(ClipDlg);

        QMetaObject::connectSlotsByName(ClipDlg);
    } // setupUi

    void retranslateUi(QDialog *ClipDlg)
    {
        ClipDlg->setWindowTitle(QApplication::translate("ClipDlg", "\350\243\201\345\210\207\345\214\272\345\237\237\345\256\232\344\271\211", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ClipDlg", "\350\243\201\345\210\207\345\214\272\345\237\237\345\256\232\344\275\215", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ClipDlg", "\345\214\272\345\237\237\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ClipDlg", "\347\273\204    \345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        groupEdit->setToolTip(QApplication::translate("ClipDlg", "\350\276\223\345\205\2450\346\227\266\357\274\214\344\273\243\350\241\250\344\270\215\345\210\206\347\273\204", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        secretCheckBox->setText(QApplication::translate("ClipDlg", "\344\277\235\345\257\206", 0, QApplication::UnicodeUTF8));
        addBtn->setText(QApplication::translate("ClipDlg", "\346\267\273\345\212\240\350\243\201\345\210\207\345\214\272\345\237\237", 0, QApplication::UnicodeUTF8));
        confirmBtn->setText(QApplication::translate("ClipDlg", "\347\241\256\350\256\244\350\243\201\345\210\207\345\214\272\345\237\237", 0, QApplication::UnicodeUTF8));
        deleteBtn->setText(QApplication::translate("ClipDlg", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ClipDlg: public Ui_ClipDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIPDLG_H
