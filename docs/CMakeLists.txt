cmake_minimum_required(VERSION 2.8.12)

# Policy
cmake_policy(SET CMP0054 NEW)

project( "CppLib_documentation" CXX )

find_package(Doxygen)

if (DOXYGEN_FOUND)
    # Configuration
    set(DOXYGEN_PROJECT_NAME "CppLib")
    set(DOXYGEN_PROJECT_NUMBER ${CPPLIB_VERSION_MAJOR}.${CPPLIB_VERSION_MINOR}.${CPPLIB_VERSION_PATCH})
    set(DOXYGEN_OUTPUT_DIRECTORY "")
    set(DOXYGEN_ALWAYS_SEC "YES")
    set(DOXYGEN_INLINE_INHERITED_MEMB "YES")
    set(DOXYGEN_EXTRACT_STATIC "YES")
    set(DOXYGEN_WARN_NO_PARAMDOC "YES")
    set(DOXYGEN_FILE_PATTERNS "*.hpp")
    set(DOXYGEN_SOURCE_BROWSER "YES")
    set(DOXYGEN_REFERENCES_LINK_SOURCE "NO")
    set(DOXYGEN_HTML_TIMESTAMP "YES")
    set(DOXYGEN_HTML_DYNAMIC_SECTIONS "YES")
    set(DOXYGEN_MACRO_EXPANSION "YES")

    doxygen_add_docs(${PROJECT_NAME} ${LIB_HEADERS})
elseif()
    MESSAGE(WARNING "Trying to build documentation but the Doxygen executable wasn't found!")
endif()
