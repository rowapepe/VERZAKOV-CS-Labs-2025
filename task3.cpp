#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::string str;
    std::ifstream in("InFile.txt");
    std::ofstream out("OutFile.txt");

    while (std::getline(in, str)) {
        for (int i = 0; i < str.size(); ++i) {
            str[i] = std::tolower(str[i]);
        }

        out << str << std::endl;
    }
    return 0;
}
