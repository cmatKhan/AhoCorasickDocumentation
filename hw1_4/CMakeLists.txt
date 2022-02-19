cmake_minimum_required(VERSION 3.14)
project(hw1_4 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

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