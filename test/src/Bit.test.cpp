#include "doctest.h"
#include <cpp/Bit.hpp>
#include <cstdint>

TEST_CASE("bits_test")
{
    static constexpr std::uint8_t low_bit{0U};

    static constexpr std::uint8_t high_bit{(sizeof(std::uint8_t) * CHAR_BIT) - 1U};

    std::uint8_t val{0U};

    for (std::uint8_t i{low_bit}; i <= high_bit; ++i) { CHECK_UNARY_FALSE(cpp::is_bit_set(val, i)); }

    CHECK(cpp::set_bit(val, low_bit) == 0b0000'0001);
    CHECK_UNARY(cpp::is_bit_set(val, low_bit));
    CHECK(cpp::set_bit(val, low_bit) == 0b0000'0001);
    CHECK_UNARY(cpp::is_bit_set(val, low_bit));
    CHECK(cpp::clear_bit(val, low_bit) == 0b0000'0000);
    CHECK_UNARY_FALSE(cpp::is_bit_set(val, low_bit));
    CHECK(cpp::clear_bit(val, low_bit) == 0b0000'0000);
    CHECK_UNARY_FALSE(cpp::is_bit_set(val, low_bit));
    CHECK(cpp::toggle_bit(val, low_bit) == 0b000'0001);
    CHECK_UNARY(cpp::is_bit_set(val, low_bit));
    CHECK(cpp::toggle_bit(val, low_bit) == 0b000'0000);
    CHECK_UNARY_FALSE(cpp::is_bit_set(val, low_bit));
}
