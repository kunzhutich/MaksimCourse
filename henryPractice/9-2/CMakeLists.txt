cmake_minimum_required(VERSION 3.16)
project(fll_with_tests CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Your program (builds your original file with its own main)
add_executable(fll_program
    fll.cpp
)

# ---- Fetch Catch2 ----
include(FetchContent)
FetchContent_Declare(
  Catch2
  URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.5.4.zip
)
FetchContent_MakeAvailable(Catch2)

# Tests executable (no need for your code as a separate library; we include the .cpp)
add_executable(fll_tests
    fll_tests.cpp
)

target_link_libraries(fll_tests PRIVATE Catch2::Catch2WithMain)

# Enable `ctest`
include(CTest)
include(Catch)
catch_discover_tests(fll_tests)
