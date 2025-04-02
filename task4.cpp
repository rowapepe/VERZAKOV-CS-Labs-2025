#include <algorithm>
#include <iostream>
#include <random>

int Random() {
    std::random_device r{};
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution distribution(0, 1);
    return distribution(randomEngine);
}

void Print(std::vector<bool> vector) {
    std::cout << "Содержимое вектора: ";
    for (bool val : vector) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<bool> vector;
    for (int i = 0; i < 20; ++i) {
        vector.push_back(Random());
    }

    Print(vector);

    int counterTrue = std::count(vector.begin(), vector.end(), true);
    int counterFalse = std::count(vector.begin(), vector.end(), false);

    std::cout << "Количество истинных значений: " << counterTrue << ", ложных значений: " << counterFalse << std::endl;
    vector.erase(vector.begin(), vector.begin() + 10);
    Print(vector);

    return 0;
}
