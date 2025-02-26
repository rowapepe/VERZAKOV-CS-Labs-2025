#pragma once
#include <cstddef>
#include <iostream>

namespace Fractions {
class Fraction {
 private:
    int numerator;
    int denominator;

 public:
    Fraction(int num = 0, int denom = 1);
    Fraction(const char* str);
    Fraction(double value);

    void SetNumerator(int num);
    void SetDenominator(int denom);

    const int GetNumerator();
    const int GetDenominator();

    Fraction& Reduct();

    friend std::ostream& operator<<(std::ostream& os, Fraction& frac);
    friend std::istream& operator>>(std::istream& is, Fraction& frac);

    Fraction operator+(int value);
    friend Fraction operator+(int value, const Fraction& frac);
    Fraction operator+(const Fraction& other);

    Fraction operator+(double value);
    friend Fraction operator+(double value, const Fraction& frac);

    Fraction& operator+=(int value);
    Fraction& operator+=(const Fraction& other);
    Fraction& operator+=(double value);
};
}  // namespace Fractions
