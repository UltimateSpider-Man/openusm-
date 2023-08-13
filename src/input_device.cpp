#include "input_device.h"

#include "common.h"
#include "vtbl.h"

VALIDATE_SIZE(input_device, 0x8);

input_device::input_device() {
    m_vtbl = 0x0088E4D0;
    this->field_4 = -1;
}

uint8_t input_device::normalize(int a1) {
    return a1;
}

bool input_device::is_connected() {
    auto &is_connected = get_vfunc(m_vtbl, 0x2C);

    return (bool) is_connected(this);
}

int input_device::get_axis_id(int a1) {
    auto &get_axis_id = get_vfunc(m_vtbl, 0x10);

    return get_axis_id(this, a1);
}

float input_device::get_axis_delta(int a2, int a3) {
    auto &get_axis_delta = get_vfunc(m_vtbl, 0x1C);

    return (float) get_axis_delta(this, a2, a3);
}

float input_device::get_axis_old_state(int a2, int a3) {
    auto &get_axis_old_state = get_vfunc(m_vtbl, 0x18);

    return (float) get_axis_old_state(this, a2, a3);
}

float input_device::get_axis_state(int a2, int a3) {
    auto &get_axis_state = get_vfunc(m_vtbl, 0x14);

    return (float) get_axis_state(this, a2, a3);
}

int input_device::get_id() const
{
    auto &get_id = get_vfunc(m_vtbl, 0x8);

    return get_id(this);
}
