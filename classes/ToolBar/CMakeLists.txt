add_library(
    ToolBar
    SHARED
    MenuBar.cpp
    ButtonClass.cpp
    SubMenu.cpp
)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

target_include_directories(ToolBar
    PUBLIC
    ${PROJECT_COMMON_INCLUDE_DIRS}
)

target_link_libraries(
    ToolBar
    glfw
    OpenGL::GL
)

if(WIN32)
    install(TARGETS ToolBar
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
else()
    install(TARGETS ToolBar
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif()