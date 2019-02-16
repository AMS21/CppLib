#pragma once

////////////////////////////////////////////////////////////
/* Compiler Detection */
////////////////////////////////////////////////////////////

// clang-format off
#define CPP_COMPILER_CLANG   (0x0000) /* meaningless number */
#define CPP_COMPILER_ICC     (0x0001) /* meaningless number */
#define CPP_COMPILER_MSVC    (0x0002) /* meaningless number */
#define CPP_COMPILER_GCC     (0x0003) /* meaningless number */
#define CPP_COMPILER_UNKNOWN (0xFFFF) /* meaningless number */
// clang-format on

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
#else
#    define CPP_COMPILER CPP_COMPILER_UNKNOWN
#    define CPP_COMPILER_MAJOR (0) /* 0 for unknown compiler */
#    define CPP_COMPILER_MINOR (0) /* 0 for unknown compiler */
#    define CPP_COMPILER_PATCH (0) /* 0 for unknown compiler */
#    define CPP_COMPILER_NAME "Unknown"
#    warning "Compiler could not be detected"
#endif

#define CPP_COMPILER_VERSION_CREATE(major, minor, patch)                                                               \
    (((major)*16777216) + ((minor)*65536) + (patch)) /* multipliers to 'push' the numbers leftward */

#define CPP_COMPILER_VERSION CPP_COMPILER_VERSION_CREATE(CPP_COMPILER_MAJOR, CPP_COMPILER_MINOR, CPP_COMPILER_PATCH)

#define CPP_COMPILER_IS(compiler) (CPP_COMPILER == (compiler))

#define CPP_COMPILER_IS_NOT(compiler) (CPP_COMPILER != (compiler))

#define CPP_COMPILER_VERSION_IS_ATLEAST(major, minor, patch)                                                           \
    (CPP_COMPILER_VERSION_CREATE(major, minor, patch) <= CPP_COMPILER_VERSION)

#define CPP_COMPILER_VERSION_IS_BELOW(major, minor, patch)                                                             \
    (CPP_COMPILER_VERSION_CREATE(major, minor, patch) > CPP_COMPILER_VERSION)
