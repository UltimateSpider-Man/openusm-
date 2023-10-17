#pragma once

#include "log.h"

#include <cassert>

#define error(fmt, ...)             \
    {                               \
        sp_log(fmt, ##__VA_ARGS__); \
        assert(0);                  \
    }

