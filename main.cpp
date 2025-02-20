 
#include "pch.h"
#include <iostream>
#include "../AnyColumn.h"
#include "../Table.h"
#include "../Tests.h"
#include <random>
#include <omp.h>
#include <chrono>
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
    std::cout << "\n\n=============\nRunning performance test on large data with vector size : " << numRows <<" x 7 columns" << "\n";

    std::cout << "Generating permutated/mismashed large size table.\n";

    Table randomIntTable = {
        AnyColumn(generateSequentialIntVector(numRows,2)),
        AnyColumn(generateSequentialIntVector(numRows,1)),
        AnyColumn(generateSequentialIntVector(numRows,3)),
        AnyColumn(generateSequentialIntVector(numRows,4)),
        AnyColumn(generateSequentialIntVector(numRows,5)),
        AnyColumn(generateSequentialIntVector(numRows,6)),
        AnyColumn(generateSequentialIntVector(numRows,7))
    };
    std::cout << "Done generating input table.\n";

    // Start timing the sorting process
    auto sort_start_time = std::chrono::high_resolution_clock::now();

    randomIntTable.sort();

    auto sort_end_time = std::chrono::high_resolution_clock::now();

    // Compute and print sorting time
    std::chrono::duration<double> sort_duration = sort_end_time - sort_start_time;

    std::cout << "Done generating random vector \n";
    std::cout << "Sorting time: " << sort_duration.count() << " seconds\n";


    return 0;
}