#include <iostream>
#include "Executor.hpp"

void addElement(MyStack::MyStack<Organization*>& organizations) {
    int type;
    std::cout << "Выберите тип организации:" << std::endl;
    std::cout << "1. Страховая компания" << std::endl;
    std::cout << "2. Завод" << std::endl;
    std::cout << "3. Судостроительная компания" << std::endl;
    std::cin >> type;

    char name[100];
    int year;
    std::cin.ignore();
    std::cout << "Введите название: ";
    std::cin.getline(name, 100);
    std::cout << "Введите год основания: ";
    std::cin >> year;

    switch (static_cast<Type>(type)) {
        case Type::Insurance: {
            double assets;
            std::cout << "Введите сумму активов: ";
            std::cin >> assets;
            organizations.push(new InsuranceCompany(name, year, assets));
            break;
        }
        case Type::Plant: {
            int employees;
            std::cout << "Введите количество сотрудников: ";
            std::cin >> employees;
            organizations.push(new Plant(name, year, employees));
            break;
        }
        case Type::Ship: {
            int ships;
            std::cout << "Введите количество построенных судов: ";
            std::cin >> ships;
            organizations.push(new ShipbuildingCompany(name, year, ships));
            break;
        }
        default:
            std::cout << "Неверный выбор типа! Элемент не добавлен." << std::endl;
    }
    std::cout << std::endl;
}

void demo(MyStack::MyStack<Organization*>& organizations) {
    organizations.push(new InsuranceCompany("Т-Страхование", 2013, 123131));
    organizations.push(new ShipbuildingCompany("ОСК", 2007, 120));
    organizations.push(new Plant("АвтоВАЗ", 1966, 4100));

    print(organizations);

    std::cout << "Удаление первого элемента:" << std::endl;
    remove(organizations, 0);
    print(organizations);

    std::cout << "Очистка контейнера:" << std::endl;
    clear(organizations);
    print(organizations);
}

void menu() {
    MyStack::MyStack<Organization*> organizations;
    int choice = 0;

    std::cout << "======================================================" << std::endl;

    while (true) {
        std::cout << "1. Добавить элемент в контейнер\n"
                  << "2. Печать содержимого контейнера\n"
                  << "3. Удалить элемент по индексу\n"
                  << "4. Очистить контейнер\n"
                  << "5. Инициализация демо\n"
                  << "6. Выход\n"
                  << "Выберите задание: ";
        std::cin >> choice;
        std::cout << std::endl;

        switch (static_cast<Task>(choice)) {
            case Task::Add:
                addElement(organizations);
                break;
            case Task::Print:
                print(organizations);
                break;
            case Task::Delete: {
                int index;
                std::cout << "Введите индекс элемента для удаления: ";
                std::cin >> index;
                remove(organizations, index);
                break;
            }
            case Task::Clear:
                clear(organizations);
                break;
            case Task::Initialize:
                demo(organizations);
                return;
            case Task::Exit:
                return;
            default:
                std::cout << "Неверный номер задания" << std::endl;
        }
    }
}
