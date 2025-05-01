add_library(WindowClass
	WindowClass.cpp
)

add_library(ButtonClass
	ButtonClass.cpp
)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(Freetype REQUIRED)

registerFilesToFormat(FILES WindowClass.cpp ButtonClass.cpp)

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