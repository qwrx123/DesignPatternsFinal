cmake_minimum_required(VERSION 3.29.5)
project (SoftwareEngineeringTest VERSION 1.1 LANGUAGES CXX)

# use C++20 language standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# First test dependency
#find_package(Qt6 REQUIRED COMPONENTS Widgets)


# Second test dependencies
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

#add_executable(QtTestApp QTExample.cpp)

add_executable(GlfwTestApp GLFWExample.cpp)

#target_link_libraries(QtTestApp Qt6::Widgets)
target_link_libraries(GlfwTestApp WindowClass glfw)

target_include_directories(GlfwTestApp
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

add_subdirectory(classes)