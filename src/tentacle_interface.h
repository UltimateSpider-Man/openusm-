#pragma once

#include "generic_interface.h"

struct tentacle_interface : generic_interface
{
    char field_4[0x34];

    void initialize_polytubes();
};
