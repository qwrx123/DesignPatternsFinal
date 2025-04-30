#Make sure header gets formatted
registerFilesToFormat(FILES WindowClass.h ButtonClass.h)

install(FILES WindowClass.h ButtonClass.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)