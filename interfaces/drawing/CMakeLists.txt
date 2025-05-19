set(FILE_LIST IDrawingTool.h 
    IDrawingEngine.h
    IStroke.h 
    ITool.h
    IStrokeManager.h
    IToolManager.h)


registerFilesToFormat(FILES ${FILE_LIST})

install(FILES ${FILE_LIST}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/daisy
)