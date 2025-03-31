#pragma once
#include "Functions/functions.hpp"
#include "MyStack/MyStack.hpp"
#include "Organizations/insurance.hpp"
#include "Organizations/organization.hpp"
#include "Organizations/plant.hpp"
#include "Organizations/shipbuilding.hpp"

enum class Task {
    Add = 1,
    Print = 2,
    Delete = 3,
    Clear = 4,
    Initialize = 5,
    Exit = 6
};

enum class Type {
    Insurance = 1,
    Plant = 2,
    Ship = 3
};

void menu();
