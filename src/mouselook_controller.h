#pragma once

#include "controller.h"

#include "float.hpp"
#include "variable.h"

struct motion_control_system;
struct dolly_and_strafe_mcs;
struct theta_and_psi_mcs;
struct entity_base;
struct camera;

struct mouselook_controller : controller {
    motion_control_system *field_8;
    theta_and_psi_mcs *field_C;
    entity_base *field_10;
    int field_14;

    mouselook_controller(
        dolly_and_strafe_mcs *a2,
        theta_and_psi_mcs *a3,
        camera *a4);

    //0x0051D0E0
    void reset();

    //0x00528BB0
    //virtual
    void _frame_advance(Float a2);
};

extern Var<mouselook_controller *> g_mouselook_controller;
