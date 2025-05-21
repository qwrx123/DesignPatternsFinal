add_library(WindowClass
	SHARED
	WindowClass.cpp
)

add_library(ButtonClass
	SHARED
	ButtonClass.cpp
)

add_subdirectory(TextClass)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

registerFilesToFormat(FILES WindowClass.cpp ButtonClass.cpp MenuBar.cpp)

target_link_libraries(WindowClass
	PRIVATE
	${GLEW_LIBRARIES}
	glfw
	OpenGL::GL
	ButtonClass
	MenuBar
)

target_include_directories(WindowClass
	PUBLIC
	${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(ButtonClass
	${GLEW_LIBRARIES}
	glfw
	OpenGL::GL
)

target_include_directories(ButtonClass
	PUBLIC
	${PROJECT_SOURCE_DIR}/include
)
if(WIN32)
	install(TARGETS WindowClass ButtonClass
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
else()
	install(TARGETS WindowClass ButtonClass
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
endif()

