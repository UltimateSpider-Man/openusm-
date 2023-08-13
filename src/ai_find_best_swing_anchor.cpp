#include "ai_find_best_swing_anchor.h"

#include "ai_state_swing.h"
#include "entity.h"
#include "func_wrapper.h"
#include "glass_house_manager.h"
#include "line_info.h"
#include "local_collision.h"
#include "quick_anchor_info.h"
#include "subdivision_node_obb_base.h"
#include "sweet_cone.h"
#include "utility.h"
#include "vector3d.h"
#include "vector4d.h"

#include <cassert>
#include <cmath>

swing_anchor_finder::swing_anchor_finder(Float a1, Float a2, Float a3, Float a4, Float a5, Float a6) {
    this->field_0 = a1;
    this->field_4 = a2;
    this->sweet_spot_distance = a3;
    this->field_C = a4;
    this->field_10 = a5;
    this->field_1C = a6;
    this->web_min_length = std::sqrt(a4);
    this->web_max_length = std::sqrt(a5);
    this->field_20 = std::sqrt(a6);
}

void swing_anchor_finder::set_max_pull_length(Float length) {
    assert(length >= 0.0f && length < 30.0f &&
           "Max pull length sanity check failed. Please inspect the callstack.");

    this->field_20 = length;
}

bool is_a_visible_swing_spot(const vector3d &a1,
                             const vector3d &a2,
                             local_collision::primitive_list_t **a1a,
                             local_collision::primitive_list_t ***a3) {
    line_info line{};

    line.field_0 = a1;
    line.field_C = a2;

    auto local_vec3 = line.field_0 - line.field_C;
    local_vec3.normalize();

    local_vec3 *= LARGE_EPSILON;

    line.field_C += local_vec3;

    auto v11 = !local_collision::test_line_intersection_ex(a1a, line, a3);

    return v11;
}

bool swing_anchor_finder::accept_swing_point(const quick_anchor_info &info,
                                             const sweet_cone_t &sweet_cone,
                                             const Float &a4,
                                             Float a5,
                                             Float *arg10,
                                             local_collision::primitive_list_t **a7,
                                             local_collision::primitive_list_t ***a8) const {
    if constexpr (0) {
        vector3d normal = info.m_normal;

        assert(std::abs(normal.length() - 1.0f) < EPSILON);

        static auto live_in_glass_house_flag = glass_house_manager::is_enabled();

        bool result;

        if (!live_in_glass_house_flag ||
            (result = glass_house_manager::is_point_in_glass_house(info.m_position))) {
            if (info.field_24 >= a4) {
                return false;
            }

            if (!sweet_cone.contains_point(info.m_position)) {
                return false;
            }

            auto v14 = info.m_position - sweet_cone.m_position;

            auto len2 = v14.length2();
            if (len2 <= this->field_C || len2 >= this->field_10 ||
                a5 + this->web_min_length >= info.m_position[1]) {
                return false;
            }

            vector3d v29{info.m_position[0], a5, info.m_position[2]};

            auto *v27 = local_collision::obbfilter_lineseg_test();
            auto *v26 = local_collision::entfilter_reject_all();

            normal *= 0.2f;

            auto v25 = v29 + normal;

            auto v20 = info.m_position + normal;

            vector3d v5, a6;
            auto v21 =
                find_intersection(v20, v25, *v26, *v27, &v5, &a6, nullptr, nullptr, nullptr, false);
            auto v22 = info.m_position[1];

            double v23;
            bool v24;
            if (v21) {
                v23 = v22 - v5[1];
                v24 = v23 >= this->web_min_length;
            } else {
                v23 = v22 - a5;
                v24 = v23 > this->web_min_length;
            }

            if (v24 && (*arg10 = v23, std::sqrt(len2) - *arg10 <= this->field_20) &&
                is_a_visible_swing_spot(sweet_cone.m_position, info.m_position, a7, a8)) {
                result = true;
            } else {
                result = false;
            }
        }

        return result;

    } else {
        return (bool) THISCALL(0x00464590, this, &info, &sweet_cone, &a4, a5, arg10, a7, a8);
    }
}

bool swing_anchor_finder::find_best_offset_anchor(entity *self,
                                                  const vector3d &a3,
                                                  const vector3d &a4,
                                                  find_best_anchor_result_t *result) {
    assert(self != nullptr);

    assert(self->is_an_actor());

    assert(result != nullptr);

    if constexpr (0) {
    } else {
        auto res = static_cast<bool>(THISCALL(0x00486280, this, self, &a3, &a4, result));

        if constexpr (0) {
            sp_log("");
            sp_log("%s, %s, %s",
                   result->m_point.to_string().c_str(),
                   result->m_normal.to_string().c_str(),
                   result->m_visual_point.to_string().c_str());
        }

        return res;
    }
}

bool swing_anchor_finder::find_best_anchor(entity *a1,
                                           const vector3d &a2,
                                           find_best_anchor_result_t *a3) {
    return this->find_best_offset_anchor(a1, a2, ZEROVEC, a3);
}

void swing_anchor_finder::remove_all_anchors() {
    ;
}

void swing_anchor_finder_patch() {
    if constexpr (0) {
        {
            FUNC_ADDRESS(address, &swing_anchor_finder::accept_swing_point);
            //REDIRECT(0x00486BD5, address);
            //REDIRECT(0x00486D2A, address);
        }

        {
            FUNC_ADDRESS(address, &sweet_cone_t::contains_point);
            REDIRECT(0x0046463E, address);
        }

        REDIRECT(0x00464731, find_intersection);

        {
            FUNC_ADDRESS(address, &subdivision_node_obb_base::find_closest_point_on_visible_faces);
            REDIRECT(0x0048685C, address);
        }
    }
}
