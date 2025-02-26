#include "Executor.hpp"
#include <iostream>
#include <iomanip>
#include "fractions/fractions.hpp"

namespace {
}

namespace Executor {
void ExecuteApp(){
    // ввод дроби с клавиатуры
    std::cout << "Введите дробь: \n";
    Fractions::Fraction z;
    std::cin >> z;
    std::cout << "z=" << z << std::endl;

    // проверка конструкторов
    Fractions::Fraction fr1(10, 14), fr2;
    std::cout << "fr2=" << fr2 << std::endl;
    std::cout << "fr1=" << fr1 << std::endl;

    Fractions::Fraction fr = "-1 4/8";
    std::cout << "fr=" << fr << std::endl;

    Fractions::Fraction x(z), y;
    std::cout << "x=" << x << std::endl;

    double dbl = -1.25;
    Fractions::Fraction f = dbl;
    std::cout << "f=" << f << std::endl;

    // проверка перегруженной операции "+"
    y = x + z;
    std::cout << "y=" << y << std::endl;

    y += x;
    f += dbl / 2;
    std::cout << "f=" << f << std::endl;

    y = x + dbl;
    std::cout << "y=" << y << std::endl;

    y = dbl + y;
    std::cout << "y=" << y << std::endl;

    y += dbl;
    std::cout << "y=" << y << std::endl;

    int i = 5;
    y += i;
    std::cout << "y=" << y << std::endl;

    y = i + x;
    std::cout << "y=" << y << std::endl;

    y = x + i;
    std::cout << "y=" << y << std::endl;

    y += dbl + i + x;
    std::cout << "y=" << y << std::endl;
}
}
