#pragma once

#include "BeginEndMacro.hpp"
#include "Compiler.hpp"

#if CPP_COMPILER_IS(CPP_COMPILER_GCC)
#    define CPP_LIKELY(condition) __builtin_expect(condition, 1)
#    define CPP_UNLIKELY(condition) __builtin_expect(condition, 0)
#elif CPP_COMPILER_IS(CPP_COMPILER_CLANG)
#    if __has_builtin(__builtin_expect)
#        define CPP_LIKELY(condition) __builtin_expect(condition, 1)
#        define CPP_UNLIKELY(condition) __builtin_expect(condition, 1)
#    else
#        define CPP_LIKELY(condition) condition
#        define CPP_UNLIKELY(condition) condition
#    endif
#else
#    define CPP_LIKELY(condition) condition
#    define CPP_UNLIKELY(condition) condition
#endif
