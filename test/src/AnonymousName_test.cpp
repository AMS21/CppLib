#include "cpp/AnonymousName.hpp"
#include "cpp/Warning.hpp"
#include "doctest.h"

CPP_MSVC_SUPPRESS_WARNING_PUSH
CPP_MSVC_SUPPRESS_WARNING(4189) // 'x': local variable is initialized but not referenced
CPP_MSVC_SUPPRESS_WARNING(4101) // 'x': unreferenced local variable

TEST_CASE("anonymous name")
{
    int CPP_ANONYMOUS_NAME(a);
    int CPP_ANONYMOUS_NAME(a);
}

CPP_MSVC_SUPPRESS_WARNING_POP
