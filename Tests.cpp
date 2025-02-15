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

    bool areE = table0.isEqual(expectedTable);

    // Log the failure but allow tests to continue
    CHECK(areE);  // Will mark test as failed but NOT stop execution
 
}


TEST_CASE("Sorting Table with Repeated Values") {
    Table table1 = {
        AnyColumn(std::vector<int>{3, 3, 3, 1, 1, 1, 2, 2, 2, 2}),
        AnyColumn(std::vector<double>{4.5, 4.5, 4.5, 2.2, 2.2, 2.2, 3.3, 3.3, 3.3, 3.3}),
        AnyColumn(std::vector<std::string>{"cat", "cat", "cat", "dog", "dog", "dog", "bird", "bird", "bird", "bird"})
    };

    Table expectedTable1 = {
        AnyColumn(std::vector<int>{1, 1, 1, 2, 2, 2, 2, 3, 3, 3}),
        AnyColumn(std::vector<double>{2.2, 2.2, 2.2, 3.3, 3.3, 3.3, 3.3, 4.5, 4.5, 4.5}),
        AnyColumn(std::vector<std::string>{"dog", "dog", "dog", "bird", "bird", "bird", "bird", "cat", "cat", "cat"})
    };

    table1.sort();
    CHECK(table1.isEqual(expectedTable1));
}

TEST_CASE("Sorting Table with Unique Values") {
    Table table2 = {
        AnyColumn(std::vector<int>{9, 2, 5, 7, 1}),
        AnyColumn(std::vector<double>{2.1, 4.2, 3.3, 1.4, 5.5}),
        AnyColumn(std::vector<std::string>{"apple", "orange", "banana", "grape", "cherry"})
    };

    Table expectedTable2 = {
        AnyColumn(std::vector<int>{1, 2, 5, 7, 9}),
        AnyColumn(std::vector<double>{5.5, 4.2, 3.3, 1.4, 2.1}),
        AnyColumn(std::vector<std::string>{"cherry", "orange", "banana", "grape", "apple"})
    };

    table2.sort();
    CHECK(table2.isEqual(expectedTable2));
}

TEST_CASE("Sorting Table with Only One Column") {
    Table table3 = {
        AnyColumn(std::vector<int>{4, 2, 8, 1, 5})
    };

    Table expectedTable3 = {
        AnyColumn(std::vector<int>{1, 2, 4, 5, 8})
    };

    table3.sort();
    CHECK(table3.isEqual(expectedTable3));
}


TEST_CASE("Sorting Empty Table") {
    Table table4 = {};

    Table expectedTable4 = {};

    table4.sort();
    CHECK(table4.isEqual(expectedTable4));
}




TEST_CASE("Sorting Table with Strings Only") {
    Table table5 = {
        AnyColumn(std::vector<std::string>{"zebra", "monkey", "apple", "banana", "dog"})
    };

    Table expectedTable5 = {
        AnyColumn(std::vector<std::string>{"apple", "banana", "dog", "monkey", "zebra"})
    };

    table5.sort();
    CHECK(table5.isEqual(expectedTable5));
}

TEST_CASE("Sorting Table with Already Sorted Values") {
    Table table6 = {
        AnyColumn(std::vector<int>{1, 2, 3, 4, 5}),
        AnyColumn(std::vector<double>{1.1, 2.2, 3.3, 4.4, 5.5}),
        AnyColumn(std::vector<std::string>{"a", "b", "c", "d", "e"})
    };

    Table expectedTable6 = {
        AnyColumn(std::vector<int>{1, 2, 3, 4, 5}),
        AnyColumn(std::vector<double>{1.1, 2.2, 3.3, 4.4, 5.5}),
        AnyColumn(std::vector<std::string>{"a", "b", "c", "d", "e"})
    };

    table6.sort();
    CHECK(table6.isEqual(expectedTable6));
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