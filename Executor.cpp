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
    MyStack::MyStack<char> s1;

    s1.push('a');

    s1.push('b');

    s1.push('c');

    std::cout << s1;

    MyStack::MyStack<char> s2(s1);

    MyStack::MyStack<char> s3;

    std::cout << s2;

    std::cout << s3;

    s3 = s1;

    std::cout << s3;
}
}  // namespace Executor
