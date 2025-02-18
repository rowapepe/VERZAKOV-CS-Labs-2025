#include "planets.hpp"
#include <cstring>
#include <fstream>
#include <iostream>

namespace Planets {
Planet::Planet(const char* n, int d, bool l, int sn) {
    name = new char[strlen(n) + 1];
    strcpy(name, n);

    diameter = d;
    life = l;
    satellitesNumber = sn;
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

char* Planet::GetName() {
    return name;
}

int Planet::GetDiameter() {
    return diameter;
}

bool Planet::GetLife() {
    return life;
}

int Planet::GetSatellitesNumber() {
    return satellitesNumber;
}

void Planet::PrintPlanet() {
    const char* l = "нет";

    if (life) {
        l = "есть";
    }

    std::cout << "Название планеты: " << name << '\n'
              << "Диаметр: " << diameter << '\n'
              << "Жизнь: " << l << '\n'
              << "Количество спутников: " << satellitesNumber << '\n'
              << '\n';
}

void Planet::ReadDB(std::fstream& file, Planet*& planets, int& size) {
    while (!file.eof()) {
        char nameBuffer[100]{};
        int diameter{};
        int satellites{};
        bool life{};

        file >> nameBuffer >> diameter >> life >> satellites;

        if (file.fail()) {
            break;
        }

        Planet::Resize(planets, size);
        planets[size - 1].SetName(nameBuffer);
        planets[size - 1].SetDiameter(diameter);
        planets[size - 1].SetLife(life);
        planets[size - 1].SetSatellitesNumber(satellites);

        ++size;
    }
}

void Planet::DeleteDB(Planet*& planets, int size) {
    if (!planets)
        return;
    delete[] planets;
    planets = nullptr;
}

void Planet::Resize(Planet*& planets, int& size) {
    Planet* newPlanets = new Planet[size + 1];

    for (int i = 0; i < size; ++i) {
        newPlanets[i].SetName(planets[i].GetName());
        newPlanets[i].SetDiameter(planets[i].GetDiameter());
        newPlanets[i].SetLife(planets[i].GetLife());
        newPlanets[i].SetSatellitesNumber(planets[i].GetSatellitesNumber());
    }

    DeleteDB(planets, size);
    planets = newPlanets;
    ++size;
}

}  // namespace Planets
