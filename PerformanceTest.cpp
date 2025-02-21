#include "PerformanceTest.h"
#include <random>
#include <omp.h>
#include <chrono>

void PerformanceTest::runPerformance() {
    size_t numRows = 300000000;  // Number of rows

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

    auto sort_start_time = std::chrono::high_resolution_clock::now();

    randomIntTable.sort();

    auto sort_end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> sort_duration = sort_end_time - sort_start_time;

    std::cout << "Done generating random vector \n";
    std::cout << "Sorting time: " << sort_duration.count() << " seconds\n";

}


std::vector<int> PerformanceTest::generateSequentialIntVector(size_t size, int thisNumber) {
    std::vector<int> values(size);

#pragma omp parallel for
    for (ptrdiff_t i = 0; i < static_cast<ptrdiff_t>(size); ++i) {
        size_t index = static_cast<size_t>(i);  // Casting to size_t for indexing
        values[index] = (thisNumber + index - 1) % 9000 + 1;
    }
    return values;
}






