# ConsoleColor Example

set(EXAMPLE_CONSOLECOLOR_NAME "ConsoleColorExample")

add_executable(${EXAMPLE_CONSOLECOLOR_NAME}
	"ConsoleColor/main.cpp")

target_link_libraries(${EXAMPLE_CONSOLECOLOR_NAME} ${LIBRARY_NAME})
set_target_properties(${EXAMPLE_CONSOLECOLOR_NAME} PROPERTIES
		CXX_STANDARD ${LatestCXXStandard}
		CXX_STANDARD_REQUIRED ON)

# ConsoleCursor
set(EXAMPLE_CONSOLECURSOR_NAME "ConsoleCursorExample")

add_executable(${EXAMPLE_CONSOLECURSOR_NAME}
	"ConsoleCursor/main.cpp")

target_link_libraries(${EXAMPLE_CONSOLECURSOR_NAME} ${LIBRARY_NAME})
set_target_properties(${EXAMPLE_CONSOLECURSOR_NAME} PROPERTIES
		CXX_STANDARD ${LatestCXXStandard}
		CXX_STANDARD_REQUIRED ON)
