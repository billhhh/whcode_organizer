/********************************************************************************
** Form generated from reading UI file 'CardSetDlg.ui'
**
** Created: Mon Apr 14 15:53:52 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CARDSETDLG_H
#define UI_CARDSETDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_CardSetDlg
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QPushButton *saveFileBtn;
    QPushButton *importXMLBtn;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QTableWidget *tableWidget;
    QPushButton *editBtn;
    QPushButton *deleteBtn;
    QPushButton *addBtn;

    void setupUi(QDialog *CardSetDlg)
    {
        if (CardSetDlg->objectName().isEmpty())
            CardSetDlg->setObjectName(QString::fromUtf8("CardSetDlg"));
        CardSetDlg->resize(275, 295);
        gridLayout_3 = new QGridLayout(CardSetDlg);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox_2 = new QGroupBox(CardSetDlg);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 3, -1, 6);
        saveFileBtn = new QPushButton(groupBox_2);
        saveFileBtn->setObjectName(QString::fromUtf8("saveFileBtn"));
        saveFileBtn->setMinimumSize(QSize(80, 23));

        gridLayout->addWidget(saveFileBtn, 0, 0, 1, 1);

        importXMLBtn = new QPushButton(groupBox_2);
        importXMLBtn->setObjectName(QString::fromUtf8("importXMLBtn"));
        importXMLBtn->setMinimumSize(QSize(80, 23));

        gridLayout->addWidget(importXMLBtn, 0, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 0, 0, 1, 1);

        groupBox = new QGroupBox(CardSetDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tableWidget = new QTableWidget(groupBox);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setLayoutDirection(Qt::LeftToRight);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setDragDropMode(QAbstractItemView::NoDragDrop);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setCascadingSectionResizes(true);
        tableWidget->verticalHeader()->setHighlightSections(false);

        gridLayout_2->addWidget(tableWidget, 0, 0, 1, 3);

        editBtn = new QPushButton(groupBox);
        editBtn->setObjectName(QString::fromUtf8("editBtn"));

        gridLayout_2->addWidget(editBtn, 1, 2, 1, 1);

        deleteBtn = new QPushButton(groupBox);
        deleteBtn->setObjectName(QString::fromUtf8("deleteBtn"));

        gridLayout_2->addWidget(deleteBtn, 1, 1, 1, 1);

        addBtn = new QPushButton(groupBox);
        addBtn->setObjectName(QString::fromUtf8("addBtn"));

        gridLayout_2->addWidget(addBtn, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 1, 0, 1, 1);


        retranslateUi(CardSetDlg);

        QMetaObject::connectSlotsByName(CardSetDlg);
    } // setupUi

    void retranslateUi(QDialog *CardSetDlg)
    {
        CardSetDlg->setWindowTitle(QApplication::translate("CardSetDlg", "CardSetDlg", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("CardSetDlg", "\350\257\225\345\215\267\350\276\223\345\207\272", 0, QApplication::UnicodeUTF8));
        saveFileBtn->setText(QApplication::translate("CardSetDlg", "\344\277\235\345\255\230\345\245\227\345\215\241", 0, QApplication::UnicodeUTF8));
        importXMLBtn->setText(QApplication::translate("CardSetDlg", "\345\257\274\345\207\272XML\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("CardSetDlg", "\350\257\225\345\215\267\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CardSetDlg", "\345\274\240", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CardSetDlg", "\346\255\243/\345\217\215\351\235\242", 0, QApplication::UnicodeUTF8));
        editBtn->setText(QApplication::translate("CardSetDlg", "\347\274\226\350\276\221", 0, QApplication::UnicodeUTF8));
        deleteBtn->setText(QApplication::translate("CardSetDlg", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        addBtn->setText(QApplication::translate("CardSetDlg", "\346\267\273\345\212\240", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CardSetDlg: public Ui_CardSetDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARDSETDLG_H
