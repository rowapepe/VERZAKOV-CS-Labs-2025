#include "planets.hpp"
#include <cstring>
#include <fstream>
#include <iostream>

namespace {
const int kBuffSize = 100;

int BinarySearch(Planets::Planet* planets, int size, const char* target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (planets[mid] == target) {
            return mid;
        } else if (planets[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}
}  // namespace

namespace Planets {
Planet::Planet(const char* n, int d, bool l, int sn) {
    name = new char[strlen(n) + 1];
    strcpy(name, n);

    diameter = d;
    life = l;
    satellitesNumber = sn;
}

Planet::Planet(const Planet& other) {
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    diameter = other.diameter;
    life = other.life;
    satellitesNumber = other.satellitesNumber;
}

Planet::~Planet() {
    delete[] name;
}

void Planet::SetName(const char* n) {
    if (name) {
        delete[] name;
    }

    name = new char[strlen(n) + 1];
    strcpy(name, n);
}

void Planet::SetDiameter(int d) {
    diameter = d;
}
void Planet::SetLife(bool l) {
    life = l;
}
void Planet::SetSatellitesNumber(int sn) {
    satellitesNumber = sn;
}

const char* Planet::GetName() const {
    return name;
}

int Planet::GetDiameter() const {
    return diameter;
}

bool Planet::GetLife() const {
    return life;
}

int Planet::GetSatellitesNumber() const {
    return satellitesNumber;
}

Planet& Planet::operator=(const Planet& other) {
    if (this == &other)
        return *this;

    delete[] name;

    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);

    diameter = other.diameter;
    life = other.life;
    satellitesNumber = other.satellitesNumber;

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Planet& planet) {
    os << planet.name << " " << planet.diameter << " " << planet.life << " " << planet.satellitesNumber << std::endl;

    return os;
}

std::istream& operator>>(std::istream& is, Planet& planet) {
    is >> planet.name >> planet.diameter >> planet.life >> planet.satellitesNumber;

    return is;
}

bool Planet::operator==(const char* n) {
    if (strcmp(this->name, n) == 0) {
        return true;
    } else {
        return false;
    }
}

bool Planet::operator<(const Planet& planet2) {
    if (strcmp(this->name, planet2.name) < 0) {
        return true;
    } else {
        return false;
    }
}

bool Planet::operator<(const char* n) {
    if (strcmp(this->name, n) < 0) {
        return true;
    } else {
        return false;
    }
}

void Planet::Resize(Planet*& planets, int& size) {
    Planet* newPlanets = new Planet[size + 1];

    for (int i = 0; i < size; ++i) {
        newPlanets[i] = planets[i];
    }

    DeleteDB(planets);
    planets = newPlanets;
    ++size;
}

void Planet::DeleteDB(Planet*& planets) {
    if (!planets) {
        return;
    }

    delete[] planets;
    planets = nullptr;
}

void Planet::ReadDB(Planet*& planets, int& size) {
    std::ifstream file("Planets.txt");
    if (!file) {
        std::cout << "Ошибка открытия файла!" << std::endl;
        return;
    }

    Planet temp;

    while (file >> temp) {
        if (size == 1 && planets[0] == "\0") {
            planets[0] = temp;
        } else {
            Resize(planets, size);
            planets[size - 1] = temp;
        }
    }

    file.close();
}

void Planet::WriteDB(Planet*& planets, int size) {
    if (!planets) {
        return;
    }

    std::ofstream file("Planets.txt");
    if (!file) {
        std::cout << "Ошибка открытия файла!" << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        file << planets[i];
    }

    file.close();
}

void Planet::SortDB(Planet*& planets, int left, int right) {
    if (!planets || left >= right) {
        return;
    }

    Planet pivot = planets[right];
    int partitionIndex = left;

    for (int i = left; i < right; ++i) {
        if (planets[i] < pivot) {
            std::swap(planets[i], planets[partitionIndex]);
            ++partitionIndex;
        }
    }
    std::swap(planets[right], planets[partitionIndex]);

    SortDB(planets, left, partitionIndex - 1);
    SortDB(planets, partitionIndex + 1, right);
}

void Planet::AddElement(Planet*& planets, int& size) {
    if (!planets) {
        return;
    }

    Resize(planets, size);

    std::cout << "Введите название планеты, диаметр, жизнь (есть - 1, нет - 0), количество спутников: ";
    std::cin >> planets[size - 1];
    std::cout << std::endl;
}

void Planet::DeleteElement(Planet*& planets, int& size) {
    if (!planets) {
        return;
    }

    char n[kBuffSize]{};
    std::cout << "Введите название планеты для удаления: ";
    std::cin >> n;
    std::cout << std::endl;

    SortDB(planets, 0, size - 1);
    int point = BinarySearch(planets, size, n);

    if (point == -1) {
        std::cout << "Планета не найдена." << std::endl;
        return;
    }

    Planet* newPlanets = new Planet[size - 1];

    for (int i = 0, j = 0; i < size; ++i) {
        if (i == point) {
            continue;
        }
        newPlanets[j++] = planets[i];
    }
 
    DeleteDB(planets);
    planets = newPlanets;
    --size;
}

void Planet::EditDB(Planet*& planets, int size) {
    if (!planets) {
        return;
    }

    char nameToEdit[kBuffSize]{};
    std::cout << "Введите название планеты, которую хотите изменить: ";
    std::cin >> nameToEdit;
    std::cout << std::endl;

    SortDB(planets, 0, size - 1);

    int point = BinarySearch(planets, size, nameToEdit);

    if (point == -1) {
        std::cout << "Планета не найдена." << std::endl;
        return;
    }

    std::cout << "Введите измененные название планеты, диаметр, наличие жизни (есть - 1, нет - 0), количество спутников: ";
    std::cin >> planets[point];
    std::cout << std::endl;
}

void Planet::PrintDB(Planet*& planets, int size) {
    if (!planets) {
        return;
    }

    const char* l{};

    for (int i = 0; i < size; ++i) {
        l = "нет";

        if (planets[i].life) {
            l = "есть";
        }
        std::cout << "Название планеты: " << planets[i].name << '\n'
                  << "Диаметр: " << planets[i].diameter << '\n'
                  << "Жизнь: " << l << '\n'
                  << "Количество спутников: " << planets[i].satellitesNumber << '\n'
                  << '\n';
    }
}
}  // namespace Planets
