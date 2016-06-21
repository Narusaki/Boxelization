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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BoxelizationClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BoxelizationClass)
    {
        if (BoxelizationClass->objectName().isEmpty())
            BoxelizationClass->setObjectName(QStringLiteral("BoxelizationClass"));
        BoxelizationClass->resize(600, 400);
        menuBar = new QMenuBar(BoxelizationClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        BoxelizationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BoxelizationClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BoxelizationClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(BoxelizationClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        BoxelizationClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(BoxelizationClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BoxelizationClass->setStatusBar(statusBar);

        retranslateUi(BoxelizationClass);

        QMetaObject::connectSlotsByName(BoxelizationClass);
    } // setupUi

    void retranslateUi(QMainWindow *BoxelizationClass)
    {
        BoxelizationClass->setWindowTitle(QApplication::translate("BoxelizationClass", "Boxelization", 0));
    } // retranslateUi

};

namespace Ui {
    class BoxelizationClass: public Ui_BoxelizationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOXELIZATION_H
