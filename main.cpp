#include "pch.h"
#include <iostream>
#include <string>
#include <initializer_list>
#include <vector>
#include <list>
#include <numeric>
#include <algorithm>

using namespace std;

// A column is a homogeneous list of values. Columns might have a very large number of elements.

class AnyColumn
{
private:

    // Only one of the fields will be non-empty.
    std::vector<int> _intVector;
    std::vector<double> _doubleVector;
    std::vector<std::string> _stringVector;

public:

    AnyColumn(const std::vector<int>& values) { _intVector = values; }
    AnyColumn(const std::vector<double>& values) { _doubleVector = values; }
    AnyColumn(const std::vector<std::string>& values) { _stringVector = values; }

    size_t size() const
    {
        if (_intVector.size() > 0) return  _intVector.size();
        if (_doubleVector.size() > 0) return  _doubleVector.size();
        if (_stringVector.size() > 0) return  _stringVector.size();
        return 0;
    }

    void printElement(size_t index, ostream& stream) const
    {
        if (_intVector.size() > 0) stream << _intVector[index];
        if (_doubleVector.size() > 0) stream << _doubleVector[index];
        if (_stringVector.size() > 0) stream << _stringVector[index];
    }
 

    std::vector<size_t> sort(std::vector<size_t>& perm, size_t start, size_t end)
    {
        if (start >= end || start >= perm.size() || end > perm.size()) {
            std::cerr << "Invalid range: start=" << start << ", end=" << end << "\n";
            return perm; // No sorting if the range is invalid
        }

        for (size_t i = start; i < end; ++i) {
            if (perm[i] >= size()) {
                std::cerr << "ERROR: perm[" << i << "] = " << perm[i] << " is out of bounds!\n";
            }
        }

        if (!_intVector.empty())
        {
           
            // Print `_intVector` before sorting
            std::cout << "Before sorting `_intVector` range: ";
            for (size_t i = start; i < end; ++i) {
                std::cout << _intVector[i] << " ";
            }
            std::cout << "\n";

            // Use `std::sort` to sort `_intVector[start:end]`, while updating `perm`
            std::vector<size_t> indices(end - start);
            std::iota(indices.begin(), indices.end(), start);  // Generate indices [start, ..., end-1]

            std::sort(indices.begin(), indices.end(), [&](size_t i, size_t j) {
                return _intVector[i] < _intVector[j];  // Sort `_intVector` directly
            });

            // Apply sorted order to `_intVector` and update `perm`
            std::vector<int> temp(_intVector);
            std::vector<size_t> tempPerm(perm);

            for (size_t i = start; i < end; ++i) {
                _intVector[i] = temp[indices[i - start]];  // Move values based on sorted indices
                perm[i] = tempPerm[indices[i - start]];  // Move perm indices accordingly
            }

            // Print `_intVector` after sorting
            std::cout << "After sorting `_intVector` range: ";
            for (size_t i = 0; i < _intVector.size(); ++i) {
                std::cout << _intVector[i] << " ";
            }
            std::cout << "\n";

            // Print how `perm` changed (bookkeeping)
            std::cout << "Updated permutation: ";
            for (size_t i = 0; i < perm.size(); ++i) {
                std::cout << perm[i] << " ";
            }
            std::cout << "\n";


        }
        else if (!_doubleVector.empty())
        { 
            // Print `_doubleVector` before sorting
            std::cout << "Before sorting `_doubleVector` range: ";
            for (size_t i = start; i < end; ++i) std::cout << _doubleVector[i] << " ";
            std::cout << "\n";

            // Selection sort applied directly to `_doubleVector`, while updating `perm`
            for (size_t i = start; i < end - 1; ++i) {
                size_t minIndex = i;
                for (size_t j = i + 1; j < end; ++j) {
                    if (_doubleVector[j] < _doubleVector[minIndex]) {
                        minIndex = j;
                    }
                }
                if (minIndex != i) {
                    std::swap(_doubleVector[i], _doubleVector[minIndex]);  // Sort `_doubleVector`
                    std::swap(perm[i], perm[minIndex]);  // Track movement in `perm`
                }
            }

            // Print `_doubleVector` after sorting
            std::cout << "After sorting `_doubleVector` range: ";
            for (size_t i = 0; i < _doubleVector.size(); ++i) std::cout << _doubleVector[i] << " ";
            std::cout << "\n";

            // Print how `perm` changed (bookkeeping)
            std::cout << "Updated permutation: ";
            for (size_t i = 0; i < perm.size(); ++i) std::cout << perm[i] << " ";
            std::cout << "\n";

        }
        else if (!_stringVector.empty())
        {
            // Print `_stringVector` before sorting
            std::cout << "Before sorting `_stringVector` range: ";
            for (size_t i = start; i < end; ++i) std::cout << _stringVector[i] << " ";
            std::cout << "\n";

            // Selection sort applied directly to `_stringVector`, while updating `perm`
            for (size_t i = start; i < end - 1; ++i) {
                size_t minIndex = i;
                for (size_t j = i + 1; j < end; ++j) {
                    if (_stringVector[j] < _stringVector[minIndex]) {
                        minIndex = j;
                    }
                }
                if (minIndex != i) {
                    std::swap(_stringVector[i], _stringVector[minIndex]);  // Sort `_stringVector`
                    std::swap(perm[i], perm[minIndex]);  // Track movement in `perm`
                }
            }

            // Print `_stringVector` after sorting
            std::cout << "After sorting `_stringVector` range: ";
            for (size_t i = 0; i < _stringVector.size(); ++i) std::cout << _stringVector[i] << " ";
            std::cout << "\n";

            // Print how `perm` changed (bookkeeping)
            std::cout << "Updated permutation: ";
            for (size_t i = 0; i < perm.size(); ++i) std::cout << perm[i] << " ";
            std::cout << "\n";

        }

        return perm;
    }


    std::vector<std::pair<size_t, size_t>> ReShard(std::vector<std::pair<size_t, size_t>>& existingShards)
    {
        std::vector<std::pair<size_t, size_t>> newShards;

        if (!_intVector.empty())
        {
            for (const auto& shard : existingShards)
            {
                size_t start = shard.first;
                size_t end = shard.second;

                if (start >= end || end > _intVector.size()) {
                    std::cerr << "Invalid shard: {" << start << ", " << end << "} ignored.\n";
                    continue;
                }

                size_t currentStart = start;
                for (size_t i = start + 1; i < end; ++i)
                {
                    if (_intVector[i] != _intVector[i - 1])
                    {
                        newShards.emplace_back(currentStart, i);
                        currentStart = i;
                    }
                }
                newShards.emplace_back(currentStart, end);
            }
        }
        else if (!_doubleVector.empty())
        {
            for (const auto& shard : existingShards)
            {
                size_t start = shard.first;
                size_t end = shard.second;

                if (start >= end || end > _doubleVector.size()) {
                    std::cerr << "Invalid shard: {" << start << ", " << end << "} ignored.\n";
                    continue;
                }

                size_t currentStart = start;
                for (size_t i = start + 1; i < end; ++i)
                {
                    if (_doubleVector[i] != _doubleVector[i - 1])
                    {
                        newShards.emplace_back(currentStart, i);
                        currentStart = i;
                    }
                }
                newShards.emplace_back(currentStart, end);
            }
        }
        else if (!_stringVector.empty())
        {
            for (const auto& shard : existingShards)
            {
                size_t start = shard.first;
                size_t end = shard.second;

                if (start >= end || end > _stringVector.size()) {
                    std::cerr << "Invalid shard: {" << start << ", " << end << "} ignored.\n";
                    continue;
                }

                size_t currentStart = start;
                for (size_t i = start + 1; i < end; ++i)
                {
                    if (_stringVector[i] != _stringVector[i - 1])
                    {
                        newShards.emplace_back(currentStart, i);
                        currentStart = i;
                    }
                }
                newShards.emplace_back(currentStart, end);
            }
        }
        existingShards = newShards;
        return newShards;
    }



    void applyPermutation(const std::vector<size_t>& perm, size_t start, size_t end)
    {
        if (start >= end || start >= perm.size() || end > perm.size()) {
            return; // No permutation needed if range is invalid
        }

        if (!_intVector.empty())
        {
            std::vector<int> temp(_intVector);
            for (size_t i = start; i < end; ++i)
                _intVector[i] = temp[perm[i]];
        }
        else if (!_doubleVector.empty())
        {
            std::vector<double> temp(_doubleVector);
            for (size_t i = start; i < end; ++i)
                _doubleVector[i] = temp[perm[i]];
        }
        else if (!_stringVector.empty())
        {
            std::vector<std::string> temp(_stringVector);
            for (size_t i = start; i < end; ++i)
                _stringVector[i] = temp[perm[i]];
        }
    }


};


// A Table is a heterogeneous ordered collection of columns, each column homogeneous
class Table
{
private:
    size_t _rows;
    std::list<AnyColumn> _columns;

public:

    Table(const std::initializer_list<AnyColumn>& l) : _columns(l)
    {
        _rows = _columns.front().size();
    }

    // Sort the rows of the table, with the first column being most significant
    void sort()
    {
        int i = 0;
        std::vector<size_t> perm(_columns.front().size());
        std::iota(perm.begin(), perm.end(), 0);
        std::vector<std::pair<size_t, size_t>> shardsVect;
        shardsVect.emplace_back(0, _rows);
 

        for (auto it = _columns.begin(); it != _columns.end(); ++it, ++i)
        {
            if ( i == 0) {
                for (size_t j = 0; j < shardsVect.size(); j++) {   
                    std::vector<size_t> tmp = it->sort(perm, shardsVect[j].first, shardsVect[j].second);
                }
                std::vector<std::pair<size_t, size_t>> newShards = it->ReShard(shardsVect);
            }
            else {


                if (i == 1) {
                    it->applyPermutation(perm, 0, _rows);
                    for (size_t j = 0; j < shardsVect.size(); j++) {
                        std::vector<size_t> tmp = it->sort(perm, shardsVect[j].first, shardsVect[j].second);
                    }
                    std::vector<std::pair<size_t, size_t>> newShards = it->ReShard(shardsVect);
                } 
                if (i == 2) {
                    it->applyPermutation(perm, 0, _rows);
                    for (size_t j = 0; j < shardsVect.size(); j++) {
                        std::vector<size_t> tmp = it->sort(perm, shardsVect[j].first, shardsVect[j].second);
                    }
                    std::vector<std::pair<size_t, size_t>> newShards = it->ReShard(shardsVect);
                }
                if (i > 2) {
                    it->applyPermutation(perm, 0, _rows);
                    for (size_t j = 0; j < shardsVect.size(); j++) {
                        std::vector<size_t> tmp = it->sort(perm, shardsVect[j].first, shardsVect[j].second);
                    }
                    std::vector<std::pair<size_t, size_t>> newShards = it->ReShard(shardsVect);
                }

                
            }
            // Do something with perm if needed, but don't apply it
            std::cout << "Column " << i << " sorted and permutation retrieved.\n";
        }
    }

    size_t numRows() const { return _columns.cbegin()->size(); }

    void print(std::string str) const
    {
        cout << str << endl;
        for (int i = 0; i < numRows(); i++)
        {
            for (auto it = _columns.begin(); it != _columns.end(); it++)
            {
                it->printElement(i, cout);
                cout << " ";
            }
            cout << endl;
        }
    }


};
 

class Tester

{

public:

    void Run()

    {
        // Testing
        Table table0 = {
            AnyColumn(std::vector<int>{ 1,     2,     1,     2,     1 }),
            AnyColumn(std::vector<double>{ 5.0,   4.0,   4.0,   1.0,   6.0 }),
            AnyColumn(std::vector<std::string>{ "second", "fifth", "first", "forth", "third" })
        };
        Table table  = {
            AnyColumn(std::vector<int>{3, 3, 3, 1, 1, 1, 2, 2, 2, 2}),  // Repeated values for deep sharding
            AnyColumn(std::vector<double>{4.5, 4.5, 4.5, 2.2, 2.2, 2.2, 3.3, 3.3, 3.3, 3.3}),  // Second column sharding
            AnyColumn(std::vector<std::string>{"cat", "cat", "cat", "dog", "dog", "dog", "bird", "bird", "bird", "bird"}),  // More repetition
            AnyColumn(std::vector<int>{10, 20, 10, 30, 40, 30, 50, 60, 50, 50}),  // Further splits in sharding
            AnyColumn(std::vector<double>{1.01, 1.02, 1.01, 2.01, 2.02, 2.01, 3.01, 3.02, 3.01, 3.01})  // Final differentiator
        };


        // Sort the "rows" of the table. That the third column ends up in order just makes it easy to check
        //    1     4.0    "first"
        //    1     5.0    "second"
        //    1     6.0    "third"
        //    2     1.0    "forth"
        //    2     4.0    "fifth"

        table.print("before sort");

        table.sort();

        table.print("after sort");
    }

};



int main()
{
    Tester().Run();

    return 0;
}