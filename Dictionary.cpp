#include "Dictionary.hpp"

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>

namespace {
const int kMaxWordLength = 100;
const int kSize = 1024;

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
int BinarySearch(Dict*& dict, const char* word, int size) {
    int low = 0;
    int high = size;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (dict[mid].engl == word) {
            return mid;
        }

        if (dict[mid].engl < word) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

void Sort(Dict*& obj, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (std::strcmp(obj[j].engl, obj[j + 1].engl)) {
                std::swap(obj[j], obj[j + 1]);
            }
        }
    }
}

void AddWord(Dict* dict, int& size) {
    if (!dict) {
        return;
    }

    char englishWord[kMaxWordLength];
    std::cout << "Введите английское слово: ";
    std::cin >> englishWord;

    char russianWord[kMaxWordLength];
    std::cout << "Введите русский перевод: ";
    std::cin >> russianWord;

    Dict* buffer = new Dict[size + 1];

    for (int i = 0; i < size; ++i) {
        buffer[i].engl = new char[kMaxWordLength];
        StrCopy(buffer[i].engl, dict[i].engl);

        buffer[i].rus = new char[kMaxWordLength];
        StrCopy(buffer[i].rus, dict[i].rus);
    }

    buffer[size].engl = new char[kMaxWordLength];
    StrCopy(buffer[size].engl, englishWord);

    buffer[size].rus = new char[kMaxWordLength];
    StrCopy(buffer[size].rus, russianWord);

    dict = buffer;
    ++size;
    Sort(dict, size);

    for (int i = 0; i < size; ++i) {
        delete[] dict[i].engl;
        delete[] dict[i].rus;
    }
    delete[] dict;
}

void DeleteWord(Dict*& dict, int& size) {
    if (!dict) {
        return;
    }

    char englishWord[kMaxWordLength];
    std::cout << "Введите английское слово, которое удалить: ";
    std::cin >> englishWord;

    for (int i = 0; i < size; ++i) {
        if (std::strcmp(dict[i].engl, englishWord)) {
            delete[] dict[i].engl;
            delete[] dict[i].rus;

            for (int j = i; j < size - 1; ++j) {
                dict[j] = dict[j + 1];
            }

            --size;
            return;
        }
    }
}

// void TranslateFromEnglishToRussian(const Dict* dict, int size) {
//     if (!dict) {
//         return;
//     }

//     ++size;
//     // bin poisk
// }

void TranslateFromRussianToEnglish(const Dict* dict, int size) {
    if (!dict) {
        return;
    }

    char russianWord[kMaxWordLength];
    std::cout << "Введите русский перевод слова: ";
    std::cin >> russianWord;
    std::cout << std::endl;

    for (int i = 0; i < size; ++i) {
        if (std::strcmp(russianWord, dict[i].rus)) {
            std::cout << "Перевод слова с английского на русский: " << dict[i].engl << std::endl;
        } else {
            std::cout << "Слово не найдено." << std::endl;
        }
    }
}

void PrintDictionary(const Dict* dict, int size) {
    if (!dict) {
        return;
    }

    if (size == 0) {
        std::cout << "Словарь пуст." << std::endl;
    } else {
        for (int i = 0; i < size; ++i) {
            std::cout << dict[i].engl << " - " << dict[i].rus << std::endl;
        }
    }
}

void SaveDictionaryToFile(const Dict* dict, int size, std::fstream& file) {
    if (!dict) {
        return;
    }

    file.open("dictionary.txt");

    if (!file.is_open()) {
        std::cout << "Ошибка при открытии файла!" << std::endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        file << dict[i].engl << " " << dict[i].rus << std::endl;
    }

    file.close();
}

void OpenFile(std::fstream& file, Dict*& dict, int& size) {
    file.open("dictionary.txt");

    if (!file.is_open()) {
        std::cout << "Ошибка при открытии файла!" << std::endl;
        return;
    }

    char word[kMaxWordLength]{};
    for (int i = 0; !file.eof(); ++i) {
        file >> word;
        dict[i].engl = word;
        ++size;
        std::cout << word << std::endl;
    }
}

void ExecuteApp() {
    std::fstream file;
    Dict dict[kSize]{};
    int size = 0;

    OpenFile(file, dict, size);

    int task = 0;
    while (true) {
        std::cout << "1. добавление слова в словарь\n"
                  << "2. удаление слов из словаря\n"
                  << "3. перевод слов с английского на русский\n"
                  << "4. перевод слов с русского на английский\n"
                  << "5. просмотр словаря\n"
                  << "6. вывод словаря в файл\n"
                  << "7. выход\n"
                  << "Введите номер задания: ";
        std::cin >> task;

        switch (static_cast<Task>(task)) {
            case Task::AddWord:
                AddWord(dict, size);
                break;
            case Task::DeleteWord:
                DeleteWord(dict, size);
                break;
            case Task::TranslateFromEnglishToRussian:
                // TranslateFromEnglishToRussian(dict, size);
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
                return;
            default:
                std::cout << "Введите число от 1 до 7: " << std::endl;
                break;
        }
    }
}
}  // namespace Dictionary
