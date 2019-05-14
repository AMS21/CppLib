cmake_minimum_required(VERSION 2.8.12)

project( "CppLib_test" CXX )

enable_testing()

file(GLOB TEST_HEADERS
	"include/doctest.h"
	)

file(GLOB TEST_SOURCES
	"src/AnonymousName.test.cpp"
	"src/At.test.cpp"
	"src/Console.test.cpp"
	"src/CppLib.test.cpp"
	"src/main.cpp"
	"src/NamedType.test.cpp"
	)

add_executable(${PROJECT_NAME}
	"${TEST_HEADERS}"
	"${TEST_SOURCES}")

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		CppLib::CppLib
		CppLib::CompileFlags)
target_include_directories(${PROJECT_NAME} PRIVATE "include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING")
set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD ${LatestCXXStandard}
	CXX_STANDARD_REQUIRED ON)

add_test(Unittest ${PROJECT_NAME})
