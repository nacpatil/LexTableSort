#pragma once
#include "Table.h"

class PerformanceTest 
{
	public: 
		void runPerformance(std::string algoType, std::string dataType, size_t numCols = 7);
		void runPerformanceOnColumns(std::string algoType, std::string dataType, size_t numRows,  size_t numCols);
		std::vector<int> generateSequentialIntVector(size_t size, int thisNumber);
		std::vector<int> generateSortedIntVector(size_t size, int thisNumber);
		std::vector<int> generateRandomIntVectorRows(size_t size, int thisNumber );
		std::vector<int> generateRandomIntVectorCols(size_t size, int thisNumber );
};






