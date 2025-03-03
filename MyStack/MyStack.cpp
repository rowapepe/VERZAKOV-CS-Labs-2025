#include "MyStack.hpp"
#include <stdexcept>

namespace MyStack {
template<class INF>
MyStack<INF>::MyStack(void) : top(nullptr) {
}

template<class INF>
MyStack<INF>::MyStack(const MyStack<INF>& other) {
    top = nullptr;
    if (other.empty()) {
        throw std::runtime_error("Стек пустой, копирование невозможно.");
    }

    MyStack<INF> reversedStack;

    Node* current = other.top;
    while (current) {
        reversedStack.push(current->d);
        current = current->next;
    }

    while (!reversedStack.empty()) {
        push(reversedStack.top_inf());
        reversedStack.pop();
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
    if (this == &other) {
        return *this;
    }

    while (!empty()) {
        pop();
    }

    if (other.empty()) {
        return *this;
    }

    MyStack<INF> reversedStack;

    Node* current = other.top;
    while (current) {
        reversedStack.push(current->d);
        current = current->next;
    }

    while (!reversedStack.empty()) {
        push(reversedStack.top_inf());
        reversedStack.pop();
    }

    return *this;
}

template<class INF>
bool MyStack<INF>::empty(void) {
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
INF MyStack<INF>::top_inf(void) {
    if (empty()) {
        throw std::runtime_error("Стек пустой.");
    }

    return top->d;
}

template<class INF>
void MyStack<INF>::Multipliers(int n, MyStack<INF>& stack, bool reversed) {
    if (n <= 0) {
        throw std::invalid_argument("Число N не валидно.");
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
