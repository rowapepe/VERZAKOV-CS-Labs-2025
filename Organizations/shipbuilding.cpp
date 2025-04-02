#include "shipbuilding.hpp"

ShipbuildingCompany::ShipbuildingCompany(const char* name, int year, int employees, int ships) : Plant(name, year, employees), shipsBuilt(ships) {
    std::cout << "ShipbuildingCompany()" << std::endl;
}

ShipbuildingCompany::~ShipbuildingCompany() {
    std::cout << "~ShipbuildingCompany()" << std::endl;
}

void ShipbuildingCompany::show() const {
    std::cout << "Судостроительная компания: " << name << ", основана в " << year << " году, сотрудников: " << employees
              << ", построено судов: " << shipsBuilt << std::endl;
}
