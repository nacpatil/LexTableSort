﻿#include "pch.h"
#include <iostream>
#include "../AnyColumn.h"
#include "../Table.h"
#include "../Tests.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

int main() {

    std::cout << "\n\n=======================Orignal Test" << std::endl;

    // Orignal test case
    Table table = {  // ? Use `Table`, not `Tests`
        AnyColumn(std::vector<int>{ 1, 2, 1, 2, 1 }),
        AnyColumn(std::vector<double>{ 5.0, 4.0, 4.0, 1.0, 6.0 }),
        AnyColumn(std::vector<std::string>{ "second", "fifth", "first", "forth", "third" })
    };

    // Print before sorting
    table.print("Before sort");  // ? Fixed: `print()` is a method of `Table`
    // Sort the table
    table.sort();
    // Print after sorting
    table.print("\nAfter sort");  // ? Fixed: `print()` is a method of `Table`
    std::cout << "=======================Run Complete \n\n";

    Tests().runDocTests();  // Run all test cases 
    return 0;
}
