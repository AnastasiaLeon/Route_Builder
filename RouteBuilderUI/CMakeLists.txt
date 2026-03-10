cmake_minimum_required(VERSION 3.14)

project(RouteBuilderUI LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(RouteBuilderUI
    main.cpp
    mainwindow.cpp
    backend/BackendRunner.cpp
)

target_include_directories(RouteBuilderUI
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/backend
)

target_link_libraries(RouteBuilderUI
    PRIVATE
        Qt6::Widgets
)

