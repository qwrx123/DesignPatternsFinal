add_library(TextClass
	SHARED
	Text.cpp
	Font.cpp
	TextBox.cpp
	TextManager.cpp
)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(Freetype REQUIRED)

registerFilesToFormat(FILES Text.cpp Font.cpp TextBox.cpp TextManager.cpp)

include_directories(${FREETYPE_INCLUDE_DIRS})

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