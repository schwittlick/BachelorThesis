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
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LukasKanadeOpticalFLowDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *itersValueLabel;
    QLabel *itersLabel;
    QSlider *itersSlider;
    QLabel *maxLevelValueLabel;
    QLabel *maxLevelLabel;
    QSlider *maxLevelSlider;

    void setupUi(QDialog *LukasKanadeOpticalFLowDialog)
    {
        if (LukasKanadeOpticalFLowDialog->objectName().isEmpty())
            LukasKanadeOpticalFLowDialog->setObjectName(QStringLiteral("LukasKanadeOpticalFLowDialog"));
        LukasKanadeOpticalFLowDialog->resize(404, 144);
        verticalLayout = new QVBoxLayout(LukasKanadeOpticalFLowDialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        itersValueLabel = new QLabel(LukasKanadeOpticalFLowDialog);
        itersValueLabel->setObjectName(QStringLiteral("itersValueLabel"));

        verticalLayout->addWidget(itersValueLabel);

        itersLabel = new QLabel(LukasKanadeOpticalFLowDialog);
        itersLabel->setObjectName(QStringLiteral("itersLabel"));

        verticalLayout->addWidget(itersLabel);

        itersSlider = new QSlider(LukasKanadeOpticalFLowDialog);
        itersSlider->setObjectName(QStringLiteral("itersSlider"));
        itersSlider->setMinimum(1);
        itersSlider->setMaximum(20);
        itersSlider->setValue(3);
        itersSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(itersSlider);

        maxLevelValueLabel = new QLabel(LukasKanadeOpticalFLowDialog);
        maxLevelValueLabel->setObjectName(QStringLiteral("maxLevelValueLabel"));

        verticalLayout->addWidget(maxLevelValueLabel);

        maxLevelLabel = new QLabel(LukasKanadeOpticalFLowDialog);
        maxLevelLabel->setObjectName(QStringLiteral("maxLevelLabel"));

        verticalLayout->addWidget(maxLevelLabel);

        maxLevelSlider = new QSlider(LukasKanadeOpticalFLowDialog);
        maxLevelSlider->setObjectName(QStringLiteral("maxLevelSlider"));
        maxLevelSlider->setMinimum(1);
        maxLevelSlider->setMaximum(20);
        maxLevelSlider->setValue(4);
        maxLevelSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(maxLevelSlider);


        retranslateUi(LukasKanadeOpticalFLowDialog);
        QObject::connect(itersSlider, SIGNAL(valueChanged(int)), itersValueLabel, SLOT(setNum(int)));
        QObject::connect(maxLevelSlider, SIGNAL(valueChanged(int)), maxLevelValueLabel, SLOT(setNum(int)));

        QMetaObject::connectSlotsByName(LukasKanadeOpticalFLowDialog);
    } // setupUi

    void retranslateUi(QDialog *LukasKanadeOpticalFLowDialog)
    {
        LukasKanadeOpticalFLowDialog->setWindowTitle(QApplication::translate("LukasKanadeOpticalFLowDialog", "LukasKanadeOpticalFLowDialog", 0));
        itersValueLabel->setText(QApplication::translate("LukasKanadeOpticalFLowDialog", "3", 0));
        itersLabel->setText(QApplication::translate("LukasKanadeOpticalFLowDialog", "iters", 0));
        maxLevelValueLabel->setText(QApplication::translate("LukasKanadeOpticalFLowDialog", "4", 0));
        maxLevelLabel->setText(QApplication::translate("LukasKanadeOpticalFLowDialog", "maxLevel", 0));
    } // retranslateUi

};

namespace Ui {
    class LukasKanadeOpticalFLowDialog: public Ui_LukasKanadeOpticalFLowDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LUKASKANADEOPTICALFLOWDIALOG_H
