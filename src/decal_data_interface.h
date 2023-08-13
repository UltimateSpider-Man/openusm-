#pragma once

#include "generic_interface.h"
#include "float.hpp"

struct conglomerate;

struct decal_data_interface : generic_interface {
    conglomerate *field_4;
    bool field_8;
    char field_C[0x74];

    decal_data_interface();

    bool is_dynamic() const;

    //0x004D1CC0
    static void frame_advance_all_decal_interfaces(Float a1);
};
