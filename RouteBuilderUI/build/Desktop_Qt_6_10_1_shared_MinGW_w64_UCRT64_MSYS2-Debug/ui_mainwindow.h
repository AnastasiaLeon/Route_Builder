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
    QLabel *toLabel;
    QLabel *fromLabel;
    QLineEdit *fromInput;
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
        toLabel->setGeometry(QRect(20, 158, 100, 16));
        toLabel->setStyleSheet(QString::fromUtf8("color: #3e4560;\n"
"font-size: 10px;\n"
"font-weight: 700;\n"
"background: transparent;"));
        fromLabel = new QLabel(centralwidget);
        fromLabel->setObjectName("fromLabel");
        fromLabel->setGeometry(QRect(20, 88, 100, 14));
        fromLabel->setStyleSheet(QString::fromUtf8("color: #3e4560;\n"
"font-size: 10px;\n"
"font-weight: 700;\n"
"background: transparent;"));
        fromInput = new QLineEdit(centralwidget);
        fromInput->setObjectName("fromInput");
        fromInput->setGeometry(QRect(20, 104, 460, 40));
        fromInput->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #121620;\n"
"    color: #dde3f0;\n"
"    border: 1.5px solid #1e2438;\n"
"    border-radius: 8px;\n"
"    padding: 8px 12px;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 1.5px solid #3d7bff;\n"
"    background-color: #181d2a;\n"
"}"));
        toInput = new QLineEdit(centralwidget);
        toInput->setObjectName("toInput");
        toInput->setGeometry(QRect(20, 174, 460, 40));
        toInput->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    background-color: #121620;\n"
"    color: #dde3f0;\n"
"    border: 1.5px solid #1e2438;\n"
"    border-radius: 8px;\n"
"    padding: 8px 12px;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"}\n"
"QLineEdit:focus {\n"
"    border: 1.5px solid #3d7bff;\n"
"    background-color: #181d2a;\n"
"}"));
        dateLabel = new QLabel(centralwidget);
        dateLabel->setObjectName("dateLabel");
        dateLabel->setGeometry(QRect(20, 240, 100, 14));
        dateLabel->setStyleSheet(QString::fromUtf8("color: #3e4560;\n"
"font-size: 10px;\n"
"font-weight: 700;\n"
"background: transparent;"));
        dateEdit = new QDateEdit(centralwidget);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(20, 258, 460, 40));
        dateEdit->setStyleSheet(QString::fromUtf8("QDateEdit {\n"
"    background-color: #121620;\n"
"    color: #dde3f0;\n"
"    border: 1.5px solid #1e2438;\n"
"    border-radius: 8px;\n"
"    padding: 8px 12px;\n"
"    font-size: 14px;\n"
"    font-weight: 600;\n"
"}\n"
"QDateEdit:focus {\n"
"    border: 1.5px solid #3d7bff;\n"
"}\n"
"QDateEdit::drop-down {\n"
"    border: none;\n"
"    background: transparent;\n"
"    width: 20px;\n"
"}"));
        routeTypeLabel = new QLabel(centralwidget);
        routeTypeLabel->setObjectName("routeTypeLabel");
        routeTypeLabel->setGeometry(QRect(20, 312, 200, 14));
        routeTypeLabel->setStyleSheet(QString::fromUtf8("color: #3e4560;\n"
"font-size: 10px;\n"
"font-weight: 700;\n"
"background: transparent;"));
        directBtn = new QPushButton(centralwidget);
        directBtn->setObjectName("directBtn");
        directBtn->setGeometry(QRect(20, 330, 222, 55));
        directBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(61,123,255,0.08);\n"
"    color: #dde3f0;\n"
"    border: 1.5px solid #3d7bff;\n"
"    border-radius: 8px;\n"
"    font-size: 13px;\n"
"    font-weight: 700;\n"
"    padding: 8px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: rgba(61,123,255,0.18);\n"
"}"));
        allRoutesBtn = new QPushButton(centralwidget);
        allRoutesBtn->setObjectName("allRoutesBtn");
        allRoutesBtn->setGeometry(QRect(252, 330, 228, 55));
        allRoutesBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #121620;\n"
"    color: #7c859e;\n"
"    border: 1.5px solid #1e2438;\n"
"    border-radius: 8px;\n"
"    font-size: 13px;\n"
"    font-weight: 700;\n"
"    padding: 8px;\n"
"}\n"
"QPushButton:hover {\n"
"    border: 1.5px solid #3d7bff;\n"
"    color: #dde3f0;\n"
"}"));
        searchBtn = new QPushButton(centralwidget);
        searchBtn->setObjectName("searchBtn");
        searchBtn->setGeometry(QRect(20, 400, 460, 45));
        searchBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #3d7bff;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    font-size: 14px;\n"
"    font-weight: 700;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #2a5fd4;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #1e4ab0;\n"
"}"));
        resultsLabel = new QLabel(centralwidget);
        resultsLabel->setObjectName("resultsLabel");
        resultsLabel->setGeometry(QRect(20, 460, 200, 14));
        resultsLabel->setStyleSheet(QString::fromUtf8("color: #3e4560;\n"
"font-size: 10px;\n"
"font-weight: 700;\n"
"background: transparent;"));
        resultsList = new QListWidget(centralwidget);
        resultsList->setObjectName("resultsList");
        resultsList->setGeometry(QRect(20, 478, 460, 340));
        resultsList->setStyleSheet(QString::fromUtf8("QListWidget {\n"
"    background-color: #121620;\n"
"    border: 1.5px solid #1e2438;\n"
"    border-radius: 8px;\n"
"    color: #dde3f0;\n"
"    font-size: 13px;\n"
"    padding: 4px;\n"
"}\n"
"QListWidget::item {\n"
"    padding: 10px;\n"
"    border-bottom: 1px solid #1e2438;\n"
"    border-radius: 6px;\n"
"}\n"
"QListWidget::item:selected {\n"
"    background-color: rgba(61,123,255,0.15);\n"
"    border: 1px solid #3d7bff;\n"
"}\n"
"QListWidget::item:hover {\n"
"    background-color: rgba(61,123,255,0.08);\n"
"}"));
        rightPanel = new QWidget(centralwidget);
        rightPanel->setObjectName("rightPanel");
        rightPanel->setGeometry(QRect(520, 0, 960, 900));
        rightPanel->setStyleSheet(QString::fromUtf8("background-color: #07090f;"));
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
        fromLabel->setText(QCoreApplication::translate("MainWindow", "\320\236\320\242\320\232\320\243\320\224\320\220", nullptr));
        fromInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\223\320\276\321\200\320\276\320\264 \320\276\321\202\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217...", nullptr));
        toInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\223\320\276\321\200\320\276\320\264 \320\277\321\200\320\270\320\261\321\213\321\202\320\270\321\217...", nullptr));
        dateLabel->setText(QCoreApplication::translate("MainWindow", "\320\224\320\220\320\242\320\220", nullptr));
        routeTypeLabel->setText(QCoreApplication::translate("MainWindow", "\320\242\320\230\320\237 \320\234\320\220\320\240\320\250\320\240\320\243\320\242\320\236\320\222", nullptr));
        directBtn->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\321\217\320\274\321\213\320\265\n"
"\320\221\320\265\320\267 \320\277\320\265\321\200\320\265\321\201\320\260\320\264\320\276\320\272", nullptr));
        allRoutesBtn->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\320\265 \320\274\320\260\321\200\321\210\321\200\321\203\321\202\321\213\n"
"+ \321\201 \320\277\320\265\321\200\320\265\321\201\320\260\320\264\320\272\320\260\320\274\320\270", nullptr));
        searchBtn->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\271\321\202\320\270 \320\274\320\260\321\200\321\210\321\200\321\203\321\202\321\213 \342\206\222", nullptr));
        resultsLabel->setText(QCoreApplication::translate("MainWindow", "\320\240\320\225\320\227\320\243\320\233\320\254\320\242\320\220\320\242\320\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
