#pragma once

#include "../Organizations/organization.hpp"
#include "../MyStack/MyStack.hpp"

void print(MyStack::MyStack<Organization*>& container);
bool remove(MyStack::MyStack<Organization*>& container, int index);
void clear(MyStack::MyStack<Organization*>& container);
