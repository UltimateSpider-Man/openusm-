#pragma once

#include "mash_virtual_base.h"
#include "param_block.h"
#include "string_hash.h"

struct actor;
struct from_mash_in_place_constructor;

namespace ai {

struct ai_core;

struct info_node : mash_virtual_base {
    string_hash field_4;
    ai_core *field_8;
    actor *field_C;
    param_block field_10;

    //0x006D6F20
    info_node();

    //0x006D9930
    info_node(from_mash_in_place_constructor *a2);

    actor *get_actor();

    ~info_node() = default;

    //virtual
    bool does_need_advance() const;

    //virtual
    void frame_advance(Float a2);
};

} // namespace ai
