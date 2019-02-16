#pragma once

#include "Compiler.hpp"
#include "OS.hpp"

#if CPP_OS_IS(CPP_OS_MACOS)
#    define CPP_BREAK_INTO_DEBUGGER() __asm__("int $3\n" : :)
#elif CPP_COMPILER_IS(CPP_COMPILER_MSVC)
#    define CPP_BREAK_INTO_DEBUGGER() __debugbreak()
#elif defined(__MINGW32__)
extern "C" __declspec(dllimport) void __stdcall DebugBreak();
#    define CPP_BREAK_INTO_DEBUGGER() ::DebugBreak()
#else
#    define CPP_BREAK_INTO_DEBUGGER() ((void)0)
#endif
