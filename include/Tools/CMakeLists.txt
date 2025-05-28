set(FILE_LIST
    BrushTool.h
    EraserTool.h
    Point.h
    Stroke.h
    StrokeManager.h
    ToolManager.h
)

registerFilesToFormat(FILES ${FILE_LIST})

install(FILES ${FILE_LIST}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/daisy
)