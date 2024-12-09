#include "mprinter.hpp"

#include <iomanip>
#include <iostream>

namespace {
const int kMaxLineLength = 80;
const int kColumnWidth = 12;
const int kPrecision = 8;
}  // namespace

namespace mprinter {
void PrintMatrix(double** matrix, int n, int m) {
    int maxColumnsPerLine = kMaxLineLength / kColumnWidth;
    if (maxColumnsPerLine < 1) {
        maxColumnsPerLine = 1;
    }

    std::cout << "================================================================================" << std::endl;
    for (int blockStart = 0; blockStart < m; blockStart += maxColumnsPerLine) {
        int blockEnd = std::min(blockStart + maxColumnsPerLine, m);

        for (int i = 0; i < n; ++i) {
            for (int j = blockStart; j < blockEnd; ++j) {
                std::cout << std::fixed << std::setw(kColumnWidth) << std::setprecision(kPrecision) << matrix[i][j];
            }
            std::cout << std::endl;
        }

        if (blockEnd < m) {
            std::cout << "--------------------------------------------------------------------------------" << std::endl;
        }
    }
    std::cout << "================================================================================" << std::endl;
}
}  // namespace mprinter
