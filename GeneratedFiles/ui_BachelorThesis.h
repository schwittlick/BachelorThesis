/********************************************************************************
** Form generated from reading UI file 'BachelorThesis.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BACHELORTHESIS_H
#define UI_BACHELORTHESIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BachelorThesisClass
{
public:
    QAction *actionOpen_File;
    QAction *actionExit;
    QAction *actionVerticalSlider;
    QAction *actionPyrLukasKanade;
    QAction *actionFarneback;
    QAction *actionBrox;
    QAction *actionMOG;
    QAction *actionMOG2;
    QAction *actionGMG;
    QAction *actionFGD;
    QAction *actionGaussian_Blur;
    QAction *actionMedian_Blur;
    QAction *actionNormal_Blur;
    QAction *actionOpen_Sample;
    QWidget *centralWidget;
    QLabel *label;
    QSlider *verticalSlider;
    QPushButton *pushButton;
    QSlider *progressBarSlider;
    QSlider *blurSlider;
    QLabel *label_2;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuOptical_Flow;
    QMenu *menuImage_Processing;
    QMenu *menuBackground_Subtraction;
    QMenu *menuBlur;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BachelorThesisClass)
    {
        if (BachelorThesisClass->objectName().isEmpty())
            BachelorThesisClass->setObjectName(QStringLiteral("BachelorThesisClass"));
        BachelorThesisClass->resize(477, 559);
        actionOpen_File = new QAction(BachelorThesisClass);
        actionOpen_File->setObjectName(QStringLiteral("actionOpen_File"));
        actionExit = new QAction(BachelorThesisClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionVerticalSlider = new QAction(BachelorThesisClass);
        actionVerticalSlider->setObjectName(QStringLiteral("actionVerticalSlider"));
        actionVerticalSlider->setCheckable(true);
        actionPyrLukasKanade = new QAction(BachelorThesisClass);
        actionPyrLukasKanade->setObjectName(QStringLiteral("actionPyrLukasKanade"));
        actionFarneback = new QAction(BachelorThesisClass);
        actionFarneback->setObjectName(QStringLiteral("actionFarneback"));
        actionBrox = new QAction(BachelorThesisClass);
        actionBrox->setObjectName(QStringLiteral("actionBrox"));
        actionMOG = new QAction(BachelorThesisClass);
        actionMOG->setObjectName(QStringLiteral("actionMOG"));
        actionMOG2 = new QAction(BachelorThesisClass);
        actionMOG2->setObjectName(QStringLiteral("actionMOG2"));
        actionGMG = new QAction(BachelorThesisClass);
        actionGMG->setObjectName(QStringLiteral("actionGMG"));
        actionFGD = new QAction(BachelorThesisClass);
        actionFGD->setObjectName(QStringLiteral("actionFGD"));
        actionGaussian_Blur = new QAction(BachelorThesisClass);
        actionGaussian_Blur->setObjectName(QStringLiteral("actionGaussian_Blur"));
        actionMedian_Blur = new QAction(BachelorThesisClass);
        actionMedian_Blur->setObjectName(QStringLiteral("actionMedian_Blur"));
        actionNormal_Blur = new QAction(BachelorThesisClass);
        actionNormal_Blur->setObjectName(QStringLiteral("actionNormal_Blur"));
        actionOpen_Sample = new QAction(BachelorThesisClass);
        actionOpen_Sample->setObjectName(QStringLiteral("actionOpen_Sample"));
        centralWidget = new QWidget(BachelorThesisClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 20, 81, 16));
        verticalSlider = new QSlider(centralWidget);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setGeometry(QRect(420, 40, 22, 151));
        verticalSlider->setMinimum(1);
        verticalSlider->setMaximum(20);
        verticalSlider->setOrientation(Qt::Vertical);
        verticalSlider->setTickInterval(1);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(40, 40, 75, 23));
        progressBarSlider = new QSlider(centralWidget);
        progressBarSlider->setObjectName(QStringLiteral("progressBarSlider"));
        progressBarSlider->setGeometry(QRect(10, 460, 441, 22));
        progressBarSlider->setMaximum(1);
        progressBarSlider->setSingleStep(1);
        progressBarSlider->setOrientation(Qt::Horizontal);
        blurSlider = new QSlider(centralWidget);
        blurSlider->setObjectName(QStringLiteral("blurSlider"));
        blurSlider->setGeometry(QRect(50, 130, 160, 22));
        blurSlider->setMaximum(20);
        blurSlider->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 100, 81, 16));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(200, 80, 161, 17));
        checkBox_2 = new QCheckBox(centralWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(200, 100, 141, 17));
        BachelorThesisClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BachelorThesisClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 477, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuOptical_Flow = new QMenu(menuEdit);
        menuOptical_Flow->setObjectName(QStringLiteral("menuOptical_Flow"));
        menuImage_Processing = new QMenu(menuEdit);
        menuImage_Processing->setObjectName(QStringLiteral("menuImage_Processing"));
        menuBackground_Subtraction = new QMenu(menuImage_Processing);
        menuBackground_Subtraction->setObjectName(QStringLiteral("menuBackground_Subtraction"));
        menuBlur = new QMenu(menuImage_Processing);
        menuBlur->setObjectName(QStringLiteral("menuBlur"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        BachelorThesisClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BachelorThesisClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BachelorThesisClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BachelorThesisClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BachelorThesisClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen_File);
        menuFile->addAction(actionOpen_Sample);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuEdit->addAction(menuOptical_Flow->menuAction());
        menuEdit->addAction(menuImage_Processing->menuAction());
        menuOptical_Flow->addAction(actionPyrLukasKanade);
        menuOptical_Flow->addAction(actionFarneback);
        menuOptical_Flow->addAction(actionBrox);
        menuImage_Processing->addAction(menuBackground_Subtraction->menuAction());
        menuImage_Processing->addAction(menuBlur->menuAction());
        menuBackground_Subtraction->addAction(actionMOG);
        menuBackground_Subtraction->addAction(actionMOG2);
        menuBackground_Subtraction->addAction(actionGMG);
        menuBackground_Subtraction->addAction(actionFGD);
        menuBlur->addAction(actionGaussian_Blur);
        menuBlur->addAction(actionMedian_Blur);
        menuBlur->addAction(actionNormal_Blur);

        retranslateUi(BachelorThesisClass);

        QMetaObject::connectSlotsByName(BachelorThesisClass);
    } // setupUi

    void retranslateUi(QMainWindow *BachelorThesisClass)
    {
        BachelorThesisClass->setWindowTitle(QApplication::translate("BachelorThesisClass", "BachelorThesis", 0));
        actionOpen_File->setText(QApplication::translate("BachelorThesisClass", "Open File.", 0));
        actionExit->setText(QApplication::translate("BachelorThesisClass", "Exit", 0));
        actionVerticalSlider->setText(QApplication::translate("BachelorThesisClass", "verticalSlider", 0));
        actionPyrLukasKanade->setText(QApplication::translate("BachelorThesisClass", "PyrLukasKanade", 0));
        actionFarneback->setText(QApplication::translate("BachelorThesisClass", "Farneback", 0));
        actionBrox->setText(QApplication::translate("BachelorThesisClass", "Brox", 0));
        actionMOG->setText(QApplication::translate("BachelorThesisClass", "MOG", 0));
        actionMOG2->setText(QApplication::translate("BachelorThesisClass", "MOG2", 0));
        actionGMG->setText(QApplication::translate("BachelorThesisClass", "GMG", 0));
        actionFGD->setText(QApplication::translate("BachelorThesisClass", "FGD", 0));
        actionGaussian_Blur->setText(QApplication::translate("BachelorThesisClass", "Gaussian Blur", 0));
        actionMedian_Blur->setText(QApplication::translate("BachelorThesisClass", "Median Blur", 0));
        actionNormal_Blur->setText(QApplication::translate("BachelorThesisClass", "Normal Blur", 0));
        actionOpen_Sample->setText(QApplication::translate("BachelorThesisClass", "Open Sample", 0));
        label->setText(QApplication::translate("BachelorThesisClass", "No File loaded.", 0));
        pushButton->setText(QApplication::translate("BachelorThesisClass", "Play", 0));
        label_2->setText(QApplication::translate("BachelorThesisClass", "Blur Amount", 0));
        checkBox->setText(QApplication::translate("BachelorThesisClass", "Background Subtraction", 0));
        checkBox_2->setText(QApplication::translate("BachelorThesisClass", "Meanshift Filtering", 0));
        menuFile->setTitle(QApplication::translate("BachelorThesisClass", "File", 0));
        menuEdit->setTitle(QApplication::translate("BachelorThesisClass", "Edit", 0));
        menuOptical_Flow->setTitle(QApplication::translate("BachelorThesisClass", "Optical Flow", 0));
        menuImage_Processing->setTitle(QApplication::translate("BachelorThesisClass", "Image Processing", 0));
        menuBackground_Subtraction->setTitle(QApplication::translate("BachelorThesisClass", "Background Subtraction", 0));
        menuBlur->setTitle(QApplication::translate("BachelorThesisClass", "Blur", 0));
        menuHelp->setTitle(QApplication::translate("BachelorThesisClass", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class BachelorThesisClass: public Ui_BachelorThesisClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACHELORTHESIS_H
