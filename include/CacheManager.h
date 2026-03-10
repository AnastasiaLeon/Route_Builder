#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include <string>
#include <nlohmann/json.hpp>
#include <unordered_map>
#include <chrono>
#include <optional>
#include <stdexcept>

class CacheException : public std::runtime_error {
public:
    explicit CacheException(const std::string& message) : std::runtime_error(message) {}
};

class CacheManager {
private:
    struct CacheEntry {
        nlohmann::json data;
        std::chrono::system_clock::time_point timestamp; // ирл время добавления
    };

    std::unordered_map<std::string, CacheEntry> memoryCache;  // кэш в памяти
    std::string cacheFile;  // файл для кэша на диске
    static constexpr int CACHE_VALIDITY_HOURS = 24;  // данные актуальны 24 часа
    bool isCacheEntryValid(const CacheEntry& entry) const;

public:
    CacheManager(const std::string& file);
    std::optional<nlohmann::json> getFromCache(const std::string& key);
    void setToCache(const std::string& key, const nlohmann::json& value);  // сохранить данные в кэше
    void saveToFile();
    void loadFromFile();
    void clearCache();
    void removeOldEntries();
};

#endif