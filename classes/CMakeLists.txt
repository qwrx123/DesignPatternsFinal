add_library(WindowClass
    WindowClass.cpp
)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

if (CLANG_FORMAT) #Format file on build
    add_custom_target(
        clangformat
        COMMAND ${CLANG_FORMAT} -i -style=file ${CMAKE_CURRENT_LIST_DIR}/WindowClass.cpp
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    )

    add_dependencies(WindowClass clangformat)
endif()

target_link_libraries(WindowClass
    ${GLEW_LIBRARIES}
    glfw
    OpenGL::GL
)

target_include_directories(WindowClass
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    
)