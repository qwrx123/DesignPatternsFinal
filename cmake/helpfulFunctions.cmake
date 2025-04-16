function(registerFilesToFormat)
	if (NOT CLANG_FORMAT) #Make sure h file get included into clang-format
		return()
	endif()

	set(Code "Format")
	set(Target "Target")

	string(APPEND Code ${ARGV0})
	string(APPEND Target ${ARGV0})

	set(fullTargetPath ${CMAKE_CURRENT_LIST_DIR}/${ARGV0})
	file(RELATIVE_PATH filePath ${CMAKE_SOURCE_DIR} ${fullTargetPath})
	message(STATUS "Targeting ${filePath} for formatting")
	
	
	add_custom_target(${Code} ALL
		COMMAND ${CLANG_FORMAT} -i -style=file ${fullTargetPath}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)

	add_custom_target(${Target} ALL
		SOURCES ${ARGV0}
	)

	add_dependencies(${Target} ${Code})
endfunction()