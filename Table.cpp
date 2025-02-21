#include "Table.h"


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

// Sort the rows of the table, with the first column being the most significant
void Table::sort() {
    if (_vectors_count == 0) { return; }

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

        // Clear the console log after processing
        std::cout << "\r\033[K" << std::flush; // Clears the current line
    }
}

// Get the number of rows
size_t Table::numRows() const {
    return _columns.empty() ? 0 : _columns.cbegin()->size();
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

 