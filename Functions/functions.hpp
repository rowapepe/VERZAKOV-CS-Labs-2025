#pragma once

#include "../Organizations/organization.hpp"
#include "../MyStack/MyStack.hpp"

void print(MyStack::MyStack<Organization*>& container);
bool remove_item(MyStack::MyStack<Organization*>& container, int index);
void clear_container(MyStack::MyStack<Organization*>& container);
