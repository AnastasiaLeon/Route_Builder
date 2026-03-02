#include "CacheManager.h"
#include <fstream>
#include <iostream>

CacheManager::CacheManager(const std::string& file) : cacheFile(file) {
    loadFromFile();
}

nlohmann::json CacheManager::getFromCache(const std::string& key) {
    if (memoryCache.find(key) != memoryCache.end()) {
        CacheEntry& entry = memoryCache[key];
        if (isCacheEntryValid(entry)) {
            return entry.data;  // Если данные актуальны -> возвращаем их
        } else {
            memoryCache.erase(key);  // Если неактуальны -> удаляем
        }
    }
    return nullptr;
}

void CacheManager::setToCache(const std::string& key, const nlohmann::json& value) {
    CacheEntry entry;
    entry.data = value;
    entry.timestamp = std::chrono::system_clock::now();  // Текущее время
    memoryCache[key] = entry;  // Сохраняем данные в кэше
    saveToFile();  // Сохраняем кэш в файл
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
        file << cacheJson.dump(4);  // Сохранение кэша в формате json
    } else {
        std::cerr << "Ошибка: Не удалось открыть файл для записи кэша." << std::endl;
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
        }
    } else {
        std::cerr << "Ошибка: Не удалось открыть файл для чтения кэша." << std::endl;
    }
}

void CacheManager::clearCache() {
    memoryCache.clear();  // Очищение кэша в памяти
    saveToFile();  // Сохранение изменения в файле
}

void CacheManager::removeOldEntries() {
    auto now = std::chrono::system_clock::now();
    for (auto i = memoryCache.begin(); i != memoryCache.end(); ) {
        if (!isCacheEntryValid(i->second)) {
            i = memoryCache.erase(i);  // Удаление неактуальных записей
        } else {
            i++;
        }
    }
    saveToFile();  // Сохранение изменений в файле
}

bool CacheManager::isCacheEntryValid(const CacheEntry& entry) const {
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::hours>(now - entry.timestamp);
    return duration.count() < 24;  // Данные актуальны 24 часа
}