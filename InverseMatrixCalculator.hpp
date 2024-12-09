#pragma once

#include <cstddef>
#include <fstream>

namespace InverseMatrixCalculator {
bool GaussJordan(double** matrix, int size);

void MultiplyMatrix(double** matrixA, double** matrixB, double** result, int size);

void FillMatrix(double** matrix, std::ifstream& file, int size);

void ExecuteApp();
}  // namespace InverseMatrixCalculator
