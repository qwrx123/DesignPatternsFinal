cmake_minimum_required(VERSION 3.29.5)

if (DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
	message(STATUS "VCPKG_ROOT: $ENV{VCPKG_ROOT}")
	string(REPLACE "\\" "/" VCPKG_ROOT $ENV{VCPKG_ROOT})
	set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "VCPKG toolchain file")
	message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
endif()

project (SoftwareEngineeringTest VERSION 1.1 LANGUAGES CXX)

# use C++20 language standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

#include helpful modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(helpfulFunctions)

set(option BUILD_TESTING "Build testing" ON)
include(CTest)

#Set up installing
include(GNUInstallDirs)
set(CMAKE_INSTALL_DOCDIR ${CMAKE_INSTALL_DATAROOTDIR}/doc/${PROJECT_NAME})

file(RELATIVE_PATH relDir
	${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}
	${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
)

if(APPLE)
	set(base @loader_path)
else()
	set(base $ORIGIN)
endif()

set(CMAKE_INSTALL_RPATH ${base} ${base}/${relDir})


# Make sure debug is set as default option on non multi-config build systems
get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(NOT isMultiConfig)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type")
endif()

# Only modify config details if the top level project
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
	if(NOT isMultiConfig)
		set_property(CACHE CMAKE_BUILD_TYPE PROPERTY
			STRINGS Debug Release Profile
		)
	elseif(NOT "Profile" IN_LIST CMAKE_CONFIGURATION_TYPES)
		list(APPEND CMAKE_CONFIGURATION_TYPES Profile)
	endif()
	
endif()

# Enable clang-tidy
find_program(CLANG_TIDY_EXE NAMES clang-tidy)
message(STATUS "clang-tidy: ${CLANG_TIDY_EXE}")
if(CLANG_TIDY_EXE)
	if (WIN32)
		set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
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

registerFilesToFormat(FILES GLFWExample.cpp)

install(TARGETS GlfwTestApp
DESTINATION ${CMAKE_INSTALL_BINDIR}
)


add_subdirectory(include)
add_subdirectory(classes)
if (BUILD_TESTING)
	add_subdirectory(test)
endif()