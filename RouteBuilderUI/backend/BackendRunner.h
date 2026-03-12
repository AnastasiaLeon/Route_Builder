```cpp
#ifndef BACKENDRUNNER_H
#define BACKENDRUNNER_H
#include <QString>

//запускает консольный бэкенд и возвращает результат
class BackendRunner {
public:
    struct Result {
        bool started = false;
        int exitCode = -1;
        QString stdOut;
        QString stdErr;
        QString errorString;
    };

    static Result runRouteBuilder(const QString &apiKey, const QString &fromCity, const QString &toCity, const QString &dateIso, bool showTransfers);
};

#endif
```