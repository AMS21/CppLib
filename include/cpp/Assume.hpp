#pragma once

#include "BeginEndMacro.hpp"
#include "Compiler.hpp"

#if CPP_COMPILER_IS(CPP_COMPILER_MSVC)
#    define CPP_ASSUME(condition) __assume(condition)
#elif CPP_COMPILER_IS(CPP_COMPILER_CLANG) && __has_builtin(__builtin_assume)
#    define CPP_ASSUME(condition) __builtin_assume(condition)
#else
#    define CPP_ASSUME(condition) CPP_BEGIN_MACRO CPP_END_MACRO /* Nothing */
#endif
