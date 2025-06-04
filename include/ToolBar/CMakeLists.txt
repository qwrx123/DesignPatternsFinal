set(FILE_LIST
    ButtonClass.h
    MenuBar.h
    SliderButton.h
)

registerFilesToFormat(FILES ${FILE_LIST})

install(FILES ${FILE_LIST}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/daisy
)