#pragma once

#include <cstdint>

#include "als_inode.h"
#include "base_state_machine.h"

#include <vector.hpp>

struct actor;
struct conglomerate;
struct animation_controller;

namespace als {

struct animation_logic_system_shared;

struct animation_logic_system {
    std::intptr_t m_vtbl = 0x00881460;
    int field_4;
    _std::vector<als::state_machine *> field_8;
    base_state_machine field_18;
    actor *field_6C;
    animation_controller *the_controller;
    int *field_74;
    void *field_78;
    bool field_7C;

    //0x004ABB80
    animation_logic_system(actor *a1);

    //0x00498F70
    void enter_biped_physics();

    void exit_biped_physics();

    //0x004ABC60
    //virtual
    int create_instance_data(animation_logic_system_shared *a2);

    //0x00498D10
    /* virtual */ bool frame_advance_should_do_frame_advance(Float a2);

    //0x0049CC90
    //virtual
    void frame_advance_post_logic_processing(Float a2);

    //0x004A63F0
    /* virtual */ state_machine *get_als_layer(layer_types a2);

    //0x00498F30
    //virtual
    void change_mocomp();
};

struct animation_logic_system_interface {
    //0x00492FC0
    void force_update(Float a2);
};

} // namespace als

extern void animation_logic_system_patch();
