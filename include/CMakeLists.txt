registerFilesToFormat(FILES WindowClass.h Bounds.h Color.h)

# Install public headers
install(FILES
    WindowClass.h
    Color.h
    Bounds.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/daisy
)

add_subdirectory(Tools)
add_subdirectory(Text)
add_subdirectory(Rendering)
add_subdirectory(Input)