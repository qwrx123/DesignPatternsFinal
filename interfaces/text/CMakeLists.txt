set(FILE_LIST IText.h ITextBox.h ITextManager.h)

registerFilesToFormat(FILES ${FILE_LIST})

install(FILES ${FILE_LIST}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/daisy
)