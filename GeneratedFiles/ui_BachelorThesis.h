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
#include <QtWidgets/QVBoxLayout>
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
    QAction *actionHardware_Info;
    QAction *actionProcesingPipeline;
    QAction *actionOpen_Video_Stream;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSlider *verticalSlider;
    QLabel *label_2;
    QLabel *videoLabel;
    QPushButton *pushButton;
    QSlider *blurSlider;
    QSlider *progressBarSlider;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuOptical_Flow;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BachelorThesisClass)
    {
        if (BachelorThesisClass->objectName().isEmpty())
            BachelorThesisClass->setObjectName(QStringLiteral("BachelorThesisClass"));
        BachelorThesisClass->resize(837, 905);
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
        actionHardware_Info = new QAction(BachelorThesisClass);
        actionHardware_Info->setObjectName(QStringLiteral("actionHardware_Info"));
        actionProcesingPipeline = new QAction(BachelorThesisClass);
        actionProcesingPipeline->setObjectName(QStringLiteral("actionProcesingPipeline"));
        actionOpen_Video_Stream = new QAction(BachelorThesisClass);
        actionOpen_Video_Stream->setObjectName(QStringLiteral("actionOpen_Video_Stream"));
        centralWidget = new QWidget(BachelorThesisClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        verticalSlider = new QSlider(centralWidget);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setMinimum(1);
        verticalSlider->setMaximum(20);
        verticalSlider->setOrientation(Qt::Vertical);
        verticalSlider->setTickInterval(1);

        verticalLayout->addWidget(verticalSlider);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        videoLabel = new QLabel(centralWidget);
        videoLabel->setObjectName(QStringLiteral("videoLabel"));
        videoLabel->setMinimumSize(QSize(720, 576));
        videoLabel->setBaseSize(QSize(720, 675));
        videoLabel->setCursor(QCursor(Qt::CrossCursor));
        videoLabel->setMouseTracking(true);

        verticalLayout->addWidget(videoLabel);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        blurSlider = new QSlider(centralWidget);
        blurSlider->setObjectName(QStringLiteral("blurSlider"));
        blurSlider->setMaximum(20);
        blurSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(blurSlider);

        progressBarSlider = new QSlider(centralWidget);
        progressBarSlider->setObjectName(QStringLiteral("progressBarSlider"));
        progressBarSlider->setMaximum(1);
        progressBarSlider->setSingleStep(1);
        progressBarSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(progressBarSlider);

        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        verticalLayout->addWidget(checkBox);

        checkBox_2 = new QCheckBox(centralWidget);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));

        verticalLayout->addWidget(checkBox_2);

        BachelorThesisClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BachelorThesisClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 837, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuOptical_Flow = new QMenu(menuEdit);
        menuOptical_Flow->setObjectName(QStringLiteral("menuOptical_Flow"));
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
        menuFile->addAction(actionOpen_Video_Stream);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuEdit->addAction(menuOptical_Flow->menuAction());
        menuEdit->addAction(actionProcesingPipeline);
        menuOptical_Flow->addAction(actionPyrLukasKanade);
        menuOptical_Flow->addAction(actionFarneback);
        menuOptical_Flow->addAction(actionBrox);
        menuHelp->addAction(actionHardware_Info);

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
        actionHardware_Info->setText(QApplication::translate("BachelorThesisClass", "Hardware Info", 0));
        actionProcesingPipeline->setText(QApplication::translate("BachelorThesisClass", "ProcesingPipeline", 0));
        actionOpen_Video_Stream->setText(QApplication::translate("BachelorThesisClass", "Open Video Stream", 0));
        label->setText(QApplication::translate("BachelorThesisClass", "No File loaded.", 0));
        label_2->setText(QApplication::translate("BachelorThesisClass", "Blur Amount", 0));
        videoLabel->setText(QApplication::translate("BachelorThesisClass", "TextLabel", 0));
        pushButton->setText(QApplication::translate("BachelorThesisClass", "Play", 0));
        checkBox->setText(QApplication::translate("BachelorThesisClass", "Background Subtraction", 0));
        checkBox_2->setText(QApplication::translate("BachelorThesisClass", "Meanshift Filtering", 0));
        menuFile->setTitle(QApplication::translate("BachelorThesisClass", "File", 0));
        menuEdit->setTitle(QApplication::translate("BachelorThesisClass", "Edit", 0));
        menuOptical_Flow->setTitle(QApplication::translate("BachelorThesisClass", "Optical Flow", 0));
        menuHelp->setTitle(QApplication::translate("BachelorThesisClass", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class BachelorThesisClass: public Ui_BachelorThesisClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACHELORTHESIS_H
