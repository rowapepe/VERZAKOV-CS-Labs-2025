#include "functions.hpp"

void print(MyStack::MyStack<Organization*>& container) {
    if (container.empty()) {
        std::cout << "Стек пустой." << std::endl;
        return;
    }

    MyStack::MyStack<Organization*> tempStack;
    std::cout << "Содержимое стека:" << std::endl;
    while (!container.empty()) {
        Organization* org = container.top_inf();
        org->show();
        tempStack.push(org);
        container.pop();
    }

    while (!tempStack.empty()) {
        container.push(tempStack.top_inf());
        tempStack.pop();
    }

    std::cout << std::endl;
}

bool remove(MyStack::MyStack<Organization*>& container, int index) {
    if (container.empty()) {
        return false;
    }

    MyStack::MyStack<Organization*> tempStack;
    int currentIndex = 0;

    while (!container.empty()) {
        if (currentIndex == index) {
            Organization* org = container.top_inf();
            delete org;
            container.pop();
            ++currentIndex;
            continue;
        }

        Organization* org = container.top_inf();
        tempStack.push(org);
        container.pop();
        ++currentIndex;
    }

    while (!tempStack.empty()) {
        container.push(tempStack.top_inf());
        tempStack.pop();
    }

    return true;
}

void clear(MyStack::MyStack<Organization*>& container) {
    while (!container.empty()) {
        Organization* org = container.top_inf();
        delete org;
        container.pop();
    }
}
