#include "Schedule.h"
#include "YandexScheduleAPI.h"
#include "CacheManager.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <memory>

int main(int argc, char* argv[]) {
    std::cout << "Введите API-ключ: ";
    std::string APIKey;
    std::cin >> APIKey;

    std::cin.ignore();

    std::string fromCity, toCity, date;
    std::cout << "Город отправления: ";
    std::getline(std::cin, fromCity);
    std::cout << "Город прибытия: ";
    std::getline(std::cin, toCity);
    std::cout << "Дата (например 2025-12-01): ";
    std::getline(std::cin, date);

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

    auto cache = std::make_unique<CacheManager>("scheduleCache.json");
    cache->removeOldEntries();

    auto api = std::make_shared<YandexScheduleAPI>(APIKey);

    std::string from, to;
    try {
        from = api->getCityCode(fromCity);
        to = api->getCityCode(toCity);
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    std::string cacheKey = from + "_" + to + "_" + date;
    auto data = cache->getFromCache(cacheKey);

    if (data.has_value()) {
        std::cout << "Данные найдены в кэше:\n";
        Schedule::printSchedule(*data, showTransfers);
    } else {
        try {
            auto schedule = api->getSchedule(from, to, date);
            cache->setToCache(cacheKey, schedule);
            std::cout << "Данные полученные из Яндекс Расписания:\n";
            Schedule::printSchedule(schedule, showTransfers);
        } catch (const std::exception& error) {
            std::cerr << "Ошибка: " << error.what() << std::endl;
            return 1;
        }
    }
    return 0;
}
