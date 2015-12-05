/********************************************************************************
** Form generated from reading UI file 'AddCourseDlg.ui'
**
** Created: Mon Jun 30 09:41:39 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCOURSEDLG_H
#define UI_ADDCOURSEDLG_H

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

class Ui_AddCourseDlg
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *courseEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *AddCourseDlg)
    {
        if (AddCourseDlg->objectName().isEmpty())
            AddCourseDlg->setObjectName(QString::fromUtf8("AddCourseDlg"));
        AddCourseDlg->resize(311, 75);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AddCourseDlg->sizePolicy().hasHeightForWidth());
        AddCourseDlg->setSizePolicy(sizePolicy);
        AddCourseDlg->setMaximumSize(QSize(311, 75));
        gridLayout_2 = new QGridLayout(AddCourseDlg);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(AddCourseDlg);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        courseEdit = new QLineEdit(AddCourseDlg);
        courseEdit->setObjectName(QString::fromUtf8("courseEdit"));

        gridLayout->addWidget(courseEdit, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(128, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 0, 1, 1);

        okBtn = new QPushButton(AddCourseDlg);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));

        gridLayout_2->addWidget(okBtn, 1, 1, 1, 1);

        cancelBtn = new QPushButton(AddCourseDlg);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));

        gridLayout_2->addWidget(cancelBtn, 1, 2, 1, 1);


        retranslateUi(AddCourseDlg);

        QMetaObject::connectSlotsByName(AddCourseDlg);
    } // setupUi

    void retranslateUi(QDialog *AddCourseDlg)
    {
        AddCourseDlg->setWindowTitle(QApplication::translate("AddCourseDlg", "\346\267\273\345\212\240\347\247\221\347\233\256", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AddCourseDlg", "\347\247\221\347\233\256\345\220\215\347\247\260\357\274\232", 0, QApplication::UnicodeUTF8));
        okBtn->setText(QApplication::translate("AddCourseDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        cancelBtn->setText(QApplication::translate("AddCourseDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddCourseDlg: public Ui_AddCourseDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCOURSEDLG_H
