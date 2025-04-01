#include <iostream>
#include <map>
#include <string>

void PrintMap(const std::map<std::string, int>& cities) {
    std::cout << "Список городов и их расстояние от Москвы:\n";
    for (std::map<std::string, int>::const_iterator it = cities.begin(); it != cities.end(); ++it) {
        std::cout << it->first << ": " << it->second << " км\n";
    }
    std::cout << std::endl;
}

int main() {
    std::map<std::string, int> cities;
    cities["Минск"] = 713;
    cities["Киев"] = 856;
    cities["Санкт-Петербург"] = 786;
    cities["Астана"] = 2748;
    cities["Нижний Новгород"] = 421;
    cities["Владивосток"] = 9141;

    PrintMap(cities);

    std::map<std::string, int>::iterator minCity = cities.begin();
    std::map<std::string, int>::iterator maxCity = cities.begin();

    for (std::map<std::string, int>::iterator it = cities.begin(); it != cities.end(); ++it) {
        if (it->second < minCity->second) {
            minCity = it;
        }
        if (it->second > maxCity->second) {
            maxCity = it;
        }
    }

    std::cout << "Ближайший город к Москве: " << minCity->first << " (" << minCity->second << " км)\n";
    std::cout << "Самый дальний город от Москвы: " << maxCity->first << " (" << maxCity->second << " км)\n";

    return 0;
}
