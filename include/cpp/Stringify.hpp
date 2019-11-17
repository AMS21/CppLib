/*!
 * \file Stringify.hpp
 * \brief Exports a macro that can be used to turn any sequence of tokens
 *        into a C-string literal at preprocessing time.
**/
#ifndef INCG_CPPLIB_STRINGIFY_HPP
#define INCG_CPPLIB_STRINGIFY_HPP

/*!
 * \def CPP_DETAIL_STRINGIFY(tokens)
 * \brief Implementation macro for CPP_STRINGIFY
 * \warning Do not use.
 * \see CPP_STRINGIFY
**/
#define CPP_DETAIL_STRINGIFY(tokens) #tokens

/*!
 * \def CPP_STRINGIFY(tokens)
 * \brief Turns a contiguous sequence of tokens passed in into a
 *        C-String literal.
 * \example CPP_STRINGIFY(helloworld) results in:
 *          "helloworld"
**/
#define CPP_STRINGIFY(tokens) CPP_DETAIL_STRINGIFY(tokens)

#endif // INCG_CPPLIB_STRINGIFY_HPP
