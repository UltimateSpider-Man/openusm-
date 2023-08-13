#pragma once

#include "actor.h"

struct conglomerate_clone : actor {
    int field_C0;
    int field_C4;
    int field_C8;
    int field_CC;

    conglomerate_clone(string_hash const &a2, unsigned a3);
};
