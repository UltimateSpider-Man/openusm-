#pragma once

#include "polytube.h"

struct swinger_t;

struct web_polytube : polytube {
    swinger_t *field_178;

    web_polytube(swinger_t *a1, const string_hash &a2, uint32_t a3);

    //0x0044BAD0
    /* virtual */ void render(Float a2);

    //0x004775A0
    /* virtual */ void rebuild_web();
};

extern void web_polytube_patch();
