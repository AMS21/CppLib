#include "cpp/CppLib.hpp"
#include "doctest.h"
#include <string>

TEST_CASE("CppLib.VersionMacros")
{
    // Check that all macros are defined in the first place
#if !defined(CPP_VERSION_MAJOR) || !defined(CPP_VERSION_MINOR) || !defined(CPP_VERSION_PATCH) ||                       \
        !defined(CPP_VERSION) || !defined(CPP_VERSION_STR)
    FAIL("Not all required macros are defined!");
#endif

    INFO("CPP_VERSION: " << TO_LVALUE(CPP_VERSION));

    CHECK_EQ(CPP_VERSION % 100, CPP_VERSION_PATCH);
    CHECK_EQ(CPP_VERSION / 100 % 1000, CPP_VERSION_MINOR);
    CHECK_EQ(CPP_VERSION / 100000, CPP_VERSION_MAJOR);
}

TEST_CASE("CppLib.ConstexprValues")
{
    CHECK_EQ(CPP_VERSION_MAJOR, cpp::VersionMajor);
    CHECK_EQ(CPP_VERSION_MINOR, cpp::VersionMinor);
    CHECK_EQ(CPP_VERSION_PATCH, cpp::VersionPatch);

    CHECK_EQ(CPP_VERSION, cpp::Version);

    CHECK_EQ(std::string(CPP_VERSION_STR), std::string(cpp::VersionStr));
}
