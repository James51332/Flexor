# Set our minimum required cmake version.
cmake_minimum_required(VERSION 3.24)

# CTest requires us to enable testing for no reason.
enable_testing()

# Include CTest for testing
include(CTest)

# Set the project
project(flexor-tests)

# Generate a driver for our test file.
set(FlexorTests
  math/vector.cpp
  math/matrix.cpp
  math/solver.cpp
  math/quaternion.cpp
)
create_test_sourcelist(Tests flexor_tests.cpp ${FlexorTests})

# Add the executable
add_executable(flexor-tests ${Tests})
target_link_libraries(flexor-tests PRIVATE flexor)

# # Add all the ADD_TEST for each test
foreach(test ${FlexorTests})

  # Remove the file extension 
  cmake_path(REMOVE_EXTENSION test)

  # Add our test to our config
  add_test(NAME ${test} COMMAND flexor-tests ${test})
  
endforeach()