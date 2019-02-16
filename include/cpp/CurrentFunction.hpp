#pragma once

#include "Compiler.hpp"

#if CPP_COMPILER_IS(CPP_COMPILER_MSVC)
#   define CPP_CURRENT_FUNCTION __FUNCSIG__
#elif CPP_COMPILER_IS(CPP_COMPILER_GCC) || CPP_COMPILER_IS(CPP_COMPILER_CLANG)
#   define CPP_CURRENT_FUNCTION __PRETTY_FUNCTION__
#else
#   define CPP_CURRENT_FUNCTION __func__ /* use __func__ from C99 as fallback */
#endif
