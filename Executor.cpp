#include "Executor.hpp"
#include <iostream>
#include "MyStack/MyStack.hpp"

namespace Executor {
void PrintDivisors(int N, bool reversed) {
    MyStack::MyStack<int> divisors;
    divisors.Multipliers(N, divisors, reversed);

    std::cout << N << "=";
    if (!divisors.empty()) {
        std::cout << divisors.top_inf();
        divisors.pop();
    }
    while (!divisors.empty()) {
        std::cout << " * " << divisors.top_inf();
        divisors.pop();
    }
    std::cout << std::endl;
}

void ExecuteApp() {
    int N{};
    std::cout << "Введите целое число N для разложения на простые множители: ";
    std::cin >> N;
    std::cout << std::endl;

    PrintDivisors(N, false);
    PrintDivisors(N, true);
}
}  // namespace Executor
