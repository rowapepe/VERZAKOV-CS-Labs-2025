#include <random>
#include <list>
#include <iostream>
#include <algorithm>

int Random() {
    std::random_device r{};
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution distribution(0, 1);
    return distribution(randomEngine);
}

void Print(std::list<bool> list) {
    std::cout << "Содержимое листа: ";
    for (const bool val : list) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::list<bool> list;
    for (int i = 0; i < 20; ++i) {
        list.push_back(Random());
    }

    Print(list);

    int counterTrue = std::count(list.begin(), list.end(), true);
    int counterFalse = std::count(list.begin(), list.end(), false);

    std::cout << "Количество истинных значений: " << counterTrue << ", ложных значений: " << counterFalse << std::endl;
    auto end = list.begin();
    std::advance(end, 10);
    list.erase(list.begin(),end);
    Print(list);

    return 0;
}
