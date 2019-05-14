/*!
 * \file NamedType.hpp
 * \brief Exports the strongly typed class NamedType.
 *
**/
#pragma once

// Based on the excellent work from Jonathan Boccara on his NamedType library: https://github.com/joboccara/NamedType

// List of changes:
// Constructor is noexcept if constructing T is noexcept
// noexcept on get
// NamedType is default constructible if T is default constructible
// Added PostIncrementable
// Added Divisible
// Added Modulable

#include "Warning.hpp"
#include <iostream>    // std::basic_ostream
#include <memory>      // std::addressof
#include <type_traits> // std::remove_reference_t, std::enable_if, std::remove_reference_t
#include <utility>     // std::move, std::forward

// Enable empty base class optimization with multiple inheritance on Visual Studio.
#if defined(_MSC_VER) && _MSC_VER >= 1910
#    define CPP_EBCO __declspec(empty_bases)
#else
#    define CPP_EBCO
#endif

namespace cpp
{
    /// \cond detail
    namespace detail
    {
        template <typename T, template <typename> class crtpType>
        struct crtp
        {
            T&       underlying() { return static_cast<T&>(*this); }
            const T& underlying() const { return static_cast<const T&>(*this); }
        };

        template <typename T>
        using IsNotReference = typename std::enable_if<!std::is_reference<T>::value, void>::type;
    } // namespace detail
    /// \endcond

    template <typename T, typename Parameter, template <typename> class... Skills>
    class CPP_EBCO NamedType : public Skills<NamedType<T, Parameter, Skills...>>...
    {
    public:
        using type = T; /// Underlying type of the NamedType

        // constructor
        template <typename T_ = T, typename = std::enable_if<std::is_default_constructible<T>::value, void>>
        constexpr NamedType() noexcept(std::is_nothrow_constructible<T>::value)
        {}

        explicit constexpr NamedType(const T& value) noexcept(std::is_nothrow_copy_constructible<T>::value)
            : mValue(value)
        {}

        template <typename T_ = T, typename = detail::IsNotReference<T_>>
        explicit constexpr NamedType(T&& value) noexcept(std::is_nothrow_move_constructible<T>::value)
            : mValue(std::move(value))
        {}

        // get
        [[nodiscard]] constexpr T& get() noexcept { return mValue; }

        [[nodiscard]] constexpr const T& get() const noexcept { return mValue; }

        // conversions
        using ref = NamedType<T&, Parameter, Skills...>;
        operator ref() { return ref(mValue); }

        struct argument
        {
            template <typename U>
            NamedType operator=(U&& value) const
            {
                CPP_GCC_SUPPRESS_WARNING_PUSH
                CPP_GCC_SUPPRESS_WARNING("-Weffc++")

                return NamedType(std::forward<U>(value));

                CPP_GCC_SUPPRESS_WARNING_POP
            }

            argument()                = default;
            argument(argument const&) = delete;
            argument(argument&&)      = delete;
            argument& operator=(argument const&) = delete;
            argument& operator=(argument&&) = delete;
        };

    private:
        T mValue{};
    };

    template <template <typename T> class StrongType, typename T>
    constexpr StrongType<T> make_named(const T& value)
    {
        return StrongType<T>(value);
    }

    //

    CPP_GCC_SUPPRESS_WARNING_PUSH
    CPP_GCC_SUPPRESS_WARNING("-Weffc++")

    template <typename T>
    struct PreIncrementable : detail::crtp<T, PreIncrementable>
    {
        T& operator++()
        {
            ++this->underlying().get();
            return this->underlying();
        }
    };

    template <typename T>
    struct PostIncrementable : detail::crtp<T, PostIncrementable>
    {
        T operator++(int) { return this->underlying().get()++; }
    };

    template <typename T>
    struct PreDecrementable : detail::crtp<T, PreDecrementable>
    {
        T& operator--()
        {
            --this->underlying().get();
            return this->underlying();
        }
    };

    template <typename T>
    struct PostDecrementable : detail::crtp<T, PostDecrementable>
    {
        T operator--(int) { return this->underlying().get()--; }
    };

    CPP_GCC_SUPPRESS_WARNING_POP

    template <typename T>
    struct Addable : detail::crtp<T, Addable>
    {
        T  operator+(const T& other) const { return T(this->underlying().get() + other.get()); }
        T& operator+=(const T& other)
        {
            this->underlying().get() += other.get();
            return this->underlying();
        }
    };

    template <typename T>
    struct Subtractable : detail::crtp<T, Subtractable>
    {
        T  operator-(const T& other) const { return T(this->underlying().get() - other.get()); }
        T& operator-=(const T& other)
        {
            this->underlying().get() -= other.get();
            return this->underlying();
        }
    };

    template <typename T>
    struct Multiplicable : detail::crtp<T, Multiplicable>
    {
        T  operator*(const T& other) const { return T(this->underlying().get() * other.get()); }
        T& operator*=(const T& other)
        {
            this->underlying().get() *= other.get();
            return this->underlying();
        }
    };

    template <typename T>
    struct Divisible : detail::crtp<T, Divisible>
    {
        T  operator/(const T& other) const { return T(this->underlying().get() / other.get()); }
        T& operator/=(const T& other)
        {
            this->underlying().get() /= other.get();
            return this->underlying();
        }
    };

    template <typename T>
    struct Modulable : detail::crtp<T, Modulable>
    {
        T  operator%(const T& other) const { return T(this->underlying().get() % other.get()); }
        T& operator%=(const T& other)
        {
            this->underlying().get() %= other.get();
            return this->underlying();
        }
    };

    template <typename T>
    struct BitWiseInvertable : detail::crtp<T, BitWiseInvertable>
    {
        T operator~() const { return T(~this->underlying().get()); }
    };

    template <typename T>
    struct BitWiseAndable : detail::crtp<T, BitWiseAndable>
    {
        T  operator&(const T& other) const { return T(this->underlying().get() & other.get()); }
        T& operator&=(const T& other)
        {
            this->underlying().get() &= other.get();
            return this->underlying();
        }
    };

    template <typename T>
    struct BitWiseOrable : detail::crtp<T, BitWiseOrable>
    {
        T  operator|(const T& other) const { return T(this->underlying().get() | other.get()); }
        T& operator|=(const T& other)
        {
            this->underlying().get() |= other.get();
            return this->underlying();
        }
    };

    template <typename T>
    struct BitWiseXorable : detail::crtp<T, BitWiseXorable>
    {
        T  operator^(const T& other) const { return T(this->underlying().get() ^ other.get()); }
        T& operator^=(const T& other)
        {
            this->underlying().get() ^= other.get();
            return this->underlying();
        }
    };

    template <typename T>
    struct BitWiseLeftShiftable : detail::crtp<T, BitWiseLeftShiftable>
    {
        T  operator<<(const T& other) const { return T(this->underlying().get() << other.get()); }
        T& operator<<=(const T& other)
        {
            this->underlying().get() <<= other.get();
            return this->underlying();
        }
    };

    template <typename T>
    struct BitWiseRightShiftable : detail::crtp<T, BitWiseRightShiftable>
    {
        T  operator>>(const T& other) const { return T(this->underlying().get() >> other.get()); }
        T& operator>>=(const T& other)
        {
            this->underlying().get() >>= other.get();
            return this->underlying();
        }
    };

    template <typename T>
    struct Negatable : detail::crtp<T, Negatable>
    {
        T operator-() const { return T(-this->underlying().get()); }
    };

    template <typename T>
    struct Comparable : detail::crtp<T, Comparable>
    {
        bool operator<(const T& other) const { return this->underlying().get() < other.get(); }
        bool operator>(const T& other) const { return other.get() < this->underlying().get(); }
        bool operator<=(const T& other) const { return !(other.get() < this->underlying().get()); }
        bool operator>=(const T& other) const { return !(*this < other); }
        bool operator==(const T& other) const { return !(*this < other) && !(other.get() < this->underlying().get()); }
        bool operator!=(const T& other) const { return !(*this == other); }
    };

    template <typename T>
    struct Printable : detail::crtp<T, Printable>
    {
        template <typename CharT>
        void print(std::basic_ostream<CharT>& os) const
        {
            os << this->underlying().get();
        }
    };

    template <typename CharT, typename T, typename Parameter, template <typename> class... Skills>
    std::basic_ostream<CharT>& operator<<(std::basic_ostream<CharT>&                os,
                                          const NamedType<T, Parameter, Skills...>& object)
    {
        object.print(os);
        return os;
    }

    template <typename Destination>
    struct ImplicitlyConvertibleTo
    {
        template <typename T>
        struct templ : detail::crtp<T, templ>
        {
            operator Destination() const { return this->underlying().get(); }
        };
    };

    template <typename T>
    struct Hashable
    {
        static constexpr bool is_hashable = true;
    };

    template <typename NamedType_>
    struct FunctionCallable;

    template <typename T, typename Parameter, template <typename> class... Skills>
    struct FunctionCallable<NamedType<T, Parameter, Skills...>>
        : detail::crtp<NamedType<T, Parameter, Skills...>, FunctionCallable>
    {
        operator T&() { return this->underlying().get(); }
        operator const T&() const { return this->underlying().get(); }
    };

    template <typename NamedType_>
    struct MethodCallable;

    template <typename T, typename Parameter, template <typename> class... Skills>
    struct MethodCallable<NamedType<T, Parameter, Skills...>>
        : detail::crtp<NamedType<T, Parameter, Skills...>, MethodCallable>
    {
        T*       operator->() { return std::addressof(this->underlying().get()); }
        T const* operator->() const { return std::addressof(this->underlying().get()); }
    };

    template <typename NamedType_>
    struct Callable : FunctionCallable<NamedType_>, MethodCallable<NamedType_>
    {};

    template <typename T>
    struct Arithmetic : PreIncrementable<T>,
                        PostIncrementable<T>,
                        PreDecrementable<T>,
                        PostDecrementable<T>,
                        Addable<T>,
                        Subtractable<T>,
                        Multiplicable<T>,
                        Divisible<T>,
                        Modulable<T>,
                        BitWiseInvertable<T>,
                        BitWiseAndable<T>,
                        BitWiseOrable<T>,
                        BitWiseXorable<T>,
                        BitWiseLeftShiftable<T>,
                        BitWiseRightShiftable<T>,
                        Negatable<T>,
                        Comparable<T>,
                        Printable<T>,
                        Hashable<T>
    {};
} // namespace cpp

namespace std
{
    template <typename T, typename Parameter, template <typename> class... Skills>
    struct hash<cpp::NamedType<T, Parameter, Skills...>>
    {
        using NamedType       = cpp::NamedType<T, Parameter, Skills...>;
        using checkIfHashable = typename std::enable_if<NamedType::is_hashable, void>::type;

        size_t operator()(const cpp::NamedType<T, Parameter, Skills...>& x) const noexcept
        {
            static_assert(noexcept(std::hash<T>()(x.get())), "hash function should not throw");

            return std::hash<T>()(x.get());
        }
    };
} // namespace std
