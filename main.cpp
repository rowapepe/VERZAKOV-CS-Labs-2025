#include <fstream>
#include "planets/planets.hpp"

int main() {
    std::fstream file;
    file.open("Planets.txt");
    int k20 = 20;
    Planets::Planet* planets = new Planets::Planet[k20];
    Planets::Planet::ReadDB(file, planets, k20);

    for (int i = 0; i < k20; ++i) {
        planets[i].PrintPlanet();
    }

    return 0;
}
