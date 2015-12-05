/********************************************************************************
** Form generated from reading UI file 'IdPointDlg.ui'
**
** Created: Mon Jun 30 09:41:39 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IDPOINTDLG_H
#define UI_IDPOINTDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_IdPointDlg
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QPushButton *addBtn;
    QPushButton *confirmBtn;
    QGridLayout *gridLayout;
    QListWidget *idPointList;
    QPushButton *deleteBtn;

    void setupUi(QDialog *IdPointDlg)
    {
        if (IdPointDlg->objectName().isEmpty())
            IdPointDlg->setObjectName(QString::fromUtf8("IdPointDlg"));
        IdPointDlg->resize(234, 127);
        gridLayout_3 = new QGridLayout(IdPointDlg);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, 3, -1, 6);
        groupBox = new QGroupBox(IdPointDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        addBtn = new QPushButton(groupBox);
        addBtn->setObjectName(QString::fromUtf8("addBtn"));

        gridLayout_2->addWidget(addBtn, 0, 0, 1, 1);

        confirmBtn = new QPushButton(groupBox);
        confirmBtn->setObjectName(QString::fromUtf8("confirmBtn"));

        gridLayout_2->addWidget(confirmBtn, 0, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        idPointList = new QListWidget(groupBox);
        idPointList->setObjectName(QString::fromUtf8("idPointList"));
        idPointList->setMaximumSize(QSize(16777215, 55));

        gridLayout->addWidget(idPointList, 0, 0, 1, 1);

        deleteBtn = new QPushButton(groupBox);
        deleteBtn->setObjectName(QString::fromUtf8("deleteBtn"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(deleteBtn->sizePolicy().hasHeightForWidth());
        deleteBtn->setSizePolicy(sizePolicy);
        deleteBtn->setMaximumSize(QSize(44, 55));

        gridLayout->addWidget(deleteBtn, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 2);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(IdPointDlg);

        QMetaObject::connectSlotsByName(IdPointDlg);
    } // setupUi

    void retranslateUi(QDialog *IdPointDlg)
    {
        IdPointDlg->setWindowTitle(QApplication::translate("IdPointDlg", "IdPointDlg", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("IdPointDlg", "ID\347\202\271\345\256\232\344\275\215", 0, QApplication::UnicodeUTF8));
        addBtn->setText(QApplication::translate("IdPointDlg", "\346\267\273\345\212\240ID\347\202\271", 0, QApplication::UnicodeUTF8));
        confirmBtn->setText(QApplication::translate("IdPointDlg", "\347\241\256\350\256\244ID\347\202\271", 0, QApplication::UnicodeUTF8));
        deleteBtn->setText(QApplication::translate("IdPointDlg", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class IdPointDlg: public Ui_IdPointDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IDPOINTDLG_H
