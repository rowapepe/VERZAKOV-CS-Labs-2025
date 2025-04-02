#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string str{};
    std::vector<int> dotPositions;
    std::getline(std::cin, str);

    dotPositions.push_back(1);
    size_t pos = 0;
    int dotsAmout = std::count(str.begin(), str.end(), '.');

    for (int i = 0; i < dotsAmout; ++i) {
        pos = str.find('.', pos);
        dotPositions.push_back(pos + 2);
        ++pos;
    }

    std::cout << "Позиции начал предложений: ";
    for (int i = 0; i < dotPositions.size(); ++i) {
        std::cout << dotPositions[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
