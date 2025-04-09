add_library(WindowClass
    WindowClass.cpp
)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)



target_link_libraries(WindowClass
    ${GLEW_LIBRARIES}
    glfw
    OpenGL::OpenGL
)

target_include_directories(WindowClass
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    
)