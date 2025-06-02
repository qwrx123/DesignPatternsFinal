add_library(
    File
    SHARED
    Export.cpp
    FileLocation.cpp
)

registerFilesToFormat(FILES Export.cpp)

target_include_directories(File
    PUBLIC
    ${PROJECT_COMMON_INCLUDE_DIRS}
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