/*!
 * \file Inline.hpp
 * \brief Exports macros to force or forbid inlining of a function.
**/
#pragma once

#include "Compiler.hpp"

/*!
 * \def CPP_ALWAYS_INLINE
 * \brief Declares a function as always to be inlined (if possible).
 * \warning Overrides the compiler's cost-benefit-analysis in regards to
 *          inlining. Only use when certain. May not work if compiler is
 *          unknown.
**/

/*!
 * \def CPP_NEVER_INLINE
 * \brief Declares a function as never to be inlined.
 * \warning May not work if compiler is unknown.
**/

#if CPP_COMPILER_IS(CPP_COMPILER_GCC)
#    define CPP_ALWAYS_INLINE __attribute__((always_inline)) inline
#    define CPP_NEVER_INLINE __attribute__((noinline))
#elif CPP_COMPILER_IS(CPP_COMPILER_CLANG)
#    define CPP_ALWAYS_INLINE __attribute__((always_inline)) inline
#    define CPP_NEVER_INLINE __attribute__((noinline))
#elif CPP_COMPILER_IS(CPP_COMPILER_ICC)
#    define CPP_ALWAYS_INLINE __attribute__((always_inline)) inline
#    define CPP_NEVER_INLINE __attribute__((noinline))
#elif CPP_COMPILER_IS(CPP_COMPILER_MSVC)
#    define CPP_ALWAYS_INLINE __forceinline
#    define CPP_NEVER_INLINE __declspec(noinline)
#elif CPP_COMPILER_IS(CPP_COMPILER_UNKNOWN)
#    define CPP_ALWAYS_INLINE inline
#    define CPP_NEVER_INLINE /* nothing */
#endif
