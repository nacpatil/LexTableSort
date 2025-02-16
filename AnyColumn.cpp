#include "pch.h"
#include "AnyColumn.h"
#include <iostream>
#include <string>
#include <initializer_list>
#include <vector>
#include <list>
#include <numeric>
#include <algorithm>
#include <variant>
  

// Constructor Implementations
AnyColumn::AnyColumn(const std::vector<int>& values) : _intVector(values) { _size = values.size(); }
AnyColumn::AnyColumn(const std::vector<double>& values) : _doubleVector(values) { _size = values.size(); }
AnyColumn::AnyColumn(const std::vector<std::string>& values) : _stringVector(values) { _size = values.size(); }

// Only one of the fields will be non-empty.
std::vector<int> _intVector;
std::vector<double> _doubleVector;
std::vector<std::string> _stringVector;
size_t _size;

 // Explicit coreSortGeneric template instantiations  
template void AnyColumn::coreSortGeneric<int>(std::vector<int>&, std::vector<size_t>&, size_t, size_t);
template void AnyColumn::coreSortGeneric<double>(std::vector<double>&, std::vector<size_t>&, size_t, size_t);
template void AnyColumn::coreSortGeneric<std::string>(std::vector<std::string>&, std::vector<size_t>&, size_t, size_t);

// Explicit reShardGeneric template instantiations  
template std::vector<std::pair<size_t, size_t>> AnyColumn::reShardGeneric<int>( const std::vector<int>&, std::vector<std::pair<size_t, size_t>>&);
template std::vector<std::pair<size_t, size_t>> AnyColumn::reShardGeneric<double>( const std::vector<double>&, std::vector<std::pair<size_t, size_t>>&);
template std::vector<std::pair<size_t, size_t>> AnyColumn::reShardGeneric<std::string>( const std::vector<std::string>&, std::vector<std::pair<size_t, size_t>>&);


size_t AnyColumn::size() const
{
    return _size;
    return 0;
}

void AnyColumn::printElement(size_t index, std::ostream& stream) const
{
    if (_intVector.size() > 0) stream << _intVector[index];
    if (_doubleVector.size() > 0) stream << _doubleVector[index];
    if (_stringVector.size() > 0) stream << _stringVector[index];
}

// This is a template to sort fragment of the object vector and update permutation index vector for the fragment. 
template <typename T> void AnyColumn::coreSortGeneric(std::vector<T>& instanceVector, std::vector<size_t>& perm,
    size_t start, size_t end) 
{
    if (instanceVector.empty()) return;

    // create a index vector for current fragment in sorting.
    std::vector<size_t> indices(end - start);
    std::iota(indices.begin(), indices.end(), start);  // Generate indices [start, ..., end-1]

    // Sort indices based on the corresponding data values
    std::sort(indices.begin(), indices.end(), [&](size_t i, size_t j) {
        return instanceVector[i] < instanceVector[j];
    });

    // Apply sorted order to the original vector and perm
    std::vector<T> temp(instanceVector);
    std::vector<size_t> tempPerm(perm);

    for (size_t i = start; i < end; ++i) {
        instanceVector[i] = temp[indices[i - start]];
        perm[i] = tempPerm[indices[i - start]];
    }
}

// This is wrapper for sorting fragment of the object vector. This calls coreSortGeneric based on vector data type. 
std::vector<size_t> AnyColumn::sort(std::vector<size_t>& perm, size_t start, size_t end) {
    if (start >= end || start >= perm.size() || end > perm.size()) {
        std::cerr << "Invalid range: start=" << start << ", end=" << end << "\n";
        return perm; // No sorting if the range is invalid
    }
    for (size_t i = start; i < end; ++i) {
        if (perm[i] >= perm.size()) {
            std::cerr << "ERROR: perm[" << i << "] = " << perm[i] << " is out of bounds!\n";
        }
    }

    if (!_intVector.empty()) {
        coreSortGeneric(_intVector, perm, start, end);
    }
    else if (!_doubleVector.empty()) {
        coreSortGeneric(_doubleVector, perm, start, end);
    }
    else if (!_stringVector.empty()) {
        coreSortGeneric(_stringVector, perm, start, end);
    }

    return perm;
}

// Templated function to compute duplicate entries making shards of full vector. This is done after vector is sorted.
template <typename T> std::vector<std::pair<size_t, size_t>> AnyColumn::reShardGeneric(
    const std::vector<T>& instanceVector, std::vector<std::pair<size_t, size_t>>& existingShards)
{
    std::vector<std::pair<size_t, size_t>> newShards;

    for (const auto& shard : existingShards) {
        size_t start = shard.first;
        size_t end = shard.second;

        if (start >= end || end > instanceVector.size()) {
            std::cerr << "Invalid shard: {" << start << ", " << end << "} ignored.\n";
            continue;
        }

        size_t currentStart = start;
        for (size_t i = start + 1; i < end; ++i) {
            if (instanceVector[i] != instanceVector[i - 1]) {
                newShards.emplace_back(currentStart, i);
                currentStart = i;
            }
        }
        newShards.emplace_back(currentStart, end);
    }

    existingShards = newShards;
    return newShards;
}

// this is wrapper to compute duplicate entries making shards of full vector. This is done after vector is sorted.
std::vector<std::pair<size_t, size_t>> AnyColumn::ReShard(std::vector<std::pair<size_t, size_t>>& existingShards) {
    if (!_intVector.empty()) {
        return reShardGeneric(_intVector, existingShards);
    }
    else if (!_doubleVector.empty()) {
        return reShardGeneric(_doubleVector, existingShards);
    }
    else if (!_stringVector.empty()) {
        return reShardGeneric(_stringVector, existingShards);
    }
    return {};  // Return empty if no data is available
}


// This function applys permutation or swapping vector based on how previous vectors were sorted. 
// This sort of forward propogates previous vector sorts. 
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


// This is used to compare two vectors. Useful for quick testing. 
bool AnyColumn::areEqual(const AnyColumn& other) const {
    // Ensure both AnyColumn objects contain the same type
    if (_size != other._size) {
        return false; // Different sizes, can't be equal
    }

    // Compare based on which vector is used
    if (!_intVector.empty() && !other._intVector.empty()) {
        return _intVector == other._intVector;
    }
    if (!_doubleVector.empty() && !other._doubleVector.empty()) {
        return _doubleVector == other._doubleVector;
    }
    if (!_stringVector.empty() && !other._stringVector.empty()) {
        return _stringVector == other._stringVector;
    }

    return false; // Mismatched types
}
