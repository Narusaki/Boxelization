/********************************************************************************
** Form generated from reading UI file 'boxelization.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOXELIZATION_H
#define UI_BOXELIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BoxelizationClass
{
public:
    QAction *actionImport;
    QAction *actionLoad_Connectivity;
    QAction *actionLoad_Path;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BoxelizationClass)
    {
        if (BoxelizationClass->objectName().isEmpty())
            BoxelizationClass->setObjectName(QStringLiteral("BoxelizationClass"));
        BoxelizationClass->resize(1366, 768);
        actionImport = new QAction(BoxelizationClass);
        actionImport->setObjectName(QStringLiteral("actionImport"));
        actionLoad_Connectivity = new QAction(BoxelizationClass);
        actionLoad_Connectivity->setObjectName(QStringLiteral("actionLoad_Connectivity"));
        actionLoad_Path = new QAction(BoxelizationClass);
        actionLoad_Path->setObjectName(QStringLiteral("actionLoad_Path"));
        centralWidget = new QWidget(BoxelizationClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        BoxelizationClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BoxelizationClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1366, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        BoxelizationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BoxelizationClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BoxelizationClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BoxelizationClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BoxelizationClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionImport);
        menuFile->addAction(actionLoad_Connectivity);
        menuFile->addAction(actionLoad_Path);

        retranslateUi(BoxelizationClass);

        QMetaObject::connectSlotsByName(BoxelizationClass);
    } // setupUi

    void retranslateUi(QMainWindow *BoxelizationClass)
    {
        BoxelizationClass->setWindowTitle(QApplication::translate("BoxelizationClass", "Boxelization", 0));
        actionImport->setText(QApplication::translate("BoxelizationClass", "Import Cubes", 0));
        actionLoad_Connectivity->setText(QApplication::translate("BoxelizationClass", "Load Connectivity", 0));
        actionLoad_Path->setText(QApplication::translate("BoxelizationClass", "Load Path", 0));
        menuFile->setTitle(QApplication::translate("BoxelizationClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class BoxelizationClass: public Ui_BoxelizationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOXELIZATION_H
