#pragma once

#include "organization.hpp"

class Plant : public Organization {
 private:
    int employees;

 public:
    Plant(const char* name, int year, int employees);
    ~Plant() override;

    void show() const override;
};
