#include "Schedule.h"
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <ctime>

#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_CYAN    "\033[36m"
#define TEXT_ITALIC   "\033[3m"
#define TEXT_BOLD     "\033[1m"

std::string Schedule::transportTypeTranslation(const std::string& transportType) {
    static const std::unordered_map<std::string, std::string> transportTranslations = {
        {"plane", "Самолет"},
        {"train", "Поезд"},
        {"suburban", "Электричка"},
        {"bus", "Автобус"},
        {"water", "Водный транспорт"},
        {"helicopter", "Вертолет"}
    };

    if (transportTranslations.find(transportType) != transportTranslations.end()) {
        return transportTranslations.at(transportType);
    } else {
        return transportType;
    }
}

int Schedule::calculateDuration(const std::string& departure, const std::string& arrival) {
    std::tm tmDeparture = {}, tmArrival = {};
    std::istringstream ssDeparture(departure);
    std::istringstream ssArrival(arrival);

    ssDeparture >> std::get_time(&tmDeparture, "%Y-%m-%dT%H:%M:%S");
    if (ssDeparture.fail()) {
        throw std::runtime_error("Ошибка парсинга времени отправления");
    }

    ssArrival >> std::get_time(&tmArrival, "%Y-%m-%dT%H:%M:%S");
    if (ssArrival.fail()) {
        throw std::runtime_error("Ошибка парсинга времени прибытия");
    }

    std::time_t timeDeparture = std::mktime(&tmDeparture);
    std::time_t timeArrival = std::mktime(&tmArrival);

    double diff = std::difftime(timeArrival, timeDeparture) / 60.0;
    return static_cast<int>(diff);
}

std::string Schedule::formatTime(const std::string& time) {
    std::string formattedTime = time;
    size_t tPos = formattedTime.find('T');
    if (tPos != std::string::npos) {
        formattedTime.replace(tPos, 1, " ");
    }
    return formattedTime;
}

void Schedule::printSchedule(const nlohmann::json& schedule, bool showTransfers) {
    if (!schedule.contains("segments")) {
        std::cerr << "Ошибка: в ответе нет ключа 'segments'" << std::endl;
        return;
    }

    int totalRoutes = 0, directRoutes = 0, transferRoutes = 0;

    for (const auto& segment : schedule["segments"]) {
        try {
            int transfersCount = segment.value("transfers_count", 0);
            if (transfersCount > 1) {
                continue;
            }

            bool hasTransfers = segment.value("has_transfers", false);

            hasTransfers ? transferRoutes++ : directRoutes++;
            totalRoutes++;

        } catch (const std::exception& error) {
            std::cerr << "Ошибка при обработке маршрута: " << error.what() << std::endl;
        }
    }

    std::cout << COLOR_CYAN << TEXT_BOLD << "📊 Статистика маршрутов:\n" << COLOR_RESET << COLOR_CYAN;
    if (showTransfers) {
        std::cout << "   - Всего маршрутов: " << totalRoutes << "\n";
        std::cout << "   - Прямых маршрутов: " << directRoutes << "\n";
        std::cout << "   - Маршрутов с одной пересадкой: " << transferRoutes << "\n";
    } else {
        std::cout << "   - Всего прямых маршрутов: " << directRoutes << "\n";
    }
    std::cout << "\n-------------------------------------------------------------\n\n" << COLOR_RESET;

    for (const auto& segment : schedule["segments"]) {
        try {
            int transfersCount = segment.value("transfers_count", 0);
            if (transfersCount > 1) {
                continue;
            }

            bool hasTransfers = segment.value("has_transfers", false);

            if (!showTransfers && hasTransfers) { // Если в запросе только прямые маршруты то маршруты с пересадками пропускаются
                continue;
            }

            if (!hasTransfers) { // Прямой маршрут
                std::string transport = "Неизвестно";
                if (segment.contains("thread")) {
                    auto thread = segment["thread"];
                    if (thread.contains("transport_subtype") && thread["transport_subtype"].contains("title") && !thread["transport_subtype"]["title"].is_null()) {
                        transport = thread["transport_subtype"]["title"];
                    } else if (thread.contains("transport_type") && !thread["transport_type"].is_null()) {
                        transport = transportTypeTranslation(thread["transport_type"]);
                    }
                }

                std::string departure = formatTime(segment.value("departure", ""));
                std::string arrival = formatTime(segment.value("arrival", ""));
                std::string duration = std::to_string(segment.value("duration", 0) / 60) + " мин";
                std::string fromTitle = segment.value("from", nlohmann::json::object()).value("title", "");
                std::string toTitle = segment.value("to", nlohmann::json::object()).value("title", "");

                std::cout << COLOR_GREEN << TEXT_BOLD << "⬆️  Прямой маршрут: " << COLOR_RESET << COLOR_GREEN << transport << "\n";
                std::cout << COLOR_RESET << TEXT_ITALIC << "   🕒 Отправление: " << COLOR_RESET << departure << TEXT_ITALIC << " | 🕓 Прибытие: " << COLOR_RESET << arrival << TEXT_ITALIC << " | ⏳ Длительность в пути: " << COLOR_RESET << duration << "\n";
                std::cout << TEXT_ITALIC << "   🚩 Место отправления: " << COLOR_RESET << fromTitle << TEXT_ITALIC << " | 🏁 Место прибытия: " << COLOR_RESET << toTitle << "\n";
            } else { // С пересадкой
                std::string departure = segment.value("departure", "");
                std::string arrival = segment.value("arrival", "");
                std::string fromTitle = segment.value("departure_from", nlohmann::json::object()).value("title", "");
                std::string toTitle = segment.value("arrival_to", nlohmann::json::object()).value("title", "");

                int totalDuration = calculateDuration(departure, arrival);
                std::string totalDurationStr = std::to_string(totalDuration) + " мин";

                std::cout << COLOR_YELLOW << TEXT_BOLD << "🔄 Маршрут с пересадкой: " << COLOR_RESET << COLOR_YELLOW << fromTitle << " → " << toTitle << "\n";
                std::cout << COLOR_RESET << TEXT_ITALIC << "   🕒 Отправление: " << COLOR_RESET << formatTime(departure) << TEXT_ITALIC << " | 🕓 Прибытие: " << COLOR_RESET << formatTime(arrival) << TEXT_ITALIC << " | ⏳ Длительность в пути: " << COLOR_RESET << totalDurationStr << "\n";

                if (segment.contains("details") && segment["details"].is_array()) {
                    int stage = 1;
                    for (const auto& detail : segment["details"]) {
                        if (detail.contains("is_transfer") && detail["is_transfer"].get<bool>()) {
                            std::string transferFrom = detail.value("transfer_from", nlohmann::json::object()).value("title", "");
                            std::string transferTo = detail.value("transfer_to", nlohmann::json::object()).value("title", "");
                            std::string transferDuration = std::to_string(detail.value("duration", 0) / 60) + " мин";

                            std::string transferTransport = "";
                            if (detail.contains("thread") && detail["thread"].contains("transport_type")) {
                                transferTransport = transportTypeTranslation(detail["thread"]["transport_type"]);
                            }

                            std::cout << COLOR_YELLOW << TEXT_ITALIC << "   🔄 Место пересадки: " << COLOR_RESET << COLOR_YELLOW << transferFrom << " → " << transferTo;
                            if (!transferTransport.empty()) {
                                std::cout << " (" << transferTransport << ")";
                            }
                            std::cout << " | ⏳ Время ожидания: " << transferDuration << "\n" << COLOR_RESET;
                        } else {
                            std::string transport = detail.value("thread", nlohmann::json::object()).value("transport_type", "");
                            std::string departure = detail.value("departure", "");
                            std::string arrival = detail.value("arrival", "");
                            std::string fromTitle = detail.value("from", nlohmann::json::object()).value("title", "");
                            std::string toTitle = detail.value("to", nlohmann::json::object()).value("title", "");

                            transport = transportTypeTranslation(transport);

                            std::cout << COLOR_BLUE << TEXT_BOLD << "   🚆 Этап " << COLOR_RESET << COLOR_BLUE << stage++ << ": " << fromTitle << " → " << toTitle;
                            if (!transport.empty()) {
                                std::cout << " (" << transport << ")";
                            }
                            std::cout << "\n";
                            std::cout << COLOR_RESET << TEXT_ITALIC << "   🕒 Отправление: " << COLOR_RESET << formatTime(departure) << TEXT_ITALIC << " | 🕓 Прибытие: " << COLOR_RESET << formatTime(arrival) << TEXT_ITALIC << " | ⏳ Длительность в пути: " << COLOR_RESET << totalDurationStr << "\n";
                        }
                    }
                }
            }

            std::cout << "\n-------------------------------------------------------------\n\n";
        } catch (const std::exception& error) {
            std::cerr << "Ошибка при обработке маршрута: " << error.what() << std::endl;
        }
    }
}
