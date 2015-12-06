/********************************************************************************
** Form generated from reading UI file 'CreateCardDlg.ui'
**
** Created: Mon Apr 14 15:53:53 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATECARDDLG_H
#define UI_CREATECARDDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_CreateCardDlg
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *okBtn;
    QPushButton *cancelBtn;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *dpiEdit;

    void setupUi(QDialog *CreateCardDlg)
    {
        if (CreateCardDlg->objectName().isEmpty())
            CreateCardDlg->setObjectName(QString::fromUtf8("CreateCardDlg"));
        CreateCardDlg->resize(344, 87);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CreateCardDlg->sizePolicy().hasHeightForWidth());
        CreateCardDlg->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(CreateCardDlg);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(CreateCardDlg);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(161, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        okBtn = new QPushButton(CreateCardDlg);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));

        gridLayout->addWidget(okBtn, 2, 1, 1, 1);

        cancelBtn = new QPushButton(CreateCardDlg);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));

        gridLayout->addWidget(cancelBtn, 2, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(CreateCardDlg);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        dpiEdit = new QLineEdit(CreateCardDlg);
        dpiEdit->setObjectName(QString::fromUtf8("dpiEdit"));
        dpiEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(dpiEdit);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 3);


        retranslateUi(CreateCardDlg);
        QObject::connect(cancelBtn, SIGNAL(clicked()), CreateCardDlg, SLOT(close()));

        QMetaObject::connectSlotsByName(CreateCardDlg);
    } // setupUi

    void retranslateUi(QDialog *CreateCardDlg)
    {
        CreateCardDlg->setWindowTitle(QApplication::translate("CreateCardDlg", "\345\210\233\345\273\272\345\245\227\345\215\241", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CreateCardDlg", "\345\210\233\345\273\272\346\226\260\347\232\204\345\245\227\345\215\241\357\274\232", 0, QApplication::UnicodeUTF8));
        okBtn->setText(QApplication::translate("CreateCardDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        cancelBtn->setText(QApplication::translate("CreateCardDlg", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CreateCardDlg", "\345\233\276\345\275\242\345\210\206\350\276\250\347\216\207(dpi)", 0, QApplication::UnicodeUTF8));
        dpiEdit->setText(QApplication::translate("CreateCardDlg", "0", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CreateCardDlg: public Ui_CreateCardDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATECARDDLG_H
