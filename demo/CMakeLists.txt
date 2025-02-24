# Set our minimum required cmake version.
cmake_minimum_required(VERSION 3.24)

# Basic Info
project(flexor-demo)

# Set the C++ Standard
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED True)

# Source Files
set(SRC_FILES src/demo.cpp 
              src/main.cpp)
set(HEADER_FILES src/demo.h)

# Define the executable for the program
add_executable(flexor-demo ${SRC_FILES} ${HEADER_FILES})

# Add vision as a subdirectory
add_subdirectory(vendor/vision)

# Add our library dependencies
target_link_libraries(flexor-demo PUBLIC flexor
                                         Vision)

# Add vision include directory
target_include_directories(flexor-demo SYSTEM PRIVATE vendor)
