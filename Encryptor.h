#pragma once

#include "Vector.h"

#include <cstddef>
#include <fstream>

namespace Encryptor {
void InitializeSourceText(std::ifstream& sourceTextInStream, Vector::VecInt& sourceText, int& sourceTextLength);
void InitializeKeys(std::ifstream& keyInStream, Vector::VecInt& keys, int& keysQuantity);

void EncodeText(std::ofstream& encodedTextOutStream, Vector::VecInt& sourceText, Vector::VecInt& encodedText, Vector::VecInt& keys);
void DecodeText(std::ofstream& decodedTextOutStream, Vector::VecInt& encodedText, Vector::VecInt& decodedText, Vector::VecInt& keys);

void ExecuteCoder();
void ExecuteProgram();
}  // namespace Encryptor
