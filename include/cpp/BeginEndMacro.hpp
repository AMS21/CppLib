/*!
 * \file BeginEndMacro.hpp
 * \brief Exports macros that simplify the definition of convenient to use
 *        function like macros.
**/
#ifndef INCG_CPPLIB_BEGINENDMACRO_HPP
#define INCG_CPPLIB_BEGINENDMACRO_HPP

// clang-format off

/*!
 * \def CPP_BEGIN_MACRO
 * \brief To be used to begin definitions of macros that shall be forced to
 *        require a semicolon when used.
 * \see CPP_END_MACRO
**/
#define CPP_BEGIN_MACRO do {

/*!
 * \def CPP_END_MACRO
 * \brief To be used to end definitions of macros that shall be forced to
 *        require a semicolon when used.
 * \see CPP_BEGIN_MACRO
**/
#define CPP_END_MACRO } while ((void) 0, 0) /* avoid warnings */

// clang-format on

/*!
 * \def CPP_EMPTY_MACRO
 * \brief To be used to define a macro which does nothing/is empty and
 *        that shall be force to require a semicolon when used.
 * \see CPP_BEGIN_MACRO, CPP_END_MACRO
**/
#define CPP_EMPTY_MACRO ((void)0)

#endif // INCG_CPPLIB_BEGINENDMACRO_HPP
