add_library(
    Input
	SHARED
    InputManager.cpp
)

find_package(glfw3 REQUIRED)

target_include_directories(Input
	PUBLIC
    ${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/include/Input
	${PROJECT_SOURCE_DIR}/interfaces/ui
)

target_link_libraries(
    Input
    ${GLFW_LIBRARIES}
    glfw
)

if(WIN32)
	install(TARGETS Input
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
else()
	install(TARGETS Input
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	)
endif()