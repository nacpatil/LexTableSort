# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(LexSortingProject VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for header files
include_directories(${PROJECT_SOURCE_DIR})

# Source files for the executable
set(SOURCES
    AnyColumn.cpp
    main.cpp
    PerformanceTest.cpp
    Table.cpp
    Tests.cpp
)

# Add executable target
add_executable(LexSortingApp ${SOURCES})

# Link libraries if needed (e.g., for testing frameworks)
# target_link_libraries(LexSortingApp PRIVATE some_library)

# Enable testing if doctest.h is used
enable_testing()

#add_subdirectory("lexSortingBuild")
