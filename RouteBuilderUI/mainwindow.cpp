#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "backend/BackendRunner.h"

#include <QApplication>
#include <QDate>
#include <QInputDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QPixmap>

namespace {

QString stripAnsiSequences(const QString &text)
{
    static const QRegularExpression ansiPattern(
        QStringLiteral(u"\x1B\\[[0-9;]*[A-Za-z]"));
    return QString(text).remove(ansiPattern);
}

} // namespace

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap map("map.jpg");
    ui->mapPlaceholder->setPixmap(map.scaled(
        ui->mapPlaceholder->size(),
        Qt::KeepAspectRatioByExpanding,
        Qt::SmoothTransformation
    ));
    ui->mapPlaceholder->setScaledContents(true);
    setWindowTitle("Route Builder");
    showMaximized();
    menuBar()->hide();

    // выбраны прямые рейсы, пользователь поменяет, если нужны с пересадками
    setDirectActive(true);

    // клик на прямые
    connect(ui->directBtn, &QPushButton::clicked, this, [this]() {
        setDirectActive(true);
    });

    // клик на все маршруты
    connect(ui->allRoutesBtn, &QPushButton::clicked, this, [this]() {
        setDirectActive(false);
    });

    // поиск маршрутов
    connect(ui->searchBtn, &QPushButton::clicked, this, &MainWindow::onSearchClicked);
}

void MainWindow::setDirectActive(bool directActive)
{
    m_showTransfers = !directActive;

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

void MainWindow::onSearchClicked()
{
    const QString from = ui->fromInput->text().trimmed();
    const QString to = ui->toInput->text().trimmed();

    if (from.isEmpty() || to.isEmpty()) {
        QMessageBox::warning(this, tr("Недостаточно данных"),
                             tr("Пожалуйста, заполните поля 'Откуда' и 'Куда'."));
        return;
    }

    const QDate date = ui->dateEdit->date();
    const QString dateIso = date.toString("yyyy-MM-dd");

    bool ok = false;
    const QString apiKey = QInputDialog::getText(
        this,
        tr("API ключ"),
        tr("Введите API-ключ Яндекс Расписаний:"),
        QLineEdit::Normal,
        QString(),
        &ok
    );

    if (!ok || apiKey.trimmed().isEmpty()) {
        return;
    }

    ui->searchBtn->setEnabled(false);
    ui->searchBtn->setText(tr("Поиск..."));
    QApplication::setOverrideCursor(Qt::BusyCursor);

    const BackendRunner::Result result =
        BackendRunner::runRouteBuilder(apiKey.trimmed(), from, to, dateIso, m_showTransfers);

    QApplication::restoreOverrideCursor();
    ui->searchBtn->setEnabled(true);
    ui->searchBtn->setText(tr("Найти маршруты →"));

    if (!result.started) {
        QMessageBox::critical(this, tr("Ошибка запуска"),
                              result.errorString.isEmpty()
                                  ? tr("Не удалось запустить консольный бекенд.")
                                  : result.errorString);
        return;
    }

    if (!result.stdErr.isEmpty()) {
        // Покажем ошибки, которые вернул бекенд
        QMessageBox::warning(this, tr("Предупреждение от бекенда"),
                             result.stdErr);
    }

    ui->resultsList->clear();
    const QStringList rawLines = result.stdOut.split(QLatin1Char('\n'),
                                                     Qt::SkipEmptyParts);

    int totalRoutes = -1;
    int directRoutes = -1;
    int transferRoutes = -1;

    QStringList lines;
    lines.reserve(rawLines.size());
    for (const QString &rawLine : rawLines) {
        const QString line = stripAnsiSequences(rawLine.trimmed());
        if (!line.isEmpty()) {
            lines << line;
        }
    }

    for (int i = 0; i < lines.size(); ++i) {
        const QString &line = lines[i];

        // Парсим строки статистики, которые печатает бекенд
        if (line.contains(QStringLiteral("Всего маршрутов:"))) {
            bool ok = false;
            const int value = line.section(QLatin1Char(':'), -1).trimmed().toInt(&ok);
            if (ok) {
                totalRoutes = value;
            }
            continue;
        }
        if (line.contains(QStringLiteral("Всего прямых маршрутов:"))) {
            bool ok = false;
            const int value = line.section(QLatin1Char(':'), -1).trimmed().toInt(&ok);
            if (ok) {
                directRoutes = value;
                totalRoutes = value;
            }
            continue;
        }
        if (line.contains(QStringLiteral("Прямых маршрутов:"))) {
            bool ok = false;
            const int value = line.section(QLatin1Char(':'), -1).trimmed().toInt(&ok);
            if (ok) {
                directRoutes = value;
            }
            continue;
        }
        if (line.contains(QStringLiteral("Маршрутов с одной пересадкой:"))) {
            bool ok = false;
            const int value = line.section(QLatin1Char(':'), -1).trimmed().toInt(&ok);
            if (ok) {
                transferRoutes = value;
            }
            continue;
        }

        // Статистика и прочий текст, не являющийся описанием маршрута, пропускается.
        if (line.startsWith(QStringLiteral("📊")) || line.startsWith(QStringLiteral("Введите 1")))
            continue;

        // Собираем краткое описание маршрута из нескольких строк подряд.
        if (line.startsWith(QStringLiteral("⬆️"))  // Прямой маршрут
            || line.startsWith(QStringLiteral("🔄"))) { // Маршрут с пересадкой

            QString summary = line;

            int j = i + 1;
            while (j < lines.size()) {
                const QString &next = lines[j];

                // Останов: начинается новый маршрут или новый блок статистики
                if (next.startsWith(QStringLiteral("⬆️"))
                    || next.startsWith(QStringLiteral("🔄"))
                    || next.startsWith(QStringLiteral("📊"))) {
                    break;
                }

                // Берём только ключевые строки маршрута:
                // время отправления/прибытия/длительность и места отправления/прибытия.
                if (next.contains(QStringLiteral("Отправление:"))
                    || next.contains(QStringLiteral("Место отправления:"))) {
                    summary += QStringLiteral("  ") + next;
                }

                ++j;
            }

            ui->resultsList->addItem(summary);
            i = j - 1;
        }
    }

    // Обновим краткую информацию справа
    if (!from.isEmpty() && !to.isEmpty()) {
        ui->routeInfoLabel->setText(
            QStringLiteral("📍 %1 → %2").arg(from, to));
        ui->distLabel->setText(
            QStringLiteral("Маршрут\n%1 → %2").arg(from, to));
    }
    ui->dateInfoLabel->setText(
        QStringLiteral("📅 %1").arg(date.toString("dd.MM.yyyy")));

    if (totalRoutes < 0) {
        totalRoutes = ui->resultsList->count();
    }
    if (directRoutes < 0 && !m_showTransfers) {
        directRoutes = totalRoutes;
    }
    if (!m_showTransfers && transferRoutes < 0) {
        transferRoutes = 0;
    }

    ui->foundLabel->setText(
        QStringLiteral("Найдено\n%1").arg(totalRoutes));

    ui->directCountLabel->setText(
        QStringLiteral("Прямых\n%1").arg(directRoutes >= 0 ? directRoutes : 0));

    ui->transferCountLabel->setText(
        QStringLiteral("С пересадками\n%1").arg(transferRoutes >= 0 ? transferRoutes : 0));
}

MainWindow::~MainWindow()
{
    delete ui;
}

