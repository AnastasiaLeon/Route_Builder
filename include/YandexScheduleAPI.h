#ifndef YANDEXSCHEDULEAPI_H
#define YANDEXSCHEDULEAPI_H

#include <string>
#include <nlohmann/json.hpp>

class YandexScheduleAPI {
private:
    std::string apiKey;

public:
    YandexScheduleAPI(const std::string& key);
    std::string getCityCode(const std::string& cityName);
    nlohmann::json getSchedule(const std::string& from, const std::string& to, const std::string& date);
};

#endif