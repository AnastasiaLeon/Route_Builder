#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

#include <string>
#include <nlohmann/json.hpp>

class CacheManager {
private:
    struct CacheEntry {
        nlohmann::json data;
        std::chrono::system_clock::time_point timestamp; // Ирл время добавления
    };

    std::unordered_map<std::string, CacheEntry> memoryCache;  // Кэш в памяти
    std::string cacheFile;  // Файл для кэша на диске
    bool isCacheEntryValid(const CacheEntry& entry) const;

public:
    CacheManager(const std::string& file);
    nlohmann::json getFromCache(const std::string& key);
    void setToCache(const std::string& key, const nlohmann::json& value);  // Сохранить данные в кэше
    void saveToFile();
    void loadFromFile();
    void clearCache();
    void removeOldEntries();
};

#endif