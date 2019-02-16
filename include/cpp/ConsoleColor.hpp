#pragma once

#include "OS.hpp"
#include <ostream>

#if CPP_OS_IS(CPP_OS_WINDOWS)
#    define WIN32_LEAN_AND_MEAN
#    include "windows.h"

namespace cpp
{
    enum class ConsoleColor : WORD
    {
        Default     = 65535,
        Black       = 0,
        DarkBlue    = FOREGROUND_BLUE,
        DarkGreen   = FOREGROUND_GREEN,
        DarkCyan    = FOREGROUND_GREEN | FOREGROUND_BLUE,
        DarkRed     = FOREGROUND_RED,
        DarkMagenta = FOREGROUND_RED | FOREGROUND_BLUE,
        DarkYellow  = FOREGROUND_RED | FOREGROUND_GREEN,
        DarkGrey    = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
        Grey        = FOREGROUND_INTENSITY,
        Blue        = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
        Green       = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
        Cyan        = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
        Red         = FOREGROUND_INTENSITY | FOREGROUND_RED,
        Magenta     = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
        Yellow      = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
        White       = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    };

    namespace
    {
        WORD default_value;
        bool first = true;
    } // namespace

    std::ostream& operator<<(std::ostream& stream, const ConsoleColor color)
    {
        if (first)
        {
            first = false;

            CONSOLE_SCREEN_BUFFER_INFO info{};
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
            default_value = info.wAttributes;
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                                (color == ConsoleColor::Default ? default_value : static_cast<WORD>(color)));
        return stream;
    }
} // namespace cpp

#elif defined(__unix__) || defined(__unix) || defined(__APPLE__)
namespace cpp
{
    enum class ConsoleColor : int
    {
        Default     = 39,
        Black       = 30,
        DarkBlue    = 34,
        DarkGreen   = 32,
        DarkCyan    = 36,
        DarkRed     = 31,
        DarkMagenta = 35,
        DarkYellow  = 33,
        DarkGrey    = 90,
        Grey        = 37,
        Blue        = 94,
        Green       = 92,
        Cyan        = 96,
        Red         = 91,
        Magenta     = 95,
        Yellow      = 33,
        White       = 97,
    };

    std::ostream& operator<<(std::ostream& stream, const ConsoleColor color)
    {
        stream << "\e[" + std::to_string(static_cast<int>(color)) + "m";
        return stream;
    }
} // namespace cpp

#else
#    warning "Couldn't get settings for colored console output!"

namespace cpp
{
    enum class ConsoleColor : int
    {
        Default = 0,
        Black,
        DarkBlue,
        DarkGreen,
        DarkCyan,
        DarkRed,
        DarkMagenta,
        DarkYellow,
        DarkGrey,
        Grey,
        Blue,
        Green,
        Cyan,
        Red,
        Magenta,
        Yellow,
        White,
    };

    std::ostream& operator<<(std::ostream& stream, const ConsoleColor color) { return stream; }

} // namespace cpp
#endif
