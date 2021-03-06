#include "cpp/AnonymousName.hpp"
#include "cpp/Warning.hpp"
#include "doctest.h"

class CPP_ANONYMOUS_NAME(A)
{};

class CPP_ANONYMOUS_NAME(A)
{};

CPP_MSVC_SUPPRESS_WARNING_PUSH
CPP_MSVC_SUPPRESS_WARNING(4189) // 'x': local variable is initialized but not referenced
CPP_MSVC_SUPPRESS_WARNING(4101) // 'x': unreferenced local variable

CPP_GCC_SUPPRESS_WARNING_PUSH
CPP_GCC_SUPPRESS_WARNING("-Wunused-variable")

CPP_CLANG_SUPPRESS_WARNING_PUSH
CPP_CLANG_SUPPRESS_WARNING("-Wunused-variable")

TEST_CASE("anonymous name")
{
    int CPP_ANONYMOUS_NAME(a);
    int CPP_ANONYMOUS_NAME(a);
}

CPP_CLANG_SUPPRESS_WARNING_POP

CPP_GCC_SUPPRESS_WARNING_POP

CPP_MSVC_SUPPRESS_WARNING_POP
