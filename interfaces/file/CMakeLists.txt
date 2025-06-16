set(FILE_LIST IExport.h IFiles.h IImport.h ILoad.h ISave.h IImage.h)

registerFilesToFormat(FILES ${FILE_LIST})

install(FILES ${FILE_LIST}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/daisy
)