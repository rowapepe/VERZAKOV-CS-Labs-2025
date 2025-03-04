#include "Executor.hpp"
#include <iostream>
#include "MyStack/MyStack.hpp"

namespace Executor {
void PrintDivisors(int N, bool reversed) {
    MyStack::MyStack<int> divisors;
    divisors.Multipliers(N, divisors, reversed);

    std::cout << N << "=";
    std::cout << divisors;
}

void ExecuteApp() {
    int N{};
    std::cout << "Введите целое число N для разложения на простые множители: ";
    std::cin >> N;

    PrintDivisors(N, false);
    PrintDivisors(N, true);
}
}  // namespace Executor
