add_library(
    Canvas
    SHARED
    TextHistory.cpp
    ToolHistory.cpp
)

find_package(glfw3 3.3 REQUIRED)

registerFilesToFormat(FILES TextHistory.cpp ToolHistory.cpp)

target_include_directories(Canvas
    SYSTEM PUBLIC
    ${PROJECT_COMMON_INCLUDE_DIRS}
)

target_link_libraries(
    Canvas
    ${GLEW_LIBRARIES}
	glfw
	OpenGL::GL
)

if(WIN32)
    install(TARGETS Canvas
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
else()
    install(TARGETS Canvas
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif()