/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "coordinatesystem.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *y1;
    QLineEdit *x1;
    QLineEdit *x3;
    QLineEdit *y2;
    QPushButton *pushButton_Draw;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *x2;
    QLineEdit *y3;
    CoordinateSystem *widget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(678, 466);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setEnabled(true);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        y1 = new QLineEdit(groupBox);
        y1->setObjectName("y1");

        gridLayout->addWidget(y1, 2, 2, 1, 1);

        x1 = new QLineEdit(groupBox);
        x1->setObjectName("x1");

        gridLayout->addWidget(x1, 1, 2, 1, 1);

        x3 = new QLineEdit(groupBox);
        x3->setObjectName("x3");

        gridLayout->addWidget(x3, 1, 4, 1, 1);

        y2 = new QLineEdit(groupBox);
        y2->setObjectName("y2");

        gridLayout->addWidget(y2, 2, 3, 1, 1);

        pushButton_Draw = new QPushButton(groupBox);
        pushButton_Draw->setObjectName("pushButton_Draw");

        gridLayout->addWidget(pushButton_Draw, 1, 0, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 2, 1, 1, 1);

        x2 = new QLineEdit(groupBox);
        x2->setObjectName("x2");

        gridLayout->addWidget(x2, 1, 3, 1, 1);

        y3 = new QLineEdit(groupBox);
        y3->setObjectName("y3");

        gridLayout->addWidget(y3, 2, 4, 1, 1);

        widget = new CoordinateSystem(groupBox);
        widget->setObjectName("widget");

        gridLayout->addWidget(widget, 0, 0, 1, 5);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 678, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_Draw->setText(QCoreApplication::translate("MainWindow", "Draw", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
