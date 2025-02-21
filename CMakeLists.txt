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

# Add executable target FIRST
add_executable(LexSortingApp ${SOURCES})

# Detect if MSVC (Visual Studio) is being used
if(MSVC)
    # Maximum optimization for Visual Studio
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /GL /arch:AVX2 /fp:fast /Ot /Ob2 /Oi /GT /LTCG")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /O2 /GL /arch:AVX2 /fp:fast /Ot /Ob2 /Oi /GT /LTCG")

    # Disable debug info for release build
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /DEBUG:NONE")

    # Enable Link-Time Code Generation (LTCG) AFTER defining the target
    set_target_properties(LexSortingApp PROPERTIES LINK_FLAGS "/LTCG")
else()
    # Maximum optimization for GCC/Clang (Linux, macOS)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -flto")
    set(CMAKE_C_FLAGS_RELEASE "-O3 -march=native -flto")
endif()

# Enable Link Time Optimization globally
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

# Enable OpenMP for parallel processing
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(LexSortingApp OpenMP::OpenMP_CXX)
endif()

# Enable testing if doctest.h is used
enable_testing()
