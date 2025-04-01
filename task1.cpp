#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string str{};
    std::vector<int> dotPositions;
    std::getline(std::cin, str);
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '.' && (str[i + 1] == '\n' || str[i + 1] == ' ')) {
            dotPositions.emplace_back(i + 1);
        }
    }

    std::cout << "Позиции начал предложений: ";
    for (int i = 0; i < dotPositions.size(); ++i) {
        std::cout << dotPositions[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
