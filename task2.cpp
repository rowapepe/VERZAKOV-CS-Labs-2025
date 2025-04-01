#include <iostream>
#include <string>

int main() {
    std::string str;
    std::getline(std::cin, str);
    std::string result;
    for (int i = 0; i < str.size(); i += 2) {
        result += str[i];
    }
    std::cout << "Резутат: " << result << std::endl;

    return 0;
}
