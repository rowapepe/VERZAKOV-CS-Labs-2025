#include "division/division.h"
#include "mymath/mymath.h"
#include <iostream>

int main() {
  setlocale(LC_ALL, "Russian");
  std::cout << "Я умею суммировать! Зацени 1+1=";
  std::cout << mymath::sum(10, 32) << std::endl;

  std::cout << "А также умею делить! Зацени 8/2=";
  std::cout << division::div(8, 2) << std::endl;

  return 0;
}
