#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <string>
#include <nlohmann/json.hpp>
#include <stdexcept>

class TimeParseException : public std::runtime_error {
public:
    explicit TimeParseException(const std::string& message) : std::runtime_error(message) {}
};

class Schedule {
public:
    static void printSchedule(const nlohmann::json& schedule, bool showTransfers);
    static int calculateDuration(const std::string& departure, const std::string& arrival);
    static std::string formatTime(const std::string& time);

private:
    static std::string transportTypeTranslation(const std::string& transportType);
};

#endif
