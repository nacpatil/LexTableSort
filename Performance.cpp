#include "pch.h"
#include "Performance.h"
#include <random>
#include <omp.h>
#include <chrono>

void Performance::runPerformance() {
    size_t numRows = 10000000;  // Number of rows
    std::cout << "\n\n=============\nRunning performance test on large data with vector size : " << numRows << " x 7 columns" << "\n";

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

}


std::vector<int> Performance::generateSequentialIntVector(size_t size, int thisNumber) {
    std::vector<int> values(size);

#pragma omp parallel for
    for (size_t i = 0; i < size; ++i) {
        values[i] = (thisNumber + i - 1) % 9000 + 1;
    }
    return values;
}