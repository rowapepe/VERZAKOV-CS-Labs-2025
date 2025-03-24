cmake_minimum_required(VERSION 3.23)

project(Organizations)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES organization.cpp insurance.cpp shipbuilding.cpp plant.cpp)
set(HEADERS organization.hpp insurance.hpp shipbuilding.hpp plant.hpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
