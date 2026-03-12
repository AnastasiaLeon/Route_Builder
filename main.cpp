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
    std::cout << "Дата (в формате 2026-03-14): ";
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

    // инициализация кэша + удаление устаревших записей
    auto cache = std::make_unique<CacheManager>("scheduleCache.json");
    cache->removeOldEntries();

    std::shared_ptr<IScheduleAPI> api = std::make_shared<YandexScheduleAPI>(APIKey); // создание экземпляра api для работы с янд.sch

    try {
        std::string from;
        std::string to;

        from = api->getCityCode(fromCity);
        to = api->getCityCode(toCity);

        std::string cacheKey = from + "_" + to + "_" + date;
        auto data = cache->getFromCache(cacheKey);

        if (data.has_value()) {
            std::cout << "Данные найдены в кэше:\n";
            Schedule::printSchedule(*data, showTransfers);
        } else {
            auto schedule = api->getSchedule(from, to, date);
            cache->setToCache(cacheKey, schedule);
            std::cout << "Данные полученные из Яндекс Расписания:\n";
            Schedule::printSchedule(schedule, showTransfers);
        }
    } // обработка исключений
    catch (const CityNotFoundException& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    } catch (const NetworkException& e) {
        std::cerr << "Ошибка сети: " << e.what() << std::endl;
        return 1;
    } catch (const ApiException& e) {
        std::cerr << "Ошибка API: " << e.what() << std::endl;
        return 1;
    } catch (const JsonParseException& e) {
        std::cerr << "Ошибка данных от сервера: " << e.what() << std::endl;
        return 1;
    } catch (const CacheException& e) {
        std::cerr << "Ошибка работы с кэшем: " << e.what() << std::endl;
        return 1;
    } catch (const TimeParseException& e) {
        std::cerr << "Ошибка обработки времени: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Неизвестная ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
