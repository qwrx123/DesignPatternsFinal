add_library(WindowClass
	SHARED
	WindowClass.cpp
)

add_library(ButtonClass
	SHARED
	ButtonClass.cpp
)

add_library(TextClass
	TextClass.cpp
)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(Freetype REQUIRED)

registerFilesToFormat(FILES WindowClass.cpp ButtonClass.cpp TextClass.cpp)

include_directories(${FREETYPE_INCLUDE_DIRS})

target_link_libraries(WindowClass
	PRIVATE 
	${FREETYPE_LIBRARIES}
	Freetype::Freetype
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

target_link_libraries(TextClass
	PRIVATE
	${FREETYPE_LIBRARIES}
	Freetype::Freetype
	${GLEW_LIBRARIES}
	glfw
	OpenGL::GL
)

target_include_directories(TextClass
	PRIVATE
	${FREETYPE_INCLUDE_DIRS}
	PUBLIC
	${PROJECT_SOURCE_DIR}/include
)