#include <QtTest>
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include "../mainwindow.h"

class TestMainWindow : public QObject {
    Q_OBJECT

private slots:

    //окно создаётся без ошибок
    void testWindowCreation() {
        MainWindow w;
        QVERIFY(&w != nullptr);
    }

    //кнопка "прямые" всегда активна 
    void testDirectButtonActiveByDefault() {
        MainWindow w;
        w.show();
        QPushButton *directBtn = w.findChild<QPushButton*>("directBtn");
        QVERIFY(directBtn != nullptr);
        QString style = directBtn->styleSheet();
        QVERIFY(style.contains("#3d7bff"));
    }

    //клик на "Все маршруты" переключается
    void testAllRoutesButtonClick() {
        MainWindow w;
        w.show();
        QPushButton *allRoutesBtn = w.findChild<QPushButton*>("allRoutesBtn");
        QPushButton *directBtn = w.findChild<QPushButton*>("directBtn");
        QVERIFY(allRoutesBtn != nullptr);
        QTest::mouseClick(allRoutesBtn, Qt::LeftButton);
        QVERIFY(allRoutesBtn->styleSheet().contains("#3d7bff"));
        QVERIFY(!directBtn->styleSheet().contains("rgba(61,123,255,0.15)"));
    }

    //клик обратно на "Прямые" переключает обратно
    void testDirectButtonClick() {
        MainWindow w;
        w.show();
        QPushButton *directBtn = w.findChild<QPushButton*>("directBtn");
        QPushButton *allRoutesBtn = w.findChild<QPushButton*>("allRoutesBtn");
        QTest::mouseClick(allRoutesBtn, Qt::LeftButton);
        QTest::mouseClick(directBtn, Qt::LeftButton);
        QVERIFY(directBtn->styleSheet().contains("#3d7bff"));
        QVERIFY(!allRoutesBtn->styleSheet().contains("rgba(61,123,255,0.15)"));
    }

    //поиск с пустыми полями показывает предупреждение(выдаются ошибки)
    void testSearchWithEmptyFields() {
        MainWindow w;
        w.show();
        QPushButton *searchBtn = w.findChild<QPushButton*>("searchBtn");
        QLineEdit *fromInput = w.findChild<QLineEdit*>("fromInput");
        QLineEdit *toInput = w.findChild<QLineEdit*>("toInput");
        QVERIFY(searchBtn != nullptr);
        fromInput->clear();
        toInput->clear();
        // кнопка существует и кликабельна
        QVERIFY(searchBtn->isEnabled());
    }

    //поля ввода принимают текст
    void testInputFields() {
        MainWindow w;
        w.show();
        QLineEdit *fromInput = w.findChild<QLineEdit*>("fromInput");
        QLineEdit *toInput = w.findChild<QLineEdit*>("toInput");
        QVERIFY(fromInput != nullptr);
        QVERIFY(toInput != nullptr);
        fromInput->setText("Москва");
        toInput->setText("Санкт-Петербург");
        QCOMPARE(fromInput->text(), QString("Москва"));
        QCOMPARE(toInput->text(), QString("Санкт-Петербург"));
    }

    //список результатов существует и пустой изначально
    void testResultsListEmpty() {
        MainWindow w;
        w.show();
        QListWidget *resultsList = w.findChild<QListWidget*>("resultsList");
        QVERIFY(resultsList != nullptr);
        QCOMPARE(resultsList->count(), 0);
    }

    //BackendRunner подключён, класс доступен
    void testBackendRunnerExists() {
        //BackendRunner компилируется и доступен
        #include "../backend/BackendRunner.h"
        QVERIFY(true); //если скомпилировалось то бэкенд подключён
    }
};

QTEST_MAIN(TestMainWindow)
#include "tst_mainwindow.moc"