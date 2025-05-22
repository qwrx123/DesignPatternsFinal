registerFilesToFormat(FILES WindowClass.h Bounds.h Color.h)

# Install public headers
install(FILES
    WindowClass.h
    Color.h
    Bounds.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/daisy
)

# Make this directory visible to targets needing headers from include/
# (No targets are defined here, so nothing else is needed)