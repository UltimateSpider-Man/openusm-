#include "camera.h"

#include "common.h"
#include "custom_math.h"
#include "entity.h"
#include "func_wrapper.h"
#include "geometry_manager.h"
#include "oldmath_po.h"
#include "utility.h"
#include "vector3d.h"
#include "vtbl.h"

#include <cmath>

VALIDATE_SIZE(camera, 0xCCu);

camera::camera([[maybe_unused]] entity *a2, const string_hash &a3)
    : actor(a3, 0)
#if 1
{

#else
{
    THISCALL(0x00577970, this, a2, &a3);

#endif
}

void camera::sync(camera &a2) {
    if constexpr (1) {
        auto &func = get_vfunc(m_vtbl, 0x294);

        func(this, &a2);

    } else {
        THISCALL(0x0057EFD0, this, &a2);
    }
}

float camera::get_fov() {
    float __thiscall (*func)(void *) = CAST(func, get_vfunc(m_vtbl, 0x2A0));
    return func(this);
}

float camera::get_far_plane_factor() {
    float __thiscall (*func)(void *) = CAST(func, get_vfunc(m_vtbl, 0x2A8));
    return func(this);
}

void camera::adjust_geometry_pipe(bool scene_analyzer) {
    sp_log("adjust_geometry_pipe: ");

    auto &v10 = this->get_abs_position();
    auto &v3 = this->get_abs_po();
    auto &v4 = v3.get_matrix();
    vector3d v5 = v4[2];

    vector3d center = v5 + v10;
    auto &v6 = this->get_abs_po();
    auto &v7 = v6.get_matrix();
    vector3d up = v7[1];
    if (scene_analyzer) {
        assert(!is_externally_controlled());

        matrix4x4 v12;

        auto &eye = this->get_abs_position();
        geometry_manager::set_look_at(&v12, eye, center, up);
        geometry_manager::set_xform((geometry_manager::xform_t) 8, v12);
    }
    else
    {
        auto &v9 = this->get_abs_position();
        geometry_manager::set_view(v9, center, up);
    }
}

float camera::compute_xz_projected_fov() {
    auto v6 = this->sub_57CB80();
    auto v1 = 1.f / geometry_manager::get_aspect_ratio();
    auto v5 = v1;
    auto v2 = std::cos(std::atan2(v1, 1.0) - std::abs(v6));
    if (v2 < v5) {
        v2 = v5;
    }

    auto v3 = std::atan2(v2 * std::sqrt(v5 * v5 + 1.f), 1.0);
    auto compensated_fov = v3 + v3 + EPSILON;

    assert(compensated_fov < PI);

    return compensated_fov;
}

bool camera::is_externally_controlled() {
    return this->is_flagged(0x400000);
}

void camera::get_look_and_up(vector3d *look, vector3d *up) {
    if (look != nullptr) {
        *look = this->get_abs_po().m[2];
    }

    if (up != nullptr) {
        *up = this->get_abs_po().m[1];
    }
}

void camera_patch() {
    FUNC_ADDRESS(address, &camera::adjust_geometry_pipe);
    SET_JUMP(0x00577AF0, address);
}
