#pragma once

#include "Compiler.hpp"

#if CPP_COMPILER_IS(CPP_COMPILER_GCC)
#   define CPP_ALWAYS_INLINE __attribute__((always_inline)) inline
#   define CPP_NEVER_INLINE __attribute__((noinline))
#elif CPP_COMPILER_IS(CPP_COMPILER_CLANG)
#   define CPP_ALWAYS_INLINE __attribute__((always_inline)) inline
#   define CPP_NEVER_INLINE __attribute__((noinline))
#elif CPP_COMPILER_IS(CPP_COMPILER_ICC)
#   define CPP_ALWAYS_INLINE __attribute__((always_inline)) inline
#   define CPP_NEVER_INLINE __attribute__((noinline))
#elif CPP_COMPILER_IS(CPP_COMPILER_MSVC)
#   define CPP_ALWAYS_INLINE __forceinline
#   define CPP_NEVER_INLINE __declspec(noinline)
#elif CPP_COMPILER_IS(CPP_COMPILER_UNKNOWN)
#   define CPP_ALWAYS_INLINE inline
#   define CPP_NEVER_INLINE /* nothing */
#endif
