add_library(
    Rendering
    SHARED
    CanvasRenderer.cpp
)

find_package(glfw3 3.3 REQUIRED)

target_include_directories(Rendering
    PUBLIC
    ${PROJECT_COMMON_INCLUDE_DIRS}
)

target_link_libraries(
    Rendering
    glfw
)

if(WIN32)
    install(TARGETS Rendering
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
else()
    install(TARGETS Rendering
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif()