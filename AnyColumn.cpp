#include "AnyColumn.h"
#include <iostream>
#include <string>
#include <initializer_list>
#include <vector>
#include <list>
#include <numeric>
#include <algorithm>
#include <variant>
#include <execution>
#include <omp.h>
#include <cstddef>  // For ptrdiff_t

bool doneSorting = false;
// Constructor Implementations
//AnyColumn::AnyColumn(const std::vector<int>& values) : _intVector(values) { _size = values.size(); }
AnyColumn::AnyColumn(     std::vector<int>&& values) : _intVector(std::move(values)) {  _size = _intVector.size();}
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
}

void AnyColumn::printElement(size_t index, std::ostream& stream) const
{
    if (_intVector.size() > 0) stream << _intVector[index];
    if (_doubleVector.size() > 0) stream << _doubleVector[index];
    if (_stringVector.size() > 0) stream << _stringVector[index];
}

// This is a template to sort fragment of the object vector and update permutation index vector for the fragment. 
template <typename T>
void AnyColumn::coreSortGeneric(std::vector<T>& instanceVector, std::vector<size_t>& perm,
    size_t start, size_t end)
{
    if (instanceVector.empty() || start >= end) return;

    // Create an index vector for sorting
    std::vector<size_t> indices(end - start);
    std::iota(indices.begin(), indices.end(), start);  // Generate indices [start, ..., end-1]

    // Parallel sort indices based on instanceVector values
    std::stable_sort(std::execution::par, indices.begin(), indices.end(), [&](size_t i, size_t j) {
        return instanceVector[i] < instanceVector[j];
    });

    std::vector<T> tempInstance;
    tempInstance.reserve(end - start);
    tempInstance.assign(instanceVector.begin() + start, instanceVector.begin() + end);
    std::vector<size_t> tempPerm(perm.begin() + start, perm.begin() + end);

     for (ptrdiff_t i = start; i < static_cast<ptrdiff_t>(end); ++i) {
        size_t index = static_cast<size_t>(i);  // Casting to size_t for indexing
        instanceVector[index] = std::move(tempInstance[indices[index - start] - start]);
        perm[index] = tempPerm[indices[index - start] - start];
    }

}

// This is wrapper for sorting fragment of the object vector. This calls coreSortGeneric based on vector data type. 
void AnyColumn::sort(std::vector<size_t>& perm, size_t start, size_t end) {
    if (start >= end || start >= perm.size() || end > perm.size()) {
        std::cerr << "Invalid range: start=" << start << ", end=" << end << "\n";
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
}

// Templated function to compute duplicate entries making shards of full vector. This is done after vector is sorted.
template <typename T> std::vector<std::pair<size_t, size_t>> AnyColumn::reShardGeneric(  const std::vector<T>& instanceVector, std::vector<std::pair<size_t, size_t>>& existingShards)
{
    if (existingShards.empty() || existingShards.size() == _size) {
        return {};
    }

    std::vector<std::pair<size_t, size_t>> newShards;
    newShards.reserve(existingShards.size());

    for (const auto& shard : existingShards) {
        size_t start = shard.first;
        size_t end = shard.second;

        size_t currentStart = start;
        for (size_t i = start + 1; i < end; ++i) {
            if (instanceVector[i] != instanceVector[i - 1]) {
                if ((i - currentStart) > 1) {
                    newShards.emplace_back(currentStart, i);
                }
                currentStart = i;
            }
        }
        if ((end - currentStart) > 1) {
            newShards.emplace_back(currentStart, end);
        }
    }

    existingShards = std::move(newShards);
    return existingShards;
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
        //#pragma omp parallel for
        for (ptrdiff_t i = start; i < static_cast<ptrdiff_t>(end); ++i) {
            size_t index = static_cast<size_t>(i);  // Casting to size_t for indexing
            _intVector[index] = temp[perm[index]];  // Access using size_t
        }

    }
    else if (!_doubleVector.empty())
    {
        std::vector<double> temp(_doubleVector);
        #pragma omp parallel for
        for (ptrdiff_t i = start; i < static_cast<ptrdiff_t>(end); ++i) {
            size_t index = static_cast<size_t>(i);  // Casting to size_t for indexing
            _doubleVector[index] = temp[perm[index]];  // Access using size_t
        }
    }
    else if (!_stringVector.empty())
    {
        std::vector<std::string> temp(_stringVector);
        #pragma omp parallel for
        for (ptrdiff_t i = start; i < static_cast<ptrdiff_t>(end); ++i) {
            size_t index = static_cast<size_t>(i);  // Casting to size_t for indexing
            _stringVector[index] = temp[perm[index]];  // Access using size_t
        }
    }
}

 
bool AnyColumn::isGreater(size_t i, size_t j) {
    if (!_intVector.empty()) {
        if (_intVector[i] < _intVector[j]) return true;
        if (_intVector[i] > _intVector[j]) return false;
    }
    if (!_doubleVector.empty()) {
        if (_doubleVector[i] < _doubleVector[j]) return true;
        if (_doubleVector[i] > _doubleVector[j]) return false;
    }
    if (!_stringVector.empty()) {
        if (_stringVector[i] < _stringVector[j]) return true;
        if (_stringVector[i] > _stringVector[j]) return false;
    }
    return false; // They are equal in this column type.
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
