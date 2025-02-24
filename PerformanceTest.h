#pragma once
#include "Table.h"

class PerformanceTest 
{
	public: 
		void runPerformance(std::string algoType, std::string dataType);
		std::vector<int> generateSequentialIntVector(size_t size, int thisNumber);
		std::vector<int> generateSortedIntVector(size_t size, int thisNumber);
		std::vector<int> generateRandomIntVector(size_t size, int thisNumber);
};






