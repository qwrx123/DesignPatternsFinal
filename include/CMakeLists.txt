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

# Make this directory visible to targets needing headers from include/
# (No targets are defined here, so nothing else is needed)