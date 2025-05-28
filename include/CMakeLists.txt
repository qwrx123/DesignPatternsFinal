registerFilesToFormat(FILES WindowClass.h ButtonClass.h Bounds.h Color.h MenuBar.h)

# Install public headers
install(FILES
    WindowClass.h
    ButtonClass.h
    Bounds.h
    Color.h
    MenuBar.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/daisy
)

add_subdirectory(Tools)
add_subdirectory(Text)
add_subdirectory(Rendering)
add_subdirectory(Input)