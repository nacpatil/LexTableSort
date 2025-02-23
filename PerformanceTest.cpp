#include "PerformanceTest.h"
#include <random>
#include <omp.h>
#include <chrono>

#include <fstream>

void PerformanceTest::runPerformance(std::string type) {
    // Open file to write results
    std::ofstream resultFile("performance_results_"+type+".csv");
    if (!resultFile) {
        std::cerr << "Error opening file for writing results!" << std::endl;
        return;
    }

    // Write column headers to the file
    resultFile << "NumRows,SortTime(seconds)\n";

    // Run performance tests for different row sizes from 1 million to 20 million with a 2 million gap
    std::vector<size_t> rowSizes = { 1000000, 3000000, 5000000, 7000000, 10000000, 15000000, 20000000 };
    for (size_t numRows : rowSizes) {
        std::cout << "\n\n=============\nRunning performance test on large data with vector size : " << numRows << " x 7 columns\n";
        std::cout << "Generating permutated/mismashed large size table.\n";

        // Generate random data (you should replace generateSequentialIntVector with actual data generation logic)
        Table randomIntTable = {
            AnyColumn(generateSequentialIntVector(numRows, 2)),
            AnyColumn(generateSequentialIntVector(numRows, 1)),
            AnyColumn(generateSequentialIntVector(numRows, 3)),
            AnyColumn(generateSequentialIntVector(numRows, 4)),
            AnyColumn(generateSequentialIntVector(numRows, 5)),
            AnyColumn(generateSequentialIntVector(numRows, 6)),
            AnyColumn(generateSequentialIntVector(numRows, 7))
        };
        std::cout << "Done generating input table.\n";

        // Measure sorting time
        auto sort_start_time = std::chrono::high_resolution_clock::now();

        randomIntTable.sort("perm");

        auto sort_end_time = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> sort_duration = sort_end_time - sort_start_time;

        std::cout << "Sorting time: " << sort_duration.count() << " seconds\n";

        // Write results to the file in columns (NumRows, SortTime)
        resultFile << numRows << "," << sort_duration.count() << "\n";
    }

    // Close the file after writing
    resultFile.close();
    std::cout << "Results saved to performance_results.csv\n";
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






