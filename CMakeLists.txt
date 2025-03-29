cmake_minimum_required(VERSION 3.23)

project(lab7)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp)

add_subdirectory(Organizations)
add_subdirectory(MyStack)
add_subdirectory(Functions)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC Organizations)
target_link_libraries(${PROJECT_NAME} Organizations)

target_include_directories(${PROJECT_NAME} PUBLIC MyStack)
target_link_libraries(${PROJECT_NAME} MyStack)

target_include_directories(${PROJECT_NAME} PUBLIC Functions)
target_link_libraries(${PROJECT_NAME} Functions)
