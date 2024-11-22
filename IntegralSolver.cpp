#include "IntegralSolver.hpp"

#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>

namespace {
const int kMaxNumberSegments = 1e5;

const int kIntegralPrecision = 10;
const int kIntSumPrecision = 6;

const int kNameColumnWidth = 16;
const int kIntColumnWidth = 18;
const int kIntSumColumnWidth = 18;
const int kNColumnWidth = 10;

const size_t kColumnNumber = 4;
const int kDecimalBase = 10;
const int kCoefficientX = 22;
const double kDivisorArithmeticMean = 2.0;
const double kDivisorFunction3 = 5.0;
const int kMaxSymbolsAccuracy = 6;

[[nodiscard]] double CalculateFunction1(double x) {
    return x;
}

[[nodiscard]] double CalculateFunction2(double x) {
    return std::sin(kCoefficientX * x);
}
[[nodiscard]] double CalculateFunction3(double x) {
    return std::pow(x, 4);
}

[[nodiscard]] double CalculateFunction4(double x) {
    return std::atan(x);
}

[[nodiscard]] double CalculateAntiDerivativeFunction1(double a, double b) {
    return (b * b - a * a) / kDivisorArithmeticMean;
}

[[nodiscard]] double CalculateAntiDerivativeFunction2(double a, double b) {
    return (cos(a * kCoefficientX) - cos(b * kCoefficientX)) / kCoefficientX;
}

[[nodiscard]] double CalculateAntiDerivativeFunction3(double a, double b) {
    return (b * b * b * b * b - a * a * a * a * a) / kDivisorFunction3;
}

[[nodiscard]] double CalculateAntiDerivativeFunction4(double a, double b) {
    return b * atan(b) - a * atan(a) - (log(b * b + 1) - log(a * a + 1)) / kDivisorArithmeticMean;
}
}  // namespace

namespace IntegralSolver {
Results IntRect(double (*function)(double), double a, double b, double eps) {
    int n = 1;
    double h{};
    double prevSum = 0.0;
    double sum = 0.0;

    while (fabs(sum - prevSum) > eps || n * 2 <= kMaxNumberSegments) {
        prevSum = sum;
        sum = 0.0;
        h = (b - a) / n;

        for (int i = 0; i < n; ++i) {
            sum += function(a + h * i + h / kDivisorArithmeticMean);
        }

        sum *= h;
        n *= 2;
    }

    return {.sum = sum, .n = n};
}

Results IntTrap(double (*function)(double), double a, double b, double eps) {
    double sum{};
    double prevSum{};
    int n = 1;
    double dx{};
    double x1{};
    double x2{};

    while (std::fabs(sum - prevSum) > eps || n * 2 < kMaxNumberSegments) {
        prevSum = sum;
        sum = 0;
        n *= 2;
        dx = (b - a) / n;

        for (int i = 0; i < n; ++i) {
            x1 = a + i * dx;
            x2 = a + (i + 1) * dx;
            sum += ((x2 - x1) * (function(x1) + function(x2))) / kDivisorArithmeticMean;
        }
    }

    return {.sum = sum, .n = n};
}

void PrintTabl(I_print i_prn[], size_t k) {
    int wn[kColumnNumber] = {kNameColumnWidth, kIntColumnWidth, kIntSumColumnWidth, kNColumnWidth};
    const char* title[kColumnNumber] = {"Function", "Integral", "IntSum", "N "};
    int size[kColumnNumber];
    for (size_t i = 0; i < kColumnNumber; ++i) {
        size[i] = (int)strlen(title[i]);
    }

    std::cout << '+' << std::setfill('-');
    for (size_t j = 0; j < kColumnNumber - 1; ++j) {
        std::cout << std::setw(wn[j]) << '+';
    }
    std::cout << std::setw(wn[kColumnNumber - 1]) << '+' << std::endl;

    std::cout << '|';
    for (size_t j = 0; j < kColumnNumber; ++j) {
        std::cout << std::setw((wn[j] - size[j]) / 2) << std::setfill(' ') << ' ' << title[j] << std::setw((wn[j] - size[j]) / 2) << '|';
    }
    std::cout << std::endl;

    for (size_t i = 0; i < k; ++i) {
        std::cout << '+' << std::fixed;
        for (size_t j = 0; j < kColumnNumber - 1; ++j) {
            std::cout << std::setfill('-') << std::setw(wn[j]) << '+';
        }
        std::cout << std::setw(wn[kColumnNumber - 1]) << '+' << std::setfill(' ') << std::endl;

        std::cout << '|' << std::setw((int)(wn[0] - strlen(i_prn[i].name)) / 2) << ' ' << i_prn[i].name
                  << std::setw((int)(wn[0] - strlen(i_prn[i].name)) / 2) << '|';
        std::cout << std::setw(wn[1] - 1) << std::setprecision(kIntegralPrecision) << i_prn[i].i_toch << '|' << std::setw(wn[2] - 1) << i_prn[i].i_sum
                  << std::setprecision(kIntSumPrecision) << '|' << std::setw(wn[3] - 1) << i_prn[i].n << '|' << std::endl;
    }

    std::cout << '+' << std::setfill('-');
    for (size_t j = 0; j < kColumnNumber - 1; ++j) {
        std::cout << std::setw(wn[j]) << '+';
    }
    std::cout << std::setw(wn[kColumnNumber - 1]) << '+' << std::setfill(' ') << std::endl;
}

void ExecuteApp() {
    double a{};
    double b{};
    std::cout << "Введите значения a и b через пробел (b > a): ";
    std::cin >> a >> b;
    std::cout << std::endl;

    for (int i = 2; i <= kMaxSymbolsAccuracy; ++i) {
        double eps = std::pow(kDecimalBase, -i);

        Results function1 = IntRect(CalculateFunction1, a, b, eps);
        Results function2 = IntRect(CalculateFunction2, a, b, eps);
        Results function3 = IntRect(CalculateFunction3, a, b, eps);
        Results function4 = IntRect(CalculateFunction4, a, b, eps);

        const char* functions[4] = {"y=x ", "y=sin(22*x) ", "y=x^4 ", "y=arctg(x)  "};

        double Int[4] = {CalculateAntiDerivativeFunction1(a, b), CalculateAntiDerivativeFunction2(a, b), CalculateAntiDerivativeFunction3(a, b),
                         CalculateAntiDerivativeFunction4(a, b)};

        double IntSum[4] = {function1.sum, function2.sum, function3.sum, function4.sum};

        int N[4] = {function1.n, function2.n, function3.n, function4.n};

        I_print i_prn[4];
        for (size_t j = 0; j < 4; ++j) {
            i_prn[j] = {functions[j], IntSum[j], Int[j], N[j]};
        }

        std::cout << "Метод прямоугольников. eps: " << std::setw(i) << eps << "\n";
        PrintTabl(i_prn, 4);
        std::cout << "\n\n";

        function1 = IntTrap(CalculateFunction1, a, b, eps);
        function2 = IntTrap(CalculateFunction2, a, b, eps);
        function3 = IntTrap(CalculateFunction3, a, b, eps);
        function4 = IntTrap(CalculateFunction4, a, b, eps);

        IntSum[0] = function1.sum;
        IntSum[1] = function2.sum;
        IntSum[2] = function3.sum;
        IntSum[3] = function4.sum;

        N[0] = function1.n;
        N[1] = function2.n;
        N[2] = function3.n;
        N[3] = function4.n;

        for (size_t j = 0; j < 4; ++j) {
            i_prn[j] = {functions[j], IntSum[j], Int[j], N[j]};
        }

        std::cout << "Метод трапеций. eps: " << std::setw(i) << eps << "\n";
        PrintTabl(i_prn, 4);
        std::cout << "\n\n";
    }
}
}  // namespace IntegralSolver
