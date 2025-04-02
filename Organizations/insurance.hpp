#pragma once
#include "organization.hpp"

class InsuranceCompany : public Organization {
 protected:
    double totalAssets;

 public:
    InsuranceCompany(const char* name, int year, double assets);
    ~InsuranceCompany() override;

    void show() const override;
};
