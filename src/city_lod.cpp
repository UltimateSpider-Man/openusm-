#include "city_lod.h"

#include "common.h"
#include "func_wrapper.h"

VALIDATE_SIZE(city_lod, 8u);

city_lod::city_lod(const char *a1) {
    THISCALL(0x00550420, this, a1);
}
