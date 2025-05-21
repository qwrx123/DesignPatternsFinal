add_library(WindowClass
	WindowClass.cpp
)

add_library(ButtonClass
	ButtonClass.cpp
)

add_library(MenuBar
	MenuBar.cpp
)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

registerFilesToFormat(FILES WindowClass.cpp ButtonClass.cpp MenuBar.cpp)

target_link_libraries(WindowClass
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
	${PROJECT_SOURCE_DIR}/interfaces/ui
)

target_include_directories(MenuBar
	PUBLIC
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/interfaces/ui
)