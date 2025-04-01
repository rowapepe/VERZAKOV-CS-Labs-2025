#include <iomanip>
#include <iostream>
#include <vector>

class Rectangle {
    double a;  // ширина
    double b;  // длина
 public:
    Rectangle() : a(0), b(0) {}
    Rectangle(double a, double bi) : a(a), b(bi) {}
    double getA() { return a; }
    double getB() { return b; }
};

void Print(std::vector<Rectangle> rect) {
    std::cout << "Содержимое массива:" << std::endl;
    for (int i = 0; i < rect.size(); ++i) {
        std::cout << (i + 1) << ": " << rect[i].getA() << "  " << rect[i].getB() << std::endl;
    }
}

int main() {
    std::vector<Rectangle> rect;
    rect.emplace_back(1.2, 6.3);
    rect.emplace_back(4.0, 0.7);
    rect.emplace_back(7.2, 0.8);
    rect.emplace_back(5.3, 3.0);
    rect.emplace_back(4.9, 6.6);
    rect.emplace_back(9.3, 0.2);
    Print(rect);

    double maxSquare = 0;
    double maxSquareIndex = 0;
    for (int i = 0; i < rect.size(); ++i) {
        maxSquare = std::max(maxSquare, rect[i].getA() * rect[i].getB());
        if (maxSquare == rect[i].getA() * rect[i].getB()) {
            maxSquareIndex = i;
        }
    }
    std::cout << "Прямоугольник с самой большой площадью: " << rect[maxSquareIndex].getA() << ", " << rect[maxSquareIndex].getB() << std::endl;

    return 0;
}
