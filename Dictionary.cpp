#include "Dictionary.hpp"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>

namespace {
const int kMaxWordLength = 100;

void StrCopy(const char* source, char* destination) {
    if (!source || !destination) {
        return;
    }

    while (*source) {
        *destination = *source;
        ++source;
        ++destination;
    }

    *destination = '\0';
}
}  // namespace

namespace Dictionary {
int BinarySearch(const Dict* dict, const char* word, const int size) {
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (std::strcmp(dict[mid].engl, word) == 0) {
            return mid;
        }

        if (std::strcmp(dict[mid].engl, word) < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

void ResizeDict(Dict*& dict, int oldSize, int newSize) {
    Dict* newDict = new Dict[newSize];
    for (int i = 0; i < oldSize; ++i) {
        newDict[i].engl = dict[i].engl;
        newDict[i].rus = dict[i].rus;
    }
    delete[] dict;
    dict = newDict;
}

void Sort(Dict* dict, const int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (std::strcmp(dict[j].engl, dict[j + 1].engl) > 0) {
                std::swap(dict[j], dict[j + 1]);
            }
        }
    }
}

void DeleteDict(Dict* dict, const int size) {
    if (!dict) {
        return;
    }

    for (int i = 0; i < size; ++i) {
        delete[] dict[i].engl;
        delete[] dict[i].rus;
    }

    delete[] dict;
}

void AddWord(Dict*& dict, int& size) {
    if (!dict) {
        return;
    }

    char englishWord[kMaxWordLength];
    std::cout << "Введите английское слово: ";
    std::cin >> englishWord;

    char russianWord[kMaxWordLength];
    std::cout << "Введите русский перевод: ";
    std::cin >> russianWord;

    ResizeDict(dict, size, size + 1);

    dict[size].engl = new char[kMaxWordLength];
    StrCopy(englishWord, dict[size].engl);

    dict[size].rus = new char[kMaxWordLength];
    StrCopy(russianWord, dict[size].rus);

    ++size;

    Sort(dict, size);

    std::cout << std::endl;
}

void DeleteWord(Dict*& dict, int& size) {
    if (!dict || size == 0) {
        return;
    }

    char englishWord[kMaxWordLength];
    std::cout << "Введите английское слово, которое удалить: ";
    std::cin >> englishWord;

    int index = -1;

    for (int i = 0; i < size; ++i) {
        if (std::strcmp(dict[i].engl, englishWord) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        std::cout << "Слово не найдено." << std::endl;
        std::cout << std::endl;
        return;
    }

    delete[] dict[index].engl;
    delete[] dict[index].rus;

    for (int i = index; i < size - 1; ++i) {
        dict[i] = dict[i + 1];
    }

    --size;

    Sort(dict, size);

    std::cout << std::endl;
}

void TranslateFromEnglishToRussian(const Dict* dict, const int size) {
    if (!dict) {
        return;
    }

    char englishWord[kMaxWordLength];
    std::cout << "Введите английский перевод слова: ";
    std::cin >> englishWord;

    int index = BinarySearch(dict, englishWord, size);
    if (index == -1) {
        std::cout << "Слово не найдено.\n";
    } else {
        std::cout << "Перевод слова: " << dict[index].rus << std::endl;
    }

    std::cout << std::endl;
}

void TranslateFromRussianToEnglish(const Dict* dict, const int size) {
    if (!dict) {
        return;
    }

    char russianWord[kMaxWordLength];
    std::cout << "Введите русский перевод слова: ";
    std::cin >> russianWord;

    bool found = false;
    for (int i = 0; i < size; ++i) {
        if (std::strcmp(russianWord, dict[i].rus) == 0) {
            std::cout << "Перевод слова: " << dict[i].engl << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "Слово не найдено." << std::endl;
    }

    std::cout << std::endl;
}

void PrintDictionary(const Dict* dict, const int size) {
    if (!dict) {
        std::cout << "Словарь пуст." << std::endl;
        std::cout << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        std::cout << dict[i].engl << " - " << dict[i].rus << std::endl;
    }

    std::cout << std::endl;
}

void SaveDictionaryToFile(const Dict* dict, const int size, std::fstream& file) {
    file.open("dictionary.txt", std::ios::out);

    if (!file.is_open()) {
        std::cout << "Ошибка при открытии файла для записи." << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        file << dict[i].engl << " " << dict[i].rus << std::endl;
    }

    file.close();
}

void OpenFile(std::fstream& file, Dict*& dict, int& size) {
    file.open("dictionary.txt", std::ios::in);

    if (!file.is_open()) {
        std::cout << "Ошибка при открытии файла." << std::endl;
        return;
    }

    while (!file.eof()) {
        char englishWord[kMaxWordLength]{};
        char russianWord[kMaxWordLength]{};
        file >> englishWord >> russianWord;

        if (file.fail()) {
            break;
        }

        Dict* buffer = new Dict[size + 1];

        for (int i = 0; i < size; ++i) {
            buffer[i].engl = new char[kMaxWordLength];
            StrCopy(dict[i].engl, buffer[i].engl);

            buffer[i].rus = new char[kMaxWordLength];
            StrCopy(dict[i].rus, buffer[i].rus);
        }

        buffer[size].engl = new char[kMaxWordLength];
        StrCopy(englishWord, buffer[size].engl);

        buffer[size].rus = new char[kMaxWordLength];
        StrCopy(russianWord, buffer[size].rus);

        DeleteDict(dict, size);
        dict = buffer;
        ++size;
    }

    if (size == 0) {
        std::cout << "Файл пуст. Создаём пустой словарь." << std::endl;
        dict = new Dict[size];
    }

    Sort(dict, size);

    file.close();
}

void ExecuteApp() {
    std::fstream file;
    Dict* dict{};
    int size = 0;

    OpenFile(file, dict, size);

    int task = 0;
    while (true) {
        std::cout << "Номера заданий для словаря:\n"
                  << "1. Добавление слова в словарь\n"
                  << "2. Удаление слов из словаря\n"
                  << "3. Перевод слов с английского на русский\n"
                  << "4. Перевод слов с русского на английский\n"
                  << "5. Просмотр словаря\n"
                  << "6. Сохранение словаря в файл\n"
                  << "7. Выход\n"
                  << "Введите номер задания: ";
        std::cin >> task;
        std::cout << std::endl;

        switch (static_cast<Task>(task)) {
            case Task::AddWord:
                AddWord(dict, size);
                break;
            case Task::DeleteWord:
                DeleteWord(dict, size);
                break;
            case Task::TranslateFromEnglishToRussian:
                TranslateFromEnglishToRussian(dict,size);
                break;
            case Task::TranslateFromRussianToEnglish:
                TranslateFromRussianToEnglish(dict, size);
                break;
            case Task::PrintDictionary:
                PrintDictionary(dict, size);
                break;
            case Task::SaveDictionaryToFile:
                SaveDictionaryToFile(dict, size, file);
                break;
            case Task::Exit:
                DeleteDict(dict, size);
                return;
            default:
                break;
        }
    }
}

}  // namespace Dictionary
