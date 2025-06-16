cmake_minimum_required(VERSION 3.28.3)

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

# Include helpful modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(helpfulFunctions)

option(BUILD_TESTING "Build testing" ON)
include(CTest)

option(BUILD_DOCS "Build documentation" ON)

# Define common include directories
set(PROJECT_COMMON_INCLUDE_DIRS
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/include/Input
	${CMAKE_SOURCE_DIR}/include/Rendering
	${CMAKE_SOURCE_DIR}/include/Text
	${CMAKE_SOURCE_DIR}/include/Tools
	${CMAKE_SOURCE_DIR}/include/ToolBar
	${CMAKE_SOURCE_DIR}/include/File
	${CMAKE_SOURCE_DIR}/include/Canvas

	${CMAKE_SOURCE_DIR}/interfaces
	${CMAKE_SOURCE_DIR}/interfaces/canvas
	${CMAKE_SOURCE_DIR}/interfaces/drawing
	${CMAKE_SOURCE_DIR}/interfaces/file
	${CMAKE_SOURCE_DIR}/interfaces/text
	${CMAKE_SOURCE_DIR}/interfaces/ui
	
	${CMAKE_SOURCE_DIR}/classes
	${CMAKE_SOURCE_DIR}/classes/Input
	${CMAKE_SOURCE_DIR}/classes/Rendering
	${CMAKE_SOURCE_DIR}/classes/TextClass
	${CMAKE_SOURCE_DIR}/classes/Tools
	${CMAKE_SOURCE_DIR}/classes/ToolBar
)

# Set up installing
include(GNUInstallDirs)
set(CMAKE_INSTALL_DOCDIR ${CMAKE_INSTALL_DATAROOTDIR}/doc/${PROJECT_NAME})

file(RELATIVE_PATH relDir
	${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}
	${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
)

if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
elseif(APPLE)
	set(CMAKE_MACOSX_RPATH TRUE)
	set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
	set(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
	set(CMAKE_INSTALL_RPATH @loader_path @loader_path/${relDir})
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux|FreeBSD|OpenBSD")
	option(ENABLE_RELOCATABLE FALSE)
	if (ENABLE_RELOCATABLE)
		message(STATUS "Enabled Relocatable Package")
		set(CMAKE_INSTALL_RPATH $ORIGIN $ORIGIN/${relDir})
	endif()
endif()

SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

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

option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

# Enable clang-tidy
find_program(CLANG_TIDY_EXE NAMES clang-tidy)
message(STATUS "clang-tidy: ${CLANG_TIDY_EXE}")
if(CLANG_TIDY_EXE)
	if (WIN32)
		set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
	else()
		set(CMAKE_CXX_CLANG_TIDY "${PROJECT_SOURCE_DIR}/clang-tidy-wrapper.sh")
	endif()
	if (WARNINGS_AS_ERRORS)
		list(APPEND CMAKE_CXX_CLANG_TIDY "--warnings-as-errors=*")
	endif()
endif()
message(STATUS "clang-tidy: ${CMAKE_CXX_CLANG_TIDY}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add clang-format support
find_program(CLANG_FORMAT clang-format)

# Required packages
find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)

add_executable(GlfwTestApp Main.cpp)

target_link_libraries(GlfwTestApp
    WindowClass
    glfw
	GLEW::GLEW
    OpenGL::GL
    Freetype::Freetype
    ${FREETYPE_LIBRARIES}
    TextClass
	Rendering
	Tools
	Input
	ToolBar
	File
)

target_include_directories(GlfwTestApp
	PRIVATE
		${PROJECT_COMMON_INCLUDE_DIRS}
)

target_include_directories(GlfwTestApp
	PRIVATE SYSTEM 
		${FREETYPE_INCLUDE_DIRS}
)

registerFilesToFormat(FILES Main.cpp)

install(TARGETS GlfwTestApp
	DESTINATION ${CMAKE_INSTALL_BINDIR}
)

add_subdirectory(include)
add_subdirectory(classes)
add_subdirectory(interfaces)
if (BUILD_TESTING)
	add_subdirectory(test)
endif()
if (BUILD_DOCS)
	add_subdirectory(doc)
endif()