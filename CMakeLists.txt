# Проверяет версию CMake и останавливает конфигурацию, если версия ниже 3.23
cmake_minimum_required(VERSION 3.23)

# Создает переменную "project" с именем "lab1"
set(project "lab1")

# Инициализирует проект с именем из переменной "project"
project(${project})

# Устанавливает стандарт C++17 для компиляции проекта
set(CMAKE_CXX_STANDARD 17)

# Создает список исходных файлов проекта, добавляя туда main.cpp
set(${project}_SOURCES
        main.cpp)

# Добавляет поддиректорию "mymath" и подключает её CMakeLists.txt для сборки как отдельной библиотеки
add_subdirectory(mymath)

# Добавляет поддиректорию "division" и подключает её CMakeLists.txt для сборки как отдельной библиотеки
add_subdirectory(division)

# Копирует список исходных файлов в новую переменную для использования при создании исполняемого файла
set(${project}_SOURCE_LIST
        ${${project}_SOURCES})

# Создает исполняемый файл с именем проекта и добавляет в него исходные файлы из списка
add_executable(${project}
        ${${project}_SOURCE_LIST})

# Добавляет к исполняемому файлу библиотеку "mymath"
target_link_libraries(${project} mymath)

# Добавляет к исполняемому файлу библиотеку "division"
target_link_libraries(${project} division)
