cmake_minimum_required(VERSION 2.8.12)

project( "CppLib_test" CXX )

enable_testing()

file(GLOB TEST_HEADERS
	"include/doctest.h"
	)

file(GLOB TEST_SOURCES
	"src/AnonymousName_test.cpp"
	"src/At_test.cpp"
	"src/Console_test.cpp"
	"src/CppLib_test.cpp"
	"src/main.cpp"
	"src/NamedType_test.cpp"
	)

add_executable(${PROJECT_NAME}
	"${TEST_HEADERS}"
	"${TEST_SOURCES}")

target_link_libraries(${PROJECT_NAME} CppLib CppLibCompileFlags)
target_include_directories(${PROJECT_NAME} PRIVATE "include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "DOCTEST_CONFIG_TREAT_CHAR_STAR_AS_STRING")
set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD ${LatestCXXStandard}
	CXX_STANDARD_REQUIRED ON)

add_test(Unittest ${PROJECT_NAME})
