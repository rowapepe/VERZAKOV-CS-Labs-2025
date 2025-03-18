#ifndef INHERITANCE_MYSET_H
#define INHERITANCE_MYSET_H

#include <iostream>
#include "myvector.h"

template<class T>
class MySet : public MyVector<T> {
 public:
    MySet(T el = NULL) : MyVector<T>(el) {}

    bool operator==(const MySet<T>& s) const {
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

    MySet<T>& operator+=(const MySet<T>& s) {
        for (int i = 0; i < s.size; ++i) {
            this->add_element(s.operator[](i));
        }
        return *this;
    }

    MySet<T>& operator-=(const MySet<T>& s) {
        for (int i = 0; i < s.size; ++i) {
            this->delete_element(s.operator[](i));
        }
        return *this;
    }

    MySet<T>& operator*=(const MySet<T>& s) {
        for (int i = 0; i < this->size; ++i) {
            if (!s.is_element(this->operator[](i))) {
                this->delete_element(this->operator[](i));
            }
        }
        return *this;
    }

    void add_element(T el) {
        if (!this->is_element(el)) {
            MyVector<T>::add_element(el);
            this->sort();
        }
    }

    void delete_element(T el) {
        int index = this->find(el);
        if (index != -1) {
            MyVector<T>::delete_element(index);
        }
    }

    bool is_element(T el) const {
        for (int i = 0; i < this->size; ++i) {
            if (this->operator[](i) == el) {
                return true;
            }
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& out, const MySet<T>& s) {
        out << "[";
        for (int i = 0; i < s.size; ++i) {
            if (i > 0) {
                out << ", ";
            }
            out << s.operator[](i);
        }
        out << "]";
        return out;
    }

    friend MySet<T> operator+(const MySet<T>& s1, const MySet<T>& s2) {
        MySet<T> result = s1;
        result += s2;
        return result;
    }

    friend MySet<T> operator-(const MySet<T>& s1, const MySet<T>& s2) {
        MySet<T> result = s1;
        result -= s2;
        return result;
    }

    friend MySet<T> operator*(const MySet<T>& s1, const MySet<T>& s2) {
        MySet<T> result = s1;
        result *= s2;
        return result;
    }
};

#endif  // INHERITANCE_MYSET_H
