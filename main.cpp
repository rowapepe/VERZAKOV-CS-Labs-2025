#include <iostream>
#include "Organizations/insurance.hpp"
#include "Organizations/organization.hpp"
#include "Organizations/plant.hpp"
#include "Organizations/shipbuilding.hpp"
#include "Vector/myvector.hpp"
#include "Functions/functions.hpp"

int main() {
    MyVector<Organization*> organizations(nullptr, 5);

    organizations.add_element(new InsuranceCompany("Т-Страхование", 2013, 123131));
    organizations.add_element(new ShipbuildingCompany("ОСК", 2007, 120));
    organizations.add_element(new Plant("АвтоВАЗ", 1966, 4100));

    print(organizations);

    std::cout << "Удаление первого элемента:" << std::endl;
    remove_item(organizations, 0);
    print(organizations);

    std::cout << "Очистка контейнера:" << std::endl;
    clear_container(organizations);
    print(organizations);

    return 0;
}
