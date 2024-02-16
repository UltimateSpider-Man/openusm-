#include "collision_geometry.h"

#include "actor.h"
#include "common.h"
#include "vtbl.h"

VALIDATE_SIZE(collision_geometry, 0x10);

collision_geometry::collision_geometry() {
    this->field_8 = false;
    this->field_9 = false;
    this->field_8 = false;
    this->field_9 = true;
    this->field_C = 2;
}

void collision_geometry::xform(const po &a2) {
    this->field_8 = 1;
}

void collision_geometry::split_xform(const po &a1, const po &a2, const po &a3, int a4, int a5) {
    ;
}

void collision_geometry::split_xform(const po &a1, const po &a2, int a3) {
    ;
}

void collision_geometry::get_colgeom_radius() {
    this->owner->get_colgeom_radius();
}

vector3d collision_geometry::get_local_space_bounding_sphere_center() {
    if constexpr (1) {
        void (__fastcall *func)(collision_geometry *, void *, vector3d *) = CAST(func, get_vfunc(m_vtbl, 0x18));

        vector3d out;
        func(this, nullptr, &out);

        return out;

    } else {
        return vector3d{0, 0, 0};
    }
}

float collision_geometry::get_bounding_sphere_radius() {
    return 0.0;
}

float collision_geometry::get_core_radius() {
    return 0.0;
}

const vector3d &collision_geometry::get_abs_position() const {
    assert(owner != nullptr);

    return this->owner->get_abs_position();
}

vector3d *collision_geometry::get_pivot() {
    static vector3d ZEROVEC{0, 0, 0};

    return &ZEROVEC;
}

int collision_geometry::get_type() {
    int (__fastcall *func)(collision_geometry *) = CAST(func, get_vfunc(m_vtbl, 0x2C));

    return func(this);
}

bool collision_geometry::is_pivot_valid() {
    return false;
}

void collision_geometry::un_mash(generic_mash_header *, void *, generic_mash_data_ptrs *) {
    this->owner = nullptr;
}

bool collision_geometry::is_dynamic() {
    return this->field_9;
}
