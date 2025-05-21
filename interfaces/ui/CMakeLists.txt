set(FILE_LIST IButton.h IMenu.h IInputReceiver.h IInputManager.h)

registerFilesToFormat(FILES ${FILE_LIST})

install(FILES ${FILE_LIST}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/daisy
)