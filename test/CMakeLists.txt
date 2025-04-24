cmake_minimum_required(VERSION 3.29.5)
project (SoftwareEngineeringTest VERSION 1.1 LANGUAGES CXX)

enable_testing()

# use C++20 language standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

registerFilesToFormat(FILES projectTests.cpp)

find_package(GTest REQUIRED)

add_executable(
	projectTests
	projectTests.cpp
)

target_link_libraries(
	projectTests
	GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(projectTests)