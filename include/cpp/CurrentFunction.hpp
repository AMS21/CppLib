/*!
 * \file CurrentFunction.hpp
 * \brief Exports an object like macro to get the name of the current function.
**/
#ifndef INCG_CPPLIB_CURRENT_FUNCTION_HPP
#define INCG_CPPLIB_CURRENT_FUNCTION_HPP

#include "Compiler.hpp"

/*!
 * \def CPP_CURRENT_FUNCTION
 * \brief Expands to a C-String literal that represents the current function.
 * \note Uses the 'prettiest' function macro that the compiler being used
 *       provides.
 * \warning Depending on the compiler used, this macro will expand to a
 *          different C-String literal!
 * \warning The result of the macro expansion can not be string concatenated
 *          by the preprocessor with other C-String literals.
**/

#if CPP_COMPILER_IS(CPP_COMPILER_MSVC)
#    define CPP_CURRENT_FUNCTION __FUNCSIG__
#elif CPP_COMPILER_IS(CPP_COMPILER_GCC) || CPP_COMPILER_IS(CPP_COMPILER_CLANG)
#    define CPP_CURRENT_FUNCTION __PRETTY_FUNCTION__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#    define CPP_CURRENT_FUNCTION __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#    define CPP_CURRENT_FUNCTION __FUNC__
#else
#    define CPP_CURRENT_FUNCTION __func__ /* use __func__ from C99 as fallback */
#endif

#endif // INCG_CPPLIB_CURRENT_FUNCTION_HPP
