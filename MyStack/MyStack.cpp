#include "MyStack.hpp"
#include <stdexcept>

namespace MyStack {
template<class INF>
MyStack<INF>::MyStack(void) : top(nullptr) {
}

template<class INF>
MyStack<INF>::MyStack(const MyStack<INF>& other) : top(nullptr) {
    if (other.empty()) {
        throw std::runtime_error("Стек пустой, копирование невозможно.");
    }

    Node* current = other.top;
    Node* prev = nullptr;

    while (current) {
        Node* newNode = new Node;
        newNode->d = current->d;
        newNode->next = nullptr;

        if (!top) {
            top = newNode;
        } else {
            prev->next = newNode;
        }

        prev = newNode;
        current = current->next;
    }
}

template<class INF>
MyStack<INF>::~MyStack(void) {
    while (!empty()) {
        pop();
    }
}

template<class INF>
MyStack<INF>& MyStack<INF>::operator=(const MyStack<INF>& other) {
    if (other.empty()) {
        throw std::runtime_error("Стек пустой, копирование невозможно.");
    }

    if (this == &other) {
        return *this;
    }

    while (!empty()) {
        pop();
    }

    Node* current = other.top;
    Node* prevNew = nullptr;

    while (current) {
        Node* newNode = new Node;
        newNode->d = current->d;
        newNode->next = nullptr;

        if (!top) {
            top = newNode;
        } else {
            prevNew->next = newNode;
        }

        prevNew = newNode;
        current = current->next;
    }

    return *this;
}

template<class INF>
bool MyStack<INF>::empty(void) const {
    return top == nullptr;
}

template<class INF>
bool MyStack<INF>::push(INF n) {
    Node* newNode = new Node;
    newNode->d = n;
    newNode->next = top;
    top = newNode;

    return true;
}

template<class INF>
bool MyStack<INF>::pop(void) {
    if (empty()) {
        return false;
    }
    Node* temp = top;
    top = top->next;
    delete temp;

    return true;
}

template<class INF>
INF MyStack<INF>::top_inf(void) const {
    if (empty()) {
        throw std::runtime_error("Стек пустой.");
    }

    return top->d;
}

template<class INF>
void MyStack<INF>::Multipliers(int n, MyStack<INF>& stack, bool reversed) {
    if (n <= 0) {
        throw std::invalid_argument("Число N невалидно.");
    }

    MyStack<INF> tempStack;

    tempStack.push(1);
    for (int div = 2; div <= n && n > 1; ++div) {
        while (n % div == 0) {
            tempStack.push(div);
            n /= div;
        }
    }

    if (reversed) {
        while (!tempStack.empty()) {
            stack.push(tempStack.top_inf());
            tempStack.pop();
        }
    } else {
        stack = tempStack;
    }
}

template class MyStack<int>;
}  // namespace MyStack
