/*!
 * \file Glue.hpp
 * \brief Exports a macro that can be used to glue two sequences of tokens
 *        together in order to form a single sequence of tokens at
 *        preprocessing time.
**/
#pragma once

/*!
 * \def CPP_DETAIL_GLUE(a, b)
 * \brief Implementation macro for CPP_GLUE
 * \warning Do not use.
 * \see CPP_GLUE
**/
#define CPP_DETAIL_GLUE(a, b) a##b

/*!
 * \def CPP_GLUE(a, b)
 * \brief Token pastes two contiguous sequences of tokens together as one.
 * \example CPP_GLUE(hello, world) results in:
 *          helloworld
**/
#define CPP_GLUE(a, b) CPP_DETAIL_GLUE(a, b)
