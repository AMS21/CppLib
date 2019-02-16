#pragma once

#define CPP_DETAIL_GLUE(a, b) a##b

#define CPP_GLUE(a, b) CPP_DETAIL_GLUE(a, b)
