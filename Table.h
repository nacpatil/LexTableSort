#pragma once

#include <list>
#include <vector>
#include <numeric>
#include <iostream>
#include "AnyColumn.h"

class Table {
private:
    size_t _rows, _vectors_count;
    std::list<AnyColumn> _columns;

public:
    // Constructor
    Table(const std::initializer_list<AnyColumn>& l);

    // Sort the table rows
    void sort(std::string type = "perm");
    void comparatorSort();
    void permSort();
    // Get the number of rows
    size_t numRows() const;

    // Print table content
    void print(const std::string& str) const;


    bool isGreater(size_t i, size_t j);
    //  Compare two tables and return if equal.
    bool isEqual(const Table& other) const;

};
