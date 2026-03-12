# Route_Builder 

Маршрутизатор для поиска рейсов между двумя городами по API Яндекс.Расписаний с кэшированием результатов и графическим интерфейсом на Qt.

# Вся информация на русском языке:

Проект состоит из двух частей - двух возможных вариантов получения результата:

- **Консольное приложение** — спрашивает у пользователя API‑ключ, города отправления и прибытия (можно задать и на английском и на русском языках), дату и тип маршрута (прямые или прямые + с 1 пересадкой), затем выводит найденные рейсы в консоль.
- **GUI‑клиент** — Qt-приложение с окном MainWindow, использующее тот же бэкенд, что и консольное приложение, для работы с API и кэшем.

## Возможности
- **Поиск маршрутов** по городам и дате через Яндекс.Расписания.
- **Поддержка ошибок**: отдельные типы исключений для сетевых ошибок, ошибок API, парсинга JSON, некорректных городов, ошибок кэша и времени.
- **Кэширование**:
  - Кэш в памяти + сохранение на диск в `scheduleCache.json`.
  - Удаление устаревших записей (старше 24 часов).
- **Фильтрация маршрутов**:
  - Только прямые рейсы.
  - Все рейсы, включая маршруты с пересадками.
- **Тестируемость**:
  - Интерфейс `IScheduleAPI` и `MockScheduleAPI` для юнит‑тестов.
  - Два модуля с тестами: `tests/RouteBuilderTests.cpp`, `RouteBuilderUI/tests`

## Структура проекта
- `CMakeLists.txt`
- `include/`
  - `YandexScheduleAPI.h` — виртуальный класс `IScheduleAPI`, наследумые классы `YandexScheduleAPI`, `MockScheduleAPI` (для тестов), а также некоторые исключения. 
  - `Schedule.h` — класс `Schedule` для вывода маршрутов + вычисление длительности и преобразование формата времени.
  - `CacheManager.h` — класс `CacheManager` для кэширования полученных ответов, чтобы повторно не обращаться к Яндекс.Расписаниям в течение 24 часов.
- `src/` — реализации классов из 'include/'.
- `main.cpp` — консольное приложение.
- `tests/RouteBuilderTests.cpp` — юнит‑тесты для бэкенда.
- `RouteBuilderUI/`
  - `RouteBuilderUI.pro`, `CMakeLists.txt` — проект Qt.
  - `main.cpp`, `mainwindow.h/.cpp/.ui` — главное окно GUI.
  - `resources.qrc` — ресурсы Qt.
  - `backend/BackendRunner.h/.cpp` — обёртка для запуска бэкенда из UI.
  - `tests/tests.pro`, `tests/tst_mainwindow.cpp` — тесты для Qt‑интерфейса (фронтенда).

## Зависимости
Основные зависимости:
- **C++23** или новее.
- **CMake** для сборки основной части и тестов.
- **nlohmann/json** — для работы с JSON.
- **cpr** — HTTP‑клиент поверх libcurl (для запросов к Яндекс.Расписаниям).
- **GoogleTest** — юнит‑тесты.
- **Qt 6** (Widgets) — для графического интерфейса.

## Сборка и запуск

1. **Консольное приложение:**

   В корне `Route_Builder`:

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ./RouteBuilder
   ```

2. **Qt‑интерфейс (`RouteBuilderUI`):**

   ### Вариант 1: через CMake

   Этот вариант работает только если Qt 6 установлена в системе, и CMake может найти `Qt6Config.cmake`.

   В папке `Route_Builder/RouteBuilderUI`:

   ```bash
   cd Route_Builder/RouteBuilderUI
   mkdir build
   cd build
   cmake ..
   make
   ```

   ### Вариант 2: через Qt Creator

   1. Открыть Qt Creator 
   2. Выбрать kit с Qt 6
   3. **Configure Project**
   4. **Build**
   5. Запустить приложение через **Run**.

---

# Information in English (absolutely the same):

Route planner for searching trips between two cities via the Yandex Timetables API, with result caching and a Qt graphical interface.

The project consists of two parts — two possible ways to get the result:

- **Console application** — asks the user for an API key, departure and arrival cities (you can enter them in either English or Russian), the date, and the route type (direct or direct + with 1 transfer), then prints the found trips to the console.
- **GUI client** — a Qt application with a MainWindow window that uses the same backend as the console application to work with the API and the cache.

## Features
- **Route search** by cities and date via Yandex Timetables.
- **Error handling**: separate exception types for network errors, API errors, JSON parsing, invalid cities, cache errors, and time errors.
- **Caching**:
  - In-memory cache + saving to disk in `scheduleCache.json`.
  - Removing outdated entries (older than 24 hours).
- **Route filtering**:
  - Direct trips only.
  - All trips, including routes with transfers.
- **Testability**:
  - The `IScheduleAPI` and `MockScheduleAPI` interface for unit tests.
  - Two test modules: `tests/RouteBuilderTests.cpp`, `RouteBuilderUI/tests`

## Project structure
- `CMakeLists.txt`
- `include/`
  - `YandexScheduleAPI.h` — the `IScheduleAPI` virtual class, derived classes `YandexScheduleAPI`, `MockScheduleAPI` (for tests), and also some exceptions.
  - `Schedule.h` — the `Schedule` class for printing routes + calculating duration and converting the time format.
  - `CacheManager.h` — the `CacheManager` class for caching received responses so that Yandex Timetables is not requested again within 24 hours.
- `src/` — implementations of classes from 'include/'.
- `main.cpp` — console application.
- `tests/RouteBuilderTests.cpp` — unit tests for the backend.
- `RouteBuilderUI/`
  - `RouteBuilderUI.pro`, `CMakeLists.txt` — the Qt project.
  - `main.cpp`, `mainwindow.h/.cpp/.ui` — the main GUI window.
  - `resources.qrc` — Qt resources.
  - `backend/BackendRunner.h/.cpp` — a wrapper for running the backend from the UI.
  - `tests/tests.pro`, `tests/tst_mainwindow.cpp` — tests for the Qt interface (frontend).

## Dependencies
Main dependencies:
- **C++23** or newer.
- **CMake** for building the main part and tests.
- **nlohmann/json** — for working with JSON.
- **cpr** — an HTTP client on top of libcurl (for requests to Yandex Timetables).
- **GoogleTest** — unit tests.
- **Qt 6** (Widgets) — for the graphical interface.

## Build and run

1. **Console application:**

   In the `Route_Builder` root:

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ./RouteBuilder
   ```

2. **Qt interface (`RouteBuilderUI`):**

   ### Option 1: via CMake

   This option works only if Qt 6 is installed on the system and CMake can find `Qt6Config.cmake`.

   In the `Route_Builder/RouteBuilderUI` folder:

   ```bash
   cd Route_Builder/RouteBuilderUI
   mkdir build
   cd build
   cmake ..
   make
   ```

   ### Option 2: via Qt Creator

   1. Open Qt Creator
   2. Select a kit with Qt 6
   3. **Configure Project**
   4. **Build**
   5. Run the application via **Run**.
