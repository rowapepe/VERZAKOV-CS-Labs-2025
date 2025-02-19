cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME "planets")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

set(SOURCES planets.cpp)
set(HEADERS planets.hpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
