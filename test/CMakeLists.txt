cmake_minimum_required(VERSION 2.8.12)

project( "CppLib_test" CXX )

enable_testing()

file(GLOB_RECURSE TEST_HEADERS
	"include/*.hpp")

file(GLOB_RECURSE TEST_SOURCES
	"src/*.cpp")

add_executable(${PROJECT_NAME}
	"${TEST_HEADERS}"
	"${TEST_SOURCES}")

target_link_libraries(${PROJECT_NAME} CppLib CppLibCompileFlags)
target_include_directories(${PROJECT_NAME} PRIVATE "include")
set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD ${LatestCXXStandard}
	CXX_STANDARD_REQUIRED ON)

add_test(Unittest ${PROJECT_NAME})
