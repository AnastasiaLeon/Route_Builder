#include <cpr/cpr.h>
#include "YandexScheduleAPI.h"
#include <iostream>

YandexScheduleAPI::YandexScheduleAPI(const std::string& key) {
    apiKey = key;
}

std::string YandexScheduleAPI::getCityCode(const std::string& cityName) {
    std::string url = "https://suggests.rasp.yandex.net/all_suggests";

    cpr::Response response = cpr::Get(
        cpr::Url{url},
        cpr::Parameters{
            {"part", cityName},
            {"format", "new"}
        }
    );

    if (response.error) {
        throw std::runtime_error("Ошибка сети при поиске города: " + response.error.message);
    }

    if (response.status_code != 200) {
        throw std::runtime_error("Ошибка запроса к подсказкам (" + std::to_string(response.status_code) + ")");
    }

    try {
        auto json = nlohmann::json::parse(response.text);
        if (!json.contains("items") || !json["items"].is_array() || json["items"].empty()) {
            throw std::runtime_error("Город не найден: " + cityName);
        }
        return json["items"][0]["point_key"].get<std::string>();
    } catch (const nlohmann::json::exception& e) {
        throw std::runtime_error("Город не найден: " + cityName);
    }
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