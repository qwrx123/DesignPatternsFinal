cmake_minimum_required(VERSION 3.30.2)
project (SoftwareEngineeringTest VERSION 1.1 LANGUAGES CXX)

# use C++17 language standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(MyQtApp QTExample.cpp)

target_link_libraries(MyQtApp PRIVATE Qt6::Widgets)