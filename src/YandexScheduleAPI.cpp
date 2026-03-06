#include <cpr/cpr.h>
#include "YandexScheduleAPI.h"
#include <iostream>

YandexScheduleAPI::YandexScheduleAPI(const std::string& key) {
    apiKey = key;
}

nlohmann::json YandexScheduleAPI::getSchedule(const std::string& from, const std::string& to, const std::string& date) {
    std::string url = "https://api.rasp.yandex.net/v3.0/search/";

    cpr::Response response = cpr::Get(
        cpr::Url{url},
        cpr::Parameters{
            {"apikey", apiKey},
            {"from", from},
            {"to", to},
            {"date", date},
            {"format", "json"},
            {"transfers", "true"}
        }
    );

    if (response.error) {
        throw std::runtime_error("Ошибка сети: " + response.error.message);
    }

    if (response.status_code != 200) {
        throw std::runtime_error("Ошибка запроса (" + std::to_string(response.status_code) + "): " + response.text);
    }

    try {
        return nlohmann::json::parse(response.text);
    } catch (const std::exception& error) {
        throw std::runtime_error("Ошибка парсинга JSON: " + std::string(error.what()));
    }
}