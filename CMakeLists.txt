cmake_minimum_required(VERSION 3.23)

project(lab6)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp)

add_subdirectory(Polynomial)
add_subdirectory(Term)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC Polynomial)
target_link_libraries(${PROJECT_NAME} Polynomial)

target_include_directories(${PROJECT_NAME} PUBLIC Term)
target_link_libraries(${PROJECT_NAME} Term)
