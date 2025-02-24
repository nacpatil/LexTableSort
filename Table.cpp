#include "Table.h"
#include <algorithm>
#include <execution>

// Constructor
Table::Table(const std::initializer_list<AnyColumn>& l) : _columns(l) {
    _rows = _columns.empty() ? 0 : _columns.front().size();
    _vectors_count = _columns.empty() ? 0 : _columns.size();
    // Ensure all columns have the same length
    for (const auto& col : _columns) {
        if (col.size() != _rows) {
            throw std::invalid_argument("Error: All columns must have the same length.");        }
    }
}

void Table::addColumn(const AnyColumn& newColumn) {
    // Ensure the new column has the same number of rows
    if (!_columns.empty() && newColumn.size() != _rows) {
        throw std::invalid_argument("Error: New column must have the same number of rows as existing columns.");
    }
    // If the table was empty, set the number of rows based on the first column added
    if (_columns.empty()) {
        _rows = newColumn.size();
    }
        // Add the new column to the list
    _columns.push_back(newColumn);

    // Update the column count
    _vectors_count++;
}


// Get the number of rows
size_t Table::numRows() const {
    return _columns.empty() ? 0 : _columns.cbegin()->size();
}

void Table::comparatorSort() {
    std::vector<size_t> perm(_rows);
    std::iota(perm.begin(), perm.end(), 0);
    std::stable_sort(std::execution::par, perm.begin(), perm.end(), [&](size_t i, size_t j) {
        return isGreater(i, j);
    });
    for (auto it = _columns.begin(); it != _columns.end(); ++it) {
        it->applyPermutation(perm, 0, _rows);
    }
}

 
void Table::permSort() {
    int i = 0;
    std::vector<size_t> perm(_rows);
    std::iota(perm.begin(), perm.end(), 0);
    std::vector<std::pair<size_t, size_t>> shardsVect;
    shardsVect.emplace_back(0, _rows);

    for (auto it = _columns.begin(); it != _columns.end(); ++it, ++i) {
        // Log message for the column being processed
        std::cout << "\rProcessing column vector " << i << "..." << std::flush;

        if (i > 0) {
            it->applyPermutation(perm, 0, _rows);
        }
        for (size_t j = 0; j < shardsVect.size(); j++) {
            it->sort(perm, shardsVect[j].first, shardsVect[j].second);
        }
        shardsVect = it->ReShard(shardsVect);
        std::cout << "shards count : " << shardsVect.size() << "\n";
        // Clear the console log after processing
        std::cout << "\r\033[K" << std::flush; // Clears the current line
    }
}


// Sort the rows of the table, with the first column being the most significant
void Table::sort(std::string type) {
    if (_vectors_count == 0) { return; }
    if (type == "perm") {permSort(); }
    if (type == "comp") { comparatorSort(); }
}



// Print table content
void Table::print(const std::string& str) const {
    std::cout << str << std::endl;
    for (size_t i = 0; i < numRows(); i++) {
        for (auto it = _columns.begin(); it != _columns.end(); ++it) {
            it->printElement(i, std::cout);
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}



// Compare two Table objects
bool Table::isEqual(const Table& other) const {
    if (_columns.size() != other._columns.size()) {
        return false; // Different number of columns
    }

    auto it1 = _columns.begin();
    auto it2 = other._columns.begin();

    while (it1 != _columns.end() && it2 != other._columns.end()) {
        if (!it1->areEqual(*it2)) {  // Use `AnyColumn::areEqual` for column-wise comparison
            return false;  // Return false if any column differs
        }
        ++it1;
        ++it2;
    }

    return true;  // If loop completes, all columns are equal
}
 

bool Table::isGreater(size_t i, size_t j) {
    for (auto it = _columns.begin(); it != _columns.end(); ++it) {
        int result = it->compare(i, j);
        if (result < 0) return true;   // i is greater than j
        else if (result > 0) return false; // j is greater than i
    }
    return false; // All columns are equal
}
