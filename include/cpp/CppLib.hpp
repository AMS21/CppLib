#pragma once

#include "Stringify.hpp"

#define CPP_CREATE_VERSION(major, minor, patch) ((major * 100000) + (minor * 100) + patch)

#define CPP_VERSION_MAJOR 1
#define CPP_VERSION_MINOR 0
#define CPP_VERSION_PATCH 0

#define CPP_VERSION CPP_CREATE_VERSION(CPP_VERSION_MAJOR, CPP_VERSION_MINOR, CPP_VERSION_PATCH)

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
