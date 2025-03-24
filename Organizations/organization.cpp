#include "organization.hpp"

Organization::Organization(const char* name, int year) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    this->year = year;
    std::cout << "Organization()" << std::endl;
}

Organization::~Organization() {
    delete[] name;
    std::cout << "~Organization()" << std::endl;
}
