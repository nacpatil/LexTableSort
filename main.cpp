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
        //std::cout << "Sorting called with start=" << start << ", end=" << end << "\n";
        //std::cout << "perm size: " << perm.size() << ", Vector size: " << size() << "\n";

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
            //std::cout << "Sorting integer vector...\n";
            //std::cout << "Before sorting: ";
            for (size_t i = start; i < end; ++i) std::cout << _intVector[perm[i]] << " ";
            //std::cout << "\n";

            std::sort(perm.begin() + start, perm.begin() + end, [&](size_t i, size_t j) {
                //std::cout << "Comparing _intVector[" << i << "] = " << _intVector[i]
                 //   << " with _intVector[" << j << "] = " << _intVector[j] << "\n";
                return _intVector[i] < _intVector[j];
            });

            std::vector<int> temp(_intVector);
            for (size_t i = start; i < end; ++i) {
               // std::cout << "Setting _intVector[" << i << "] = temp[" << perm[i] << "] ("
                 //   << temp[perm[i]] << ")\n";
                _intVector[i] = temp[perm[i]];
            }

           // std::cout << "After sorting: ";
            for (size_t val : _intVector) std::cout << val << " ";
            //std::cout << "\n";
        }
        else if (!_doubleVector.empty())
        {
           // std::cout << "Sorting double vector...\n";
            std::vector<double> temp(_doubleVector);
            for (size_t i = start; i < end; ++i)
                _doubleVector[i] = temp[perm[i]];
        }
        else if (!_stringVector.empty())
        {
          //  std::cout << "Sorting string vector...\n";
            std::vector<std::string> temp(_stringVector);
            for (size_t i = start; i < end; ++i)
                _stringVector[i] = temp[perm[i]];
        }

       // std::cout << "Final permutation: ";
        for (size_t p : perm) std::cout << p << " ";
        //std::cout << "\n";

        return perm;
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
                for (size_t j = 0; j < shardsVect.size(); j++) {  

                }
            }
            else {

                if (i == 0) {
                    it->applyPermutation(perm, 0, _rows);

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
        Table table = {
            AnyColumn(std::vector<int>{ 1,     2,     1,     2,     1 }),
            AnyColumn(std::vector<double>{ 5.0,   4.0,   4.0,   1.0,   6.0 }),
            AnyColumn(std::vector<std::string>{ "second", "fifth", "first", "forth", "third" })
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