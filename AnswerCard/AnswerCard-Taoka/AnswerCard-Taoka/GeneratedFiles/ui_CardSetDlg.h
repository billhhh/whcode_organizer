/********************************************************************************
** Form generated from reading UI file 'CardSetDlg.ui'
**
** Created: Mon Jun 30 09:41:39 2014
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
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_CardCombineClass
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *editPageBtn;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *deletePageBtn;
    QPushButton *addPageBtn;
    QSpacerItem *horizontalSpacer_5;
    QTableWidget *subTable;
    QPushButton *addPaperBtn;
    QPushButton *deletePaperBtn;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_4;
    QTableWidget *paperSetTable;
    QGridLayout *gridLayout_2;
    QComboBox *comboBox;
    QLabel *label;
    QPushButton *addCourseBtn;
    QPushButton *deleteCourseBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *openPaperBtn;
    QPushButton *savePaperBtn;
    QPushButton *importPaperBtn;

    void setupUi(QDialog *CardCombineClass)
    {
        if (CardCombineClass->objectName().isEmpty())
            CardCombineClass->setObjectName(QString::fromUtf8("CardCombineClass"));
        CardCombineClass->resize(806, 554);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CardCombineClass->sizePolicy().hasHeightForWidth());
        CardCombineClass->setSizePolicy(sizePolicy);
        CardCombineClass->setMaximumSize(QSize(16777215, 1666666));
        gridLayout_3 = new QGridLayout(CardCombineClass);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(CardCombineClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        editPageBtn = new QPushButton(groupBox);
        editPageBtn->setObjectName(QString::fromUtf8("editPageBtn"));
        editPageBtn->setMinimumSize(QSize(0, 28));
        editPageBtn->setFlat(false);

        gridLayout->addWidget(editPageBtn, 1, 8, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(112, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 7, 1, 1);

        deletePageBtn = new QPushButton(groupBox);
        deletePageBtn->setObjectName(QString::fromUtf8("deletePageBtn"));
        deletePageBtn->setMinimumSize(QSize(32, 28));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/CardCombine/Resources/minus2_.png"), QSize(), QIcon::Normal, QIcon::Off);
        deletePageBtn->setIcon(icon);
        deletePageBtn->setIconSize(QSize(20, 20));

        gridLayout->addWidget(deletePageBtn, 1, 6, 1, 1);

        addPageBtn = new QPushButton(groupBox);
        addPageBtn->setObjectName(QString::fromUtf8("addPageBtn"));
        addPageBtn->setMinimumSize(QSize(32, 28));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/CardCombine/Resources/plus2_.png"), QSize(), QIcon::Normal, QIcon::Off);
        addPageBtn->setIcon(icon1);
        addPageBtn->setIconSize(QSize(20, 20));

        gridLayout->addWidget(addPageBtn, 1, 5, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(113, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 1, 4, 1, 1);

        subTable = new QTableWidget(groupBox);
        if (subTable->columnCount() < 1)
            subTable->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        subTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        subTable->setObjectName(QString::fromUtf8("subTable"));
        subTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        subTable->setSelectionMode(QAbstractItemView::SingleSelection);
        subTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        subTable->horizontalHeader()->setVisible(true);
        subTable->horizontalHeader()->setCascadingSectionResizes(false);
        subTable->horizontalHeader()->setMinimumSectionSize(30);
        subTable->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        subTable->horizontalHeader()->setStretchLastSection(true);
        subTable->verticalHeader()->setVisible(false);
        subTable->verticalHeader()->setCascadingSectionResizes(true);
        subTable->verticalHeader()->setHighlightSections(false);

        gridLayout->addWidget(subTable, 0, 5, 1, 4);

        addPaperBtn = new QPushButton(groupBox);
        addPaperBtn->setObjectName(QString::fromUtf8("addPaperBtn"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(addPaperBtn->sizePolicy().hasHeightForWidth());
        addPaperBtn->setSizePolicy(sizePolicy1);
        addPaperBtn->setMinimumSize(QSize(32, 28));
        addPaperBtn->setIcon(icon1);
        addPaperBtn->setIconSize(QSize(20, 20));

        gridLayout->addWidget(addPaperBtn, 1, 0, 1, 1);

        deletePaperBtn = new QPushButton(groupBox);
        deletePaperBtn->setObjectName(QString::fromUtf8("deletePaperBtn"));
        sizePolicy1.setHeightForWidth(deletePaperBtn->sizePolicy().hasHeightForWidth());
        deletePaperBtn->setSizePolicy(sizePolicy1);
        deletePaperBtn->setMinimumSize(QSize(32, 28));
        deletePaperBtn->setIcon(icon);
        deletePaperBtn->setIconSize(QSize(20, 20));

        gridLayout->addWidget(deletePaperBtn, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(112, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(133, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 3, 1, 1);

        paperSetTable = new QTableWidget(groupBox);
        if (paperSetTable->columnCount() < 2)
            paperSetTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        paperSetTable->setHorizontalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        paperSetTable->setHorizontalHeaderItem(1, __qtablewidgetitem2);
        paperSetTable->setObjectName(QString::fromUtf8("paperSetTable"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(paperSetTable->sizePolicy().hasHeightForWidth());
        paperSetTable->setSizePolicy(sizePolicy2);
        paperSetTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        paperSetTable->setSelectionMode(QAbstractItemView::SingleSelection);
        paperSetTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        paperSetTable->horizontalHeader()->setCascadingSectionResizes(false);
        paperSetTable->horizontalHeader()->setDefaultSectionSize(200);
        paperSetTable->horizontalHeader()->setHighlightSections(true);
        paperSetTable->horizontalHeader()->setMinimumSectionSize(50);
        paperSetTable->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        paperSetTable->horizontalHeader()->setStretchLastSection(true);
        paperSetTable->verticalHeader()->setCascadingSectionResizes(false);

        gridLayout->addWidget(paperSetTable, 0, 0, 1, 5);


        gridLayout_3->addWidget(groupBox, 2, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        comboBox = new QComboBox(CardCombineClass);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(150, 0));

        gridLayout_2->addWidget(comboBox, 0, 1, 1, 1);

        label = new QLabel(CardCombineClass);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        addCourseBtn = new QPushButton(CardCombineClass);
        addCourseBtn->setObjectName(QString::fromUtf8("addCourseBtn"));
        sizePolicy1.setHeightForWidth(addCourseBtn->sizePolicy().hasHeightForWidth());
        addCourseBtn->setSizePolicy(sizePolicy1);
        addCourseBtn->setMinimumSize(QSize(32, 28));
        addCourseBtn->setIcon(icon1);
        addCourseBtn->setIconSize(QSize(20, 20));

        gridLayout_2->addWidget(addCourseBtn, 0, 2, 1, 1);

        deleteCourseBtn = new QPushButton(CardCombineClass);
        deleteCourseBtn->setObjectName(QString::fromUtf8("deleteCourseBtn"));
        sizePolicy1.setHeightForWidth(deleteCourseBtn->sizePolicy().hasHeightForWidth());
        deleteCourseBtn->setSizePolicy(sizePolicy1);
        deleteCourseBtn->setMinimumSize(QSize(32, 28));
        deleteCourseBtn->setIcon(icon);
        deleteCourseBtn->setIconSize(QSize(20, 20));

        gridLayout_2->addWidget(deleteCourseBtn, 0, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 4, 1, 1);

        openPaperBtn = new QPushButton(CardCombineClass);
        openPaperBtn->setObjectName(QString::fromUtf8("openPaperBtn"));
        openPaperBtn->setMinimumSize(QSize(90, 28));

        gridLayout_2->addWidget(openPaperBtn, 0, 5, 1, 1);

        savePaperBtn = new QPushButton(CardCombineClass);
        savePaperBtn->setObjectName(QString::fromUtf8("savePaperBtn"));
        savePaperBtn->setMinimumSize(QSize(90, 28));

        gridLayout_2->addWidget(savePaperBtn, 0, 6, 1, 1);

        importPaperBtn = new QPushButton(CardCombineClass);
        importPaperBtn->setObjectName(QString::fromUtf8("importPaperBtn"));
        sizePolicy1.setHeightForWidth(importPaperBtn->sizePolicy().hasHeightForWidth());
        importPaperBtn->setSizePolicy(sizePolicy1);
        importPaperBtn->setMinimumSize(QSize(90, 28));

        gridLayout_2->addWidget(importPaperBtn, 0, 7, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 1, 0, 1, 1);

        QWidget::setTabOrder(openPaperBtn, savePaperBtn);
        QWidget::setTabOrder(savePaperBtn, addPaperBtn);
        QWidget::setTabOrder(addPaperBtn, deletePaperBtn);
        QWidget::setTabOrder(deletePaperBtn, paperSetTable);
        QWidget::setTabOrder(paperSetTable, addPageBtn);
        QWidget::setTabOrder(addPageBtn, deletePageBtn);
        QWidget::setTabOrder(deletePageBtn, editPageBtn);
        QWidget::setTabOrder(editPageBtn, subTable);
        QWidget::setTabOrder(subTable, importPaperBtn);

        retranslateUi(CardCombineClass);

        QMetaObject::connectSlotsByName(CardCombineClass);
    } // setupUi

    void retranslateUi(QDialog *CardCombineClass)
    {
        CardCombineClass->setWindowTitle(QApplication::translate("CardCombineClass", "\345\245\227\345\215\241\345\210\266\344\275\234\350\275\257\344\273\266", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("CardCombineClass", "\350\257\225\345\215\267\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        editPageBtn->setToolTip(QApplication::translate("CardCombineClass", "\346\240\274\345\274\217\345\210\266\344\275\234", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        editPageBtn->setText(QApplication::translate("CardCombineClass", "\347\274\226\350\276\221\350\257\225\345\215\267", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        deletePageBtn->setToolTip(QApplication::translate("CardCombineClass", "\347\247\273\351\231\244\344\270\200\345\274\240\350\257\225\345\215\267", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        deletePageBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        addPageBtn->setToolTip(QApplication::translate("CardCombineClass", "\346\267\273\345\212\240\344\270\200\345\274\240\350\257\225\345\215\267", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        addPageBtn->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = subTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CardCombineClass", "\347\254\254 N \345\274\240", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        addPaperBtn->setToolTip(QApplication::translate("CardCombineClass", "\346\226\260\345\273\272\344\270\200\345\245\227\350\257\225\345\215\267", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        addPaperBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        deletePaperBtn->setToolTip(QApplication::translate("CardCombineClass", "\345\210\240\351\231\244\344\270\200\345\245\227\350\257\225\345\215\267", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        deletePaperBtn->setText(QString());
        QTableWidgetItem *___qtablewidgetitem1 = paperSetTable->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("CardCombineClass", "\345\245\227\345\215\241\345\217\267", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = paperSetTable->horizontalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("CardCombineClass", "\346\225\260\351\207\217", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CardCombineClass", "\347\247\221\347\233\256\357\274\232", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        addCourseBtn->setToolTip(QApplication::translate("CardCombineClass", "\346\226\260\345\273\272\344\270\200\345\245\227\350\257\225\345\215\267", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        addCourseBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        deleteCourseBtn->setToolTip(QApplication::translate("CardCombineClass", "\345\210\240\351\231\244\344\270\200\345\245\227\350\257\225\345\215\267", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        deleteCourseBtn->setText(QString());
        openPaperBtn->setText(QApplication::translate("CardCombineClass", "\346\211\223\345\274\200\350\257\225\345\215\267", 0, QApplication::UnicodeUTF8));
        savePaperBtn->setText(QApplication::translate("CardCombineClass", "\344\277\235\345\255\230\350\257\225\345\215\267", 0, QApplication::UnicodeUTF8));
        importPaperBtn->setText(QApplication::translate("CardCombineClass", "\345\257\274\345\207\272XML", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CardCombineClass: public Ui_CardCombineClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CARDSETDLG_H
