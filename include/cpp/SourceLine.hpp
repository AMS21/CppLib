/*!
 * \file SourceLine.hpp
 * \brief Exports an object like macro that expands to a C-style string
 *        of the current line number in the source code.
**/
#pragma once

#include "Stringify.hpp" // CPP_STRINGIFY

/*!
 * \def CPP_SOURCE_LINE
 * \brief The current line in the current source file.
 * \note Note that the line number may have been manipulated using #line.
 *
 * Macro that expands to a C-String literal of the current line in the current
 * source file. Equivalent to the stringification of the standard predefined
 * macro __LINE__
**/
#define CPP_SOURCE_LINE CPP_STRINGIFY(__LINE__)
