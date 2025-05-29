add_library(WindowClass
	SHARED
	WindowClass.cpp
)

add_subdirectory(TextClass)
add_subdirectory(Tools)
add_subdirectory(Rendering)
add_subdirectory(Input)
add_subdirectory(ToolBar)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

registerFilesToFormat(FILES WindowClass.cpp)

target_link_libraries(WindowClass
	PRIVATE
	${GLEW_LIBRARIES}
	glfw
	OpenGL::GL
	ToolBar
)

target_include_directories(WindowClass
	PUBLIC
	${PROJECT_COMMON_INCLUDE_DIRS}
)

if(WIN32)
	install(TARGETS WindowClass
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
else()
	install(TARGETS WindowClass
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
endif()