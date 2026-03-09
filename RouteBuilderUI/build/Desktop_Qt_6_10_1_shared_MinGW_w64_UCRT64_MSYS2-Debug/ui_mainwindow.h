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
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *sidePanel;
    QLabel *logoLabel;
    QLabel *paramsLabel;
    QLabel *fromLabel;
    QLineEdit *fromInput;
    QLabel *toLabel;
    QLineEdit *toInput;
    QLabel *dateLabel;
    QDateEdit *dateEdit;
    QLabel *routeTypeLabel;
    QPushButton *directBtn;
    QPushButton *allRoutesBtn;
    QPushButton *searchBtn;
    QLabel *resultsLabel;
    QListWidget *resultsList;
    QWidget *rightPanel;
    QLabel *routeInfoLabel;
    QLabel *dateInfoLabel;
    QLabel *mapPlaceholder;
    QLabel *distLabel;
    QLabel *foundLabel;
    QLabel *directCountLabel;
    QLabel *transferCountLabel;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(812, 697);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget { background-color: #07090f; color: #dde3f0; }"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        sidePanel = new QWidget(centralwidget);
        sidePanel->setObjectName("sidePanel");
        sidePanel->setGeometry(QRect(0, 0, 500, 900));
        sidePanel->setStyleSheet(QString::fromUtf8("background-color: #0d1018; border-right: 1px solid rgba(255,255,255,0.06);"));
        logoLabel = new QLabel(centralwidget);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setGeometry(QRect(20, 18, 280, 30));
        logoLabel->setStyleSheet(QString::fromUtf8("color: #3d7bff; font-size: 18px; font-weight: 800; background: transparent;"));
        paramsLabel = new QLabel(centralwidget);
        paramsLabel->setObjectName("paramsLabel");
        paramsLabel->setGeometry(QRect(20, 55, 250, 16));
        paramsLabel->setStyleSheet(QString::fromUtf8("color: #3e4560; font-size: 10px; font-weight: 700; background: transparent;"));
        fromLabel = new QLabel(centralwidget);
        fromLabel->setObjectName("fromLabel");
        fromLabel->setGeometry(QRect(20, 88, 100, 14));
        fromLabel->setStyleSheet(QString::fromUtf8("color: #3e4560; font-size: 10px; font-weight: 700; background: transparent;"));
        fromInput = new QLineEdit(centralwidget);
        fromInput->setObjectName("fromInput");
        fromInput->setGeometry(QRect(20, 104, 460, 40));
        fromInput->setStyleSheet(QString::fromUtf8("QLineEdit { background-color: #121620; color: #dde3f0; border: 1.5px solid #1e2438; border-radius: 8px; padding: 8px 12px; font-size: 14px; font-weight: 600; } QLineEdit:focus { border: 1.5px solid #3d7bff; background-color: #181d2a; }"));
        toLabel = new QLabel(centralwidget);
        toLabel->setObjectName("toLabel");
        toLabel->setGeometry(QRect(20, 158, 100, 14));
        toLabel->setStyleSheet(QString::fromUtf8("color: #3e4560; font-size: 10px; font-weight: 700; background: transparent;"));
        toInput = new QLineEdit(centralwidget);
        toInput->setObjectName("toInput");
        toInput->setGeometry(QRect(20, 174, 460, 40));
        toInput->setStyleSheet(QString::fromUtf8("QLineEdit { background-color: #121620; color: #dde3f0; border: 1.5px solid #1e2438; border-radius: 8px; padding: 8px 12px; font-size: 14px; font-weight: 600; } QLineEdit:focus { border: 1.5px solid #3d7bff; background-color: #181d2a; }"));
        dateLabel = new QLabel(centralwidget);
        dateLabel->setObjectName("dateLabel");
        dateLabel->setGeometry(QRect(20, 228, 100, 14));
        dateLabel->setStyleSheet(QString::fromUtf8("color: #3e4560; font-size: 10px; font-weight: 700; background: transparent;"));
        dateEdit = new QDateEdit(centralwidget);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(20, 246, 460, 40));
        dateEdit->setStyleSheet(QString::fromUtf8("QDateEdit { background-color: #121620; color: #dde3f0; border: 1.5px solid #1e2438; border-radius: 8px; padding: 8px 12px; font-size: 14px; font-weight: 600; } QDateEdit:focus { border: 1.5px solid #3d7bff; } QDateEdit::drop-down { border: none; background: transparent; width: 20px; }"));
        routeTypeLabel = new QLabel(centralwidget);
        routeTypeLabel->setObjectName("routeTypeLabel");
        routeTypeLabel->setGeometry(QRect(20, 300, 200, 14));
        routeTypeLabel->setStyleSheet(QString::fromUtf8("color: #3e4560; font-size: 10px; font-weight: 700; background: transparent;"));
        directBtn = new QPushButton(centralwidget);
        directBtn->setObjectName("directBtn");
        directBtn->setGeometry(QRect(20, 318, 222, 55));
        directBtn->setStyleSheet(QString::fromUtf8("QPushButton { background-color: rgba(61,123,255,0.08); color: #dde3f0; border: 1.5px solid #3d7bff; border-radius: 8px; font-size: 13px; font-weight: 700; padding: 8px; } QPushButton:hover { background-color: rgba(61,123,255,0.18); }"));
        allRoutesBtn = new QPushButton(centralwidget);
        allRoutesBtn->setObjectName("allRoutesBtn");
        allRoutesBtn->setGeometry(QRect(252, 318, 228, 55));
        allRoutesBtn->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #121620; color: #7c859e; border: 1.5px solid #1e2438; border-radius: 8px; font-size: 13px; font-weight: 700; padding: 8px; } QPushButton:hover { border: 1.5px solid #3d7bff; color: #dde3f0; }"));
        searchBtn = new QPushButton(centralwidget);
        searchBtn->setObjectName("searchBtn");
        searchBtn->setGeometry(QRect(20, 388, 460, 45));
        searchBtn->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #3d7bff; color: white; border: none; border-radius: 8px; font-size: 14px; font-weight: 700; } QPushButton:hover { background-color: #2a5fd4; } QPushButton:pressed { background-color: #1e4ab0; }"));
        resultsLabel = new QLabel(centralwidget);
        resultsLabel->setObjectName("resultsLabel");
        resultsLabel->setGeometry(QRect(20, 448, 200, 14));
        resultsLabel->setStyleSheet(QString::fromUtf8("color: #3e4560; font-size: 10px; font-weight: 700; background: transparent;"));
        resultsList = new QListWidget(centralwidget);
        resultsList->setObjectName("resultsList");
        resultsList->setGeometry(QRect(20, 466, 460, 340));
        resultsList->setStyleSheet(QString::fromUtf8("QListWidget { background-color: #121620; border: 1.5px solid #1e2438; border-radius: 8px; color: #dde3f0; font-size: 13px; padding: 4px; } QListWidget::item { padding: 10px; border-bottom: 1px solid #1e2438; border-radius: 6px; } QListWidget::item:selected { background-color: rgba(61,123,255,0.15); border: 1px solid #3d7bff; } QListWidget::item:hover { background-color: rgba(61,123,255,0.08); }"));
        rightPanel = new QWidget(centralwidget);
        rightPanel->setObjectName("rightPanel");
        rightPanel->setGeometry(QRect(510, 0, 960, 900));
        rightPanel->setStyleSheet(QString::fromUtf8("background-color: #07090f;"));
        routeInfoLabel = new QLabel(rightPanel);
        routeInfoLabel->setObjectName("routeInfoLabel");
        routeInfoLabel->setGeometry(QRect(20, 18, 400, 22));
        routeInfoLabel->setStyleSheet(QString::fromUtf8("color: #dde3f0; font-size: 13px; font-weight: 700; background: transparent;"));
        dateInfoLabel = new QLabel(rightPanel);
        dateInfoLabel->setObjectName("dateInfoLabel");
        dateInfoLabel->setGeometry(QRect(450, 18, 200, 22));
        dateInfoLabel->setStyleSheet(QString::fromUtf8("color: #7c859e; font-size: 13px; font-weight: 700; background: transparent;"));
        mapPlaceholder = new QLabel(rightPanel);
        mapPlaceholder->setObjectName("mapPlaceholder");
        mapPlaceholder->setGeometry(QRect(280, 380, 300, 30));
        mapPlaceholder->setStyleSheet(QString::fromUtf8("color: #3e4560; font-size: 18px; font-weight: 600; background: transparent;"));
        distLabel = new QLabel(rightPanel);
        distLabel->setObjectName("distLabel");
        distLabel->setGeometry(QRect(20, 620, 150, 40));
        distLabel->setStyleSheet(QString::fromUtf8("color: #3d7bff; font-size: 12px; font-weight: 700; background: transparent;"));
        foundLabel = new QLabel(rightPanel);
        foundLabel->setObjectName("foundLabel");
        foundLabel->setGeometry(QRect(190, 620, 150, 40));
        foundLabel->setStyleSheet(QString::fromUtf8("color: #dde3f0; font-size: 12px; font-weight: 700; background: transparent;"));
        directCountLabel = new QLabel(rightPanel);
        directCountLabel->setObjectName("directCountLabel");
        directCountLabel->setGeometry(QRect(360, 620, 150, 40));
        directCountLabel->setStyleSheet(QString::fromUtf8("color: #00c896; font-size: 12px; font-weight: 700; background: transparent;"));
        transferCountLabel = new QLabel(rightPanel);
        transferCountLabel->setObjectName("transferCountLabel");
        transferCountLabel->setGeometry(QRect(530, 620, 150, 40));
        transferCountLabel->setStyleSheet(QString::fromUtf8("color: #ff9f43; font-size: 12px; font-weight: 700; background: transparent;"));
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
        fromLabel->setText(QCoreApplication::translate("MainWindow", "\320\236\320\242\320\232\320\243\320\224\320\220", nullptr));
        fromInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\223\320\276\321\200\320\276\320\264 \320\276\321\202\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217...", nullptr));
        toLabel->setText(QCoreApplication::translate("MainWindow", "\320\232\320\243\320\224\320\220", nullptr));
        toInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\223\320\276\321\200\320\276\320\264 \320\277\321\200\320\270\320\261\321\213\321\202\320\270\321\217...", nullptr));
        dateLabel->setText(QCoreApplication::translate("MainWindow", "\320\224\320\220\320\242\320\220", nullptr));
        routeTypeLabel->setText(QCoreApplication::translate("MainWindow", "\320\242\320\230\320\237 \320\234\320\220\320\240\320\250\320\240\320\243\320\242\320\236\320\222", nullptr));
        directBtn->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\321\217\320\274\321\213\320\265\n"
"\320\221\320\265\320\267 \320\277\320\265\321\200\320\265\321\201\320\260\320\264\320\276\320\272", nullptr));
        allRoutesBtn->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\320\265 \320\274\320\260\321\200\321\210\321\200\321\203\321\202\321\213\n"
"+ \321\201 \320\277\320\265\321\200\320\265\321\201\320\260\320\264\320\272\320\260\320\274\320\270", nullptr));
        searchBtn->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\271\321\202\320\270 \320\274\320\260\321\200\321\210\321\200\321\203\321\202\321\213 \342\206\222", nullptr));
        resultsLabel->setText(QCoreApplication::translate("MainWindow", "\320\240\320\225\320\227\320\243\320\233\320\254\320\242\320\220\320\242\320\253", nullptr));
        routeInfoLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\223\215 \320\236\321\202\320\272\321\203\320\264\320\260 \342\206\222 \320\232\321\203\320\264\320\260", nullptr));
        dateInfoLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\223\205 01.01.2000", nullptr));
        mapPlaceholder->setText(QCoreApplication::translate("MainWindow", "\360\237\227\272 \320\227\320\264\320\265\321\201\321\214 \320\261\321\203\320\264\320\265\321\202 \320\272\320\260\321\200\321\202\320\260", nullptr));
        distLabel->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\200\321\210\321\200\321\203\321\202\n"
"\342\200\224 \342\206\222 \342\200\224", nullptr));
        foundLabel->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\271\320\264\320\265\320\275\320\276\n"
"\342\200\224", nullptr));
        directCountLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\321\217\320\274\321\213\321\205\n"
"\342\200\224", nullptr));
        transferCountLabel->setText(QCoreApplication::translate("MainWindow", "\320\241 \320\277\320\265\321\200\320\265\321\201\320\260\320\264\320\272\320\260\320\274\320\270\n"
"\342\200\224", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
