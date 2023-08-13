#pragma once

#include "entity_base_vhandle.h"

#include "vector3d.h"

struct rigid_body_constraint_distance;
struct physical_interface;
struct rigid_body;

struct pendulum : entity_base_vhandle {
    //0x004BD930
    pendulum();

    vector3d field_4;
    vector3d field_10;
    float m_constraint;
    float field_20;
    rigid_body_constraint_distance *biped_physics_constraint;
    rigid_body *pivot_rigid_body;
    int field_2C;
    int field_30;
    bool field_34;

    float get_constraint() const {
        return this->m_constraint;
    }

    void set_constraint(Float _constraint);

    void set_constraint_lenience(Float a2);

    //0x004BD970
    void set_attach_limb(int l);

    //0x004DF780
    [[nodiscard]] vector3d &get_pivot_abs_pos();

    //0x004DF9A0
    void create_biped_constraint(physical_interface *a2);

    void sub_4BD990(physical_interface *a2);

    void update_biped_constraint(physical_interface *a2);
};
