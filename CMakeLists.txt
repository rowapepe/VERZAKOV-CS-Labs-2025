cmake_minimum_required(VERSION 3.23)

project(lab3)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp Executor.cpp)

add_subdirectory(fractions)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC fractions)
target_link_libraries(${PROJECT_NAME} fractions)
