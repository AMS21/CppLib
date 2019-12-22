#ifndef INCG_CPPLIB_BIT_HPP
#define INCG_CPPLIB_BIT_HPP

#include "Compiler.hpp"
#include "Warning.hpp"
#include <type_traits>

CPP_GCC_SUPPRESS_WARNING_PUSH
CPP_GCC_SUPPRESS_WARNING("-Wconversion")

namespace cpp
{
    /*!
     * \brief Sets the bit at position bit of numeric.
     * \param numeric The number to have its bit bit set.
     * \param bit The bit to set in numeric. [0..bits(Numeric))
     * \return A reference to 'numeric'.
     * \warning Do not pass a value in bit that is larger than the amount
     *          of bits in Numeric - 1.
     * \note When using MSVC the function is only constexpr enabled with msvc17
     *       and newer.
     **/
    template <typename Numeric>
#if (CPP_COMPILER_IS_NOT(CPP_COMPILER_MSVC) || (CPP_COMPILER_VERSION_IS_ATLEAST(19, 11, 0)))
    constexpr
#else
    inline
#endif
            Numeric&
            set_bit(Numeric& numeric, Numeric bit) noexcept
    {
        static_assert(std::is_unsigned<Numeric>::value, "Numeric in cpp::set_bit should be an unsigned type.");

        numeric |= static_cast<Numeric>(static_cast<Numeric>(1U) << bit);
        return numeric;
    }

    /*!
     * \brief Clears the bit bit in numeric.
     * \param numeric The number to have its bit bit cleared.
     * \param bit The bit to clear in numeric. [0..bits(Numeric))
     * \return A reference to 'numeric'.
     * \warning The value in bit must not be larger than the amount of bits in
     *          Numeric - 1.
     * \note When using MSVC the function is only constexpr enabled with msvc17
     *       and newer.
     **/
    template <typename Numeric>
#if (CPP_COMPILER_IS_NOT(CPP_COMPILER_MSVC) || (CPP_COMPILER_VERSION_IS_ATLEAST(19, 11, 0)))
    constexpr
#else
    inline
#endif
            Numeric&
            clear_bit(Numeric& numeric, Numeric bit) noexcept
    {
        static_assert(std::is_unsigned<Numeric>::value, "Numeric in cpp::clear_bit should be an unsigned type.");

        numeric &= static_cast<Numeric>(~(static_cast<Numeric>(1U) << bit));
        return numeric;
    }

    /*!
     * \brief Toggles the bit bit in numeric.
     * \param numeric The number to have its bit bit toggled.
     * \param bit The bit in numeric to toggle. [0..bits(Numeric))
     * \return A reference to 'numeric'.
     * \warning Do not pass a value in bit that is larger than
     *          the number of bits in Numeric - 1.
     * \note When using MSVC the function is only constexpr enabled with msvc17
     *       and newer.
     *
     * Toggles the bit that was passed into the parameter bit in the
     * numeric (first parameter). If the bit bit in numeric is 1 it will be
     * 0 after having executed this function. If the bit bit in numeric is 0 it
     * will be 1 after having executed this function.
     **/
    template <typename Numeric>
#if (CPP_COMPILER_IS_NOT(CPP_COMPILER_MSVC) || (CPP_COMPILER_VERSION_IS_ATLEAST(19, 11, 0)))
    constexpr
#else
    inline
#endif
            Numeric&
            toggle_bit(Numeric& numeric, Numeric bit) noexcept
    {
        static_assert(std::is_unsigned<Numeric>::value, "Numeric in pl::toggle_bit should be an unsigned type.");

        numeric ^= static_cast<Numeric>(static_cast<Numeric>(1U) << bit);
        return numeric;
    }

    /*!
     * \brief Determines whether or not the bit bit in numeric is set.
     * \param numeric The number in which to check the bit bit.
     * \param bit The bit that is to be checked in number. [0..bits(Numeric))
     * \return true if the bit bit in numeric is set; false otherwise.
     * \warning Do not pass a value into the parameter bit that is larger than
     *          the number of bits in Numeric - 1.
     **/
    template <typename Numeric>
    constexpr bool is_bit_set(Numeric numeric, Numeric bit) noexcept
    {
        static_assert(std::is_unsigned<Numeric>::value, "Numeric in pl::is_bit_set should be an unsigned type.");

        return ((numeric & (static_cast<Numeric>(1U) << bit)) != 0);
    }
} // namespace cpp

CPP_GCC_SUPPRESS_WARNING_POP

#endif //INCG_CPPLIB_BIT_HPP
