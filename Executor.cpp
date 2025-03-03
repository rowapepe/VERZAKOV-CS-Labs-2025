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

    MyStack::MyStack<int> divisors;
    MyStack::MyStack<int>::Multipliers(N, divisors);


    std::cout << N << "=";
    while (!divisors.empty()){
        std::cout << divisors.top_inf() << " * ";
    }
    std::cout<< std::endl;
}
}
