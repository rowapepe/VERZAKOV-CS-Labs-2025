#include "Executor.hpp"
#include <iostream>

int main() {
    try {
        Executor::ExecuteApp();
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
