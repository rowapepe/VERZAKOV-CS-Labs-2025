#pragma once

namespace Dictionary {
struct Dict {
    char* engl;
    char* rus;
};

enum class Task {
    AddWord = 1,
    DeleteWord,
    TranslateFromEnglishToRussian,
    TranslateFromRussianToEnglish,
    PrintDictionary,
    SaveDictionaryToFile,
    Exit
};

void ExecuteApp();
}  // namespace Dictionary
