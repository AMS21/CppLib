#include "cpp/Assume.hpp"
#include "cpp/Warning.hpp"
#include <doctest.h>

TEST_CASE("cpp.Assume")
{
    int a = 16;

    CPP_ASSUME((a % 8) == 0);

    CHECK_EQ((a % 8), 0);
}
