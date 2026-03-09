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

    //выбраны пямые рейсы, пользоватеь поменяет, если нужны с пересадками
    setDirectActive(true);

    // клик на прямые
    connect(ui->directBtn, &QPushButton::clicked, this, [this]() {
        setDirectActive(true);
    });

    // клик на все маршруты
    connect(ui->allRoutesBtn, &QPushButton::clicked, this, [this]() {
        setDirectActive(false);
    });
}

void MainWindow::setDirectActive(bool directActive)
{
    if (directActive) {
        ui->directBtn->setStyleSheet(
            "QPushButton { background-color: rgba(61,123,255,0.15); color: #dde3f0; "
            "border: 1.5px solid #3d7bff; border-radius: 8px; font-size: 13px; font-weight: 700; padding: 8px; }"
            "QPushButton:hover { background-color: rgba(61,123,255,0.25); }"
        );
        ui->allRoutesBtn->setStyleSheet(
            "QPushButton { background-color: #121620; color: #7c859e; "
            "border: 1.5px solid #1e2438; border-radius: 8px; font-size: 13px; font-weight: 700; padding: 8px; }"
            "QPushButton:hover { border: 1.5px solid #3d7bff; color: #dde3f0; }"
        );
    } else {
        ui->allRoutesBtn->setStyleSheet(
            "QPushButton { background-color: rgba(61,123,255,0.15); color: #dde3f0; "
            "border: 1.5px solid #3d7bff; border-radius: 8px; font-size: 13px; font-weight: 700; padding: 8px; }"
            "QPushButton:hover { background-color: rgba(61,123,255,0.25); }"
        );
        ui->directBtn->setStyleSheet(
            "QPushButton { background-color: #121620; color: #7c859e; "
            "border: 1.5px solid #1e2438; border-radius: 8px; font-size: 13px; font-weight: 700; padding: 8px; }"
            "QPushButton:hover { border: 1.5px solid #3d7bff; color: #dde3f0; }"
        );
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
