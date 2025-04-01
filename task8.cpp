#include <iostream>
#include <map>
#include <string>

int main(){
    std::map<std::string, int> planets;
    planets["Меркурий"] = 0;
    planets["Венера"] = 0;
    planets["Земля"] = 1;
    planets["Марс"] = 2;
    planets["Юпитер"] = 69;
    planets["Сатурн"] = 62;
    planets["Уран"] = 27;
    planets["Нептун"] = 14;
    planets["Плутон"] = 10;

    std::cout << "Планеты и количество спутников:\n";
    for (std::map<std::string, int>::iterator it = planets.begin(); it != planets.end(); ++it) {
        std::cout << it->first << ": " << it->second << "\n";
    }

    std::map<std::string, int>::iterator maxPlanet = planets.begin();
    for (std::map<std::string, int>::iterator it = planets.begin(); it != planets.end(); ++it) {
        if (it->second > maxPlanet->second) {
            maxPlanet = it;
        }
    }

    std::cout << "Планета с максимальным числом спутников: " << maxPlanet->first << " (" << maxPlanet->second << " спутников)\n";

    return 0;
}
