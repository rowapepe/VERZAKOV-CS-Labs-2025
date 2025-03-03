cmake_minimum_required(VERSION 3.23)

project(lab2)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp Executor.cpp)

add_subdirectory(planets)
add_subdirectory(candidats)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC planets)
target_link_libraries(${PROJECT_NAME} planets)

target_include_directories(${PROJECT_NAME} PUBLIC candidats)
target_link_libraries(${PROJECT_NAME} candidats)
