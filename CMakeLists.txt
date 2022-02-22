cmake_minimum_required(VERSION 3.9)

project(trivial VERSION 1.0.0 DESCRIPTION "contains some useful cpp codes")

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

# enable unit test
enable_testing()
set(install_gtest OFF)
set(install_gmock OFF)
add_subdirectory("third_party/googletest")
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(trivial_tests "")
target_sources(trivial_tests
  PRIVATE
  "tests/algorithm_test.cpp"
  "tests/strings_test.cpp"
  "tests/skiplist_test.cpp"
)
target_link_libraries(trivial_tests gtest gtest_main)
add_test(NAME "trivial_tests" COMMAND "trivial_tests")

# install header files
install(
  FILES 
  "include/trivial/algorithm.h" 
  "include/trivial/strings.h"
  DESTINATION 
  "/usr/local/include/trivial"
)