/********************************************************************************
** Form generated from reading UI file 'MarkerDlg.ui'
**
** Created: Mon Jun 30 09:41:39 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MARKERDLG_H
#define UI_MARKERDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_MarkerDlg
{
public:
    QGridLayout *mainGridLayout;
    QGroupBox *markerGroupBox;
    QGridLayout *groupGridLayout;
    QLabel *label;
    QGridLayout *gridLayout;
    QPushButton *horMarkersBtn;
    QPushButton *verMarkersBtn;
    QLineEdit *horMarkersEdit;
    QLineEdit *verMarkersEdit;
    QPushButton *confirmBtn;

    void setupUi(QDialog *MarkerDlg)
    {
        if (MarkerDlg->objectName().isEmpty())
            MarkerDlg->setObjectName(QString::fromUtf8("MarkerDlg"));
        MarkerDlg->resize(238, 151);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MarkerDlg->sizePolicy().hasHeightForWidth());
        MarkerDlg->setSizePolicy(sizePolicy);
        mainGridLayout = new QGridLayout(MarkerDlg);
        mainGridLayout->setSpacing(6);
        mainGridLayout->setContentsMargins(11, 11, 11, 11);
        mainGridLayout->setObjectName(QString::fromUtf8("mainGridLayout"));
        mainGridLayout->setContentsMargins(-1, 2, -1, 6);
        markerGroupBox = new QGroupBox(MarkerDlg);
        markerGroupBox->setObjectName(QString::fromUtf8("markerGroupBox"));
        groupGridLayout = new QGridLayout(markerGroupBox);
        groupGridLayout->setSpacing(6);
        groupGridLayout->setContentsMargins(11, 11, 11, 11);
        groupGridLayout->setObjectName(QString::fromUtf8("groupGridLayout"));
        label = new QLabel(markerGroupBox);
        label->setObjectName(QString::fromUtf8("label"));

        groupGridLayout->addWidget(label, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, -1, -1, -1);
        horMarkersBtn = new QPushButton(markerGroupBox);
        horMarkersBtn->setObjectName(QString::fromUtf8("horMarkersBtn"));
        horMarkersBtn->setMinimumSize(QSize(100, 25));

        gridLayout->addWidget(horMarkersBtn, 0, 0, 1, 1);

        verMarkersBtn = new QPushButton(markerGroupBox);
        verMarkersBtn->setObjectName(QString::fromUtf8("verMarkersBtn"));
        verMarkersBtn->setMinimumSize(QSize(100, 25));

        gridLayout->addWidget(verMarkersBtn, 1, 0, 1, 1);

        horMarkersEdit = new QLineEdit(markerGroupBox);
        horMarkersEdit->setObjectName(QString::fromUtf8("horMarkersEdit"));
        horMarkersEdit->setEnabled(true);
        horMarkersEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(horMarkersEdit, 0, 1, 1, 1);

        verMarkersEdit = new QLineEdit(markerGroupBox);
        verMarkersEdit->setObjectName(QString::fromUtf8("verMarkersEdit"));
        verMarkersEdit->setEnabled(true);
        verMarkersEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(verMarkersEdit, 1, 1, 1, 1);


        groupGridLayout->addLayout(gridLayout, 1, 0, 1, 1);

        confirmBtn = new QPushButton(markerGroupBox);
        confirmBtn->setObjectName(QString::fromUtf8("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(0, 28));

        groupGridLayout->addWidget(confirmBtn, 2, 0, 1, 1);


        mainGridLayout->addWidget(markerGroupBox, 0, 0, 1, 1);

        QWidget::setTabOrder(horMarkersBtn, horMarkersEdit);
        QWidget::setTabOrder(horMarkersEdit, verMarkersBtn);
        QWidget::setTabOrder(verMarkersBtn, verMarkersEdit);
        QWidget::setTabOrder(verMarkersEdit, confirmBtn);

        retranslateUi(MarkerDlg);

        QMetaObject::connectSlotsByName(MarkerDlg);
    } // setupUi

    void retranslateUi(QDialog *MarkerDlg)
    {
        MarkerDlg->setWindowTitle(QApplication::translate("MarkerDlg", "\346\240\207\350\256\260\347\202\271\345\256\232\344\275\215", 0, QApplication::UnicodeUTF8));
        markerGroupBox->setTitle(QApplication::translate("MarkerDlg", "\346\240\207\350\256\260\347\202\271\345\256\232\344\275\215", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MarkerDlg", "\347\202\271\345\207\273\344\270\213\351\235\242\346\214\211\351\222\256\346\241\206\351\200\211\345\220\204\347\273\204\346\240\207\350\256\260\347\202\271", 0, QApplication::UnicodeUTF8));
        horMarkersBtn->setText(QApplication::translate("MarkerDlg", "\346\260\264\345\271\263\346\240\207\350\256\260\347\202\271\347\273\204", 0, QApplication::UnicodeUTF8));
        verMarkersBtn->setText(QApplication::translate("MarkerDlg", "\345\236\202\347\233\264\346\240\207\350\256\260\347\202\271\347\273\204", 0, QApplication::UnicodeUTF8));
        confirmBtn->setText(QApplication::translate("MarkerDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MarkerDlg: public Ui_MarkerDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MARKERDLG_H
