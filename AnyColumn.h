#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <utility>

class AnyColumn {
private:
    std::vector<int> _intVector;
    std::vector<double> _doubleVector;
    std::vector<std::string> _stringVector;
    size_t _size;
    template <typename T> void coreSortGeneric(std::vector<T>& data, std::vector<size_t>& perm, size_t start, size_t end);
    template <typename T> std::vector<std::pair<size_t, size_t>> reShardGeneric( const std::vector<T>& data,
        std::vector<std::pair<size_t, size_t>>& existingShards);


public:
    // Constructors
     //AnyColumn(const std::vector<int>& values); 
     AnyColumn(std::vector<int>&& values);
    AnyColumn(const std::vector<double>& values);
    AnyColumn(const std::vector<std::string>& values);

    // Get the size of the column
    size_t size() const;

    // Print an element at a given index
    void printElement(size_t index, std::ostream& stream) const;

    // Sorts the column within the given range and updates the permutation vector
    void sort(std::vector<size_t>& perm, size_t start, size_t end);

    // Resharding function to split based on unique values
    std::vector<std::pair<size_t, size_t>> ReShard(std::vector<std::pair<size_t, size_t>>& existingShards);

    // Apply permutation to reorder the column
    void applyPermutation(const std::vector<size_t>& perm, size_t start, size_t end);

    bool isGreater(size_t i, size_t j);
    bool areEqual(const AnyColumn& other) const;

};
