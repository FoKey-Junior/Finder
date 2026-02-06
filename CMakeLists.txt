cmake_minimum_required(VERSION 3.26)
project(finder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(finder MACOSX_BUNDLE
        src/main.cpp
        src/MainWindow.cpp
        include/MainWindow.h
)

target_include_directories(finder
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(finder
        PRIVATE
        Qt6::Widgets
)
