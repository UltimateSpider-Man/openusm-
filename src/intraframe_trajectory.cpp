#include "intraframe_trajectory.h"

#include "actor.h"
#include "collide_aux.h"
#include "collision_geometry.h"
#include "func_wrapper.h"
#include "sphere.h"

#include <cassert>
#include <cmath>

intraframe_trajectory_t::intraframe_trajectory_t() {}

capsule xform3d_1_capsule(const matrix4x4 &mat, const capsule &p_cap) {
    capsule cap;
    cap.radius = p_cap.radius;

    cap.base = mat * p_cap.base;

    cap.end = mat * p_cap.end;

    return cap;
}

capsule intraframe_trajectory_t::get_abs_cap0() {
    assert(is_capsule);
    auto &v2 = this->world_po0.get_matrix();
    auto result = xform3d_1_capsule(v2, this->my_abs_cap0);
    return result;
}

capsule intraframe_trajectory_t::get_abs_cap1() {
    assert(is_capsule);
    auto &v2 = this->world_po1.get_matrix();
    auto result = xform3d_1_capsule(v2, this->my_abs_cap1);
    return result;
}

collision_geometry *intraframe_trajectory_t::get_colgeom() {
    assert(ent->get_colgeom());

    return this->ent->get_colgeom();
}

collision_capsule &intraframe_trajectory_t::get_capsule() {
    assert(ent->get_colgeom());

    assert(ent->get_colgeom()->get_type() == collision_geometry::CAPSULE);

    return *bit_cast<collision_capsule *>(this->get_colgeom());
}

sphere intraframe_trajectory_t::get_bounding_sphere() {
    sphere a3{};

    if (this->is_capsule) {
        capsule cap1 = this->get_abs_cap1();

        capsule cap0 = this->get_abs_cap0();

        compute_bounding_sphere_for_two_capsules(cap0, cap1, &a3);
    } else {
        assert(world_po0.is_valid());
        assert(world_po1.is_valid());

        auto colgeom_radius = this->ent->get_colgeom_radius();

        assert(ent->get_colgeom() != nullptr);

        vector3d v9 = this->ent->get_colgeom()->get_local_space_bounding_sphere_center();

        vector3d v6 = this->world_po1.get_matrix() * v9;

        vector3d v4 = this->world_po0.get_matrix() * v9;

        sub_5628F0(v4, colgeom_radius, v6, colgeom_radius, a3.center, a3.radius);
    }

    return a3;
}
