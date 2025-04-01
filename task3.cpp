#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::string str;
    std::ifstream in("InFile.txt");
    std::getline(in, str);
    for (int i = 0; i < str.size(); ++i) {
        str[i] = std::tolower(str[i]);
    }
    std::ofstream out("OutFile.txt");
    out << str;

    return 0;
}
