function(registerFormat)
    if (CLANG_FORMAT) #Make sure h file get included into clang-format
        add_custom_target(format_window_header ALL
            COMMAND ${CLANG_FORMAT} -i -style=file ${CMAKE_CURRENT_LIST_DIR}/WindowClass.h
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )

        add_custom_target(WindowClassHeader ALL
            SOURCES WindowClass.h
        )

        add_dependencies(WindowClassHeader format_window_header)
    endif()
endfunction()