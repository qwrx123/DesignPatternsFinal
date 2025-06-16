set(FILE_LIST
    BrushTool.cpp
    EraserTool.cpp
    Stroke.cpp
    StrokeManager.cpp
    ToolManager.cpp
)

registerFilesToFormat(FILES ${FILE_LIST})

add_library(
    Tools
    SHARED
    Stroke.cpp
    BrushTool.cpp
    ToolManager.cpp
    EraserTool.cpp
    StrokeManager.cpp
)

find_package(glfw3 REQUIRED)

target_include_directories(Tools
    PUBLIC
    ${PROJECT_COMMON_INCLUDE_DIRS}
)

target_link_libraries(
    Tools
    Rendering
    glfw
)

if(WIN32)
    install(TARGETS Tools
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
else()
    install(TARGETS Tools
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif()