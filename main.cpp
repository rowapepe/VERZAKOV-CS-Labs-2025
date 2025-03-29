#include <iostream>
#include "Organizations/insurance.hpp"
#include "Organizations/organization.hpp"
#include "Organizations/plant.hpp"
#include "Organizations/shipbuilding.hpp"
#include "MyStack/MyStack.hpp"
#include "Functions/functions.hpp"

int main() {
    MyStack::MyStack<Organization*> organizations;

    organizations.push(new InsuranceCompany("Т-Страхование", 2013, 123131));
    organizations.push(new ShipbuildingCompany("ОСК", 2007, 120));
    organizations.push(new Plant("АвтоВАЗ", 1966, 4100));

    print(organizations);

    std::cout << "Удаление первого элемента:" << std::endl;
    remove_item(organizations, 0);
    print(organizations);

    std::cout << "Очистка контейнера:" << std::endl;
    clear_container(organizations);
    print(organizations);

    return 0;
}
