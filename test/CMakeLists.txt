cmake_minimum_required(VERSION 3.28.3)
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
find_package(GLEW REQUIRED)

add_executable(projectTests
    ToolManagerTests.cpp
    projectTests.cpp
    CanvasRendererTest.cpp
    StrokeManagerTest.cpp
    TextManagerTest.cpp
    TextTest.cpp

    ${CMAKE_SOURCE_DIR}/classes/Tools/ToolManager.cpp
    ${CMAKE_SOURCE_DIR}/classes/Tools/BrushTool.cpp
    ${CMAKE_SOURCE_DIR}/classes/Tools/Stroke.cpp
    ${CMAKE_SOURCE_DIR}/classes/Tools/StrokeManager.cpp
    ${CMAKE_SOURCE_DIR}/classes/Tools/EraserTool.cpp

    ${CMAKE_SOURCE_DIR}/classes/Rendering/CanvasRenderer.cpp

    ${CMAKE_SOURCE_DIR}/classes/TextClass/Text.cpp
    ${CMAKE_SOURCE_DIR}/classes/TextClass/TextManager.cpp
    ${CMAKE_SOURCE_DIR}/classes/TextClass/TextBox.cpp
)

target_include_directories(projectTests PRIVATE ${PROJECT_COMMON_INCLUDE_DIRS})

target_link_libraries(projectTests
    PRIVATE
    ${GLEW_LIBRARIES}
    TextClass
    glfw
    GLEW::GLEW
    OpenGL::GL
    GTest::gtest_main
)

# skip linting for test files
set_target_properties(
    projectTests
    PROPERTIES
        CXX_CLANG_TIDY ""
)

include(GoogleTest)
gtest_discover_tests(projectTests)