#pragma once
#include <cstddef>
#include <fstream>

namespace Planets {
class Planet {
 private:
    char* name{};
    int diameter{};
    bool life{};
    int satellitesNumber{};

 public:
    Planet(const char* n = "\0", int d = 0, bool l = false, int sn = 0);
    ~Planet();

    void SetName(const char* n);
    void SetDiameter(int d);
    void SetLife(bool l);
    void SetSatellitesNumber(int sn);

    char* GetName();
    int GetDiameter();
    bool GetLife();
    int GetSatellitesNumber();

    static void ReadDB(std::fstream& file, Planet*& planets, int& size);
    static void Resize(Planet*& planets, int& size);
    static void DeleteDB(Planet*& planets, int size);

    void PrintPlanet();
};
}  // namespace Planets
