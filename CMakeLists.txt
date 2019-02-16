## Cpp Lib CMake Base
# V. 1.1.0

## GLOBAL SETTINGS
cmake_minimum_required(VERSION 3.12)

# Project
project( "CppLib" CXX )

# Options
option(CPPLIB_BUILD_TESTS "Build the unit test suite" ON)

# Use latest standard available but at least C++-14
if    (DEFINED CMAKE_CXX20_STANDARD_COMPILE_OPTION OR DEFINED CMAKE_CXX20_EXTENSION_COMPILE_OPTION)
	set(LatestCXXStandard 20)
elseif(DEFINED CMAKE_CXX17_STANDARD_COMPILE_OPTION OR DEFINED CMAKE_CXX17_EXTENSION_COMPILE_OPTION)
	set(LatestCXXStandard 17)
else()
	set(LatestCXXStandard 14)
endif()

# Header only Library
set(LIBRARY_NAME "cpplib")

file(GLOB_RECURSE LIB_HEADERS
		"include/*.hpp")

# Defined as header only library
add_library(${LIBRARY_NAME} INTERFACE)
add_library(${LIBRARY_NAME}::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})

target_include_directories(${LIBRARY_NAME} INTERFACE "include")
# Hack for IDE's like MSVC see https://stackoverflow.com/a/29214327
add_custom_target(${LIBRARY_NAME}_ide SOURCES ${LIB_HEADERS})

# NDEBUG preprocessor symbol
if (NOT CMAKE_BUILD_TYPE MATCHES Debug AND NOT MSVC)
	target_compile_definitions(${LIBRARY_NAME} INTERFACE "NDEBUG")
endif()

### TESTS
if (CPPLIB_BUILD_TESTS)
	enable_testing()

	set(UNIT_TEST_NAME "cpplib_tests")

	file(GLOB_RECURSE TEST_HEADERS
		"test/include/*.hpp")

	file(GLOB_RECURSE TEST_SOURCES
		"test/src/*.cpp")

	add_executable(${UNIT_TEST_NAME}
		"${TEST_HEADERS}"
		"${TEST_SOURCES}")

	target_link_libraries(${UNIT_TEST_NAME} ${LIBRARY_NAME})
	target_include_directories(${UNIT_TEST_NAME} PRIVATE "test/include")
	set_target_properties(${UNIT_TEST_NAME} PROPERTIES
		CXX_STANDARD ${LatestCXXStandard}
		CXX_STANDARD_REQUIRED ON)

	add_test(Unittest ${UNIT_TEST_NAME})

	# MSVC settings
	if(MSVC)
		# Warning flags
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "/Wall")

		if(MSVC_VERSION GREATER_EQUAL "1912")
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "/permissive-") # disable MSVC extensions
		endif()

		# Disable undesirable warnings
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "/wd4514") # 'x': unreferenced inline function has been removed
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "/wd4571") # SEH related
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "/wd4623") # 'x': default constructor was implicitly defined as deleted
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "/wd4625") # 'x': copy constructor was implicitly defined as deleted
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "/wd4626") # 'x': assignment operator was implicitly defined as deleted
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "/wd4643") # Forward declaring 'x' in namespace std is not permitted by the C++ Standard.
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "/wd4710") # 'x': function not inlined
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "/wd4711") # function 'x' selected for automatic inline expansion
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "/wd4774") # 'x' : format string expected in argument y is not a string literal
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "/wd4820") # 'bytes' bytes padding added after construct 'member_name' - https://msdn.microsoft.com/en-us/library/t7khkyth.aspx
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "/wd5026") # 'x': move constructor was implicitly defined as deleted
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "/wd5027") # 'x': move assignment operator was implicitly defined as deleted

		# Treat warnings as errors when using msvc.
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "/WX")

	# Clang settings
	elseif(CMAKE_CXX_COMPILER MATCHES ".*clang")
		# Warning flags
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Weverything")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Werror")

		# disable undesirable warnings
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wno-c++1z-extensions")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wno-c++98-compat")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wno-c++98-compat-pedantic")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wno-c++98-c++11-compat-pedantic")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wno-documentation-unknown-command")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wno-double-promotion")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wno-missing-prototypes")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wno-missing-variable-declarations")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wno-padded")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wno-unused-template")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wno-weak-vtables")

		# Optimization flags
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "$<$<CONFIG:DEBUG>:-O0>")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "$<$<CONFIG:RELEASE>:-O3>")

		# processor architecture
		if(ARCH STREQUAL "x86")
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-m32")
	    elseif(ARCH STREQUAL "x64")
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-m64")
	    endif()

	# GCC settings
	elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
		# Warning flags
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-pedantic")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-pedantic-errors")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wall")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wcast-align")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wcast-qual")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wconversion")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Weffc++")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Werror")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wextra")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wfloat-equal")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wformat=2")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Winline")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Winvalid-pch")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wlogical-op")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wmissing-declarations")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wmissing-field-initializers")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wmissing-include-dirs")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wmissing-noreturn")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wold-style-cast")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wpointer-arith")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wredundant-decls")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wshadow")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wstack-protector")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wstrict-aliasing=2")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wstrict-overflow=5")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wundef")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wunreachable-code")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wunused")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wunused-parameter")

		if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.6)
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wnoexcept")
		endif()

		if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 5.0)
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wdouble-promotion")
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wtrampolines")
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wuseless-cast")
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wvector-operation-performance")
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wzero-as-null-pointer-constant")
		endif()

		if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 6.0)
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wduplicated-cond")
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wnull-dereference")
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wshift-overflow=2")
		endif()

		if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 7.0)
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Walloc-zero")
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Walloca")
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wduplicated-branches")
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wrestrict")
		endif()

		# disable undesirable warnings
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wno-unused-function")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wno-missing-declarations")

		if (CMAKE_CXX_COMPILER_VERSION GREATER_EQUAL 4.5)
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-Wno-error=suggest-attribute=noreturn")
		endif()

		# Optimization flags
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "$<$<CONFIG:DEBUG>:-O0>")
		target_compile_options(${UNIT_TEST_NAME} PRIVATE "$<$<CONFIG:RELEASE>:-O3>")

		# processor architecture
		if(ARCH STREQUAL "x86")
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-m32")
		elseif(ARCH STREQUAL "x64")
			target_compile_options(${UNIT_TEST_NAME} PRIVATE "-m64")
		endif()
	endif()
endif() # CPPLIB_BUILD_TESTS
