cmake_minimum_required(VERSION 3.23)

project(lab4)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp Executor.cpp)
set(HEADERS Executor.hpp)

add_subdirectory(MyStack)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC MyStack)
target_link_libraries(${PROJECT_NAME} MyStack)
