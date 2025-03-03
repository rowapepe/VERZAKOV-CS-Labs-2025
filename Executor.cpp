#include "Executor.hpp"
#include <iostream>
#include "MyStack/MyStack.hpp"

namespace {
}

namespace Executor {
void ExecuteApp(){
    int N{};
    std::cout << "Введите целое число N для разложения: ";
    std::cin >> N;
    std::cout << std::endl;
    MyStack::MyStack<int> stack;
    MyStack::MyStack<int> divisors;
    divisors.Multipliers(N, divisors);


    std::cout << N << "=";
    while (!divisors.empty()){
        std::cout << divisors.top_inf() << " * ";
        divisors.pop();
    }
    std::cout<< std::endl;
}
}
