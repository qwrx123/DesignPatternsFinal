find_package(Doxygen)
if (NOT DOXYGEN_FOUND)
	message(STATUS "Documentation generation requires Doxygen")
else()
	find_package(LATEX)
	find_package(LibXml2)
	if (LATEX_FOUND)
		set(DOXYGEN_LATEX_SUPPORT YES)
		install(DIRECTORY "${CMAKE_BINARY_DIR}/doc/latex"
				DESTINATION "${CMAKE_INSTALL_DOCDIR}")
	else()
		set(DOXYGEN_LATEX_SUPPORT NO)
	endif()

	if (LibXml2_FOUND)
		set(DOXYGEN_XML_SUPPORT YES)
		install(DIRECTORY "${CMAKE_BINARY_DIR}/doc/xml"
				DESTINATION "${CMAKE_INSTALL_DOCDIR}")
	else()
		set(DOXYGEN_XML_SUPPORT NO)
	endif()

	configure_file(Doxyfile.in Doxyfile @ONLY)

	add_custom_target( docs ALL
		COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen"
		VERBATIM )
		
	install(DIRECTORY "${CMAKE_BINARY_DIR}/doc/html"
			DESTINATION "${CMAKE_INSTALL_DOCDIR}")
	install(DIRECTORY "${CMAKE_BINARY_DIR}/doc/docbook"
			DESTINATION "${CMAKE_INSTALL_DOCDIR}")
	install(DIRECTORY "${CMAKE_BINARY_DIR}/doc/man"
			DESTINATION "${CMAKE_INSTALL_DOCDIR}")
	install(DIRECTORY "${CMAKE_BINARY_DIR}/doc/rtf"
			DESTINATION "${CMAKE_INSTALL_DOCDIR}")
endif()