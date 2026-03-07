#ifndef YANDEXSCHEDULEAPI_H
#define YANDEXSCHEDULEAPI_H

#include <string>
#include <nlohmann/json.hpp>
#include <stdexcept>

// cпециализированные типы исключений для работы с API
class NetworkException : public std::runtime_error {
public:
    explicit NetworkException(const std::string& message) : std::runtime_error(message) {}
};

class ApiException : public std::runtime_error {
public:
    explicit ApiException(const std::string& message) : std::runtime_error(message) {}
};

class JsonParseException : public std::runtime_error {
public:
    explicit JsonParseException(const std::string& message) : std::runtime_error(message) {}
};

class CityNotFoundException : public std::runtime_error {
public:
    explicit CityNotFoundException(const std::string& cityName) : std::runtime_error("Город не найден: " + cityName) {}
};

class IScheduleAPI {
public:
    virtual ~IScheduleAPI() = default;

    virtual std::string getCityCode(const std::string& cityName) = 0;
    virtual nlohmann::json getSchedule(const std::string& from, const std::string& to, const std::string& date) = 0;
};

class YandexScheduleAPI : public IScheduleAPI {
private:
    std::string apiKey;

public:
    YandexScheduleAPI(const std::string& key);
    std::string getCityCode(const std::string& cityName) override;
    nlohmann::json getSchedule(const std::string& from, const std::string& to, const std::string& date) override;
};

// реализация для тестов возвращающая заранее подготовленные данные
class MockScheduleAPI : public IScheduleAPI {
public:
    explicit MockScheduleAPI(const nlohmann::json& mockData) : mockSchedule(mockData) {}

    std::string getCityCode(const std::string& cityName) override {
        return cityName;
    }

    nlohmann::json getSchedule(const std::string& from, const std::string& to, const std::string& date) override {
        (void)from;
        (void)to;
        (void)date;
        return mockSchedule;
    }

private:
    nlohmann::json mockSchedule;
};

#endif