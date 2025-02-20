 

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


#include "pch.h"
#include <iostream>
#include "../AnyColumn.h"
#include "../Table.h"
#include "../Tests.h"
#include <random>
#include <omp.h>

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

// Function to generate a random vector of integers (values between 1 and 6)

std::vector<int> generateSequentialIntVector(size_t size, int thisNumber) {
    std::vector<int> values(size);

#pragma omp parallel for
    for (size_t i = 0; i < size; ++i) {
        values[i] = (thisNumber + i - 1) % 9000 + 1;
    }
    return values;
}

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

    size_t numRows = 300000000;  // Number of rows

    Table randomIntTable = {
        AnyColumn(generateSequentialIntVector(numRows,2)),
        AnyColumn(generateSequentialIntVector(numRows,1)),
        AnyColumn(generateSequentialIntVector(numRows,3)),
        AnyColumn(generateSequentialIntVector(numRows,4)),
        AnyColumn(generateSequentialIntVector(numRows,5)),
        AnyColumn(generateSequentialIntVector(numRows,6)),
        AnyColumn(generateSequentialIntVector(numRows,7))
    };
    randomIntTable.sort();

    std::cout << "Done generating random vector \n";

    return 0;
}