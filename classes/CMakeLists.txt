add_library(WindowClass
    WindowClass.cpp
)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

registerFilesToFormat(WindowClass.cpp)

target_link_libraries(WindowClass
    ${GLEW_LIBRARIES}
    glfw
    OpenGL::GL
)

target_include_directories(WindowClass
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    
)