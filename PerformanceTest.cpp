#include "PerformanceTest.h"
#include <random>
#include <omp.h>
#include <chrono>
#include <random>

#include <fstream>

void PerformanceTest::runPerformance(std::string algoType, std::string dataType) {
    // Open file to write results
    std::ofstream resultFile("performance_results_"+ algoType+ "_" + dataType + ".csv");
    if (!resultFile) {
        std::cerr << "Error opening file for writing results!" << std::endl;
        return;
    }

    // Write column headers to the file
    resultFile << "NumRows,SortTime(seconds)\n";

    // Run performance tests for different row sizes from 1 million to 20 million with a 2 million gap
    std::vector<size_t> rowSizes = { 1000000, 5000000, 10000000, 20000000, 30000000, 50000000, 100000000 };//,200000000 , 300000000, 400000000};
    //std::vector<size_t> rowSizes = { 30000000 };
    for (size_t numRows : rowSizes) {
        std::cout << "\n\n=============\nRunning performance test on large data with vector size : " << numRows << " x 7 columns\n";
        std::cout << "Generating permutated/mismashed large size table.\n";

        // Define a pointer-to-member type for your functions.
        using GenFunc = std::vector<int>(PerformanceTest::*)(size_t, int);

        // Assign the function pointer using the '&' operator.
        GenFunc generator = (dataType == "seq")
            ? &PerformanceTest::generateSequentialIntVector
            : (dataType == "rand")
            ? &PerformanceTest::generateRandomIntVector
            : &PerformanceTest::generateSortedIntVector;


        // When calling the function, use the instance (e.g., 'this') and the pointer-to-member syntax:
        Table randomIntTable = {
            AnyColumn((this->*generator)(numRows, 1)),
            AnyColumn((this->*generator)(numRows, 2)),
            AnyColumn((this->*generator)(numRows, 3)),
            AnyColumn((this->*generator)(numRows, 4)),
            AnyColumn((this->*generator)(numRows, 5)),
            AnyColumn((this->*generator)(numRows, 6)),
            AnyColumn((this->*generator)(numRows, 7)),
            AnyColumn((this->*generator)(numRows, 8))
        };

        std::cout << "Done generating input table.\n";

        // Measure sorting time
        auto sort_start_time = std::chrono::high_resolution_clock::now();

        randomIntTable.sort(algoType);

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



std::vector<int> PerformanceTest::generateRandomIntVector(size_t size, int thisNumber) {
    std::vector<int> values(size);

    #pragma omp parallel
    {
        // Use a combination of std::random_device and thread-specific info for extra entropy
        std::random_device rd;
        unsigned seed = rd() ^ (static_cast<unsigned>(omp_get_thread_num()) +
            static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));
        std::mt19937 rng(seed);
        std::uniform_int_distribution<int> dist(1, 100);  // Change range as needed

        #pragma omp for
        for (ptrdiff_t i = 0; i < static_cast<ptrdiff_t>(size); ++i) {
            values[i] = dist(rng);
        }
    }

    return values;
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


std::vector<int> PerformanceTest::generateSortedIntVector(size_t size, int thisNumber) {
    std::vector<int> values(size);

#pragma omp parallel for
    for (ptrdiff_t i = 0; i < static_cast<ptrdiff_t>(size); ++i) {
        size_t index = static_cast<size_t>(i);  // Casting to size_t for indexing
        values[index] = index;
    }
    return values;
}





