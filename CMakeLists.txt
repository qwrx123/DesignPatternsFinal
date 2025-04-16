cmake_minimum_required(VERSION 3.29.5)
project (SoftwareEngineeringTest VERSION 1.1 LANGUAGES CXX)

# use C++20 language standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

#include helpful modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(helpfulFunctions)

# Enable clang-tidy
find_program(CLANG_TIDY_EXE NAMES clang-tidy)
message(STATUS "clang-tidy: ${CLANG_TIDY_EXE}")
if(CLANG_TIDY_EXE)
    if (WIN32)
        set(CMAKE_CXX_CLANG_TIDY "${PROJECT_SOURCE_DIR}/clang-tidy-wrapper.ps1")
    else()
        set(CMAKE_CXX_CLANG_TIDY "${PROJECT_SOURCE_DIR}/clang-tidy-wrapper.sh")
    endif()
endif()
message(STATUS "clang-tidy: ${CMAKE_CXX_CLANG_TIDY}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#Add clang-format support
find_program(CLANG_FORMAT clang-format)

# Second test dependencies
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(GlfwTestApp GLFWExample.cpp)

target_link_libraries(GlfwTestApp WindowClass glfw)

target_include_directories(GlfwTestApp
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

registerFilesToFormat(GLFWExample.cpp)

add_subdirectory(include)
add_subdirectory(classes)
