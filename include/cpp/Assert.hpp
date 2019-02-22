#pragma once

#include "BeginEndMacro.hpp"
#include "CurrentFunction.hpp"
#include "Debug.hpp"
#include "SourceLine.hpp"

#include <exception>
#include <stdexcept>
#include <string>

////////////////////////////////////////////////////////////
/* Exceptions */
////////////////////////////////////////////////////////////

/*!
* \def CPP_DEFINE_EXCEPTION_TYPE(exception_type_identifier, base_class)
* \brief Defines an exception type. Its name will be exception_type_identifier
*        and the base class will be base_class. The exception type is defined
*        in the current namespace. This macro makes defining new exception
*        types a lot more convenient by generating a lot of boilerplate code.
**/
#define CPP_DEFINE_EXCEPTION_TYPE(exception_type_identifier, base_class)                                               \
    class exception_type_identifier : public base_class                                                                \
    {                                                                                                                  \
    public:                                                                                                            \
        using this_type = exception_type_identifier;                                                                   \
        using base_type = base_class;                                                                                  \
                                                                                                                       \
        explicit exception_type_identifier(const std::string& what_arg)                                                \
            : base_type{what_arg}                                                                                      \
        {}                                                                                                             \
                                                                                                                       \
        explicit exception_type_identifier(const char* what_arg)                                                       \
            : base_type{what_arg}                                                                                      \
        {}                                                                                                             \
    }

#define CPP_THROW_WITH_SOURCE_INFO(exceptionType, message)                                                             \
    throw exceptionType                                                                                                \
    {                                                                                                                  \
        "Message: " + std::string{message} +                                                                           \
                "\nexception was thrown at:"                                                                           \
                "\nfile: " __FILE__ "\nline: " CPP_SOURCE_LINE "\nfunction: " +                                        \
                std::string                                                                                            \
        {                                                                                                              \
            CPP_CURRENT_FUNCTION                                                                                       \
        }                                                                                                              \
    }

#define CPP_THROW_IF_NULL(pointer)                                                                                     \
    CPP_BEGIN_MACRO                                                                                                    \
    if (pointer == nullptr)                                                                                            \
    { CPP_THROW_WITH_SOURCE_INFO(::cpp::NullPointerException, CPP_STRINGIFY(pointer) " was null!"); }                  \
    CPP_END_MACRO

#define CPP_NOT_YET_IMPLEMENTED                                                                                        \
    CPP_THROW_WITH_SOURCE_INFO(::cpp::NotYetImplementedException, "function has not yet been implemented!")

////////////////////////////////////////////////////////////
/* Asserts */
////////////////////////////////////////////////////////////

#define CPP_DETAIL_ASSERTION_IMPLEMENTATION(condition, exceptionType, violationTypeString)                             \
    CPP_BEGIN_MACRO                                                                                                    \
    if (!(condition))                                                                                                  \
    {                                                                                                                  \
        CPP_THROW_WITH_SOURCE_INFO(exceptionType, violationTypeString                                                  \
                                   " VIOLATION:\n" CPP_STRINGIFY(condition) "\nevaluated to false!");                  \
    }                                                                                                                  \
    CPP_END_MACRO

#define CPP_DETAIL_ASSERTION_IMPLEMENTATION_MSG(condition, exceptionType, violationTypeString, message)                \
    CPP_BEGIN_MACRO                                                                                                    \
    if (!(condition))                                                                                                  \
    {                                                                                                                  \
        CPP_THROW_WITH_SOURCE_INFO(exceptionType, violationTypeString                                                  \
                                   " VIOLATION:\n" message "\n" CPP_STRINGIFY(condition) "\nevaluated to false!");     \
    }                                                                                                                  \
    CPP_END_MACRO

#define CPP_CHECK_PRE(precondition)                                                                                    \
    CPP_DETAIL_ASSERTION_IMPLEMENTATION(precondition, ::cpp::PreconditionViolationException, "PRECONDITION")

#define CPP_CHECK_PRE_MSG(precondition, message)                                                                       \
    CPP_DETAIL_ASSERTION_IMPLEMENTATION_MSG(precondition, ::cpp::PreconditionViolationException, "PRECONDITION",       \
                                            message)

#define CPP_CHECK_POST(postcondition)                                                                                  \
    CPP_DETAIL_ASSERTION_IMPLEMENTATION(postcondition, ::cpp::PostconditionViolationException, "POSTCONDITION")

#define CPP_CHECK_POST_MSG(postcondition, message)                                                                     \
    CPP_DETAIL_ASSERTION_IMPLEMENTATION_MSG(postcondition, ::cpp::PostconditionViolationException, "POSTCONDITION",    \
                                            message)

#define CPP_ASSERT(condition)                                                                                          \
    CPP_DETAIL_ASSERTION_IMPLEMENTATION(condition, ::cpp::AssertionViolationException, "ASSERTION")

#define CPP_ASSERT_MSG(condition, message)                                                                             \
    CPP_DETAIL_ASSERTION_IMPLEMENTATION_MSG(condition, ::cpp::AssertionViolationException, "ASSERTION", message)

#define CPP_CHECK_BOUNDS(item, lower_bound, upper_bound)                                                               \
    CPP_DETAIL_ASSERTION_IMPLEMENTATION((lower_bound <= item) && (item <= upper_bound),                                \
                                        ::cpp::IndexOutOfBoundsException, "BOUNDSCHECK")

#ifdef CPP_DEBUG
#    define CPP_DBG_CHECK_PRE(precondition) CPP_CHECK_PRE(precondition)
#    define CPP_DBG_CHECK_PRE_MSG(precondition, message) CPP_CHECK_PRE_MSG(precondition, message)
#    define CPP_DBG_CHECK_POST(postcondition) CPP_CHECK_POST(postcondition)
#    define CPP_DBG_CHECK_POST_MSG(postcondition, message) CPP_CHECK_POST_MSG(postcondition, message)
#    define CPP_DBG_ASSERT(condition) CPP_ASSERT(condition)
#    define CPP_DBG_ASSERT_MSG(condition, message) CPP_ASSERT_MSG(condition, message)
#    define CPP_DBG_CHECK_BOUNDS(item, lower_bound, upper_bound) CPP_CHECK_BOUNDS(item, lower_bound, upper_bound)
#else
#    define CPP_DBG_CHECK_PRE(precondition) CPP_BEGIN_MACRO CPP_END_MACRO                      /* do nothing */
#    define CPP_DBG_CHECK_PRE_MSG(precondition, message) CPP_BEGIN_MACRO CPP_END_MACRO         /* do nothing */
#    define CPP_DBG_CHECK_POST(postcondition) CPP_BEGIN_MACRO CPP_END_MACRO                    /* do nothing */
#    define CPP_DBG_CHECK_POST_MSG(postcondition, message) CPP_BEGIN_MACRO CPP_END_MACRO       /* do nothing */
#    define CPP_DBG_ASSERT(condition) CPP_BEGIN_MACRO CPP_END_MACRO                            /* do nothing */
#    define CPP_DBG_ASSERT_MSG(condition, message) CPP_BEGIN_MACRO CPP_END_MACRO               /* do nothing */
#    define CPP_DBG_CHECK_BOUNDS(item, lower_bound, upper_bound) CPP_BEGIN_MACRO CPP_END_MACRO /* do nothing */
#endif

////////////////////////////////////////////////////////////
/* Exceptions */
////////////////////////////////////////////////////////////

namespace cpp
{
    /*!
    * \brief Exception thrown on assertion violation.
    * \note Not to be caught, this exception indicates a bug.
    * \see assert.hpp
    **/
    class AssertionViolationException : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };

    /*!
    * \brief Exception thrown on precondition violation.
    * \note Not to be caught, this exception indicates a bug.
    * \see assert.hpp
    **/
    class PreconditionViolationException : public AssertionViolationException
    {
    public:
        using AssertionViolationException::AssertionViolationException;
    };

    /*!
    * \brief Exception thrown on postcondition violation.
    * \note Not to be caught, this exception indicates a bug.
    * \see assert.hpp
    **/
    class PostconditionViolationException : public AssertionViolationException
    {
    public:
        using AssertionViolationException::AssertionViolationException;
    };

    /*!
    * \brief Exception that you can throw if given an unexpected null pointer.
    **/
    class NullPointerException : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };

    /*!
    * \brief Used by the CPP_NOT_YET_IMPLEMENTED macro.
    **/
    class NotYetImplementedException : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };

    /*!
    * \brief Exception that you can throw if an arithmetic error were to occur.
    **/
    class ArithmeticException : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };

    /*!
    * \brief Exception that you can throw if given an illegal argument.
    **/
    class IllegalArgumentException : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };

    /*!
    * \brief Exception that you can throw if an index is out of bounds.
    **/
    class IndexOutOfBoundsException : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };

    /*!
    * \brief Exception that you can throw if a requested operation is not supported.
    **/
    class OperationNotSupportedException : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };

    /*!
    * \brief Exception that indicates an invalid size.
    **/
    class InvalidSizeException : public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };
} // namespace cpp
