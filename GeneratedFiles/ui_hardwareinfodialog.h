/********************************************************************************
** Form generated from reading UI file 'hardwareinfodialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HARDWAREINFODIALOG_H
#define UI_HARDWAREINFODIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_HardwareInfoDialog
{
public:
    QLabel *label;
    QLabel *usedMemoryLabel;
    QLabel *label_2;
    QProgressBar *usedMemoryProgressBar;
    QPushButton *closeButton;
    QLabel *labelGraphics;
    QLabel *totalMemoryLabel;
    QLabel *label_3;

    void setupUi(QDialog *HardwareInfoDialog)
    {
        if (HardwareInfoDialog->objectName().isEmpty())
            HardwareInfoDialog->setObjectName(QStringLiteral("HardwareInfoDialog"));
        HardwareInfoDialog->resize(295, 234);
        label = new QLabel(HardwareInfoDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(9, 9, 71, 16));
        usedMemoryLabel = new QLabel(HardwareInfoDialog);
        usedMemoryLabel->setObjectName(QStringLiteral("usedMemoryLabel"));
        usedMemoryLabel->setGeometry(QRect(90, 140, 51, 16));
        label_2 = new QLabel(HardwareInfoDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(9, 142, 69, 16));
        usedMemoryProgressBar = new QProgressBar(HardwareInfoDialog);
        usedMemoryProgressBar->setObjectName(QStringLiteral("usedMemoryProgressBar"));
        usedMemoryProgressBar->setGeometry(QRect(9, 175, 271, 21));
        usedMemoryProgressBar->setValue(0);
        closeButton = new QPushButton(HardwareInfoDialog);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        closeButton->setGeometry(QRect(9, 202, 75, 23));
        labelGraphics = new QLabel(HardwareInfoDialog);
        labelGraphics->setObjectName(QStringLiteral("labelGraphics"));
        labelGraphics->setGeometry(QRect(10, 30, 171, 16));
        totalMemoryLabel = new QLabel(HardwareInfoDialog);
        totalMemoryLabel->setObjectName(QStringLiteral("totalMemoryLabel"));
        totalMemoryLabel->setGeometry(QRect(170, 140, 81, 16));
        label_3 = new QLabel(HardwareInfoDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(140, 140, 16, 16));

        retranslateUi(HardwareInfoDialog);
        QObject::connect(closeButton, SIGNAL(clicked()), HardwareInfoDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(HardwareInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *HardwareInfoDialog)
    {
        HardwareInfoDialog->setWindowTitle(QApplication::translate("HardwareInfoDialog", "HardwareInfoDialog", 0));
        label->setText(QApplication::translate("HardwareInfoDialog", "Graphics Card:", 0));
        usedMemoryLabel->setText(QApplication::translate("HardwareInfoDialog", "used", 0));
        label_2->setText(QApplication::translate("HardwareInfoDialog", "Used memory:", 0));
        closeButton->setText(QApplication::translate("HardwareInfoDialog", "Close", 0));
        labelGraphics->setText(QString());
        totalMemoryLabel->setText(QApplication::translate("HardwareInfoDialog", "total", 0));
        label_3->setText(QApplication::translate("HardwareInfoDialog", "/", 0));
    } // retranslateUi

};

namespace Ui {
    class HardwareInfoDialog: public Ui_HardwareInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HARDWAREINFODIALOG_H
