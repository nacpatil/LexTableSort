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
TEST_CASE("Sorting Table with One Row") {
    Table table = {
        AnyColumn(std::vector<int>{42}),
        AnyColumn(std::vector<double>{3.14}),
        AnyColumn(std::vector<std::string>{"hello"})
    };

    Table expectedTable = {
        AnyColumn(std::vector<int>{42}),
        AnyColumn(std::vector<double>{3.14}),
        AnyColumn(std::vector<std::string>{"hello"})
    };

    table.sort();
    CHECK(table.isEqual(expectedTable));  // Should be true
}

TEST_CASE("Sorting Table with Identical Rows") {
    Table table = {
        AnyColumn(std::vector<int>{1, 1, 1}),
        AnyColumn(std::vector<double>{2.2, 2.2, 2.2}),
        AnyColumn(std::vector<std::string>{"apple", "apple", "apple"})
    };

    Table expectedTable = {
        AnyColumn(std::vector<int>{1, 1, 1}),
        AnyColumn(std::vector<double>{2.2, 2.2, 2.2}),
        AnyColumn(std::vector<std::string>{"apple", "apple", "apple"})
    };

    table.sort();
    CHECK(table.isEqual(expectedTable));  // Order should remain unchanged
}
/* Currently constructor for table is set to throw an exception. This needs more thinking when table is used in actual applciation. 
TEST_CASE("Sorting Table with Different Column Sizes") {
    CHECK_THROWS_AS(Table({
        AnyColumn(std::vector<int>{1, 2, 3}),
        AnyColumn(std::vector<double>{4.5, 5.5})  // Different size
        }), std::invalid_argument);
}
*/

TEST_CASE("Sorting Table with Empty Strings") {
    Table table = {
        AnyColumn(std::vector<std::string>{"apple", "", "banana", " "})
    };

    Table expectedTable = {
        AnyColumn(std::vector<std::string>{"", " ", "apple", "banana"})  // Empty strings first
    };

    table.sort();
    CHECK(table.isEqual(expectedTable));
}


// Function to manually run tests
void Tests::Run() {
    doctest::Context context;
    int res = context.run();  // Run all test cases
    if (context.shouldExit()) {
        exit(res);  // Exit if required by doctest
    }

    // First test case
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
    table.print("After sort");  // ? Fixed: `print()` is a method of `Table`

}

 
 