cmake_minimum_required(VERSION 2.8.12)

# Project
project( "ConsoleColorExample" CXX )

add_executable(${PROJECT_NAME}
	"main.cpp")

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		CppLib::CppLib
		CppLib::CompileFlags
	)
set_target_properties(${PROJECT_NAME} PROPERTIES
		CXX_STANDARD ${LatestCXXStandard}
		CXX_STANDARD_REQUIRED ON
		FOLDER "Examples")