cmake_minimum_required(VERSION 3.29.5)
project (SoftwareEngineeringTest VERSION 1.1 LANGUAGES CXX)

enable_testing()

# use C++20 language standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

registerFilesToFormat(FILES projectTests.cpp)

find_package(GTest REQUIRED)

add_executable(projectTests
    ToolManagerTest.cpp
    projectTests.cpp

    ${CMAKE_SOURCE_DIR}/classes/Tools/ToolManager.cpp
    ${CMAKE_SOURCE_DIR}/classes/Tools/BrushTool.cpp
    ${CMAKE_SOURCE_DIR}/classes/Tools/Stroke.cpp
)

target_include_directories(projectTests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/Tools
    ${CMAKE_SOURCE_DIR}/interfaces
    ${CMAKE_SOURCE_DIR}/interfaces/drawing
    ${CMAKE_SOURCE_DIR}/classes
    ${CMAKE_SOURCE_DIR}/classes/Tools
)

find_package(GTest REQUIRED)

target_link_libraries(projectTests
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(projectTests)