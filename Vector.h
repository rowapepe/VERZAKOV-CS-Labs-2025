#pragma once

#include <cstddef>

namespace Vector {
struct VecInt {
    size_t size{};
    size_t capacity{};
    int* vector{};
};

[[nodiscard]] VecInt CreateVector();
void DeleteVector(VecInt& vector);

[[nodiscard]] int GetElement(const VecInt& vector, size_t index);
void PushBack(VecInt& vector, int element);
}  // namespace Vector
