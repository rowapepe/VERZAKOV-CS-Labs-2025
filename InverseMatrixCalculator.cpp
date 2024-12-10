#include "InverseMatrixCalculator.hpp"
#include "mprinter.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>

namespace {
const int kPrecision = 6;
double** CreateMatrix(int n, int m) {
    double** matrix = new double*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new double[m]();
    }

    return matrix;
}

void DeleteMatrix(double** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    matrix = nullptr;
}

double Determinant(double** matrix, int size) {
    if (!matrix) {
        return 0;
    }

    double** bigMatrix = CreateMatrix(size, 2 * size);
    double result{};
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            bigMatrix[i][j + size] = matrix[i][j];
            bigMatrix[i][j] = matrix[i][j];
        }
    }

    for (int i = 0; i < size; i++) {
        double front = 1;
        for (int j = 0; j < size; j++) {
            front *= bigMatrix[j][i + j];
        }
        result += front;
    }

    for (int i = size * 2 - 1; i >= size; i--) {
        double back = 1;
        for (int j = 0; j < size; j++) {
            back *= bigMatrix[j][i - j];
        }

        result -= back;
    }

    DeleteMatrix(bigMatrix, size);
    return result;
}
}  // namespace

namespace InverseMatrixCalculator {
bool GaussJordan(double** matrix, int size) {
    if (!matrix) {
        return false;
    }

    double** bigMatrix = CreateMatrix(size, 2 * size);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            bigMatrix[i][j] = matrix[i][j];
        }
        bigMatrix[i][i + size] = 1;
    }

    for (int k = 0; k < size; ++k) {
        if (bigMatrix[k][k] == 0) {
            int swapRow = k + 1;
            while (swapRow < size && bigMatrix[swapRow][k] == 0) {
                ++swapRow;
            }

            if (swapRow == size) {
                DeleteMatrix(bigMatrix, size);
                return false;
            }

            for (int j = 0; j < 2 * size; ++j) {
                std::swap(bigMatrix[k][j], bigMatrix[swapRow][j]);
            }
        }

        double diagonalElement = bigMatrix[k][k];
        for (int j = 0; j < 2 * size; ++j) {
            bigMatrix[k][j] /= diagonalElement;
        }

        for (int i = k + 1; i < size; ++i) {
            double factor = bigMatrix[i][k];
            for (int j = 0; j < 2 * size; ++j) {
                bigMatrix[i][j] -= factor * bigMatrix[k][j];
            }
        }
    }

    std::cout << "Промежуточная матрица после прямого обхода:" << std::endl;
    mprinter::PrintMatrix(bigMatrix, size, 2 * size, kPrecision);

    for (int k = size - 1; k >= 0; --k) {
        for (int i = k - 1; i >= 0; --i) {
            double factor = bigMatrix[i][k];
            for (int j = 0; j < 2 * size; ++j) {
                bigMatrix[i][j] -= factor * bigMatrix[k][j];
            }
        }
    }

    std::cout << "Промежуточная матрица после обратного обхода:" << std::endl;
    mprinter::PrintMatrix(bigMatrix, size, 2 * size, kPrecision);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = bigMatrix[i][j + size];
        }
    }

    DeleteMatrix(bigMatrix, size);
    return true;
}

void MultiplyMatrix(double** matrixA, double** matrixB, double** result, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < size; ++k) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

void FillMatrix(double** matrix, std::ifstream& file, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            file >> matrix[i][j];
        }
    }
}

void ExecuteApp() {
    std::ifstream file("matrix.txt");
    if (!file.is_open()) {
        std::cout << "Не получилось открыть файл с матрицей и ее размером." << std::endl;
        return;
    }

    int size{};
    file >> size;

    if (size <= 0) {
        std::cout << "Размер матрицы должен быть положительным." << std::endl;
        return;
    }

    double** matrix = CreateMatrix(size, size);

    FillMatrix(matrix, file, size);
    file.close();

    std::cout << "Исходная матрица:" << std::endl;
    mprinter::PrintMatrix(matrix, size, size, 1);

    double** inversedMatrix = CreateMatrix(size, size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            inversedMatrix[i][j] = matrix[i][j];
        }
    }

    if (Determinant(matrix, size) == 0 || !GaussJordan(inversedMatrix, size)) {
        std::cout << "Обратная матрица не существует (определитель равен 0)." << std::endl;
        DeleteMatrix(matrix, size);
        DeleteMatrix(inversedMatrix, size);
        return;
    }

    std::cout << "Обратная матрица:" << std::endl;
    mprinter::PrintMatrix(inversedMatrix, size, size, kPrecision);

    double** resultMatrix = CreateMatrix(size, size);
    MultiplyMatrix(matrix, inversedMatrix, resultMatrix, size);

    std::cout << "Результат умножения исходной матрицы на обратную:" << std::endl;
    mprinter::PrintMatrix(resultMatrix, size, size, 1);

    DeleteMatrix(matrix, size);
    DeleteMatrix(inversedMatrix, size);
    DeleteMatrix(resultMatrix, size);
}
}  // namespace InverseMatrixCalculator
