/********************************************************************************
** Form generated from reading UI file 'AddPageDlg.ui'
**
** Created: Mon Apr 14 15:53:52 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPAGEDLG_H
#define UI_ADDPAGEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_AddPageDlg
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelBtn;
    QPushButton *okBtn;
    QFormLayout *formLayout;
    QPushButton *addFrontPageBtn;
    QLineEdit *pathEdit;
    QPushButton *addBackPageBtn;
    QLineEdit *backPathEdit;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLineEdit *idEdit;

    void setupUi(QDialog *AddPageDlg)
    {
        if (AddPageDlg->objectName().isEmpty())
            AddPageDlg->setObjectName(QString::fromUtf8("AddPageDlg"));
        AddPageDlg->resize(369, 131);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AddPageDlg->sizePolicy().hasHeightForWidth());
        AddPageDlg->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(AddPageDlg);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(88, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        cancelBtn = new QPushButton(AddPageDlg);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(cancelBtn, 2, 2, 1, 1);

        okBtn = new QPushButton(AddPageDlg);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(okBtn, 2, 1, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        addFrontPageBtn = new QPushButton(AddPageDlg);
        addFrontPageBtn->setObjectName(QString::fromUtf8("addFrontPageBtn"));

        formLayout->setWidget(0, QFormLayout::LabelRole, addFrontPageBtn);

        pathEdit = new QLineEdit(AddPageDlg);
        pathEdit->setObjectName(QString::fromUtf8("pathEdit"));
        pathEdit->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, pathEdit);

        addBackPageBtn = new QPushButton(AddPageDlg);
        addBackPageBtn->setObjectName(QString::fromUtf8("addBackPageBtn"));
        addBackPageBtn->setEnabled(false);

        formLayout->setWidget(1, QFormLayout::LabelRole, addBackPageBtn);

        backPathEdit = new QLineEdit(AddPageDlg);
        backPathEdit->setObjectName(QString::fromUtf8("backPathEdit"));
        backPathEdit->setEnabled(false);

        formLayout->setWidget(1, QFormLayout::FieldRole, backPathEdit);


        gridLayout->addLayout(formLayout, 1, 0, 1, 3);

        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        label = new QLabel(AddPageDlg);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        idEdit = new QLineEdit(AddPageDlg);
        idEdit->setObjectName(QString::fromUtf8("idEdit"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, idEdit);


        gridLayout->addLayout(formLayout_2, 0, 0, 1, 3);


        retranslateUi(AddPageDlg);

        QMetaObject::connectSlotsByName(AddPageDlg);
    } // setupUi

    void retranslateUi(QDialog *AddPageDlg)
    {
        AddPageDlg->setWindowTitle(QApplication::translate("AddPageDlg", "\346\267\273\345\212\240\347\255\224\351\242\230\345\215\267", 0, QApplication::UnicodeUTF8));
        cancelBtn->setText(QApplication::translate("AddPageDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        okBtn->setText(QApplication::translate("AddPageDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        addFrontPageBtn->setText(QApplication::translate("AddPageDlg", "\346\267\273\345\212\240\350\257\225\345\215\267\346\255\243\351\235\242", 0, QApplication::UnicodeUTF8));
        addBackPageBtn->setText(QApplication::translate("AddPageDlg", "\346\267\273\345\212\240\350\257\225\345\215\267\345\217\215\351\235\242", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AddPageDlg", " \347\254\254\345\207\240\345\274\240      ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddPageDlg: public Ui_AddPageDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPAGEDLG_H
