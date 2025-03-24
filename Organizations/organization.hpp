#pragma once

#include <cstring>
#include <iostream>

class Organization {
 protected:
    char* name;
    int year;

 public:
    Organization(const char* name, int year);
    virtual ~Organization();

    virtual void show() const = 0;
};
