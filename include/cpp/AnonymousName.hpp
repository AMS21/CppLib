#pragma once

#include "Glue.hpp"

#if defined(__COUNTER__) // not standard and may be missing for some compilers
#   define CPP_ANONYMOUS_NAME(x) CPP_GLUE(x, __COUNTER__)
#else // __COUNTER__
#   define CPP_ANONYMOUS_NAME(x) CPP_GLUE(x, __LINE__)
#endif // __COUNTER__
