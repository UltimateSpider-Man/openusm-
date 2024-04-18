#pragma once

#include "input_mgr.h"

#include <cstdint>

struct input_device {
    std::intptr_t m_vtbl;
    int field_4;

    input_device();

    //0x005B0A60
    //virtual
    uint8_t normalize(int a1);

    //virtual
    bool is_connected();

    //virtual
    int get_axis_id(int a1);

    //virtual
    float get_axis_delta(int a2, int a3);

    //virtual
    float get_axis_old_state(int a2, int a3);

    //virtual
    float get_axis_state(int a2, int a3);

    //virtual
    device_id_t get_id() const;
};
