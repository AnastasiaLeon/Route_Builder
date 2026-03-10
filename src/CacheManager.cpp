#include "CacheManager.h"
#include <fstream>
#include <iostream>

CacheManager::CacheManager(const std::string& file) : cacheFile(file) {
    loadFromFile();
}

std::optional<nlohmann::json> CacheManager::getFromCache(const std::string& key) {
    if (memoryCache.find(key) != memoryCache.end()) {
        CacheEntry& entry = memoryCache[key];
        if (isCacheEntryValid(entry)) {
            return entry.data;  // если данные актуальны -> возвращаем их
        } else {
            memoryCache.erase(key);  // если неактуальны -> удаляем
        }
    }
    return std::nullopt;
}

void CacheManager::setToCache(const std::string& key, const nlohmann::json& value) {
    CacheEntry entry;
    entry.data = value;
    entry.timestamp = std::chrono::system_clock::now();  // текущее время
    memoryCache[key] = entry;  // сохраняем данные в кэше
    saveToFile();  // сохраняем кэш в файл
}

void CacheManager::saveToFile() {
    std::ofstream file(cacheFile);
    if (file) {
        nlohmann::json cacheJson;
        for (const auto& [key, entry] : memoryCache) {
            nlohmann::json entryJson;
            entryJson["data"] = entry.data;
            entryJson["timestamp"] = std::chrono::system_clock::to_time_t(entry.timestamp);
            cacheJson[key] = entryJson;
        }
        file << cacheJson.dump(4);
    } else {
        std::cerr << "Ошибка: Не удалось открыть файл для записи кэша." << std::endl;
        throw CacheException("Не удалось открыть файл для записи кэша: " + cacheFile);
    }
}

void CacheManager::loadFromFile() {
    std::ifstream file(cacheFile);
    if (file) {
        nlohmann::json cacheJson;
        try {
            file >> cacheJson;
            for (const auto& [key, entryJson] : cacheJson.items()) {
                CacheEntry entry;
                entry.data = entryJson["data"];
                entry.timestamp = std::chrono::system_clock::from_time_t(entryJson["timestamp"]);
                memoryCache[key] = entry;
            }
        } catch (const std::exception& error) {
            std::cerr << "Ошибка при загрузке кэша: " << error.what() << std::endl;
            throw CacheException("Ошибка при загрузке кэша: " + std::string(error.what()));
        }
    } else {
        // отсутствие файла кэша - не ршибка и он будет создан при первой записи
    }
}

void CacheManager::clearCache() {
    memoryCache.clear();
    saveToFile();
}

void CacheManager::removeOldEntries() {
    auto now = std::chrono::system_clock::now();
    for (auto i = memoryCache.begin(); i != memoryCache.end(); ) {
        if (!isCacheEntryValid(i->second)) {
            i = memoryCache.erase(i);
        } else {
            i++;
        }
    }
    saveToFile();
}

bool CacheManager::isCacheEntryValid(const CacheEntry& entry) const {
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::hours>(now - entry.timestamp);
    return duration.count() < CACHE_VALIDITY_HOURS;
}