#include "BackendRunner.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QProcess>

namespace {

QString findBackendProgramPath(const QString &programName)
{
    const QString appDir = QCoreApplication::applicationDirPath();
    QStringList candidates;

    // 1. Папка, где лежит Qt-приложение (готовая "установленная" версия)
    candidates << QDir(appDir).filePath(programName);

    // 2. Попробуем найти корень репозитория и стандартные build-папки
    QDir dir(appDir);
    for (int i = 0; i < 5; ++i) {
        const QString rootPath = dir.absolutePath();
        candidates << QDir(rootPath).filePath(QStringLiteral("build/Release/") + programName);
        candidates << QDir(rootPath).filePath(QStringLiteral("build/Debug/") + programName);

        if (!dir.cdUp())
            break;
    }

    for (const QString &path : candidates) {
        if (QFileInfo::exists(path)) {
            return path;
        }
    }

    return QString();
}

} // namespace

BackendRunner::Result BackendRunner::runRouteBuilder(const QString &apiKey,
                                                     const QString &fromCity,
                                                     const QString &toCity,
                                                     const QString &dateIso,
                                                     bool showTransfers)
{
    Result result;

#if defined(Q_OS_WIN)
    const QString programName = QStringLiteral("RouteBuilder.exe");
#else
    const QString programName = QStringLiteral("RouteBuilder");
#endif

    const QString programPath = findBackendProgramPath(programName);

    if (programPath.isEmpty()) {
        result.errorString =
            QStringLiteral("Не найден исполняемый файл бекенда RouteBuilder.\n"
                           "Убедитесь, что RouteBuilder.exe:\n"
                           "  • лежит рядом с Qt-приложением ИЛИ\n"
                           "  • собран CMake'ом и находится в папке build/Release или build/Debug "
                           "рядом с корнем проекта.");
        return result;
    }

    QProcess process;
    process.setProgram(programPath);

    process.start();
    if (!process.waitForStarted(5000)) {
        result.errorString =
            QStringLiteral("Не удалось запустить бекенд: %1").arg(process.errorString());
        return result;
    }

    result.started = true;

    const QString input =
        apiKey + QLatin1Char('\n') +
        fromCity + QLatin1Char('\n') +
        toCity + QLatin1Char('\n') +
        dateIso + QLatin1Char('\n') +
        (showTransfers ? QStringLiteral("2") : QStringLiteral("1")) +
        QLatin1Char('\n');

    process.write(input.toUtf8());
    process.closeWriteChannel();

    process.waitForFinished(-1);

    result.exitCode = process.exitCode();
    // Бекенд печатает текст и данные из Яндекс API в UTF-8,
    // поэтому декодируем вывод как UTF-8, чтобы не было "кракозябр".
    result.stdOut = QString::fromUtf8(process.readAllStandardOutput());
    result.stdErr = QString::fromUtf8(process.readAllStandardError());

    if (process.exitStatus() == QProcess::CrashExit && result.errorString.isEmpty()) {
        result.errorString = QStringLiteral("Процесс бекенда завершился с ошибкой.");
    }

    return result;
}

