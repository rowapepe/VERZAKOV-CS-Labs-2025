#include "Encryptor.h"
#include "Vector.h"

#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace {
const int kCodePoints = 128;
const int kWordMaxLength = 8;
const int kSpaceCodePoint = 32;
const int kNewLineCodePoint = 10;

const int kSymbolColumnWidth = 9;
const int kColumnWidth = 18;
}  // namespace

namespace Encryptor {
void InitializeSourceText(std::ifstream& sourceText, Vector::VecInt& sourceBuffer, int& sourceTextLength) {
    if (!sourceText) {
        return;
    }

    char buffer{};

    while (sourceText.get(buffer)) {
        std::cout << buffer;

        PushBack(sourceBuffer, buffer);
        ++sourceTextLength;
    }
}

void InitializeKeys(std::ifstream& keysText, Vector::VecInt& keysBuffer, int& keysNumber) {
    if (!keysText) {
        return;
    }

    char buffer{};
    int sum{};
    bool spaceRepeat{};
    bool newlineRepeat{};
    int wordLength{};

    while (keysText.get(buffer)) {
        std::cout << buffer;

        if (buffer != kSpaceCodePoint && buffer != kNewLineCodePoint && wordLength < kWordMaxLength) {
            sum += buffer;
            spaceRepeat = false;
            newlineRepeat = false;

            ++wordLength;
        } else if (!spaceRepeat && !newlineRepeat) {
            PushBack(keysBuffer, sum % kCodePoints);
            ++keysNumber;

            spaceRepeat = (buffer == kSpaceCodePoint);
            newlineRepeat = (buffer == kNewLineCodePoint);

            wordLength == kWordMaxLength && !spaceRepeat && !newlineRepeat ? (sum = buffer, wordLength = 1) : (sum = 0, wordLength = 0);
        }
    }

    if (buffer != kSpaceCodePoint && buffer != kNewLineCodePoint) {
        PushBack(keysBuffer, sum % kCodePoints);
        ++keysNumber;
    }
}

void EncodeText(std::ofstream& encodedText, Vector::VecInt& sourceBuffer, Vector::VecInt& encodedBuffer, Vector::VecInt& keysBuffer) {
    for (size_t i = 0; i < sourceBuffer.size; ++i) {
        PushBack(encodedBuffer, (GetElement(sourceBuffer, i) + GetElement(keysBuffer, i % keysBuffer.size)) % kCodePoints);

        std::cout << char(GetElement(encodedBuffer, i));
        encodedText << char(GetElement(encodedBuffer, i));
    }
}

void DecodeText(std::ofstream& decodedText, Vector::VecInt& sourceBuffer, Vector::VecInt& decodedBuffer, Vector::VecInt& keysBuffer) {
    for (size_t i = 0; i < sourceBuffer.size; ++i) {
        if (GetElement(sourceBuffer, i) < GetElement(keysBuffer, i % keysBuffer.size)) {
            PushBack(decodedBuffer, kCodePoints + GetElement(sourceBuffer, i) - GetElement(keysBuffer, i % keysBuffer.size));
        } else {
            PushBack(decodedBuffer, GetElement(sourceBuffer, i) - GetElement(keysBuffer, i % keysBuffer.size));
        }

        std::cout << char(GetElement(decodedBuffer, i));
        decodedText << char(GetElement(decodedBuffer, i));
    }
}

void WithdrawTable(int* symbolsNumberSourceText, int* codeVariants, int keysNumber, int sourceTextLength) {
    std::cout << "| символ  |  кол-во в исх-ом |   кол-во вар-ов  |  размер блокнота |   длина исх-ый   |" << std::endl;
    std::cout << "|---------|------------------|------------------|------------------|------------------|" << std::endl;

    for (int i = 0; i < kCodePoints; ++i) {
        if (i == kNewLineCodePoint) {
            if (symbolsNumberSourceText[i] != 0) {
                std::cout << "|" << std::setw(kSymbolColumnWidth) << "LF" << "|" << std::setw(kColumnWidth) << symbolsNumberSourceText[i] << "|"
                          << std::setw(kColumnWidth) << codeVariants[i] << "|" << std::setw(kColumnWidth) << keysNumber << "|"
                          << std::setw(kColumnWidth) << sourceTextLength << "|" << std::endl;
            }
        } else {
            if (symbolsNumberSourceText[i] != 0) {
                std::cout << "|" << std::setw(kSymbolColumnWidth) << char(i) << "|" << std::setw(kColumnWidth) << symbolsNumberSourceText[i] << "|"
                          << std::setw(kColumnWidth) << codeVariants[i] << "|" << std::setw(kColumnWidth) << keysNumber << "|"
                          << std::setw(kColumnWidth) << sourceTextLength << "|" << std::endl;
            }
        }
    }

    std::cout << "|---------|------------------|------------------|------------------|------------------|" << std::endl;
}

void ExecuteCoder() {
    std::ifstream sourceText("SourceText.txt", std::ios::binary);
    std::ifstream keysText("Keys.txt", std::ios::binary);
    std::ofstream encodedText("EncodedText.txt", std::ios::binary);
    std::ofstream decodedText("DecodedText.txt", std::ios::binary);

    int keysNumber = 0;
    int sourceTextLength = 0;

    if (!keysText && !sourceText) {
        return;
    }

    Vector::VecInt sourceBuffer = Vector::CreateVector();
    std::cout << "Содержимое SourceText.txt:" << std::endl;
    InitializeSourceText(sourceText, sourceBuffer, sourceTextLength);
    std::cout << std::endl;
    sourceText.close();

    Vector::VecInt keysBuffer = Vector::CreateVector();
    std::cout << "Содержимое Keys.txt:" << std::endl;
    InitializeKeys(keysText, keysBuffer, keysNumber);
    std::cout << std::endl;
    keysText.close();

    Vector::VecInt encodedBuffer = Vector::CreateVector();
    std::cout << "Содержимое EncodedText.txt:" << std::endl;
    EncodeText(encodedText, sourceBuffer, encodedBuffer, keysBuffer);
    std::cout << std::endl;
    encodedText.close();

    Vector::VecInt decodedBuffer = Vector::CreateVector();
    std::cout << "Содержимое DecodedText.txt:" << std::endl;
    DecodeText(decodedText, encodedBuffer, decodedBuffer, keysBuffer);
    std::cout << std::endl;
    decodedText.close();

    int symbolsNumberSourceText[kCodePoints]{};
    int symbolsNumberEncodedText[kCodePoints]{};
    int replacements[kCodePoints][kCodePoints]{};
    int codeVariants[kCodePoints];

    for (size_t i = 0; i < sourceBuffer.size; ++i) {
        ++symbolsNumberSourceText[GetElement(sourceBuffer, i)];
        ++symbolsNumberEncodedText[GetElement(encodedBuffer, i)];
        ++replacements[GetElement(sourceBuffer, i)][GetElement(encodedBuffer, i)];
    }

    for (size_t i = 0; i < kCodePoints; ++i) {
        for (size_t j = 0; j < kCodePoints; ++j) {
            if (replacements[i][j] != 0) {
                ++codeVariants[i];
            }
        }
    }

    WithdrawTable(symbolsNumberSourceText, codeVariants, keysNumber, sourceTextLength);
    Vector::DeleteVector(sourceBuffer);
    Vector::DeleteVector(keysBuffer);
    Vector::DeleteVector(encodedBuffer);
    Vector::DeleteVector(decodedBuffer);
}

void ExecuteProgram() {
    ExecuteCoder();
}
}  // namespace Encryptor
