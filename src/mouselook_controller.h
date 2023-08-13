#pragma once

#include "controller.h"

#include "float.hpp"
#include "variable.h"

struct motion_control_system;
struct theta_and_psi_mcs;
struct entity_base;

struct mouselook_controller : controller {
    motion_control_system *field_8;
    theta_and_psi_mcs *field_C;
    entity_base *field_10;
    int field_14;

    mouselook_controller();

    //0x00528BB0
    //virtual
    void frame_advance(Float a2);
};

extern Var<mouselook_controller *> g_mouselook_controller;
