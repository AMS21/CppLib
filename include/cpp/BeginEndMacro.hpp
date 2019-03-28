/*!
 * \file BeginEndMacro.hpp
 * \brief Exports macros that simplify the definition of convenient to use
 *        function like macros.
**/
#pragma once

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
