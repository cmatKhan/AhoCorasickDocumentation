cmake_minimum_required(VERSION 3.14)
project(hw1_4 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

enable_testing()

# add_executable(
#   hello_test
#   hello_test.cc
# )

add_executable(
  aho_corasick.test 
  aho_corasick.test.cpp 
)

target_link_libraries(
#   hello_test
  aho_corasick.test
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(
#   hello_test
  aho_corasick.test  
)