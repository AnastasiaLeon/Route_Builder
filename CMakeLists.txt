cmake_minimum_required(VERSION 3.14)
project(RouteBuilder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG        1.10.5
)
set(CPR_USE_SYSTEM_CURL ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)

add_executable(${PROJECT_NAME}
    main.cpp
    src/CacheManager.cpp
    src/Schedule.cpp
    src/YandexScheduleAPI.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        cpr::cpr
        nlohmann_json::nlohmann_json
)