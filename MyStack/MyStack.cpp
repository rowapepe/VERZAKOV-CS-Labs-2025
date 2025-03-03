#include "MyStack.hpp"
#include <stdexcept>

namespace MyStack {
template<class INF>
MyStack<INF>::MyStack(void) : top(nullptr) {
}

template<class INF>
MyStack<INF>::~MyStack(void) {
    while (!empty()) {
        pop();
    }
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
        throw std::invalid_argument("Стек пустой.");
    }
    return top->d;
}

template<class INF>
void MyStack<INF>::Multipliers(int n, MyStack<INF>& stack) {
    for (int i = 1; i <= n; ++i) {
        if (n % i == 0) {
            stack.push(i);
        }
    }
}

template class MyStack<int>;
}  // namespace MyStack
