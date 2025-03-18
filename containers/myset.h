#ifndef INHERITANCE_MYSET_H
#define INHERITANCE_MYSET_H

#include <iostream>
#include "myvector.h"

template<class T>
class MySet : public MyVector<T> {
public:
    MySet(T el = NULL);
    bool operator==(const MySet<T>& s) const;

    MySet<T>& operator+=(const MySet<T>& s);
    MySet<T>& operator-=(const MySet<T>& s);
    MySet<T>& operator*=(const MySet<T>& s);

    void add_element(T el);
    void delete_element(T el);
    bool is_element(T el) const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& out, const MySet<U>& s);

    template <typename U>
    friend MySet<U> operator+(const MySet<U>& s1, const MySet<U>& s2);

    template <typename U>
    friend MySet<U> operator-(const MySet<U>& s1, const MySet<U>& s2);

    template <typename U>
    friend MySet<U> operator*(const MySet<U>& s1, const MySet<U>& s2);
};

template<class T>
MySet<T>::MySet(T el) : MyVector<T>(el) {}

template<class T>
bool MySet<T>::operator==(const MySet<T>& s) const {
    if (this->size != s.size) {
        return false;
    }
    for (int i = 0; i < this->size; ++i) {
        if (!s.is_element(this->operator[](i))) {
            return false;
        }
    }
    return true;
}

template<class T>
MySet<T>& MySet<T>::operator+=(const MySet<T>& s) {
    for (int i = 0; i < s.size; ++i) {
        this->add_element(s[i]);
    }
    return *this;
}

template<class T>
MySet<T>& MySet<T>::operator-=(const MySet<T>& s) {
    for (int i = 0; i < s.size; ++i) {
        this->delete_element(s[i]);
    }
    return *this;
}

template<class T>
MySet<T>& MySet<T>::operator*=(const MySet<T>& s) {
    for (int i = 0; i < this->size; ++i) {
        if (!s.is_element(this->operator[](i))) {
            this->delete_element(this->operator[](i));
        }
    }
    return *this;
}

template<class T>
void MySet<T>::add_element(T el) {
    if (!this->is_element(el)) {
        MyVector<T>::add_element(el);
        this->sort();
    }
}

template<class T>
void MySet<T>::delete_element(T el) {
    int index = this->find(el);
    if (index != -1) {
        MyVector<T>::delete_element(index);
    }
}

template<class T>
bool MySet<T>::is_element(T el) const {
    for (int i = 0; i < this->size; ++i) {
        if (this->operator[](i) == el) {
            return true;
        }
    }
    return false;
}

template<class U>
std::ostream& operator<<(std::ostream& out, const MySet<U>& s) {
    out << "[";
    for (int i = 0; i < s.size; ++i) {
        if (i > 0) {
            out << ", ";
        }
        out << s[i];
    }
    out << "]";
    return out;
}

template<class U>
MySet<U> operator+(const MySet<U>& s1, const MySet<U>& s2) {
    MySet<U> result = s1;
    result += s2;
    return result;
}

template<class U>
MySet<U> operator-(const MySet<U>& s1, const MySet<U>& s2) {
    MySet<U> result = s1;
    result -= s2;
    return result;
}

template<class U>
MySet<U> operator*(const MySet<U>& s1, const MySet<U>& s2) {
    MySet<U> result = s1;
    result *= s2;
    return result;
}

#endif  // INHERITANCE_MYSET_H
