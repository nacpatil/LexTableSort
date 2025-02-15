#include "pch.h"
#include "Tests.h"
#include "../Table.h"
#include "../AnyColumn.h"
 
 
#include "doctest.h"

int add(int a, int b) {
    return a + b;
}

 

TEST_CASE("Sorting Table and Comparing with Expected Result") {
    // Unsorted Table
    Table table0 = {
        AnyColumn(std::vector<int>{1, 2, 1, 2, 1}),
        AnyColumn(std::vector<double>{5.0, 4.0, 4.0, 1.0, 6.0}),
        AnyColumn(std::vector<std::string>{"second", "fifth", "first", "forth", "third"})
    };

    // Expected sorted result
    Table expectedTable = {
        AnyColumn(std::vector<int>{1, 1, 1, 2, 2}),
        AnyColumn(std::vector<double>{4.0, 5.0, 6.0, 1.0, 4.0}),
        AnyColumn(std::vector<std::string>{"first", "second", "third", "forth", "fifth"})
    };

    // Sort table0
    table0.sort();

    // Compare the sorted table with the expected result
    CHECK(table0.isEqual(expectedTable));
}




// Function to manually run tests
void Tests::Run() {
    doctest::Context context;
    int res = context.run();  // Run all test cases
    if (context.shouldExit()) {
        exit(res);  // Exit if required by doctest
    }

    // First test case
    Table table0 = {  // ? Use `Table`, not `Tests`
        AnyColumn(std::vector<int>{ 1, 2, 1, 2, 1 }),
        AnyColumn(std::vector<double>{ 5.0, 4.0, 4.0, 1.0, 6.0 }),
        AnyColumn(std::vector<std::string>{ "second", "fifth", "first", "forth", "third" })
    };

    // Second test case with deep sharding
    Table table = {
        AnyColumn(std::vector<int>{3, 3, 3, 1, 1, 1, 2, 2, 2, 2}),
        AnyColumn(std::vector<double>{4.5, 4.5, 4.5, 2.2, 2.2, 2.2, 3.3, 3.3, 3.3, 3.3}),
        AnyColumn(std::vector<std::string>{"cat", "cat", "cat", "dog", "dog", "dog", "bird", "bird", "bird", "bird"}),
        AnyColumn(std::vector<int>{10, 20, 10, 30, 40, 30, 50, 60, 50, 50}),
        AnyColumn(std::vector<double>{1.01, 1.02, 1.01, 2.01, 2.02, 2.01, 3.01, 3.02, 3.01, 3.01})
    };

    // Print before sorting
    table.print("Before sort");  // ? Fixed: `print()` is a method of `Table`

    // Sort the table
    table.sort();

    // Print after sorting
    table.print("After sort");  // ? Fixed: `print()` is a method of `Table`

}

 
// Define the Tests::Run method separately (if needed)
 
/* 

// Run the test cases
void Tests::Run() {
 
    // First test case
    Table table0 = {  // ? Use `Table`, not `Tests`
        AnyColumn(std::vector<int>{ 1, 2, 1, 2, 1 }),
        AnyColumn(std::vector<double>{ 5.0, 4.0, 4.0, 1.0, 6.0 }),
        AnyColumn(std::vector<std::string>{ "second", "fifth", "first", "forth", "third" })
    };

    // Second test case with deep sharding
    Table table = {
        AnyColumn(std::vector<int>{3, 3, 3, 1, 1, 1, 2, 2, 2, 2}),
        AnyColumn(std::vector<double>{4.5, 4.5, 4.5, 2.2, 2.2, 2.2, 3.3, 3.3, 3.3, 3.3}),
        AnyColumn(std::vector<std::string>{"cat", "cat", "cat", "dog", "dog", "dog", "bird", "bird", "bird", "bird"}),
        AnyColumn(std::vector<int>{10, 20, 10, 30, 40, 30, 50, 60, 50, 50}),
        AnyColumn(std::vector<double>{1.01, 1.02, 1.01, 2.01, 2.02, 2.01, 3.01, 3.02, 3.01, 3.01})
    };

    // Print before sorting
    table.print("Before sort");  // ? Fixed: `print()` is a method of `Table`

    // Sort the table
    table.sort();

    // Print after sorting
    table.print("After sort");  // ? Fixed: `print()` is a method of `Table`
}

*/