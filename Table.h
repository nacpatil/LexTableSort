#pragma once

#include <list>
#include <vector>
#include <numeric>
#include <iostream>
#include "AnyColumn.h"

class Table {
private:
    size_t _rows;
    std::list<AnyColumn> _columns;

public:
    // Constructor
    Table(const std::initializer_list<AnyColumn>& l);

    // Sort the table rows
    void sort();

    // Get the number of rows
    size_t numRows() const;

    // Print table content
    void print(const std::string& str) const;
    bool isEqual(const Table& other) const;

};
