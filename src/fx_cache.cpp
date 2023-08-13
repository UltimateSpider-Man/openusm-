#include "fx_cache.h"

#include "func_wrapper.h"

fx_cache::fx_cache() {}

void fx_cache::frame_advance(Float a3) {
    THISCALL(0x004D4FB0, this, a3);
}
