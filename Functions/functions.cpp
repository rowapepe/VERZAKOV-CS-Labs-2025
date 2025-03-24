#include "functions.hpp"
#include <iostream>

void print(const MyVector<Organization*>& container) {
    std::cout << "В контейнере содержится:" << std::endl;
    for (int i = 0; i < container.GetSize(); ++i) {
        std::cout << (i + 1) << ". ";
        container[i]->show();
    }
    std::cout << std::endl;
}

bool remove_item(MyVector<Organization*>& container, size_t index) {
    if (index >= container.GetSize()) {
        std::cout << "Индекс не валидный." << std::endl;
        return false;
    }

    delete container[index];
    return container.delete_element(index);
}

void clear_container(MyVector<Organization*>& container) {
    for (int i = 0; i < container.GetSize(); ++i) {
        delete container[i];
    }
    while (container.GetSize() > 0) {
        container.delete_element(0);
    }
}
