#pragma once

#include "Stringify.hpp"
#include "Versioning.hpp"

#define CPP_VERSION_MAJOR 1
#define CPP_VERSION_MINOR 2
#define CPP_VERSION_PATCH 0

#define CPP_VERSION CPP_VERSION_CREATE(CPP_VERSION_MAJOR, CPP_VERSION_MINOR, CPP_VERSION_PATCH)

#define CPP_VERSION_STR                                                                                                \
    CPP_STRINGIFY(CPP_VERSION_MAJOR) "." CPP_STRINGIFY(CPP_VERSION_MINOR) "." CPP_STRINGIFY(CPP_VERSION_PATCH)

namespace cpp
{
    constexpr unsigned VersionMajor{CPP_VERSION_MAJOR};
    constexpr unsigned VersionMinor{CPP_VERSION_MINOR};
    constexpr unsigned VersionPatch{CPP_VERSION_PATCH};

    constexpr unsigned Version{CPP_VERSION};

    constexpr char VersionStr[]{CPP_VERSION_STR};
} // namespace cpp
