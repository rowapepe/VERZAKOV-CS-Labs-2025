#pragma once

namespace Dictionary {
struct Dict {
    char* engl;
    char* rus;
};

enum class Task {
    AddWord = 1,
    DeleteWord = 2,
    TranslateFromEnglishToRussian = 3,
    TranslateFromRussianToEnglish = 4,
    PrintDictionary = 5,
    SaveDictionaryToFile = 6,
    Exit = 7,
};

void ExecuteApp();
}  // namespace Dictionary
