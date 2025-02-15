﻿#include "pch.h"
#include <iostream>
#include "../AnyColumn.h"
#include "../Table.h"
#include "../Tests.h"

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

int main() {
    Tests().Run();  // Run all test cases
    std::cout << "Main application logic here." << std::endl;
    return 0;
}
