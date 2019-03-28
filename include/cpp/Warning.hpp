#pragma once

#include "Compiler.hpp"
#include "Stringify.hpp"

// Suppress warnings
/* MSVC Warnings */
#if CPP_COMPILER_IS(CPP_COMPILER_MSVC)
#    define CPP_MSVC_SUPPRESS_WARNING_PUSH __pragma(warning(push))
#    define CPP_MSVC_SUPPRESS_WARNING(warning_number) __pragma(warning(disable : warning_number))
#    define CPP_MSVC_SUPPRESS_WARNING_WITH_PUSH(warning_number)                                                        \
        CPP_MSVC_SUPPRESS_WARNING_PUSH CPP_MSVC_SUPPRESS_WARNING(warning_number)
#    define CPP_MSVC_SUPPRESS_WARNING_POP __pragma(warning(pop))
#    define CPP_COMPILER_WARNING(msg) __pragma(message(__FILE__ "(" CPP_STRINGIFY(__LINE__) ") : warning: " #    msg))
#else
#    define CPP_MSVC_SUPPRESS_WARNING_PUSH               /* Nothing */
#    define CPP_MSVC_SUPPRESS_WARNING(warning)           /* Nothing */
#    define CPP_MSVC_SUPPRESS_WARNING_WITH_PUSH(warning) /* Nothing */
#    define CPP_MSVC_SUPPRESS_WARNING_POP                /* Nothing */
#endif

/* Clang Warnings */
#if CPP_COMPILER_IS(CPP_COMPILER_CLANG)
#    define DETAIL_CPP_PRAGMA_TO_STR(string) _Pragma(#    string)
#    define CPP_CLANG_SUPPRESS_WARNING_PUSH _Pragma("clang diagnostic push")
#    define CPP_CLANG_SUPPRESS_WARNING(warning) DETAIL_CPP_PRAGMA_TO_STR(clang diagnostic ignored warning)
#    define CPP_CLANG_SUPPRESS_WARNING_WITH_PUSH(warning)                                                              \
        CPP_CLANG_SUPPRESS_WARNING_PUSH CPP_CLANG_SUPPRESS_WARNING(warning)
#    define CPP_CLANG_SUPPRESS_WARNING_POP _Pragma("clang diagnostic push")
#    define CPP_COMPILER_WARNING(msg)                                                                                  \
        _Pragma(CPP_STRINGIFY(GCC warning(__FILE__ "(" CPP_STRINGIFY(__LINE__) ") : warning: " msg)))
#else
#    define CPP_CLANG_SUPPRESS_WARNING_PUSH               /* Nothing */
#    define CPP_CLANG_SUPPRESS_WARNING(warning)           /* Nothing */
#    define CPP_CLANG_SUPPRESS_WARNING_WITH_PUSH(warning) /* Nothing */
#    define CPP_CLANG_SUPPRESS_WARNING_POP                /* Nothing */
#endif

/* GCC Warnings */
#if CPP_COMPILER_IS(CPP_COMPILER_GCC)
#    define DETAIL_CPP_PRAGMA_TO_STR(string) _Pragma(#    string)
#    if CPP_COMPILER_VERSION_IS_ATLEAST(4, 7, 0)
#        define CPP_GCC_SUPPRESS_WARNING_PUSH _Pragma("GCC diagnostic push")
#        define CPP_GCC_SUPPRESS_WARNING_POP _Pragma("GCC diagnostic pop")
#    else
#        define CPP_GCC_SUPPRESS_WARNING_PUSH /* Nothing */
#        define CPP_GCC_SUPPRESS_WARNING_POP  /* Nothing */
#    endif
#    define CPP_GCC_SUPPRESS_WARNING(warning) DETAIL_CPP_PRAGMA_TO_STR(GCC diagnostic ignored warning)
#    define CPP_GCC_SUPPRESS_WARNING_WITH_PUSH(warning) CPP_GCC_SUPPRESS_WARNING_PUSH CPP_GCC_SUPPRESS_WARNING(warning)
#    define CPP_COMPILER_WARNING(msg) DETAIL_CPP_PRAGMA_TO_STR(GCC warning msg)
#else
#    define CPP_GCC_SUPPRESS_WARNING_PUSH               /* Nothing */
#    define CPP_GCC_SUPPRESS_WARNING(warning)           /* Nothing */
#    define CPP_GCC_SUPPRESS_WARNING_WITH_PUSH(warning) /* Nothing */
#    define CPP_GCC_SUPPRESS_WARNING_POP                /* Nothing */
#endif

#if !defined(CPP_COMPILER_WARNING)
#    define CPP_COMPILER_WARNING(msg) /* Nothing */
#endif

#define CPP_UNUSED_PARAMETER(parameter) ((void)(parameter))
