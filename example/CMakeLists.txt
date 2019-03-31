# Console Example

set(EXAMPLE_CONSOLE_NAME "ConsoleExample")

add_executable(${EXAMPLE_CONSOLE_NAME}
	"Console/main.cpp")

target_link_libraries(${EXAMPLE_CONSOLE_NAME} ${LIBRARY_NAME})
set_target_properties(${EXAMPLE_CONSOLE_NAME} PROPERTIES
		CXX_STANDARD ${LatestCXXStandard}
		CXX_STANDARD_REQUIRED ON)
