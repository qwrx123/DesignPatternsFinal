function(registerFilesToFormat)
	if (NOT CLANG_FORMAT) #Make sure h file get included into clang-format
		return()
	endif()

	add_custom_target(${ARGV0} ALL
		COMMAND ${CLANG_FORMAT} -i -style=file ${CMAKE_CURRENT_LIST_DIR}/${ARGV0}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)

	add_custom_target(${ARGV0}File ALL
		SOURCES ${ARGV0}
	)

	add_dependencies(${ARGV0}File ${ARGV0})
endfunction()