/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *sidePanel;
    QLabel *logoLabel;
    QLabel *paramsLabel;
    QLabel *toLabel;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(812, 697);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: #07090f;\n"
"    color: #dde3f0;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        sidePanel = new QWidget(centralwidget);
        sidePanel->setObjectName("sidePanel");
        sidePanel->setGeometry(QRect(0, 0, 500, 900));
        sidePanel->setStyleSheet(QString::fromUtf8("background-color: #0d1018;\n"
"border-right: 1px solid rgba(255,255,255,0.06);"));
        logoLabel = new QLabel(centralwidget);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setGeometry(QRect(20, 18, 280, 30));
        logoLabel->setStyleSheet(QString::fromUtf8("color: #3d7bff;\n"
"font-size: 18px;\n"
"font-weight: 800;\n"
"background: transparent;"));
        paramsLabel = new QLabel(centralwidget);
        paramsLabel->setObjectName("paramsLabel");
        paramsLabel->setGeometry(QRect(20, 55, 250, 16));
        paramsLabel->setStyleSheet(QString::fromUtf8("color: #3e4560;\n"
"font-size: 10px;\n"
"font-weight: 700;\n"
"background: transparent;\n"
"letter-spacing: 1px;"));
        toLabel = new QLabel(centralwidget);
        toLabel->setObjectName("toLabel");
        toLabel->setGeometry(QRect(20, 155, 100, 16));
        toLabel->setStyleSheet(QString::fromUtf8("color: #3e4560;\n"
"font-size: 10px;\n"
"font-weight: 700;\n"
"background: transparent;"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 812, 21));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        logoLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\227\272 RouteBuilder", nullptr));
        paramsLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\320\220\320\240\320\220\320\234\320\225\320\242\320\240\320\253 \320\234\320\220\320\240\320\250\320\240\320\243\320\242\320\220", nullptr));
        toLabel->setText(QCoreApplication::translate("MainWindow", "\320\232\320\243\320\224\320\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
