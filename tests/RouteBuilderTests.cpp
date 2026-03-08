#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <cstdio>
#include <string>

#include "Schedule.h"
#include "CacheManager.h"
#include "YandexScheduleAPI.h"

// ScheduleTests

TEST(ScheduleTests, CalculateDurationSimple) {
    std::string from = "2026-04-01T10:00:00";
    std::string to   = "2026-04-01T11:30:00";

    int minutes = Schedule::calculateDuration(from, to);
    EXPECT_EQ(minutes, 90);
}

TEST(ScheduleTests, CalculateDurationZero) {
    std::string from = "2026-04-01T10:00:00";
    std::string to   = "2026-04-01T10:00:00";

    int minutes = Schedule::calculateDuration(from, to);
    EXPECT_EQ(minutes, 0);
}

TEST(ScheduleTests, CalculateDurationLong) {
    std::string from = "2026-04-01T08:00:00";
    std::string to   = "2026-04-02T08:00:00";

    int minutes = Schedule::calculateDuration(from, to);
    EXPECT_EQ(minutes, 1440);
}

TEST(ScheduleTests, CalculateDurationInvalidDeparture) {
    EXPECT_THROW(
        Schedule::calculateDuration("не-дата", "2026-04-01T10:00:00"),
        TimeParseException
    );
}

TEST(ScheduleTests, CalculateDurationInvalidArrival) {
    EXPECT_THROW(
        Schedule::calculateDuration("2026-04-01T10:00:00", "не-дата"),
        TimeParseException
    );
}

TEST(ScheduleTests, FormatTimeRemovesTimezoneAndAddsMsk) {
    std::string raw = "2026-04-01T20:30:00+03:00";
    std::string formatted = Schedule::formatTime(raw);

    EXPECT_EQ(formatted, "2026-04-01 20:30:00 МСК");
}

TEST(ScheduleTests, FormatTimeNegativeTimezone) {
    std::string raw = "2026-04-01T10:00:00-05:00";
    std::string formatted = Schedule::formatTime(raw);

    EXPECT_EQ(formatted, "2026-04-01 10:00:00 МСК");
}

TEST(ScheduleTests, FormatTimeNoTimezone) {
    std::string raw = "2026-04-01T15:45:00";
    std::string formatted = Schedule::formatTime(raw);

    EXPECT_EQ(formatted, "2026-04-01 15:45:00 МСК");
}

TEST(ScheduleTests, PrintScheduleNoSegmentsKey) {
    nlohmann::json emptyJson;
    EXPECT_NO_THROW(Schedule::printSchedule(emptyJson, false));
}

TEST(ScheduleTests, PrintScheduleEmptySegments) {
    nlohmann::json json;
    json["segments"] = nlohmann::json::array();
    EXPECT_NO_THROW(Schedule::printSchedule(json, false));
}

TEST(ScheduleTests, PrintScheduleDirectRoute) {
    nlohmann::json segment;
    segment["has_transfers"] = false;
    segment["transfers_count"] = 0;
    segment["departure"] = "2026-04-01T10:00:00";
    segment["arrival"]   = "2026-04-01T12:00:00";
    segment["duration"]  = 7200;
    segment["from"]      = {{"title", "Москва"}};
    segment["to"]        = {{"title", "Санкт-Петербург"}};
    segment["thread"]    = {{"transport_type", "train"}};

    nlohmann::json json;
    json["segments"] = nlohmann::json::array({segment});

    EXPECT_NO_THROW(Schedule::printSchedule(json, false));
}

TEST(ScheduleTests, PrintScheduleTransferRouteSkippedWhenNotRequested) {
    nlohmann::json segment;
    segment["has_transfers"] = true;
    segment["transfers_count"] = 1;
    segment["departure"] = "2026-04-01T10:00:00";
    segment["arrival"]   = "2026-04-01T18:00:00";
    segment["departure_from"] = {{"title", "Москва"}};
    segment["arrival_to"]     = {{"title", "Казань"}};

    nlohmann::json json;
    json["segments"] = nlohmann::json::array({segment});

    EXPECT_NO_THROW(Schedule::printSchedule(json, false));
}

TEST(ScheduleTests, PrintScheduleMoreThanOneTransferSkipped) {
    nlohmann::json segment;
    segment["has_transfers"] = true;
    segment["transfers_count"] = 2;
    segment["departure"] = "2026-04-01T10:00:00";
    segment["arrival"]   = "2026-04-01T22:00:00";

    nlohmann::json json;
    json["segments"] = nlohmann::json::array({segment});

    EXPECT_NO_THROW(Schedule::printSchedule(json, true));
}

// CacheManagerTests

TEST(CacheManagerTests, SaveAndLoadCacheFromFile) {
    const std::string cacheFile = "test_cache.json";
    const std::string key = "route_key";

    {
        CacheManager cache(cacheFile);
        nlohmann::json value;
        value["answer"] = 42;
        cache.setToCache(key, value);
    }

    {
        CacheManager cache(cacheFile);
        auto loaded = cache.getFromCache(key);
        ASSERT_TRUE(loaded.has_value());
        EXPECT_EQ((*loaded)["answer"], 42);
    }

    std::remove(cacheFile.c_str());
}

TEST(CacheManagerTests, MissingKeyReturnsNullopt) {
    const std::string cacheFile = "test_cache_miss.json";
    CacheManager cache(cacheFile);

    auto result = cache.getFromCache("nonexistent_key");
    EXPECT_FALSE(result.has_value());

    std::remove(cacheFile.c_str());
}

TEST(CacheManagerTests, ClearCacheRemovesAllEntries) {
    const std::string cacheFile = "test_cache_clear.json";
    CacheManager cache(cacheFile);

    cache.setToCache("key1", {{"x", 1}});
    cache.setToCache("key2", {{"x", 2}});
    cache.clearCache();

    EXPECT_FALSE(cache.getFromCache("key1").has_value());
    EXPECT_FALSE(cache.getFromCache("key2").has_value());

    std::remove(cacheFile.c_str());
}

TEST(CacheManagerTests, OverwriteExistingKey) {
    const std::string cacheFile = "test_cache_overwrite.json";
    CacheManager cache(cacheFile);

    cache.setToCache("key", {{"val", 1}});
    cache.setToCache("key", {{"val", 99}});

    auto result = cache.getFromCache("key");
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ((*result)["val"], 99);

    std::remove(cacheFile.c_str());
}

TEST(CacheManagerTests, MultipleKeysStoredCorrectly) {
    const std::string cacheFile = "test_cache_multi.json";
    CacheManager cache(cacheFile);

    cache.setToCache("a", {{"v", 1}});
    cache.setToCache("b", {{"v", 2}});
    cache.setToCache("c", {{"v", 3}});

    EXPECT_EQ((*cache.getFromCache("a"))["v"], 1);
    EXPECT_EQ((*cache.getFromCache("b"))["v"], 2);
    EXPECT_EQ((*cache.getFromCache("c"))["v"], 3);

    std::remove(cacheFile.c_str());
}

TEST(CacheManagerTests, RemoveOldEntriesKeepsValidEntries) {
    const std::string cacheFile = "test_cache_remove.json";
    CacheManager cache(cacheFile);

    cache.setToCache("fresh_key", {{"data", "fresh"}});
    cache.removeOldEntries();

    EXPECT_TRUE(cache.getFromCache("fresh_key").has_value());

    std::remove(cacheFile.c_str());
}

// MockScheduleAPITests

TEST(MockScheduleAPITests, ReturnsProvidedSchedule) {
    nlohmann::json mockData;
    mockData["segments"] = nlohmann::json::array();

    MockScheduleAPI api(mockData);

    std::string code = api.getCityCode("SomeCity");
    EXPECT_EQ(code, "SomeCity");

    auto schedule = api.getSchedule("from", "to", "2026-01-01");
    EXPECT_EQ(schedule, mockData);
}

TEST(MockScheduleAPITests, GetCityCodeReturnsInputAsIs) {
    nlohmann::json mockData;
    MockScheduleAPI api(mockData);

    EXPECT_EQ(api.getCityCode("Москва"), "Москва");
    EXPECT_EQ(api.getCityCode("c200"), "c200");
    EXPECT_EQ(api.getCityCode(""), "");
}

TEST(MockScheduleAPITests, GetScheduleIgnoresArguments) {
    nlohmann::json mockData;
    mockData["segments"] = {{{"has_transfers", false}, {"transfers_count", 0}}};

    MockScheduleAPI api(mockData);

    auto r1 = api.getSchedule("A", "B", "2026-01-01");
    auto r2 = api.getSchedule("X", "Y", "2099-12-31");
    EXPECT_EQ(r1, mockData);
    EXPECT_EQ(r2, mockData);
}

TEST(MockScheduleAPITests, PrintScheduleWithMockData) {
    nlohmann::json segment;
    segment["has_transfers"] = false;
    segment["transfers_count"] = 0;
    segment["departure"] = "2026-06-01T09:00:00";
    segment["arrival"]   = "2026-06-01T11:00:00";
    segment["duration"]  = 7200;
    segment["from"]      = {{"title", "Екатеринбург"}};
    segment["to"]        = {{"title", "Тюмень"}};
    segment["thread"]    = {{"transport_type", "bus"}};

    nlohmann::json mockData;
    mockData["segments"] = nlohmann::json::array({segment});

    MockScheduleAPI api(mockData);
    auto schedule = api.getSchedule("from", "to", "2026-06-01");

    EXPECT_NO_THROW(Schedule::printSchedule(schedule, false));
}
