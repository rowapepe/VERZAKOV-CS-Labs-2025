#pragma once

#include "organization.hpp"

class ShipbuildingCompany : public Organization {
 private:
    int shipsBuilt;

 public:
    ShipbuildingCompany(const char* name, int year, int ships);
    ~ShipbuildingCompany() override;

    void show() const override;
};
