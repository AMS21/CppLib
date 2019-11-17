/*!
 * \file Compiler.hpp
 * \brief Defines macros to determine the compiler
 *        and the version of the compiler being used.
 *
 * This implementation is mostly based upon this article https://sourceforge.net/p/predef/wiki/Compilers
**/
#ifndef INCG_CPPLIB_COMPILER_HPP
#define INCG_CPPLIB_COMPILER_HPP

#include "Versioning.hpp" // CPP_VERSION_CREATE

/*!
 * \def CPP_COMPILER_CLANG
 * \brief CPP_COMPILER will be defined as this if clang is being used.
**/
#define CPP_COMPILER_CLANG (0x0001) /* meaningless number */

/*!
 * \def CPP_COMPILER_ICC
 * \brief CPP_COMPILER will be defined as this
 *        if Intel C++ Compiler is being used.
**/
#define CPP_COMPILER_ICC (0x0002) /* meaningless number */

/*!
 * \def CPP_COMPILER_MSVC
 * \brief CPP_COMPILER will be defined as this if Microsoft Visual Compiler is
 *        being used.
**/
#define CPP_COMPILER_MSVC (0x0003) /* meaningless number */

/*!
 * \def CPP_COMPILER_GCC
 * \brief CPP_COMPILER will be defined as this if gcc is being used.
**/
#define CPP_COMPILER_GCC (0x0004) /* meaningless number */

/*!
 * \def CPP_COMPILER_MINGW
 * \brief CPP_COMPILER will be defined as this if MinGW or MinGW-w64 is being used.
**/
#define CPP_COMPILER_MINGW (0x0005) /* meaningless number */

/*!
* \def CPP_COMPILER_UNKNOWN
* \brief CPP_COMPILER will be defined as this if the compiler being used
*        could not be determined.
**/
#define CPP_COMPILER_UNKNOWN (0xFFFF) /* meaningless number */

#if defined(__clang__)
#    define CPP_COMPILER CPP_COMPILER_CLANG
#    define CPP_COMPILER_MAJOR __clang_major__
#    define CPP_COMPILER_MINOR __clang_minor__
#    define CPP_COMPILER_PATCH __clang_patchlevel__
#    define CPP_COMPILER_NAME "Clang"
#elif defined(__INTEL_COMPILER) || defined(__ICL) || defined(__ICC)
#    define CPP_COMPILER CPP_COMPILER_ICC
#    define CPP_COMPILER_MAJOR __INTEL_COMPILER / 100
#    define CPP_COMPILER_MINOR __INTEL_COMPILER % 100 / 10
#    define CPP_COMPILER_PATCH __INTEL_COMPILER % 10
#    define CPP_COMPILER_NAME "Intel ICC"
#elif defined(_MSC_VER)
#    define CPP_COMPILER CPP_COMPILER_MSVC
#    define CPP_COMPILER_MAJOR _MSC_FULL_VER / 10000000
#    define CPP_COMPILER_MINOR _MSC_FULL_VER % 10000000 / 100000
#    define CPP_COMPILER_PATCH _MSC_FULL_VER % 100000
#    define CPP_COMPILER_NAME "Microsoft Visual C++ Compiler"
#elif defined(__GNUC__) || defined(__GNUG__)
#    define CPP_COMPILER CPP_COMPILER_GCC
#    define CPP_COMPILER_MAJOR __GNUC__
#    define CPP_COMPILER_MINOR __GNUC_MINOR__
#    define CPP_COMPILER_PATCH __GNUC_PATCHLEVEL__
#    define CPP_COMPILER_NAME "GCC"
#elif defined(__MINGW32__)
#    include "stdlib.h" // Needed for version information
#    define CPP_COMPILER CPP_COMPILER_MINGW
#    define CPP_COMPILER_MAJOR __MINGW32_MAJOR_VERSION
#    define CPP_COMPILER_MINOR __MINGW32_MINOR_VERSION
#    define CPP_COMPILER_PATCH 0 // no patch version defined for MingW
#    if defined(__MINGW64__) || defined(__MINGW64_VERSION_MAJOR) || defined(__MINGW64_VERSION_MINOR)
#        define CPP_COMPILER_NAME "MinGW64"
#    else
#        define CPP_COMPILER_NAME "MinGW32"
#    endif
#else
#    define CPP_COMPILER CPP_COMPILER_UNKNOWN
#    define CPP_COMPILER_MAJOR (0) /* 0 for unknown compiler */
#    define CPP_COMPILER_MINOR (0) /* 0 for unknown compiler */
#    define CPP_COMPILER_PATCH (0) /* 0 for unknown compiler */
#    define CPP_COMPILER_NAME "Unknown"
#    warning "Compiler could not be detected"
#endif

/*!
 * \def CPP_COMPILER
 * \brief Will be defined as CPP_COMPILER_CLANG, CPP_COMPILER_ICC,
 *        CPP_COMPILER_MSVC, CPP_COMPILER_GCC, CPP_COMPILER_MINGW
 *        or CPP_COMPILER_UNKNOWN depending on which compiler is being used.
 *        Can be used to check which compiler is being used.
 *        Use CPP_COMPILER_NAME to get a c-style string of the compiler name.
 * \note Using CPP_COMPILER_IS(CPP_COMPILER_X) is equivalent to using
 *       CPP_COMPILER == CPP_COMPILER_X
 *       Using CPP_COMPILER_IS_NOT(CPP_COMPILER_X) is equivalent to using
 *       CPP_COMPILER != CPP_COMPILER_X
 * \sa CPP_COMPILER_IS, CPP_COMPILER_IS_NOT, CPP_COMPILER_NAME, CPP_COMPILER_CLANG
 *     CPP_COMPILER_ICC, CPP_COMPILER_MSVC, CPP_COMPILER_GCC, CPP_COMPILER_MINGW,
 *     CPP_COMPILER_UNKNOWN
**/

/*!
 * \def CPP_COMPILER_MAJOR
 * \brief The major version of the compiler.
 * \sa CPP_COMPILER_VERSION, CPP_COMPILER_MINOR, CPP_COMPILER_PATCH
**/

/*!
 * \def CPP_COMPILER_MINOR
 * \brief The minor version of the compiler.
 * \sa CPP_COMPILER_VERSION, CPP_COMPILER_MAJOR, CPP_COMPILER_PATCH
**/

/*!
 * \def CPP_COMPILER_PATCH
 * \brief The patch level of the compiler.
 * \sa CPP_COMPILER_VERSION, CPP_COMPILER_MAJOR, CPP_COMPILER_MINOR
**/

/*!
 * \def CPP_COMPILER_NAME
 * \brief C-string like representation of the compilers name.
 * \sa CPP_COMPILER
**/

/*!
 * \def CPP_COMPILER_VERSION
 * \brief The current compiler version, may be compared to a number generated
 *        with CPP_VERSION_CREATE.
 *        \code{.cpp}
 *        // Example of using the CPP_COMPILER_VERSION macro
 *        #if CPP_COMPILER_VERSION >= CPP_VERSION_CREATE(5, 0, 0)
 *        // Compiler version is greater/equal to 5.0.0
 *        #endif
 *        \endcode
 * \note There are also more expressive macros for testing compiler versions available:
 *       CPP_COMPILER_VERSION_IS_ATLEAST and CPP_COMPILER_VERSION_IS_BELOW
 * \sa CPP_VERSION_CREATE, CPP_COMPILER_MAJOR, CPP_COMPILER_MINOR, CPP_COMPILER_PATCH,
 *     CPP_COMPILER_VERSION_IS_ATLEAST, CPP_COMPILER_VERSION_IS_BELOW, CPP_COMPILER_IS_ATLEAST,
 *     CPP_COMPILER_IS_BELOW
**/
#define CPP_COMPILER_VERSION CPP_VERSION_CREATE(CPP_COMPILER_MAJOR, CPP_COMPILER_MINOR, CPP_COMPILER_PATCH)

/*!
 * \def CPP_COMPILER_VERSION_IS_ATLEAST(major, minor, patch)
 * \brief Tests whether the current compiler version is at least
 *        the specified version.
 * \param major Major version to compare against CPP_COMPILER_MAJOR
 * \param minor Minor version to compare against CPP_COMPILER_MINOR
 * \param patch Patch version to compare against CPP_COMPILER_PATCH
 * \note This doesn't check the compiler only the version
 * \sa CPP_COMPILER_VERSION_IS_BELOW, CPP_COMPILER_VERSION, CPP_COMPILER_MAJOR,
 *     CPP_COMPILER_MINOR, CPP_COMPILER_PATCH
**/
#define CPP_COMPILER_VERSION_IS_ATLEAST(major, minor, patch)                                                           \
    (CPP_VERSION_CREATE(major, minor, patch) <= CPP_COMPILER_VERSION)

/*!
 * \def CPP_COMPILER_VERSION_IS_BELOW(major, minor, patch)
 * \brief Tests whether the current compiler version is at below
 *        the specified version.
 * \param major Major version to compare against CPP_COMPILER_MAJOR
 * \param minor Minor version to compare against CPP_COMPILER_MINOR
 * \param patch Patch version to compare against CPP_COMPILER_PATCH
 * \note This doesn't check the compiler only the version
 * \sa CPP_COMPILER_VERSION_IS_ATLEAST, CPP_COMPILER_VERSION, CPP_COMPILER_MAJOR,
 *     CPP_COMPILER_MINOR, CPP_COMPILER_PATCH
**/
#define CPP_COMPILER_VERSION_IS_BELOW(major, minor, patch)                                                             \
    (CPP_VERSION_CREATE(major, minor, patch) > CPP_COMPILER_VERSION)

/*!
 * \def CPP_COMPILER_IS(compiler)
 * \brief Compares CPP_COMPILER to \a compiler. Equivalent to using CPP_COMPILER == compiler
 * \param compiler Compiler value to compare to. Must be any of the following
 *        CPP_COMPILER_CLANG, CPP_COMPILER_ICC, CPP_COMPILER_MSVC, CPP_COMPILER_GCC,
 *        CPP_COMPILER_MINGW or CPP_COMPILER_UNKNOWN
 * \warning Using CPP_COMPILER_IS with any other value than one in the format of CPP_COMPILER_X
 *          can result in unexpected behaviour!
 * \sa CPP_COMPILER_IS_NOT, CPP_COMPILER
**/
#define CPP_COMPILER_IS(compiler) (CPP_COMPILER == (compiler))

/*!
 * \def CPP_COMPILER_IS_NOT(compiler)
 * \brief Compares CPP_COMPILER to \a compiler. Equivalent to using CPP_COMPILER != compiler
 * \param compiler Compiler value to compare to. Must be any of the following
 *        CPP_COMPILER_CLANG, CPP_COMPILER_ICC, CPP_COMPILER_MSVC, CPP_COMPILER_GCC,
 *        CPP_COMPILER_MINGW or CPP_COMPILER_UNKNOWN
 * \warning Using CPP_COMPILER_IS_NOT with any other value than one in the format of CPP_COMPILER_X
 *          can result in unexpected behaviour!
 * \sa CPP_COMPILER_IS, CPP_COMPILER
**/
#define CPP_COMPILER_IS_NOT(compiler) (CPP_COMPILER != (compiler))

/*!
 * \def CPP_COMPILER_IS_ATLEAST(compiler, major, minor, patch)
 * \brief Tests the compiler and that the compilers version is
 *        at least the given value. Is equivalent to using
 *        CPP_COMPILER_IS(compiler) && CPP_COMPILER_VERSION_IS_ATLEAST(major, minor, patch)
 * \param compiler Compiler to check
 * \param major Major version to compare against CPP_COMPILER_MAJOR
 * \param minor Minor version to compare against CPP_COMPILER_MINOR
 * \param patch Patch version to compare against CPP_COMPILER_PATCH
 * \warning Using \a compiler with any other value than one in the format of CPP_COMPILER_X
 *          can result in unexpected behaviour!
 * \sa CPP_COMPILER_VERSION_IS_ATLEAST, CPP_COMPILER_IS, CPP_COMPILER, CPP_COMPILER_IS_BELOW
 *
**/
#define CPP_COMPILER_IS_ATLEAST(compiler, major, minor, patch)                                                         \
    (CPP_COMPILER_IS(compiler) && CPP_COMPILER_VERSION_IS_ATLEAST(major, minor, patch))

/*!
 * \def CPP_COMPILER_IS_BELOW(compiler, major, minor, patch)
 * \brief Tests the compiler and that the compilers version is
 *        below the given value. Is equivalent to using
 *        CPP_COMPILER_IS(compiler) && CPP_COMPILER_VERSION_IS_BELOW(major, minor, patch)
 * \param compiler Compiler to check
 * \param major Major version to compare against CPP_COMPILER_MAJOR
 * \param minor Minor version to compare against CPP_COMPILER_MINOR
 * \param patch Patch version to compare against CPP_COMPILER_PATCH
 * \warning Using \a compiler with any other value than one in the format of CPP_COMPILER_X
 *          can result in unexpected behaviour!
 * \sa CPP_COMPILER_VERSION_IS_BELOW, CPP_COMPILER_IS, CPP_COMPILER, CPP_COMPILER_IS_ATLEAST
 *
**/
#define CPP_COMPILER_IS_BELOW(compiler, major, minor, patch)                                                           \
    (CPP_COMPILER_IS(compiler) && CPP_COMPILER_VERSION_IS_BELOW(major, minor, patch))

#endif // INCG_CPPLIB_COMPILER_HPP
