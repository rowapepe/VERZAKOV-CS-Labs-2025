cmake_minimum_required(VERSION 3.23)

project(lab2)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp Executor.cpp)
set(HEADERS Executor.hpp candidats.hpp)

add_subdirectory(planets)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC planets)
target_link_libraries(${PROJECT_NAME} planets)

link_directories(${CMAKE_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/libcandidats.a)
