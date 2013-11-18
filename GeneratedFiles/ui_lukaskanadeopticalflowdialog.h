/********************************************************************************
** Form generated from reading UI file 'lukaskanadeopticalflowdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LUKASKANADEOPTICALFLOWDIALOG_H
#define UI_LUKASKANADEOPTICALFLOWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_LukasKanadeOpticalFLowDialog
{
public:
    QSlider *itersSlider;
    QSlider *winSizeSlider;
    QSlider *maxLevelSlider;
    QLabel *itersLabel;
    QLabel *winSizeLabel;
    QLabel *maxLevelLabel;
    QLabel *itersValueLabel;
    QLabel *winSizeValueLabel;
    QLabel *maxLevelValueLabel;

    void setupUi(QDialog *LukasKanadeOpticalFLowDialog)
    {
        if (LukasKanadeOpticalFLowDialog->objectName().isEmpty())
            LukasKanadeOpticalFLowDialog->setObjectName(QStringLiteral("LukasKanadeOpticalFLowDialog"));
        LukasKanadeOpticalFLowDialog->resize(404, 445);
        itersSlider = new QSlider(LukasKanadeOpticalFLowDialog);
        itersSlider->setObjectName(QStringLiteral("itersSlider"));
        itersSlider->setGeometry(QRect(80, 30, 261, 22));
        itersSlider->setMinimum(1);
        itersSlider->setMaximum(20);
        itersSlider->setValue(3);
        itersSlider->setOrientation(Qt::Horizontal);
        winSizeSlider = new QSlider(LukasKanadeOpticalFLowDialog);
        winSizeSlider->setObjectName(QStringLiteral("winSizeSlider"));
        winSizeSlider->setGeometry(QRect(80, 70, 261, 22));
        winSizeSlider->setMinimum(1);
        winSizeSlider->setMaximum(30);
        winSizeSlider->setValue(11);
        winSizeSlider->setOrientation(Qt::Horizontal);
        maxLevelSlider = new QSlider(LukasKanadeOpticalFLowDialog);
        maxLevelSlider->setObjectName(QStringLiteral("maxLevelSlider"));
        maxLevelSlider->setGeometry(QRect(80, 110, 261, 22));
        maxLevelSlider->setMinimum(1);
        maxLevelSlider->setMaximum(20);
        maxLevelSlider->setValue(4);
        maxLevelSlider->setOrientation(Qt::Horizontal);
        itersLabel = new QLabel(LukasKanadeOpticalFLowDialog);
        itersLabel->setObjectName(QStringLiteral("itersLabel"));
        itersLabel->setGeometry(QRect(20, 30, 46, 13));
        winSizeLabel = new QLabel(LukasKanadeOpticalFLowDialog);
        winSizeLabel->setObjectName(QStringLiteral("winSizeLabel"));
        winSizeLabel->setGeometry(QRect(20, 70, 46, 13));
        maxLevelLabel = new QLabel(LukasKanadeOpticalFLowDialog);
        maxLevelLabel->setObjectName(QStringLiteral("maxLevelLabel"));
        maxLevelLabel->setGeometry(QRect(20, 110, 46, 13));
        itersValueLabel = new QLabel(LukasKanadeOpticalFLowDialog);
        itersValueLabel->setObjectName(QStringLiteral("itersValueLabel"));
        itersValueLabel->setGeometry(QRect(350, 30, 46, 13));
        winSizeValueLabel = new QLabel(LukasKanadeOpticalFLowDialog);
        winSizeValueLabel->setObjectName(QStringLiteral("winSizeValueLabel"));
        winSizeValueLabel->setGeometry(QRect(350, 70, 46, 13));
        maxLevelValueLabel = new QLabel(LukasKanadeOpticalFLowDialog);
        maxLevelValueLabel->setObjectName(QStringLiteral("maxLevelValueLabel"));
        maxLevelValueLabel->setGeometry(QRect(350, 110, 46, 13));

        retranslateUi(LukasKanadeOpticalFLowDialog);
        QObject::connect(itersSlider, SIGNAL(valueChanged(int)), itersValueLabel, SLOT(setNum(int)));
        QObject::connect(maxLevelSlider, SIGNAL(valueChanged(int)), maxLevelValueLabel, SLOT(setNum(int)));
        QObject::connect(winSizeSlider, SIGNAL(valueChanged(int)), winSizeValueLabel, SLOT(setNum(int)));

        QMetaObject::connectSlotsByName(LukasKanadeOpticalFLowDialog);
    } // setupUi

    void retranslateUi(QDialog *LukasKanadeOpticalFLowDialog)
    {
        LukasKanadeOpticalFLowDialog->setWindowTitle(QApplication::translate("LukasKanadeOpticalFLowDialog", "LukasKanadeOpticalFLowDialog", 0));
        itersLabel->setText(QApplication::translate("LukasKanadeOpticalFLowDialog", "iters", 0));
        winSizeLabel->setText(QApplication::translate("LukasKanadeOpticalFLowDialog", "winSize", 0));
        maxLevelLabel->setText(QApplication::translate("LukasKanadeOpticalFLowDialog", "maxLevel", 0));
        itersValueLabel->setText(QApplication::translate("LukasKanadeOpticalFLowDialog", "3", 0));
        winSizeValueLabel->setText(QApplication::translate("LukasKanadeOpticalFLowDialog", "11", 0));
        maxLevelValueLabel->setText(QApplication::translate("LukasKanadeOpticalFLowDialog", "4", 0));
    } // retranslateUi

};

namespace Ui {
    class LukasKanadeOpticalFLowDialog: public Ui_LukasKanadeOpticalFLowDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LUKASKANADEOPTICALFLOWDIALOG_H
