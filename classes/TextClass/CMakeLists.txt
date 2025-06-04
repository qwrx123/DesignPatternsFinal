add_library(TextClass
    SHARED
    Text.cpp
    Font.cpp
    TextBox.cpp
    TextManager.cpp
)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(Freetype REQUIRED)

registerFilesToFormat(FILES Text.cpp Font.cpp TextBox.cpp TextManager.cpp)

target_include_directories(TextClass
    PUBLIC
    ${PROJECT_COMMON_INCLUDE_DIRS}
)

target_include_directories(TextClass
    SYSTEM PUBLIC
    ${FREETYPE_INCLUDE_DIRS}
)

target_link_libraries(TextClass
    PRIVATE
    Canvas
    Freetype::Freetype
    glfw
    OpenGL::GL
)

if(WIN32)
    install(TARGETS TextClass
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
else()
    install(TARGETS TextClass
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif()