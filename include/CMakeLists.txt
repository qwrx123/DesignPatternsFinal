#Make sure header gets formatted
registerFilesToFormat(FILES WindowClass.h)

install(FILES WindowClass.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)