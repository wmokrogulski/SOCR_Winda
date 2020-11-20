/********************************************************************************
** Form generated from reading UI file 'RTOS_Elevatorrslvnp.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef RTOS_ELEVATORRSLVNP_H
#define RTOS_ELEVATORRSLVNP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RTOS_ElevatorClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RTOS_ElevatorClass)
    {
        if (RTOS_ElevatorClass->objectName().isEmpty())
            RTOS_ElevatorClass->setObjectName(QString::fromUtf8("RTOS_ElevatorClass"));
        RTOS_ElevatorClass->resize(600, 400);
        centralWidget = new QWidget(RTOS_ElevatorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1, Qt::AlignHCenter|Qt::AlignVCenter);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 1, 0, 1, 1);

        RTOS_ElevatorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RTOS_ElevatorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        RTOS_ElevatorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(RTOS_ElevatorClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        RTOS_ElevatorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(RTOS_ElevatorClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        RTOS_ElevatorClass->setStatusBar(statusBar);

        retranslateUi(RTOS_ElevatorClass);

        QMetaObject::connectSlotsByName(RTOS_ElevatorClass);
    } // setupUi

    void retranslateUi(QMainWindow *RTOS_ElevatorClass)
    {
        RTOS_ElevatorClass->setWindowTitle(QCoreApplication::translate("RTOS_ElevatorClass", "RTOS_Elevator", nullptr));
        label->setText(QCoreApplication::translate("RTOS_ElevatorClass", "Hello World!!!", nullptr));
        pushButton->setText(QCoreApplication::translate("RTOS_ElevatorClass", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RTOS_ElevatorClass: public Ui_RTOS_ElevatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // RTOS_ELEVATORRSLVNP_H
