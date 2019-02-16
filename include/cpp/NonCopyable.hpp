#pragma once

// TODO: Pre-C++11 support

namespace cpp
{
    class NonCopyable
    {
    protected:
        NonCopyable() = default;

        ~NonCopyable() = default;

    private:
        NonCopyable(const NonCopyable&) = delete;

        NonCopyable& operator=(const NonCopyable&) = delete;
    };
} // namespace cpp

/*!
 * \def CPP_NONCOPYABLE(type_identifier)
 * \brief Macro to be placed in the public section of a type.
 *        Pass the identifier of the type into this macro.
 *        Used to declare a type as noncopyable.
**/
#define CPP_NONCOPYABLE(type_identifier)                                                                               \
    type_identifier(const type_identifier&) = delete;                                                                  \
    type_identifier& operator=(const type_identifier&) = delete
