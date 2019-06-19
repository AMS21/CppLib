/*!
 * \file AnonymouseName.hpp
 * \brief Exports a macro that simplifies the definition functions or variables
 *        with an anonymous name.
**/
#pragma once

#include "Glue.hpp" // CPP_GLUE

/*!
 * \def CPP_ANONYMOUS_NAME
 * \brief Used to wrap something into an anonymous name
 * \note Due to a limitation on some compilers its recommended, for maximum
 *        cross platform support, that you do not use this macro multiple times
 *        on the same line or mess around with the #line pre processor directive.
**/
#if defined(__COUNTER__) // not standard and may be missing for some compilers
#    define CPP_ANONYMOUS_NAME(x) CPP_GLUE(x, __COUNTER__)
#else // __COUNTER__
#    define CPP_ANONYMOUS_NAME(x) CPP_GLUE(x, __LINE__)
#endif // __COUNTER__
