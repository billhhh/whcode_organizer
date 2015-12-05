/********************************************************************************
** Form generated from reading UI file 'AddPaperDlg.ui'
**
** Created: Mon Jun 30 09:41:39 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPAPERDLG_H
#define UI_ADDPAPERDLG_H

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
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_AddPaperDlg
{
public:
    QGridLayout *gridLayout_2;
    QPushButton *okBtn;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *numEdit;
    QLabel *label_2;
    QLineEdit *dpiEdit;
    QPushButton *cancelBtn;

    void setupUi(QDialog *AddPaperDlg)
    {
        if (AddPaperDlg->objectName().isEmpty())
            AddPaperDlg->setObjectName(QString::fromUtf8("AddPaperDlg"));
        AddPaperDlg->resize(322, 97);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AddPaperDlg->sizePolicy().hasHeightForWidth());
        AddPaperDlg->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(AddPaperDlg);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        okBtn = new QPushButton(AddPaperDlg);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setMinimumSize(QSize(0, 25));

        gridLayout_2->addWidget(okBtn, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(91, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(AddPaperDlg);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        numEdit = new QLineEdit(AddPaperDlg);
        numEdit->setObjectName(QString::fromUtf8("numEdit"));

        gridLayout->addWidget(numEdit, 0, 1, 1, 1);

        label_2 = new QLabel(AddPaperDlg);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        dpiEdit = new QLineEdit(AddPaperDlg);
        dpiEdit->setObjectName(QString::fromUtf8("dpiEdit"));

        gridLayout->addWidget(dpiEdit, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 3);

        cancelBtn = new QPushButton(AddPaperDlg);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(0, 25));

        gridLayout_2->addWidget(cancelBtn, 1, 2, 1, 1);

        QWidget::setTabOrder(numEdit, dpiEdit);
        QWidget::setTabOrder(dpiEdit, okBtn);
        QWidget::setTabOrder(okBtn, cancelBtn);

        retranslateUi(AddPaperDlg);

        QMetaObject::connectSlotsByName(AddPaperDlg);
    } // setupUi

    void retranslateUi(QDialog *AddPaperDlg)
    {
        AddPaperDlg->setWindowTitle(QApplication::translate("AddPaperDlg", "\346\226\260\345\273\272\344\270\200\345\245\227\350\257\225\345\215\267", 0, QApplication::UnicodeUTF8));
        okBtn->setText(QApplication::translate("AddPaperDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AddPaperDlg", "\345\245\227\345\215\241\345\217\267\357\274\232", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AddPaperDlg", "\345\210\206\350\276\250\347\216\207\357\274\232", 0, QApplication::UnicodeUTF8));
        dpiEdit->setText(QString());
        cancelBtn->setText(QApplication::translate("AddPaperDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddPaperDlg: public Ui_AddPaperDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPAPERDLG_H
