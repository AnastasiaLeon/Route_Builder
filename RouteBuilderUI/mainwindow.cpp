#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Route Builder");
    showMaximized();
    menuBar()->hide();

    // sidebar на всю высоту
    ui->sidePanel->setFixedWidth(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}
