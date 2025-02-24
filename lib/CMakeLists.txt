# Set our minimum required cmake version.
cmake_minimum_required(VERSION 3.24)

# Basic Info
project(flexor)

# Set the C++ Standard
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED True)

# Source Files
set(SRC_FILES src/engine.cpp)
set(HEADER_FILES include/engine.h)

# Define the executable for the program
add_library(flexor ${SRC_FILES} ${HEADER_FILES})

# These are for other project that add this library via cmake.
target_include_directories(flexor SYSTEM INTERFACE include)

# This is for our own library
target_include_directories(flexor PRIVATE include)
