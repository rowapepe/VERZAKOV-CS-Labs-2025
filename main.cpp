#include <iostream>
#include "Polynomial/polynomial.hpp"
#include "Term/term.hpp"

int main() {
    std::cout << "Введите первый терм: ";
    Term t1, t2, t3;
    std::cin >> t1;

    std::cout << "Введите второй терм: ";
    std::cin >> t2;
    std::cout << std::endl;

    try {
        t3 = t1 + t2;
        std::cout << "Сложение: " << t3 << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    t1 = t1 * t2;
    std::cout << "Перемножение термов: " << t1 << std::endl;
    std::cout << std::endl;

    std::cout << "Введите первый полином: ";
    Polynomial p1 , p2 , p3;
    std::cin >> p1;
    p3 = p1;
    std::cout << p1 << std::endl;

    std::cout << "Введите второй полином : ";
    std::cin >> p2;
    std::cout << p2 << std::endl;

    p3 *= p2;
    p1 += p2;
    bool increase = false;
    std::cout << "Введите 1 для вывода по увеличению степени, 0 по уменьшению степени: ";
    std::cin >> increase;
    p1.sort(increase);
    p3.sort(increase);

    std::cout << "Сложение полиномов: " << p1 << std::endl;
    std::cout << "Перемножение полиномов: " << p3 << std::endl;
    return 0;
}
