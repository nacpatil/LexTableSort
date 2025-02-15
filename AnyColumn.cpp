#include "pch.h"
#include "AnyColumn.h"
#include <iostream>
#include <string>
#include <initializer_list>
#include <vector>
#include <list>
#include <numeric>
#include <algorithm>

  

// Only one of the fields will be non-empty.
std::vector<int> _intVector;
std::vector<double> _doubleVector;
std::vector<std::string> _stringVector;

 

// Constructor Implementations
AnyColumn::AnyColumn(const std::vector<int>& values) : _intVector(values) {}
AnyColumn::AnyColumn(const std::vector<double>& values) : _doubleVector(values) {}
AnyColumn::AnyColumn(const std::vector<std::string>& values) : _stringVector(values) {}

size_t AnyColumn::size() const
{
    if (_intVector.size() > 0) return  _intVector.size();
    if (_doubleVector.size() > 0) return  _doubleVector.size();
    if (_stringVector.size() > 0) return  _stringVector.size();
    return 0;
}

void AnyColumn::printElement(size_t index, std::ostream& stream) const
{
    if (_intVector.size() > 0) stream << _intVector[index];
    if (_doubleVector.size() > 0) stream << _doubleVector[index];
    if (_stringVector.size() > 0) stream << _stringVector[index];
}


std::vector<size_t> AnyColumn::sort(std::vector<size_t>& perm, size_t start, size_t end)
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


std::vector<std::pair<size_t, size_t>> AnyColumn::ReShard(std::vector<std::pair<size_t, size_t>>& existingShards)
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



void AnyColumn::applyPermutation(const std::vector<size_t>& perm, size_t start, size_t end)
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


 