add_library(WindowClass
	SHARED
	WindowClass.cpp
)

add_library(ButtonClass
	SHARED
	ButtonClass.cpp
)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

registerFilesToFormat(FILES WindowClass.cpp ButtonClass.cpp)

target_link_libraries(WindowClass
	${GLEW_LIBRARIES}
	glfw
	OpenGL::GL
	ButtonClass
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

install(TARGETS WindowClass ButtonClass
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)

if (WIN32)
	install(FILES $<TARGET_RUNTIME_DLLS:WindowClass> $<TARGET_RUNTIME_DLLS:ButtonClass>
		TYPE bin
	)
endif()
