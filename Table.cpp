#include "pch.h"
#include "Table.h"

 

// Constructor
Table::Table(const std::initializer_list<AnyColumn>& l) : _columns(l) {
    _rows = _columns.front().size();
}

// Sort the rows of the table, with the first column being the most significant
void Table::sort() {
    int i = 0;
    std::vector<size_t> perm(_columns.front().size());
    std::iota(perm.begin(), perm.end(), 0);
    std::vector<std::pair<size_t, size_t>> shardsVect;
    shardsVect.emplace_back(0, _rows);

    for (auto it = _columns.begin(); it != _columns.end(); ++it, ++i) {
        if (i == 0) {
            for (size_t j = 0; j < shardsVect.size(); j++) {
                std::vector<size_t> tmp = it->sort(perm, shardsVect[j].first, shardsVect[j].second);
            }
            shardsVect = it->ReShard(shardsVect);
        }
        else {
            it->applyPermutation(perm, 0, _rows);
            for (size_t j = 0; j < shardsVect.size(); j++) {
                std::vector<size_t> tmp = it->sort(perm, shardsVect[j].first, shardsVect[j].second);
            }
            shardsVect = it->ReShard(shardsVect);
        }
        std::cout << "Column " << i << " sorted and permutation retrieved.\n";
    }
}

// Get the number of rows
size_t Table::numRows() const {
    return _columns.cbegin()->size();
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
