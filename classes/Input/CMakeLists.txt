add_library(
    Input
    SHARED
    InputManager.cpp
)

find_package(glfw3 REQUIRED)

target_include_directories(Input
    PUBLIC
    ${PROJECT_COMMON_INCLUDE_DIRS}
)

target_link_libraries(Input
    glfw
)

if(WIN32)
    install(TARGETS Input
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
else()
    install(TARGETS Input
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
endif()