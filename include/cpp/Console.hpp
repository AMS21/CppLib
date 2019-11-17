// This file is based upon Abhinav Gauniyal's excellent rang Library: <https://github.com/agauniyal/rang>

/* Original License <https://github.com/agauniyal/rang/blob/master/LICENSE>
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org>
*/

/*!
 * \file Console.hpp
 * \brief Defines functions to help with console output.
 *	      Like different styles or coloring.
 *
 * This implementation is heavily based upon Abhinav Gauniyal's excellent rang Library.
 * https://github.com/agauniyal/rang
**/
#ifndef INCG_CPPLIB_CONSOLE_HPP
#define INCG_CPPLIB_CONSOLE_HPP

#include "OS.hpp"
#include "StreamScopeGuard.hpp"
#include "Warning.hpp"

CPP_GCC_SUPPRESS_WARNING_PUSH
CPP_GCC_SUPPRESS_WARNING("-Wconversion")

#if CPP_OS_UNIX_BASED || CPP_OS_IS(CPP_OS_MACOS)
#    include <unistd.h>

#elif CPP_OS_IS(CPP_OS_WINDOWS)

#    if defined(_WIN32_WINNT) && (_WIN32_WINNT < 0x0600)
#        error "Please include Console.hpp before any windows system headers or set _WIN32_WINNT at least to _WIN32_WINNT_VISTA"
#    elif !defined(_WIN32_WINNT)
#        define _WIN32_WINNT _WIN32_WINNT_VISTA
#    endif

#    include <io.h>
#    include <memory>

CPP_MSVC_SUPPRESS_WARNING_PUSH
CPP_MSVC_SUPPRESS_WARNING(4668) // 'x' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
CPP_MSVC_SUPPRESS_WARNING(
        5039) // 'x': pointer or reference to potentially throwing function passed to extern C function under -EHc. Undefined behavior may occur if this function throws an exception.
#    define WIN32_LEAN_AND_MEAN
#    include <windows.h>
CPP_MSVC_SUPPRESS_WARNING_POP

// Only defined in windows 10 onwards, redefining in lower windows since it
// doesn't gets used in lower versions
// https://docs.microsoft.com/en-us/windows/console/getconsolemode
#    ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#        define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#    endif

#endif

#include <algorithm>
#include <atomic>
#include <cstdlib>
#include <cstring>
#include <iostream>

namespace cpp
{
    /* For better compatibility with most of terminals do not use any style settings
     * except of reset, bold and reversed.
     * Note that on Windows terminals bold style is same as fgB color.
     */
    enum class style
    {
        reset     = 0,
        bold      = 1,
        dim       = 2,
        italic    = 3,
        underline = 4,
        blink     = 5,
        rblink    = 6,
        reversed  = 7,
        conceal   = 8,
        crossed   = 9
    };

    enum class fg
    {
        black   = 30,
        red     = 31,
        green   = 32,
        yellow  = 33,
        blue    = 34,
        magenta = 35,
        cyan    = 36,
        gray    = 37,
        reset   = 39
    };

    enum class bg
    {
        black   = 40,
        red     = 41,
        green   = 42,
        yellow  = 43,
        blue    = 44,
        magenta = 45,
        cyan    = 46,
        gray    = 47,
        reset   = 49
    };

    enum class fgB
    {
        black   = 90,
        red     = 91,
        green   = 92,
        yellow  = 93,
        blue    = 94,
        magenta = 95,
        cyan    = 96,
        gray    = 97
    };

    enum class bgB
    {
        black   = 100,
        red     = 101,
        green   = 102,
        yellow  = 103,
        blue    = 104,
        magenta = 105,
        cyan    = 106,
        gray    = 107
    };

    /*
     * Use cpp::setControlMode() to set rang control mode
     *  Off  : Toggle off style/color calls
     *  Auto : Auto detect terminal and colorize if needed (Default)
     *  Force: Force ANSI color output to non terminal streams
    **/
    enum class control
    {
        Off   = 0, /// Toggle off style/color calls
        Auto  = 1, /// Auto detect terminal and colorize if needed (Default)
        Force = 2  /// Force ANSI color output to non terminal streams
    };

    /*!
     * Use cpp::setWinTermMode() to explicitly set terminal API for Windows
     * Calling cpp::setWinTermMode() have no effect on other OS
     *  Auto  : Automatically detects whether Ansi or Native API (Default)
     *  Ansi  : Force use Ansi API
     *  Native: Force use Native API
    **/
    enum class winTerm
    {
        Auto   = 0, /// Automatically detects whether Ansi or Native API (Default)
        Ansi   = 1, /// Force use Ansi API
        Native = 2  /// Force use Native API
    };

    /// \cond detail
    namespace detail
    {
        inline std::atomic<control>& controlMode() noexcept
        {
            static std::atomic<control> value(control::Auto);
            return value;
        }

        inline std::atomic<winTerm>& winTermMode() noexcept
        {
            static std::atomic<winTerm> termMode(winTerm::Auto);
            return termMode;
        }

        template <typename CharT, typename Traits>
        inline FILE* stdio_file(const std::basic_streambuf<CharT, Traits>* sbuf) noexcept
        {
            return nullptr;
        }

        inline FILE* stdio_file(const std::wstreambuf* sbuf) noexcept
        {
            if (sbuf == std::wcout.rdbuf()) { return stdout; }
            else if (sbuf == std::wcerr.rdbuf() || sbuf == std::wclog.rdbuf())
            {
                return stderr;
            }
            return nullptr;
        }

        inline FILE* stdio_file(const std::streambuf* sbuf) noexcept
        {
            if (sbuf == std::cout.rdbuf()) { return stdout; }
            else if (sbuf == std::cerr.rdbuf() || sbuf == std::clog.rdbuf())
            {
                return stderr;
            }
            return nullptr;
        }

        inline bool isSupportedTerm() noexcept
        {
#if CPP_OS_UNIX_BASED || CPP_OS_IS(CPP_OS_MACOS)

            static const bool result = [] {
                const char* Terms[] = {"ansi",  "color", "console", "cygwin", "gnome",  "konsole", "kterm",
                                       "linux", "msys",  "putty",   "rxvt",   "screen", "vt100",   "xterm"};

                const char* env_p = std::getenv("TERM");
                if (env_p == nullptr) { return false; }
                return std::any_of(std::begin(Terms), std::end(Terms),
                                   [&](const char* term) { return std::strstr(env_p, term) != nullptr; });
            }();

#elif CPP_OS_IS(CPP_OS_WINDOWS)
            // All windows versions support colors through native console methods
            static constexpr bool result = true;
#endif
            return result;
        }

#if CPP_OS_IS(CPP_OS_WINDOWS)

        inline bool isMsysPty(int fd) noexcept
        {
            // Dynamic load for binary compability with old Windows
            const auto ptrGetFileInformationByHandleEx =
                    reinterpret_cast<decltype(&GetFileInformationByHandleEx)>(reinterpret_cast<void*>(
                            GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetFileInformationByHandleEx")));
            if (!ptrGetFileInformationByHandleEx) { return false; }

            HANDLE h = reinterpret_cast<HANDLE>(_get_osfhandle(fd));
            if (h == INVALID_HANDLE_VALUE) { return false; }

            // Check that it's a pipe:
            if (GetFileType(h) != FILE_TYPE_PIPE) { return false; }

            // POD type is binary compatible with FILE_NAME_INFO from WinBase.h
            // It have the same alignment and used to avoid UB in caller code
            struct MyFileNameInfo
            {
                DWORD FileNameLength;
                WCHAR FileName[MAX_PATH];
            };

            auto pNameInfo = std::unique_ptr<MyFileNameInfo>(new (std::nothrow) MyFileNameInfo());
            if (!pNameInfo) { return false; }

            // Check pipe name is template of
            // {"cygwin-","msys-"}XXXXXXXXXXXXXXX-ptyX-XX
            if (!ptrGetFileInformationByHandleEx(h, FileNameInfo, pNameInfo.get(), sizeof(MyFileNameInfo)))
            { return false; }

            std::wstring name(pNameInfo->FileName, pNameInfo->FileNameLength / sizeof(WCHAR));
            if ((name.find(L"msys-") == std::wstring::npos && name.find(L"cygwin-") == std::wstring::npos) ||
                name.find(L"-pty") == std::wstring::npos)
            { return false; }
            return true;
        }

#endif

        template <typename CharT, typename Traits>
        inline bool isTTY(std::basic_streambuf<CharT, Traits>* osbuf) noexcept
        {
            const FILE* ioFile = stdio_file(osbuf);
#if CPP_OS_UNIX_BASED || CPP_OS_IS(CPP_OS_MACOS)
            if (ioFile == stdout)
            {
                static const bool cout_term = isatty(fileno(stdout)) != 0;
                return cout_term;
            }
            else if (ioFile == stderr)
            {
                static const bool cerr_term = isatty(fileno(stderr)) != 0;
                return cerr_term;
            }
#elif CPP_OS_IS(CPP_OS_WINDOWS)
            if (ioFile == stdout)
            {
                static const bool cout_term = (_isatty(_fileno(stdout)) || isMsysPty(_fileno(stdout)));
                return cout_term;
            }
            else if (ioFile == stderr)
            {
                static const bool cerr_term = (_isatty(_fileno(stderr)) || isMsysPty(_fileno(stderr)));
                return cerr_term;
            }
#endif
            return false;
        }

        template <typename T>
        using enableConsole =
                typename std::enable_if<std::is_same<T, cpp::style>::value || std::is_same<T, cpp::fg>::value ||
                                                std::is_same<T, cpp::bg>::value || std::is_same<T, cpp::fgB>::value ||
                                                std::is_same<T, cpp::bgB>::value,
                                        T>::type;

#if CPP_OS_IS(CPP_OS_WINDOWS)

        struct SGR
        {                      // Select Graphic Rendition parameters for Windows console
            BYTE    fgColor;   // foreground color (0-15) lower 3 rgb bits + intense bit
            BYTE    bgColor;   // background color (0-15) lower 3 rgb bits + intense bit
            BYTE    bold;      // emulated as FOREGROUND_INTENSITY bit
            BYTE    underline; // emulated as BACKGROUND_INTENSITY bit
            BOOLEAN inverse;   // swap foreground/bold & background/underline
            BOOLEAN conceal;   // set foreground/bold to background/underline
        };

        enum class AttrColor : BYTE
        { // Color attributes for console screen buffer
            black   = 0,
            red     = 4,
            green   = 2,
            yellow  = 6,
            blue    = 1,
            magenta = 5,
            cyan    = 3,
            gray    = 7
        };

        template <typename CharT, typename Traits>
        inline HANDLE getConsoleHandle(const std::basic_streambuf<CharT, Traits>* osbuf) noexcept
        {
            const FILE* ioFile = stdio_file(osbuf);
            if (ioFile == stdout)
            {
                static const HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
                return hStdout;
            }
            else if (ioFile == stderr)
            {
                static const HANDLE hStderr = GetStdHandle(STD_ERROR_HANDLE);
                return hStderr;
            }
            return INVALID_HANDLE_VALUE;
        }

        template <typename CharT, typename Traits>
        inline bool setWinTermAnsiColors(const std::basic_streambuf<CharT, Traits>* osbuf) noexcept
        {
            HANDLE h = getConsoleHandle(osbuf);
            if (h == INVALID_HANDLE_VALUE) { return false; }
            DWORD dwMode = 0;
            if (!GetConsoleMode(h, &dwMode)) { return false; }
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            if (!SetConsoleMode(h, dwMode)) { return false; }
            return true;
        }

        template <typename CharT, typename Traits>
        inline bool supportsAnsi(const std::basic_streambuf<CharT, Traits>* osbuf) noexcept
        {
            const FILE* ioFile = stdio_file(osbuf);
            if (ioFile == stdout)
            {
                static const bool cout_ansi = (isMsysPty(_fileno(stdout)) || setWinTermAnsiColors(osbuf));
                return cout_ansi;
            }
            else if (ioFile == stderr)
            {
                static const bool cerr_ansi = (isMsysPty(_fileno(stderr)) || setWinTermAnsiColors(osbuf));
                return cerr_ansi;
            }
            return false;
        }

        inline const SGR& defaultState() noexcept
        {
            static const SGR defaultSgr = []() -> SGR {
                CONSOLE_SCREEN_BUFFER_INFO info;
                WORD                       attrib = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
                if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info) ||
                    GetConsoleScreenBufferInfo(GetStdHandle(STD_ERROR_HANDLE), &info))
                { attrib = info.wAttributes; }
                SGR sgr     = {0, 0, 0, 0, FALSE, FALSE};
                sgr.fgColor = static_cast<BYTE>(attrib & 0x0F);
                sgr.bgColor = static_cast<BYTE>((attrib & 0xF0) >> 4);
                return sgr;
            }();
            return defaultSgr;
        }

        inline BYTE ansi2attr(BYTE rgb) noexcept
        {
            static const AttrColor rev[8] = {AttrColor::black, AttrColor::red,     AttrColor::green, AttrColor::yellow,
                                             AttrColor::blue,  AttrColor::magenta, AttrColor::cyan,  AttrColor::gray};
            return static_cast<BYTE>(rev[rgb]);
        }

        inline void setWinSGR(cpp::bg col, SGR& state) noexcept
        {
            if (col != cpp::bg::reset) { state.bgColor = ansi2attr(static_cast<BYTE>(col) - 40u); }
            else
            {
                state.bgColor = defaultState().bgColor;
            }
        }

        inline void setWinSGR(cpp::fg col, SGR& state) noexcept
        {
            if (col != cpp::fg::reset) { state.fgColor = ansi2attr(static_cast<BYTE>(col) - 30u); }
            else
            {
                state.fgColor = defaultState().fgColor;
            }
        }

        inline void setWinSGR(cpp::bgB col, SGR& state) noexcept
        {
            state.bgColor = static_cast<BYTE>((BACKGROUND_INTENSITY >> 4) | ansi2attr(static_cast<BYTE>(col) - 100u));
        }

        inline void setWinSGR(cpp::fgB col, SGR& state) noexcept
        {
            state.fgColor = static_cast<BYTE>(FOREGROUND_INTENSITY | ansi2attr(static_cast<BYTE>(col) - 90u));
        }

        inline void setWinSGR(cpp::style style, SGR& state) noexcept
        {
            switch (style)
            {
                case cpp::style::reset: state = defaultState(); break;
                case cpp::style::bold: state.bold = FOREGROUND_INTENSITY; break;
                case cpp::style::underline:
                case cpp::style::blink: state.underline = BACKGROUND_INTENSITY; break;
                case cpp::style::reversed: state.inverse = TRUE; break;
                case cpp::style::conceal: state.conceal = TRUE; break;

                case cpp::style::crossed:
                case cpp::style::dim:
                case cpp::style::italic:
                case cpp::style::rblink:
                default: break;
            }
        }

        inline SGR& current_state() noexcept
        {
            static SGR state = defaultState();
            return state;
        }

        inline WORD SGR2Attr(const SGR& state) noexcept
        {
            WORD attrib = 0;
            if (state.conceal)
            {
                if (state.inverse)
                {
                    attrib = static_cast<WORD>((state.fgColor << 4) | state.fgColor);
                    if (state.bold) { attrib |= FOREGROUND_INTENSITY | BACKGROUND_INTENSITY; }
                }
                else
                {
                    attrib = static_cast<WORD>((state.bgColor << 4) | state.bgColor);
                    if (state.underline) { attrib |= FOREGROUND_INTENSITY | BACKGROUND_INTENSITY; }
                }
            }
            else if (state.inverse)
            {
                attrib = static_cast<WORD>((state.fgColor << 4) | state.bgColor);
                if (state.bold) { attrib |= BACKGROUND_INTENSITY; }
                if (state.underline) { attrib |= FOREGROUND_INTENSITY; }
            }
            else
            {
                attrib = static_cast<WORD>(state.fgColor | (state.bgColor << 4) | state.bold | state.underline);
            }
            return attrib;
        }

        template <typename CharT, typename Traits, typename T, typename = enableConsole<T>>
        inline void setWinColorAnsi(std::basic_ostream<CharT, Traits>& os, T const value)
        {
            StreamScopeGuard<CharT, Traits> guard(os);
            os.flags(std::ios::dec | std::ios::left);
            os << "\033[" << static_cast<int>(value) << "m";
        }

        template <typename CharT, typename Traits, typename T, typename = enableConsole<T>>
        inline void setWinColorNative(std::basic_ostream<CharT, Traits>& os, T const value)
        {
            const HANDLE h = getConsoleHandle(os.rdbuf());
            if (h != INVALID_HANDLE_VALUE)
            {
                setWinSGR(value, current_state());
                os.flush(); // necessary
                SetConsoleTextAttribute(h, SGR2Attr(current_state()));
            }
        }

        template <typename CharT, typename Traits, typename T, typename = enableConsole<T>>
        inline std::basic_ostream<CharT, Traits>& setColor(std::basic_ostream<CharT, Traits>& os, T const value)
        {
            if (winTermMode() == winTerm::Auto)
            {
                if (supportsAnsi(os.rdbuf())) { setWinColorAnsi(os, value); }
                else
                {
                    setWinColorNative(os, value);
                }
            }
            else if (winTermMode() == winTerm::Ansi)
            {
                setWinColorAnsi(os, value);
            }
            else
            {
                setWinColorNative(os, value);
            }
            return os;
        }
#else
        template <typename CharT, typename Traits, typename T, typename = enableConsole<T>>
        inline std::basic_ostream<CharT, Traits>& setColor(std::basic_ostream<CharT, Traits>& os, T const value)
        {
            StreamScopeGuard<CharT, Traits> guard(os);
            os.flags(std::ios::dec | std::ios::left);
            return os << "\033[" << static_cast<int>(value) << "m";
        }
#endif

#if CPP_OS_IS(CPP_OS_WINDOWS)
        template <typename CharT, typename Traits>
        inline void showCursorNative(const std::basic_ostream<CharT, Traits>& os, const bool flg) noexcept
        {
            const HANDLE h = getConsoleHandle(os.rdbuf());
            if (h == INVALID_HANDLE_VALUE) return;

            CONSOLE_CURSOR_INFO info;
            if (!GetConsoleCursorInfo(h, &info)) return;

            info.bVisible = flg ? TRUE : FALSE;
            SetConsoleCursorInfo(h, &info);
        }
#endif

        // CRTP base class
        template <typename T>
        class Cursor
        {
            Cursor() = default;
            friend T;
        };
    } // namespace detail
    /// \endcond

    inline void setWinTermMode(const cpp::winTerm value) noexcept { detail::winTermMode() = value; }

    inline void setControlMode(const control value) noexcept { detail::controlMode() = value; }

    namespace cursor
    {
        struct setVisible final : public detail::Cursor<setVisible>
        {
            const bool visible;
            setVisible(const bool v = true)
                : visible(v)
            {}

            template <typename CharT, typename Traits>
            void execAnsi(std::basic_ostream<CharT, Traits>& os) const
            {
                os << (visible ? "\033[?25h" : "\033[?25l");
            }
#if CPP_OS_IS(CPP_OS_WINDOWS)
            template <typename CharT, typename Traits>
            void execNative(const std::basic_ostream<CharT, Traits>& os) const noexcept
            {
                detail::showCursorNative(os, visible);
            }
#endif
        };

        struct setPos final : public detail::Cursor<setPos>
        {
            const short x;
            const short y;

            setPos(const short a = 0, const short b = 0)
                : x(a)
                , y(b)
            {}

            template <typename CharT, typename Traits>
            void execAnsi(std::basic_ostream<CharT, Traits>& os) const
            {
                os << "\033[" << x << ';' << y << 'H';
            }
#if CPP_OS_IS(CPP_OS_WINDOWS)
            template <typename CharT, typename Traits>
            void execNative(const std::basic_ostream<CharT, Traits>& os) const noexcept
            {
                const auto consoleHandle = cpp::detail::getConsoleHandle(os.rdbuf());
                if (consoleHandle != INVALID_HANDLE_VALUE) { SetConsoleCursorPosition(consoleHandle, {y, x}); }
            }
#endif
        };
    } // namespace cursor

} // namespace cpp

// Applies cursor operation to given ostream
template <typename CharT, typename Traits, typename T>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                              const cpp::detail::Cursor<T>&&     base)
{
    const auto useCursor = [&]() -> std::basic_ostream<CharT, Traits>& {
        const auto&& drv = static_cast<T const&&>(base);
#if CPP_OS_UNIX_BASED || CPP_OS_IS(CPP_OS_MACOS)
        cpp::StreamScopeGuard<CharT, Traits> guard(os);
        os.flags(std::ios::dec | std::ios::left);
        drv.execAnsi(os);
        os.flush();
#elif CPP_OS_IS(CPP_OS_WINDOWS)
        if (cpp::detail::winTermMode() == cpp::winTerm::Auto)
        {
            if (cpp::detail::supportsAnsi(os.rdbuf()))
            {
                cpp::StreamScopeGuard<CharT, Traits> guard(os);
                os.flags(std::ios::dec | std::ios::left);
                drv.execAnsi(os);
                os.flush();
            }
            else
            {
                drv.execNative(os);
            }
        }
        else if (cpp::detail::winTermMode() == cpp::winTerm::Ansi)
        {
            cpp::StreamScopeGuard<CharT, Traits> guard(os);
            os.flags(std::ios::dec | std::ios::left);
            drv.execAnsi(os);
            os.flush();
        }
        else
        {
            drv.execNative(os);
        }
#endif
        return os;
    };

    const cpp::control option = cpp::detail::controlMode();
    switch (option)
    {
        case cpp::control::Auto:
            return cpp::detail::isSupportedTerm() && cpp::detail::isTTY(os.rdbuf()) ? useCursor() : os;
        case cpp::control::Force: return useCursor();

        case cpp::control::Off:
        default: return os;
    }
}

// Applies color operation to given ostream
template <typename CharT, typename Traits, typename T, typename = cpp::detail::enableConsole<T>>
inline std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const T& value)
{
    const cpp::control option = cpp::detail::controlMode();
    switch (option)
    {
        case cpp::control::Auto:
            return cpp::detail::isSupportedTerm() && cpp::detail::isTTY(os.rdbuf()) ? cpp::detail::setColor(os, value) :
                                                                                      os;
        case cpp::control::Force: return cpp::detail::setColor(os, value);

        case cpp::control::Off:
        default: return os;
    }
}

CPP_GCC_SUPPRESS_WARNING_POP

#endif // INCG_CPPLIB_CONSOLE_HPP
