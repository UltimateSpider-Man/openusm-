#pragma once

#include "nal_system.h"

struct CharComponentBase : BaseComponent {
    int field_4;
    uint32_t field_8;
    const char *field_C;

    //virtual
    uint32_t GetType();
};

extern void CharComponentBase_patch();
