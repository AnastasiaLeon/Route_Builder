```cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "backend/BackendRunner.h"
#include <QApplication>
#include <QDate>
#include <QInputDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QPixmap>
#include <QDir>
#include <QFileInfo>
#include <memory>
#include <optional>
#include <variant>
#include <QCoreApplication>

namespace {

//убираем ansi-escape последовательности из вывода бэкенда (цветные символы терминала)
QString stripAnsiSequences(const QString &text) {
    static const QRegularExpression ansiPattern(QStringLiteral(u"\x1B\\[[0-9;]*[A-Za-z]"));
    return QString(text).remove(ansiPattern);
}

//если данных нет, прочерк
using RouteCountValue = std::variant<int, QString>;

QString routeCountToText(const RouteCountValue &value) {
    return std::visit([](auto &&val) -> QString {
        using T = std::decay_t<decltype(val)>;
        if constexpr (std::is_same_v<T, int>) return QString::number(val);
        else return val;
    }, value);
}

//обёртка над QListWidgetItem
class RouteListItem : public QListWidgetItem {
public:
    using QListWidgetItem::QListWidgetItem;
};

}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //для фотки карты
    QPixmap resMap(QStringLiteral(":/images/map.jpg"));
    if (!resMap.isNull()) {
        ui->mapPlaceholder->setPixmap(resMap);
        ui->mapPlaceholder->setScaledContents(true);
    }

    const QString appDir = QCoreApplication::applicationDirPath();
    QStringList candidates;
    candidates << QDir(appDir).filePath(QStringLiteral("map.jpg"));
    QDir dir(appDir);
    for (int i = 0; i < 5; i++) {
        candidates << dir.filePath(QStringLiteral("map.jpg"));
        if (!dir.cdUp()) break;
    }
    for (const QString &path : candidates) {
        if (QFileInfo::exists(path)) {
            QPixmap map(path);
            if (!map.isNull()) {
                ui->mapPlaceholder->setPixmap(map);
                ui->mapPlaceholder->setScaledContents(true);
            }
            break;
        }
    }

    setWindowTitle("Route Builder");
    showMaximized();
    menuBar()->hide();

    //по умолчанию ищем прямые рейсы
    setDirectActive(true);
    connect(ui->directBtn, &QPushButton::clicked, this, [this]() { setDirectActive(true); });
    connect(ui->allRoutesBtn, &QPushButton::clicked, this, [this]() { setDirectActive(false); });
    connect(ui->searchBtn, &QPushButton::clicked, this, &MainWindow::onSearchClicked);
}

void MainWindow::setDirectActive(bool directActive) {
    m_showTransfers = !directActive;
    //активная кнопка
    if (directActive) {
        ui->directBtn->setStyleSheet("QPushButton { background-color: rgba(61,123,255,0.15); color: #dde3f0; border: 1.5px solid #3d7bff; border-radius: 8px; font-size: 13px; font-weight: 700; padding: 8px; } QPushButton:hover { background-color: rgba(61,123,255,0.25); }");
        ui->allRoutesBtn->setStyleSheet("QPushButton { background-color: #121620; color: #7c859e; border: 1.5px solid #1e2438; border-radius: 8px; font-size: 13px; font-weight: 700; padding: 8px; } QPushButton:hover { border: 1.5px solid #3d7bff; color: #dde3f0; }");
    } else {
        ui->allRoutesBtn->setStyleSheet("QPushButton { background-color: rgba(61,123,255,0.15); color: #dde3f0; border: 1.5px solid #3d7bff; border-radius: 8px; font-size: 13px; font-weight: 700; padding: 8px; } QPushButton:hover { background-color: rgba(61,123,255,0.25); }");
        ui->directBtn->setStyleSheet("QPushButton { background-color: #121620; color: #7c859e; border: 1.5px solid #1e2438; border-radius: 8px; font-size: 13px; font-weight: 700; padding: 8px; } QPushButton:hover { border: 1.5px solid #3d7bff; color: #dde3f0; }");
    }
}

void MainWindow::onSearchClicked() {
    const QString from = ui->fromInput->text().trimmed();
    const QString to = ui->toInput->text().trimmed();
    if (from.isEmpty() || to.isEmpty()) {
        QMessageBox::warning(this, tr("Недостаточно данных"), tr("Пожалуйста, заполните поля 'Откуда' и 'Куда'."));
        return;
    }
    const QDate date = ui->dateEdit->date();
    const QString dateIso = date.toString("yyyy-MM-dd");
    bool ok = false;
    const QString apiKey = QInputDialog::getText(this, tr("API ключ"), tr("Введите API-ключ Яндекс Расписаний:"), QLineEdit::Normal, QString(), &ok);
    if (!ok || apiKey.trimmed().isEmpty()) return;

    ui->searchBtn->setEnabled(false);
    ui->searchBtn->setText(tr("Поиск..."));
    QApplication::setOverrideCursor(Qt::BusyCursor);

    //получаем результат
    std::optional<BackendRunner::Result> resultOpt = std::make_optional(BackendRunner::runRouteBuilder(apiKey.trimmed(), from, to, dateIso, m_showTransfers));
    const BackendRunner::Result &result = *resultOpt;

    QApplication::restoreOverrideCursor();
    ui->searchBtn->setEnabled(true);
    ui->searchBtn->setText(tr("Найти маршруты →"));

    if (!result.started) {
        QMessageBox::critical(this, tr("Ошибка запуска"), result.errorString.isEmpty() ? tr("Не удалось запустить консольный бекенд.") : result.errorString);
        return;
    }
    if (!result.stdErr.isEmpty()) QMessageBox::warning(this, tr("Предупреждение от бекенда"), result.stdErr);

    ui->resultsList->clear();
    const QStringList rawLines = result.stdOut.split(QLatin1Char('\n'), Qt::SkipEmptyParts);
    int totalRoutes = -1, directRoutes = -1, transferRoutes = -1;
    QStringList lines;
    lines.reserve(rawLines.size());
    for (const QString &rawLine : rawLines) {
        const QString line = stripAnsiSequences(rawLine.trimmed());
        if (!line.isEmpty()) lines << line;
    }

    for (int i = 0; i < lines.size(); i++) {
        const QString &line = lines[i];

        //парсим статистику из вывода бэкенда
        if (line.contains(QStringLiteral("Всего маршрутов:"))) {
            bool ok = false;
            const int value = line.section(QLatin1Char(':'), -1).trimmed().toInt(&ok);
            if (ok) totalRoutes = value;
            continue;
        }
        if (line.contains(QStringLiteral("Всего прямых маршрутов:"))) {
            bool ok = false;
            const int value = line.section(QLatin1Char(':'), -1).trimmed().toInt(&ok);
            if (ok) { directRoutes = value; totalRoutes = value; }
            continue;
        }
        if (line.contains(QStringLiteral("Прямых маршрутов:"))) {
            bool ok = false;
            const int value = line.section(QLatin1Char(':'), -1).trimmed().toInt(&ok);
            if (ok) directRoutes = value;
            continue;
        }
        if (line.contains(QStringLiteral("Маршрутов с одной пересадкой:"))) {
            bool ok = false;
            const int value = line.section(QLatin1Char(':'), -1).trimmed().toInt(&ok);
            if (ok) transferRoutes = value;
            continue;
        }
        if (line.startsWith(QStringLiteral("📊")) || line.startsWith(QStringLiteral("Введите 1"))) continue;
        //собираем маршрут из нескольких строк и добавляем в список
        if (line.startsWith(QStringLiteral("⬆️")) || line.startsWith(QStringLiteral("🔄"))) {
            QString summary = line;
            int j = i + 1;
            while (j < lines.size()) {
                const QString &next = lines[j];
                if (next.startsWith(QStringLiteral("⬆️")) || next.startsWith(QStringLiteral("🔄")) || next.startsWith(QStringLiteral("📊"))) break;
                if (next.contains(QStringLiteral("Отправление:")) || next.contains(QStringLiteral("Место отправления:")) || next.contains(QStringLiteral("Место пересадки:")))
                    summary += QStringLiteral("  ") + next;
                ++j;
            }
            auto summaryPtr = std::make_unique<QString>(summary);
            std::shared_ptr<QString> sharedSummary(std::move(summaryPtr));
            auto *item = new RouteListItem(*sharedSummary);
            ui->resultsList->addItem(item);
            i = j - 1;
        }
    }

    //обновляем информацию справа
    if (!from.isEmpty() && !to.isEmpty()) {
        ui->routeInfoLabel->setText(QStringLiteral("📍 %1 → %2").arg(from, to));
        ui->distLabel->setText(QStringLiteral("Маршрут\n%1 → %2").arg(from, to));
    }
    ui->dateInfoLabel->setText(QStringLiteral("📅 %1").arg(date.toString("dd.MM.yyyy")));

    if (totalRoutes < 0) totalRoutes = ui->resultsList->count();
    if (directRoutes < 0 && !m_showTransfers) directRoutes = totalRoutes;
    if (!m_showTransfers && transferRoutes < 0) transferRoutes = 0;

    RouteCountValue totalValue = totalRoutes;
    RouteCountValue directValue = (directRoutes >= 0) ? RouteCountValue{directRoutes} : RouteCountValue{QStringLiteral("0")};
    RouteCountValue transferValue = (transferRoutes >= 0) ? RouteCountValue{transferRoutes} : RouteCountValue{QStringLiteral("0")};

    ui->foundLabel->setText(QStringLiteral("Найдено\n%1").arg(routeCountToText(totalValue)));
    ui->directCountLabel->setText(QStringLiteral("Прямых\n%1").arg(routeCountToText(directValue)));
    ui->transferCountLabel->setText(QStringLiteral("С пересадками\n%1").arg(routeCountToText(transferValue)));
}

MainWindow::~MainWindow() {
    delete ui;
}
```