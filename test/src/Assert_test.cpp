#include "cpp/Assert.hpp"
#include "doctest.h"

#include <string>

CPP_DEFINE_EXCEPTION_TYPE(TestExcept, std::runtime_error);

TEST_CASE("define exception type")
{
    CHECK_THROWS_AS(throw TestExcept("Test"), TestExcept);
    CHECK_THROWS_AS(throw TestExcept(std::string{"Test"}), TestExcept);
}

TEST_CASE("throw with source info")
{
    CHECK_THROWS_AS(CPP_THROW_WITH_SOURCE_INFO(TestExcept, "Test"), TestExcept);
    CHECK_THROWS_AS(CPP_THROW_WITH_SOURCE_INFO(std::runtime_error, "test"), std::runtime_error);
}

TEST_CASE("throw if null")
{
    int* p1 = nullptr;
    int  i  = 5;
    int* p2 = &i;

    CHECK_THROWS_AS(CPP_THROW_IF_NULL(p1), cpp::NullPointerException);
    CHECK_NOTHROW(CPP_THROW_IF_NULL(p2));
}

TEST_CASE("not yet implemented") { CHECK_THROWS_AS(CPP_NOT_YET_IMPLEMENTED, cpp::NotYetImplementedException); }

TEST_CASE("check pre")
{
    CHECK_THROWS_AS(CPP_CHECK_PRE(false), cpp::PreconditionViolationException);
    CHECK_THROWS_AS(CPP_CHECK_PRE_MSG(false, "Failed"), cpp::PreconditionViolationException);
    CHECK_NOTHROW(CPP_CHECK_PRE(true));
    CHECK_NOTHROW(CPP_CHECK_PRE_MSG(true, "Failed"));

    // Debug
#if defined(CPP_DEBUG)
    CHECK_THROWS_AS(CPP_DBG_CHECK_PRE(false), cpp::PreconditionViolationException);
    CHECK_THROWS_AS(CPP_DBG_CHECK_PRE_MSG(false, "Failed"), cpp::PreconditionViolationException);
#else
    CHECK_NOTHROW(CPP_DBG_CHECK_PRE(false));
    CHECK_NOTHROW(CPP_DBG_CHECK_PRE_MSG(false, "Failed"));
#endif
    CHECK_NOTHROW(CPP_DBG_CHECK_PRE(true));
    CHECK_NOTHROW(CPP_DBG_CHECK_PRE_MSG(true, "Failed"));
}

TEST_CASE("check pos")
{
    CHECK_THROWS_AS(CPP_CHECK_POST(false), cpp::PostconditionViolationException);
    CHECK_THROWS_AS(CPP_CHECK_POST_MSG(false, "Failed"), cpp::PostconditionViolationException);
    CHECK_NOTHROW(CPP_CHECK_POST(true));
    CHECK_NOTHROW(CPP_CHECK_POST_MSG(true, "Failed"));

    // Debug
#if defined(CPP_DEBUG)
    CHECK_THROWS_AS(CPP_DBG_CHECK_POST(false), cpp::PostconditionViolationException);
    CHECK_THROWS_AS(CPP_DBG_CHECK_POST_MSG(false, "Failed"), cpp::PostconditionViolationException);
#else
    CHECK_NOTHROW(CPP_DBG_CHECK_POST(false));
    CHECK_NOTHROW(CPP_DBG_CHECK_POST_MSG(false, "Failed"));
#endif
    CHECK_NOTHROW(CPP_DBG_CHECK_POST(true));
    CHECK_NOTHROW(CPP_DBG_CHECK_POST_MSG(true, "Failed"));
}

TEST_CASE("Assert")
{
    CHECK_THROWS_AS(CPP_ASSERT(false), cpp::AssertionViolationException);
    CHECK_THROWS_AS(CPP_ASSERT_MSG(false, "Failed"), cpp::AssertionViolationException);
    CHECK_NOTHROW(CPP_ASSERT(true));
    CHECK_NOTHROW(CPP_ASSERT_MSG(true, "Failed"));

    // Debug
#if defined(CPP_DEBUG)
    CHECK_THROWS_AS(CPP_DBG_ASSERT(false), cpp::AssertionViolationException);
    CHECK_THROWS_AS(CPP_DBG_ASSERT_MSG(false, "Failed"), cpp::AssertionViolationException);
#else
    CHECK_NOTHROW(CPP_DBG_ASSERT(false));
    CHECK_NOTHROW(CPP_DBG_ASSERT_MSG(false, "Failed"));
#endif
    CHECK_NOTHROW(CPP_DBG_ASSERT(true));
    CHECK_NOTHROW(CPP_DBG_ASSERT_MSG(true, "Failed"));
}

TEST_CASE("check bounds")
{
    int i = 5;

    CHECK_THROWS_AS(CPP_CHECK_BOUNDS(i, 6, 10), cpp::IndexOutOfBoundsException);
    CHECK_THROWS_AS(CPP_CHECK_BOUNDS(i, 0, 4), cpp::IndexOutOfBoundsException);

    CHECK_NOTHROW(CPP_CHECK_BOUNDS(i, 0, 5));
    CHECK_NOTHROW(CPP_CHECK_BOUNDS(i, 5, 5));
    CHECK_NOTHROW(CPP_CHECK_BOUNDS(i, 5, 10));

    // Debug
#if defined(CPP_DEBUG)
    CHECK_THROWS_AS(CPP_DBG_CHECK_BOUNDS(i, 6, 10), cpp::IndexOutOfBoundsException);
    CHECK_THROWS_AS(CPP_DBG_CHECK_BOUNDS(i, 0, 4), cpp::IndexOutOfBoundsException);
#else
    CHECK_NOTHROW(CPP_DBG_CHECK_BOUNDS(i, 6, 10));
    CHECK_NOTHROW(CPP_DBG_CHECK_BOUNDS(i, 0, 4));
#endif

    CHECK_NOTHROW(CPP_DBG_CHECK_BOUNDS(i, 0, 5));
    CHECK_NOTHROW(CPP_DBG_CHECK_BOUNDS(i, 5, 5));
    CHECK_NOTHROW(CPP_DBG_CHECK_BOUNDS(i, 5, 10));
}
