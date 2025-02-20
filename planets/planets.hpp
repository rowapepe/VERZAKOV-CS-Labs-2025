#pragma once
#include <cstddef>
#include <fstream>

namespace Planets {
class Planet {
 private:
    char* name;
    int diameter;
    bool life;
    int satellitesNumber;

 public:
    Planet(const char* n = "\0", int d = 0, bool l = false, int sn = 0);
    Planet(const Planet& other);

    ~Planet();

    void SetName(const char* n);
    void SetDiameter(int d);
    void SetLife(bool l);
    void SetSatellitesNumber(int sn);

    char* GetName();
    int GetDiameter();
    bool GetLife();
    int GetSatellitesNumber();

    Planet& operator=(const Planet& other);
    friend std::ofstream& operator<<(std::ofstream& file, Planet& planet);
    friend std::ifstream& operator>>(std::ifstream& file, Planet& planet);
    bool operator==(const char* n);
    bool operator<(Planet& planet2);
    bool operator<(const char* n);

    static void Resize(Planet*& planets, int& size);
    static void DeleteDB(Planet*& planets, int size);

    static void ReadDB(Planet*& planets, int& size);
    static void WriteDB(Planet*& planets, int size);
    static void SortDB(Planet*& planets, int left, int right);
    static void AddElement(Planet*& planets, int& size);
    static void DeleteElement(Planet*& planets, int& size);
    static void EditDB(Planet*& planets, int size);
    static void PrintDB(Planet*& planets, int size);
};
}  // namespace Planets
