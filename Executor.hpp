#pragma once
#include <cstddef>

namespace Executor {
enum class PlanetsTasks {
    Read = 1,
    Write = 2,
    Sort = 3,
    Add = 4,
    Delete = 5,
    Edit = 6,
    Print = 7,
    Exit = 0,
};

enum class DebatsTasks {
    Read = 1,
    Write = 2,
    Sort = 3,
    Add = 4,
    Delete = 5,
    Edit = 6,
    Print = 7,
    Exit = 0,
};

enum class AppTasks {
    Planets = 1,
    Debats = 2,
    Exit = 0,
};

void ExecutePlanetsApp();
void ExecuteDebatsApp();
void ExecuteApp();
}  // namespace Executor
