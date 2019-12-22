#ifndef INCG_CPPLIB_OS_HPP
#define INCG_CPPLIB_OS_HPP

////////////////////////////////////////////////////////////
/* Operating System Detection */
////////////////////////////////////////////////////////////

// clang-format off
#define CPP_OS_WINDOWS (0x0001) /* meaningless number */
#define CPP_OS_MACOS   (0x0002) /* meaningless number */
#define CPP_OS_LINUX   (0x0003) /* meaningless number */
#define CPP_OS_ANDROID (0x0004) /* meaningless number */
#define CPP_OS_FREEBSD (0x0005) /* meaningless number */
#define CPP_OS_SOLARIS (0x0006) /* meaningless number */
#define CPP_OS_IOS     (0x0007) /* meaningless number */
#define CPP_OS_OPENBSD (0x0008) /* meaningless number */
#define CPP_OS_UNKNOWN (0xFFFF) /* meaningless number */
// clang-format on

#if defined(_WIN32)
#    define CPP_OS CPP_OS_WINDOWS
#    define CPP_OS_NAME "Windows"
#elif defined(__APPLE__) && defined(__MACH__)
// Apple platform, see which one it is
#    include "TargetConditionals.h"
#    if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#        define CPP_OS CPP_OS_IOS
#        define CPP_OS_NAME "IPhone"
#    elif TARGET_OS_MAC
#        define CPP_OS CPP_OS_MACOS
#        define CPP_OS_NAME "MacOS"
#    else
#        warning "Unknown MacOS based operating system"
#        define CPP_OS CPP_OS_UNKNOWN
#        define CPP_OS_NAME "Unknown"
#    endif
#elif defined(__unix__) || defined(__unix) // Unix based OS
#    if defined(__ANDROID__)
#        define CPP_OS CPP_OS_ANDROID
#        define CPP_OS_NAME "Android"
#    elif defined(__linux__)
#        define CPP_OS CPP_OS_LINUX
#        define CPP_OS_NAME "Linux"
#    elif defined(__FreeBSD__)
#        define CPP_OS CPP_OS_FREEBSD
#        define CPP_OS_NAME "FreeBSD"
#    elif defined(__OpenBSD__)
#        define CPP_OS CPP_OS_OPENBSD
#        define CPP_OS_NAME "OpenBSD"
#    else
#        define CPP_OS CPP_OS_UNKNOWN
#        define CPP_OS_NAME "Unknown"
#        warning "Unknown Unix based operating system"
#    endif
#    define CPP_OS_UNIX_BASED 1
#elif defined(__sun) && defined(__SVR4)
#    define CPP_OS CPP_OS_SOLARIS
#    define CPP_OS_NAME "Solaris"
#else
#    define CPP_OS CPP_OS_UNKNOWN
#    define CPP_OS_NAME "Unknown"
#    warning "Operating system could not be detected"
#endif

#if !defined(CPP_OS_UNIX_BASED)
#    define CPP_OS_UNIX_BASED 0
#endif

#define CPP_OS_IS(os) (CPP_OS == (os))

#define CPP_OS_IS_NOT(os) (CPP_OS != (os))

#endif // INCG_CPPLIB_OS_HPP
