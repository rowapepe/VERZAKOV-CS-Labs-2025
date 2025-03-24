#pragma once

#include "../Organizations/organization.hpp"
#include "../Vector/myvector.hpp"

void print(const MyVector<Organization*>& container);
bool remove_item(MyVector<Organization*>& container, size_t index);
void clear_container(MyVector<Organization*>& container);


