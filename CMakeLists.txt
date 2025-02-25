# Set our minimum required cmake version.
cmake_minimum_required(VERSION 3.24)

# Set the C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Project
project(flexor-engine)

# Enable testing for the project
enable_testing()

# Include our other cmake files.
add_subdirectory(lib)
add_subdirectory(demo)
add_subdirectory(tests)
