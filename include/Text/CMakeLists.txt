set(FILE_LIST
    Font.h
    Text.h
    TextBox.h
    TextManager.h
)

registerFilesToFormat(FILES ${FILE_LIST})

install(FILES ${FILE_LIST}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/daisy
)