#pragma once

#include "Stringify.hpp"

#define CPP_VERSION_MAJOR 0
#define CPP_VERSION_MINOR 1
#define CPP_VERSION_PATCH 0

#define CPP_VERSION_STR                                                                                                \
    CPP_STRINGIFY(CPP_VERSION_MAJOR) "." CPP_STRINGIFY(CPP_VERSION_MINOR) "." CPP_STRINGIFY(CPP_VERSION_PATCH)
