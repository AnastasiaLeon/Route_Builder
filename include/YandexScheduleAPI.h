#ifndef YANDEXSCHEDULEAPI_H
#define YANDEXSCHEDULEAPI_H

#include <string>
#include <nlohmann/json.hpp>
#include <stdexcept>

class NetworkException : public std::runtime_error {
public:
    explicit NetworkException(const std::string& message)
        : std::runtime_error(message) {}
};

class ApiException : public std::runtime_error {
public:
    explicit ApiException(const std::string& message)
        : std::runtime_error(message) {}
};

class JsonParseException : public std::runtime_error {
public:
    explicit JsonParseException(const std::string& message)
        : std::runtime_error(message) {}
};

class CityNotFoundException : public std::runtime_error {
public:
    explicit CityNotFoundException(const std::string& cityName)
        : std::runtime_error("Город не найден: " + cityName) {}
};

class YandexScheduleAPI {
private:
    std::string apiKey;

public:
    YandexScheduleAPI(const std::string& key);
    std::string getCityCode(const std::string& cityName);
    nlohmann::json getSchedule(const std::string& from, const std::string& to, const std::string& date);
};

#endif