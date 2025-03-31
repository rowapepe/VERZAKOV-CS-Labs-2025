#pragma once
#include <iostream>
#include <stdexcept>

namespace MyStack {
template<class INF, class FRIEND>
class ListNode {
 private:
    INF d;
    ListNode* next;
    ListNode(void) { next = nullptr; }

    friend FRIEND;
};

template<class INF>
class MyStack {
    typedef class ListNode<INF, MyStack<INF>> Node;
    Node* top;

 public:
    MyStack(void);
    MyStack(const MyStack<INF>& other);
    ~MyStack(void);
    bool empty(void) const;
    bool push(INF n);
    bool pop(void);
    INF top_inf(void) const;
};

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
}  // namespace MyStack
