/********************************************************************************
** Form generated from reading UI file 'PagePointDlg.ui'
**
** Created: Mon Apr 14 15:53:52 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEPOINTDLG_H
#define UI_PAGEPOINTDLG_H

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

class Ui_PagePointDlg
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

    void setupUi(QDialog *PagePointDlg)
    {
        if (PagePointDlg->objectName().isEmpty())
            PagePointDlg->setObjectName(QString::fromUtf8("PagePointDlg"));
        PagePointDlg->resize(234, 127);
        gridLayout_3 = new QGridLayout(PagePointDlg);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, 3, -1, 6);
        groupBox = new QGroupBox(PagePointDlg);
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


        retranslateUi(PagePointDlg);

        QMetaObject::connectSlotsByName(PagePointDlg);
    } // setupUi

    void retranslateUi(QDialog *PagePointDlg)
    {
        PagePointDlg->setWindowTitle(QApplication::translate("PagePointDlg", "IdPointDlg", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("PagePointDlg", "\351\241\265\347\240\201\346\240\207\350\257\206\345\256\232\344\275\215", 0, QApplication::UnicodeUTF8));
        addBtn->setText(QApplication::translate("PagePointDlg", "\346\267\273\345\212\240\351\241\265\347\240\201\346\240\207\350\257\206", 0, QApplication::UnicodeUTF8));
        confirmBtn->setText(QApplication::translate("PagePointDlg", "\347\241\256\350\256\244\351\241\265\347\240\201\346\240\207\350\257\206", 0, QApplication::UnicodeUTF8));
        deleteBtn->setText(QApplication::translate("PagePointDlg", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PagePointDlg: public Ui_PagePointDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEPOINTDLG_H
