/*!
 * \file BreakIntoDebugger.hpp
 * \brief Cross platform macro to break into the debugger
 *
**/
#pragma once

#include "Compiler.hpp" // CPP_COMPILER_IS, CPP_COMPILER_MSVC, CPP_COMPILER_MINGW
#include "OS.hpp"       // CPP_OS_IS, CPP_OS_MACOS

#if CPP_OS_IS(CPP_OS_MACOS)
#    define CPP_BREAK_INTO_DEBUGGER() __asm__("int $3\n" : :)
#elif CPP_COMPILER_IS(CPP_COMPILER_MSVC)
#    define CPP_BREAK_INTO_DEBUGGER() __debugbreak()
#elif CPP_COMPILER_IS(CPP_COMPILER_MINGW)
extern "C" __declspec(dllimport) void __stdcall DebugBreak();
#    define CPP_BREAK_INTO_DEBUGGER() ::DebugBreak()
#else
#    define CPP_BREAK_INTO_DEBUGGER() ((void)0)
#endif

/*!
 * \def CPP_BREAK_INTO_DEBUGGER
 * \brief Function like macro for breaking into the debugger
 * \note Currently only supported on MacOs, MSVC and MinGW on
 *       all other platforms/compilers it simply does nothing
**/
