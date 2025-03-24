#include "plant.hpp"

Plant::Plant(const char* name, int year, int employees) : Organization(name, year), employees(employees) {
    std::cout << "Plant()" << std::endl;
}

Plant::~Plant() {
    std::cout << "~Plant()" << std::endl;
}

void Plant::show() const {
    std::cout << "Завод: " << name << ", основан в " << year << " году, количество сотрудников: " << employees << std::endl;
}
