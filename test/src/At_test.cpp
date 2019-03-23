#include "cpp/At.hpp"
#include "doctest.h"
#include <cstdint>
#include <vector>

TEST_CASE("at - array")
{
    int arr[] = {0, 1, 2, 3, 4, 5};

    for (std::size_t i{0}; i < 6; ++i) { CHECK_EQ(cpp::at(arr, i), i); }

    // Out of Bounds access
#if defined(CPP_DEBUG)
    CHECK_THROWS_AS(cpp::at(arr, 6), cpp::IndexOutOfBoundsException);
#endif
}

TEST_CASE("at - container")
{
    std::vector<int> v{};

    for (int i{0}; i < 6; ++i) { v.emplace_back(i); }

    for (std::size_t i{0}; i < 6; ++i) { CHECK_EQ(cpp::at(v, i), i); }

    // Out of Bounds access
#if defined(CPP_DEBUG)
    CHECK_THROWS_AS(cpp::at(v, 6), cpp::IndexOutOfBoundsException);
#endif
}

TEST_CASE("at - initializer_lists")
{
    std::initializer_list<int> li{0, 1, 2, 3, 4, 5};

    for (std::size_t i{0}; i < 6; ++i) { CHECK_EQ(cpp::at(li, i), i); }

    // Out of Bounds access
#if defined(CPP_DEBUG)
    CHECK_THROWS_AS(cpp::at(li, 6), cpp::IndexOutOfBoundsException);
#endif
}
