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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BachelorThesisClass
{
public:
    QAction *actionOpen_File;
    QAction *actionExit;
    QWidget *centralWidget;
    QLabel *label;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BachelorThesisClass)
    {
        if (BachelorThesisClass->objectName().isEmpty())
            BachelorThesisClass->setObjectName(QStringLiteral("BachelorThesisClass"));
        BachelorThesisClass->resize(294, 559);
        actionOpen_File = new QAction(BachelorThesisClass);
        actionOpen_File->setObjectName(QStringLiteral("actionOpen_File"));
        actionExit = new QAction(BachelorThesisClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(BachelorThesisClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 261, 16));
        BachelorThesisClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BachelorThesisClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 294, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
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
        menuFile->addSeparator();
        menuFile->addAction(actionExit);

        retranslateUi(BachelorThesisClass);

        QMetaObject::connectSlotsByName(BachelorThesisClass);
    } // setupUi

    void retranslateUi(QMainWindow *BachelorThesisClass)
    {
        BachelorThesisClass->setWindowTitle(QApplication::translate("BachelorThesisClass", "BachelorThesis", 0));
        actionOpen_File->setText(QApplication::translate("BachelorThesisClass", "Open File.", 0));
        actionExit->setText(QApplication::translate("BachelorThesisClass", "Exit", 0));
        label->setText(QApplication::translate("BachelorThesisClass", "No File loaded.", 0));
        menuFile->setTitle(QApplication::translate("BachelorThesisClass", "File", 0));
        menuEdit->setTitle(QApplication::translate("BachelorThesisClass", "Edit", 0));
        menuHelp->setTitle(QApplication::translate("BachelorThesisClass", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class BachelorThesisClass: public Ui_BachelorThesisClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACHELORTHESIS_H
