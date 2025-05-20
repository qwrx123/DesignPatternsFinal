set(FILE_LIST 
    IHistoryStack.h
    IRenderManager.h
    ICanvasRenderer.h)

registerFilesToFormat(FILES ${FILE_LIST})

install(FILES ${FILE_LIST}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/daisy
)