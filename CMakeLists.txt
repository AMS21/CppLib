## CppLib top level cmake file
cmake_minimum_required(VERSION 2.8.12)

# Project
project( "CppLib" CXX )

# Check if CppLib is being used directly or via add_subdirectory, but allow overriding
if (NOT DEFINED CPPLIB_MASTER_PROJECT)
    if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(CPPLIB_MASTER_PROJECT ON)
    else()
        set(CPPLIB_MASTER_PROJECT OFF)
    endif()
endif()

# Options
option(CPPLIB_BUILD_TESTS    "Build the unit test suite"       ${CPPLIB_MASTER_PROJECT})
option(CPPLIB_BUILD_DOCS     "Build the doxygen documentation" ${CPPLIB_MASTER_PROJECT})
option(CPPLIB_BUILD_EXAMPLES "Build the example applications"  ${CPPLIB_MASTER_PROJECT})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Read version from file
file(STRINGS "include/cpp/CppLib.hpp"
    CPPLIB_VERSION_MAJOR_READ
    REGEX "^[ \t\r\n]*#define[ \t\r\n]+CPP_VERSION_MAJOR+[ \t\r\n]+[0-9]+.*$")
file(STRINGS "include/cpp/CppLib.hpp"
    CPPLIB_VERSION_MINOR_READ
    REGEX "^[ \t\r\n]*#define[ \t\r\n]+CPP_VERSION_MINOR+[ \t\r\n]+[0-9]+.*$")
file(STRINGS "include/cpp/CppLib.hpp"
    CPPLIB_VERSION_PATCH_READ
    REGEX "^[ \t\r\n]*#define[ \t\r\n]+CPP_VERSION_PATCH+[ \t\r\n]+[0-9]+.*$")

string(REGEX REPLACE "[ \t\r\n]*#define[ \t\r\n]+CPP_VERSION_MAJOR+[ \t\r\n]+([0-9])+.*" "\\1" CPPLIB_VERSION_MAJOR ${CPPLIB_VERSION_MAJOR_READ})
string(REGEX REPLACE "[ \t\r\n]*#define[ \t\r\n]+CPP_VERSION_MINOR+[ \t\r\n]+([0-9])+.*" "\\1" CPPLIB_VERSION_MINOR ${CPPLIB_VERSION_MINOR_READ})
string(REGEX REPLACE "[ \t\r\n]*#define[ \t\r\n]+CPP_VERSION_PATCH+[ \t\r\n]+([0-9])+.*" "\\1" CPPLIB_VERSION_PATCH ${CPPLIB_VERSION_PATCH_READ})

set("CPPLIB_VERSION_MAJOR" ${CPPLIB_VERSION_MAJOR} CACHE STRING "Major version number for the CppLib")
set("CPPLIB_VERSION_MINOR" ${CPPLIB_VERSION_MINOR} CACHE STRING "Minor version number for the CppLib")
set("CPPLIB_VERSION_PATCH" ${CPPLIB_VERSION_PATCH} CACHE STRING "Patch version number for the CppLib")

include("CppLibCompileFlags")

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find all header files
file(GLOB LIB_HEADERS
    "include/cpp/AnonymousName.hpp"
    "include/cpp/Assume.hpp"
    "include/cpp/At.hpp"
    "include/cpp/BeginEndMacro.hpp"
	"include/cpp/Bit.hpp"
    "include/cpp/BreakIntoDebugger.hpp"
    "include/cpp/Compiler.hpp"
    "include/cpp/Console.hpp"
    "include/cpp/CppLib.hpp"
    "include/cpp/CurrentFunction.hpp"
    "include/cpp/Debug.hpp"
    "include/cpp/Glue.hpp"
    "include/cpp/Inline.hpp"
    "include/cpp/Likely.hpp"
    "include/cpp/NamedType.hpp"
    "include/cpp/NonCopyable.hpp"
    "include/cpp/OS.hpp"
    "include/cpp/SourceLine.hpp"
    "include/cpp/StreamScopeGuard.hpp"
    "include/cpp/Stringify.hpp"
    "include/cpp/Versioning.hpp"
    "include/cpp/Warning.hpp"
    )

# Defined as header only library
add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Link public flags
target_link_libraries(${PROJECT_NAME}
    INTERFACE
        CppLib::PublicFlags)

target_include_directories(${PROJECT_NAME} INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>" # <prefix>/include
    )

if (CPPLIB_MASTER_PROJECT)
    # Hack for IDE's like MSVC see https://stackoverflow.com/a/29214327
    add_custom_target(${PROJECT_NAME}_ide SOURCES ${LIB_HEADERS})
endif()

### TESTS
if (CPPLIB_BUILD_TESTS)
    enable_testing()

    add_subdirectory("test")
endif(CPPLIB_BUILD_TESTS)

### Examples
if (CPPLIB_BUILD_EXAMPLES)
    add_subdirectory("example")
endif(CPPLIB_BUILD_EXAMPLES)

### Documentation
if (CPPLIB_BUILD_DOCS)
    add_subdirectory("docs")
endif(CPPLIB_BUILD_DOCS)

### Installation
install(
    FILES       ${LIB_HEADERS}
    DESTINATION "include"
)

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}PublicFlags EXPORT ${PROJECT_NAME}Targets)

include(CMakePackageConfigHelpers)
set(CONFIG_PACKAGE_BUILD_LOCATION   "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")
set(CONFIG_PACKAGE_INSTALL_LOCATION "lib/cmake/${PROJECT_NAME}")
write_basic_package_version_file (
    "${CONFIG_PACKAGE_BUILD_LOCATION}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${CPPLIB_VERSION_MAJOR}.${CPPLIB_VERSION_MINOR}.${CPPLIB_VERSION_PATCH}
    COMPATIBILITY AnyNewerVersion
)

export(
    EXPORT ${PROJECT_NAME}Targets
    FILE "${CONFIG_PACKAGE_BUILD_LOCATION}/${PROJECT_NAME}Targets.cmake"
    #NAMESPACE ${PROJECT_NAME}::
)

configure_file(
    "cmake/Config.cmake.in"
    "${CONFIG_PACKAGE_BUILD_LOCATION}/${PROJECT_NAME}Config.cmake"
    @ONLY
)

install(
    EXPORT      "${PROJECT_NAME}Targets"
    FILE        "${PROJECT_NAME}Targets.cmake"
    #NAMESPACE   ${PROJECT_NAME}::
    DESTINATION "${CONFIG_PACKAGE_INSTALL_LOCATION}"
)

install(
    FILES
    "${CONFIG_PACKAGE_BUILD_LOCATION}/${PROJECT_NAME}Config.cmake"
    "${CONFIG_PACKAGE_BUILD_LOCATION}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION "${CONFIG_PACKAGE_INSTALL_LOCATION}"
)
