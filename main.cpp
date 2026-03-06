#include "Schedule.h"
#include "YandexScheduleAPI.h"
#include "CacheManager.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <unordered_map>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Ошибка: аргументы заданы неверно. Пример задачи аргументов: " << argv[0] << " \"to Saint Petersburg\" или \"to Nizhniy Novgorod\" <дата>" << std::endl;
        return 1;
    }

    std::cout << "Выберите тип маршрутов:\n";
    std::cout << "1. Только прямые маршруты\n";
    std::cout << "2. Все маршруты (прямые и с пересадками)\n";
    std::cout << "Введите 1 или 2: ";

    int choice;
    std::cin >> choice;
    if (choice != 1 && choice != 2) {
        std::cerr << "Ошибка: Некорректный выбор. Введите 1 или 2." << std::endl;
        return 1;
    }

    bool showTransfers = (choice == 2);

    std::cout << "Введите API-ключ: ";
    std::string APIKey;
    std::cin >> APIKey;

    CacheManager cache("scheduleCache.json");

    cache.removeOldEntries(); // Удаление устаревших данных в кэше

    std::unordered_map<std::string, std::pair<std::string, std::string>> routes = {
        {"to Saint Petersburg", {"c23243", "c2"}},
        {"to Nizhniy Novgorod", {"c2", "c23243"}}
    };

    std::string routeKey = argv[1];
    std::string date = argv[2];

    if (routes.find(routeKey) == routes.end()) {
        std::cerr << "Ошибка: Некорректный маршрут. Доступные маршруты: \"to Saint Petersburg\" или \"to Nizhniy Novgorod\"." << std::endl;
        return 1;
    }

    std::string from = routes[routeKey].first;
    std::string to = routes[routeKey].second;

    std::string cacheKey = from + "_" + to + "_" + date;

    // Смотрим на наличие данных о данном маршруте в кэше
    nlohmann::json data = cache.getFromCache(cacheKey);

    if (data != nullptr) {
        std::cout << "Данные найдены в кэше:\n";
        Schedule::printSchedule(data, showTransfers);
    } else {
        // Усли данных нет в кэше: запрос к API
        YandexScheduleAPI api(APIKey);

        try {
            auto schedule = api.getSchedule(from, to, date);
            cache.setToCache(cacheKey, schedule);  // Сохраняем в кэш
            std::cout << "Данные полученные из Яндекс Расписания:\n";
            Schedule::printSchedule(schedule, showTransfers);
        } catch (const std::exception& error) {
            std::cerr << "Ошибка: " << error.what() << std::endl;
        }
    }
    return 0;
}
