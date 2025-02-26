#include "fractions.hpp"
#include <cmath>
#include <cstring>
#include <iostream>

namespace {
const int N_DEC = 4;
const int kBufferSize = 100;

int CalculateGCD(int a, int b) {
    while (b > 0) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}
}  // namespace

namespace Fractions {
Fraction& Fraction::Reduct() {
    int divisor = CalculateGCD(abs(this->numerator), abs(this->denominator));
    if (divisor != 0) {
        this->numerator /= divisor;
        this->denominator /= divisor;
    }

    if (this->denominator < 0) {
        this->numerator = -this->numerator;
        this->denominator = -this->denominator;
    }

    return *this;
}

Fraction::Fraction(int num, int denom) {
    if (denom == 0) {
        throw std::invalid_argument("Делитель не может равняться 0.");
    }

    numerator = num;
    denominator = denom;
    Reduct();
}

Fraction::Fraction(const char* str) {
    int integerPart = 0;
    int num = 0;
    int denom = 1;
    int sign = (str[0] == '-') ? -1 : 1;

    char buffer[kBufferSize]{};
    strncpy(buffer, str, kBufferSize - 1);

    char* number = strtok(buffer, " /");

    int numberCount = 0;
    while (number) {
        numberCount++;
        if (numberCount == 1) {
            integerPart = std::atoi(number);
        } else if (numberCount == 2) {
            num = std::atoi(number);
        } else if (numberCount == 3) {
            denom = std::atoi(number);
        }
        number = strtok(nullptr, " /");
    }

    if (numberCount == 3) {
        numerator = abs(integerPart) * denom + num;
    } else if (numberCount == 2) {
        numerator = integerPart;
        denom = num;
    } else if (numberCount == 1) {
        numerator = integerPart;
        denom = 1;
    } else {
        throw std::invalid_argument("Введен некорректный формат.");
    }

    if (denom == 0) {
        throw std::invalid_argument("Делитель не может равняться 0.");
    }

    numerator *= sign;
    denominator = denom;

    Reduct();
}


Fraction::Fraction(double value) {
    double integerPart{};
    double fractionPart = std::modf(value, &integerPart);

    int scale = std::pow(10, N_DEC);

    numerator = static_cast<int>(integerPart * scale + std::round(fractionPart * scale));
    denominator = scale;

    Reduct();
}

void Fraction::SetNumerator(int num) {
    numerator = num;
}

void Fraction::SetDenominator(int denom) {
    if (denom == 0) {
        throw std::invalid_argument("Делитель не может равняться 0.");
    }

    denominator = denom;
}

const int Fraction::GetNumerator() {
    return numerator;
}

const int Fraction::GetDenominator() {
    return denominator;
}

std::ostream& operator<<(std::ostream& out, Fraction& frac) {
    if (frac.GetDenominator() == 1) {
        out << frac.GetNumerator();
    } else if (abs(frac.GetNumerator()) > frac.GetDenominator()) {
        int integerPart = frac.GetNumerator() / frac.GetDenominator();
        int remainder = abs(frac.GetNumerator() % frac.GetDenominator());

        out << integerPart << " " << remainder << "/" << frac.GetDenominator();
    } else {
        out << frac.GetNumerator() << "/" << frac.GetDenominator();
    }
    return out;
}

std::istream& operator>>(std::istream& in, Fraction& frac) {
    char buffer[kBufferSize];
    in.getline(buffer, kBufferSize);
    Fraction temp(buffer);
    frac = temp;

    return in;
}

Fraction Fraction::operator+(int value) {
    return *this + Fraction(value);
}

Fraction operator+(int value, const Fraction& frac) {
    return Fraction(value) + frac;
}

Fraction Fraction::operator+(const Fraction& other) {
    int num = this->numerator * other.denominator + other.numerator * this->denominator;
    int denom = this->denominator * other.denominator;

    Fraction result(num, denom);
    return result;
}

Fraction Fraction::operator+(double value) {
    return *this + Fraction(value);
}

Fraction operator+(double value, const Fraction& frac) {
    return Fraction(value) + frac;
}

Fraction& Fraction::operator+=(int value) {
    *this = *this + value;
    return *this;
}

Fraction& Fraction::operator+=(const Fraction& other) {
    *this = *this + other;
    return *this;
}

Fraction& Fraction::operator+=(double value) {
    *this = *this + value;
    return *this;
}
}  // namespace Fractions
