add_library(
    Rendering
	SHARED
    CanvasRenderer.cpp
)

find_package(glfw3 REQUIRED)

target_include_directories(Rendering
	PUBLIC
    ${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/include/Rendering
	${PROJECT_SOURCE_DIR}/interfaces/Canvas
)

target_link_libraries(
    Rendering
    ${GLFW_LIBRARIES}
    glfw
)

if(WIN32)
	install(TARGETS Tools
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
else()
	install(TARGETS Tools
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
endif()