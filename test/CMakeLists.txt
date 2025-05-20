cmake_minimum_required(VERSION 3.29.5)
project (SoftwareEngineeringTest VERSION 1.1 LANGUAGES CXX)

enable_testing()

# use C++20 language standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

registerFilesToFormat(FILES projectTests.cpp)

find_package(GTest REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glad CONFIG REQUIRED)


add_executable(projectTests
    # add test files here
    ToolManagerTests.cpp
    projectTests.cpp
    CanvasRendererTest.cpp
    StrokeManagerTest.cpp

    # add source files here
    ${CMAKE_SOURCE_DIR}/classes/Tools/ToolManager.cpp
    ${CMAKE_SOURCE_DIR}/classes/Tools/BrushTool.cpp
    ${CMAKE_SOURCE_DIR}/classes/Tools/Stroke.cpp
    ${CMAKE_SOURCE_DIR}/classes/Tools/StrokeManager.cpp
    ${CMAKE_SOURCE_DIR}/classes/Tools/EraserTool.cpp

    ${CMAKE_SOURCE_DIR}/classes/Rendering/CanvasRenderer.cpp
)

target_include_directories(projectTests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/Tools
    ${CMAKE_SOURCE_DIR}/include/Rendering
    ${CMAKE_SOURCE_DIR}/interfaces
    ${CMAKE_SOURCE_DIR}/interfaces/drawing
    ${CMAKE_SOURCE_DIR}/interfaces/canvas
)

target_link_libraries(projectTests
	PRIVATE
	${GLEW_LIBRARIES}
	glfw
    glad::glad
	OpenGL::GL
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(projectTests)