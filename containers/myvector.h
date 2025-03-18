#ifndef INHERITANCE_MYVECTOR_H
#define INHERITANCE_MYVECTOR_H

#include <cstring>
#include <iostream>

const int MAX_SIZE = 5;

template<class T>
class MyVector {
 protected:
    int max_size;
    int size;
    T* pdata;
    void resize(bool increase) {
        if (increase) {
            max_size *= 2;
            T* new_pdata = new T[max_size];
            for (int i = 0; i < size; ++i) {
                new_pdata[i] = pdata[i];
            }
            delete[] pdata;
            pdata = new_pdata;
        } else {
            max_size /= 2;
            T* new_pdata = new T[max_size];
            for (int i = 0; i < size; ++i) {
                new_pdata[i] = pdata[i];
            }
            delete[] pdata;
            pdata = new_pdata;
        }
    }

 public:
    MyVector(T el = NULL, int maxsize = MAX_SIZE) : max_size(maxsize), size(0) {
        pdata = new T[max_size];
        if (el) {
            add_element(el);
        }
    }

    MyVector(const MyVector& v) {
        max_size = v.max_size;
        size = v.size;
        pdata = new T[max_size];
        for (int i = 0; i < size; ++i) {
            pdata[i] = v.pdata[i];
        }
    }

    ~MyVector() { delete[] pdata; }

    void add_element(T el) {
        if (!el) {
            return;
        }

        if (size >= max_size) {
            resize(true);
        }
        pdata[size] = el;
        ++size;
    }

    bool delete_element(int i) {
        if (size == 0 || i < 0 || i >= size) {
            return false;
        }
        for (int j = i; j < size; ++j) {
            pdata[j] = pdata[j + 1];
        }
        --size;

        if (size > 0 && size <= max_size / 4 && max_size > MAX_SIZE) {
            resize(false);
        }

        return true;
    }

    const T& operator[](int i) const {
        if (i < 0 || i >= size) {
            throw std::invalid_argument("Индекс не валидный.");
        }
        return pdata[i];
    }

    void sort() {
        bool sorted = false;

        for (int i = 0; i < size && !sorted; ++i) {
            sorted = true;
            for (int j = 0; j < size - i - 1; ++j) {
                if (pdata[j] > pdata[j + 1]) {
                    std::swap(pdata[j], pdata[j + 1]);
                    sorted = false;
                }
            }
        }
    }

    int find(T el) const {
        for (int i = 0; i < size; ++i) {
            if (pdata[i] == el) {
                return i;
            }
        }
        return -1;
    }

    MyVector<T>& operator=(const MyVector<T>& v) {
        delete[] pdata;

        if (this == &v) {
            return *this;
        }

        this->max_size = v.max_size;
        this->size = v.size;
        this->pdata = new T[max_size];
        for (int i = 0; i < size; ++i) {
            this->pdata[i] = v.pdata[i];
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const MyVector<T>& v) {
        for (int i = 0; i < v.size; ++i) {
            out << v[i] << ' ';
        }
        out << '\n';
        return out;
    }
};

template<>
void MyVector<const char*>::sort() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (!strcmp(pdata[j], pdata[j + 1])) {
                std::swap(pdata[j], pdata[j + 1]);
            }
        }
    }
}

template<>
int MyVector<const char*>::find(const char* el) const {
    for (int i = 0; i < size; ++i) {
        if (!strcmp(pdata[i], el)) {
            return i;
        }
    }
    return -1;
}
#endif  // INHERITANCE_MYVECTOR_H
