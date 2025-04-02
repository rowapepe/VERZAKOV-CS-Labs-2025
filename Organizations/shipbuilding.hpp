#pragma once

#include "plant.hpp"

class ShipbuildingCompany : public Plant {
 protected:
    int shipsBuilt;

 public:
    ShipbuildingCompany(const char* name, int year, int employees, int ships);
    ~ShipbuildingCompany() override;

    void show() const override;
};
