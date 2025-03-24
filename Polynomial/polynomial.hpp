#pragma once
#include <algorithm>
#include <sstream>
#include "../Term/term.hpp"

class Polynomial {
    Term* poly;
    int degree;
    int size;
    bool order_;

 public:
    Polynomial();
    Polynomial(int p);
    Polynomial(const Term& t);
    Polynomial(const Polynomial& p);
    ~Polynomial();

    void sort(bool increase);

    Polynomial& operator=(const Polynomial& p);
    Polynomial& operator+=(const Polynomial& p);
    Polynomial& operator*=(const Polynomial& p);

    friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2);
    friend Polynomial operator*(const Polynomial& p1, const Polynomial& p2);

    friend std::istream& operator>>(std::istream& in, Polynomial& p);
    friend std::ostream& operator<<(std::ostream& out, Polynomial& p);
};

void Polynomial::sort(bool increase) {
    order_ = increase;
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if ((increase && poly[j].exponent > poly[j + 1].exponent) || (!increase && poly[j].exponent < poly[j + 1].exponent)) {
                std::swap(poly[j], poly[j + 1]);
            }
        }
    }
}

Polynomial::Polynomial() : poly(nullptr), degree(), size(0), order_(true) {
}

Polynomial::Polynomial(int p) : degree(0), size(1), order_(true) {
    poly = new Term[1];
    poly[0] = Term(p, 0);
}

Polynomial::Polynomial(const Term& t) : degree(t.exponent), size(1), order_(true) {
    poly = new Term[1];
    poly[0] = t;
}

Polynomial::Polynomial(const Polynomial& p) {
    degree = p.degree;
    size = p.size;
    order_ = p.order_;

    poly = new Term[size];

    for (int i = 0; i < size; ++i) {
        poly[i] = p.poly[i];
    }
}

Polynomial::~Polynomial() {
    delete[] poly;
}

Polynomial& Polynomial::operator=(const Polynomial& p) {
    if (this == &p)
        return *this;

    delete[] poly;
    size = p.size;
    degree = p.degree;
    poly = new Term[size];
    for (int i = 0; i < size; i++) {
        poly[i] = p.poly[i];
    }
    return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& p) {
    for (int i = 0; i < p.size; ++i) {
        bool found = false;
        for (int j = 0; j < size; ++j) {
            if (poly[j].exponent == p.poly[i].exponent) {
                poly[j] = poly[j] + p.poly[i];
                found = true;
                break;
            }
        }

        if (!found) {
            Term* newPoly = new Term[size + 1];
            for (int j = 0; j < size; ++j) {
                newPoly[j] = poly[j];
            }
            newPoly[size] = p.poly[i];

            delete[] poly;
            poly = newPoly;
            ++size;
        }
    }

    for (int i = 0; i < size; ++i) {
        if (poly[i].GetCoefficient() == 0) {
            for (int j = i; j < size - 1; ++j) {
                poly[j] = poly[j + 1];
            }
            --size;
            --i;
        }
    }

    degree = std::max(degree, p.degree);
    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& p) {
    Polynomial result;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < p.size; ++j) {
            result += poly[i] * p.poly[j];
        }
    }

    *this = result;
    return *this;
}

Polynomial operator+(const Polynomial& p1, const Polynomial& p2) {
    Polynomial result = p1;
    result += p2;
    return result;
}

Polynomial operator*(const Polynomial& p1, const Polynomial& p2) {
    Polynomial result = p1;
    result *= p2;
    return result;
}

std::istream& operator>>(std::istream& in, Polynomial& p) {
    delete[] p.poly;
    p.poly = nullptr;
    p.size = 0;
    p.degree = 0;

    char buffer[256];
    in.getline(buffer, 256);

    char* token = buffer;
    char sign = '+';

    if (*token == '+' || *token == '-') {
        sign = *token;
        ++token;
    }

    while (*token) {
        while (*token == ' ') {
            ++token;
        }

        char* nextOp = std::strchr(token, '+');
        char* minusOp = std::strchr(token, '-');

        if (minusOp && (!nextOp || minusOp < nextOp)) {
            nextOp = minusOp;
        }

        char termBuffer[50];
        termBuffer[0] = sign;
        std::strcpy(termBuffer + 1, token);

        std::istringstream tempStream(termBuffer);

        Term temp;
        tempStream >> temp;
        p += Polynomial(temp);

        if (nextOp) {
            sign = *nextOp;
            token = nextOp + 1;
        } else {
            break;
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, Polynomial& p) {
    if (p.size == 0) {
        return out << "0";
    }

    bool firstTerm = true;
    for (int i = 0; i < p.size; ++i) {
        if (p.poly[i].GetCoefficient() == 0) {
            continue;
        }

        if (!firstTerm && p.poly[i].GetCoefficient() > 0) {
            out << "+";
        }

        out << p.poly[i];
        firstTerm = false;
    }

    return out;
}
