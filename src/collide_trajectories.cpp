#include "collide_trajectories.h"

#include "actor.h"
#include "collide_aux.h"
#include "collision_capsule.h"
#include "fixed_pool.h"
#include "func_wrapper.h"
#include "intersected_trajectory.h"
#include "intraframe_trajectory.h"
#include "line_segment.h"
#include "local_collision.h"
#include "primitive_query_token.h"
#include "scratchpad_stack.h"
#include "stack_allocator.h"

#include <cmath>

static Var<fixed_pool> stru_937580{0x00937580};

sphere compute_bounding_sphere_for_trajectory_and_intersected_trajectories(
    intraframe_trajectory_t *trj) {
    assert(trj != nullptr);

    auto v15 = trj->get_bounding_sphere();

    intraframe_trajectory_t *i = nullptr;
    for (auto *iter = trj->field_168; iter != nullptr; iter = iter->field_4) {
        assert(iter->trj != nullptr);

        if (iter->trj != i) {
            auto v16 = iter->trj->get_bounding_sphere();
            auto a2a = v15.radius + v16.radius;

            vector3d center;
            float radius;
            sub_5628F0(v15.center, a2a, v16.center, a2a, center, radius);
            v15.center = center;
            v15.radius = radius;
        }

        i = iter->trj;
    }

    for (auto *iter = trj->field_168; iter != nullptr; iter = iter->field_4) {
        intersected_trajectory_t::pool().set(iter);
    }

    trj->field_168 = nullptr;

    return v15;
}

void sub_602E30(local_collision::primitive_list_t *a1, intraframe_trajectory_t *trj) {
    while (a1 != nullptr) {
        if (a1->is_entity()) {
            for (auto *i = trj; i != nullptr; i = i->field_15C) {
                if (a1->field_4.ent == i->ent && a1->field_8 == i->field_13C) {
                    a1->field_10 = i;
                }
            }
        }

        a1 = a1->field_0;
    }
}

bool need_to_roll_back_rotation(const capsule &a3,
                                const capsule &a4,
                                local_collision::primitive_list_t *a1) {
    auto v5 = (a3.end - a4.end);
    if (v5.length2() < 0.0000000099999991) {
        return false;
    }

    capsule a3a{a3.end, a4.end, LARGE_EPSILON};

    auto v18 = a3a.end - a3a.base;
    auto v17 = v18.length();
    if (v17 > EPSILON) {
        v18 /= v17;
    }

    auto v10 = a3a.end + v18 * LARGE_EPSILON;

    auto v9 = a3a.base - v18 * LARGE_EPSILON;

    line_segment_t lif{v9, v10};
    return local_collision::get_closest_line_intersection(a1, &lif, false, nullptr, nullptr, nullptr);
}

void roll_back_rotation_and_rel_capsule_if_tunnelled(intraframe_trajectory_t *trj,
                                                     primitive_query_token_t *token) {
    if (trj->is_capsule) {
        assert(trj->world_po0.is_valid());

        assert(trj->world_po1.is_valid());

        auto *v5 = token->field_38;
        if (need_to_roll_back_rotation(token->field_0, token->field_1C, v5)) {
            auto pos = trj->world_po1.get_position();

            trj->world_po1 = trj->world_po0;
            trj->world_po1.set_position(pos);

            if (trj->is_capsule) {
                trj->get_capsule().rel_cap = trj->my_abs_cap0;
            }

            trj->final_relcap = &trj->relcap0;
            trj->field_165 = true;
            trj->my_abs_cap1 = trj->my_abs_cap0;

            auto v12 = 1.f / trj->field_14C;

            vector3d v14;
            v14[0] = (trj->world_po1.m[3][0] - trj->world_po0.m[3][0]) * v12;
            v14[1] = (trj->world_po1.m[3][1] - trj->world_po0.m[3][1]) * v12;
            v14[2] = (trj->world_po1.m[3][2] - trj->world_po0.m[3][2]) * v12;
            trj->field_140 = v14;
        } else {
            auto pos = trj->world_po0.get_position();

            trj->world_po0 = trj->world_po1;

            trj->world_po0.set_position(pos);

            if (trj->is_capsule) {
                trj->get_capsule().rel_cap = trj->my_abs_cap1;
            }

            trj->final_relcap = &trj->relcap1;
            trj->my_abs_cap0 = trj->my_abs_cap1;
        }

        for (auto *v8 = v5; v8 != nullptr; v8 = v8->field_0) {
            local_collision::primitive_list_t::pool().set(v8);
        }
    }
}

local_collision::primitive_list_t *query_potential_collision_primitives(
    const capsule &, const capsule &a3, actor *a4, intraframe_trajectory_t *eax0) {}

void resolve_rotations(intraframe_trajectory_t *a2, int a1) {
    if constexpr (1) {
        stack_allocator allocator;
        scratchpad_stack::save_state(&allocator);
        auto *token = (primitive_query_token_t *) scratchpad_stack::stk().current;
        if (scratchpad_stack::stk().current == scratchpad_stack::stk().segment) {
            tlScratchpadLocked() = true;
        }

        auto v4 = 0x3C * a1 + scratchpad_stack::stk().alignment - 1;

        scratchpad_stack::stk().current += ~(scratchpad_stack::stk().alignment - 1) & v4;

        for (auto *trj = a2; trj != nullptr; trj = trj->field_15C) {
            if (a2->is_capsule) {
                assert(trj->world_po0.is_valid());

                assert(trj->world_po1.is_valid());

                token->field_0 = trj->get_abs_cap0();
                token->field_1C = trj->get_abs_cap1();

                auto v9 = token->field_1C.base - token->field_0.base;

                token->field_1C.base = token->field_1C.base - v9;

                token->field_1C.end = token->field_1C.end - v9;

                auto *v11 = query_potential_collision_primitives(token->field_0,
                                                                 token->field_1C,
                                                                 trj->ent,
                                                                 a2);
                token->field_38 = v11;
                sub_602E30(v11, a2);
                ++token;

            } else {
                token->field_38 = nullptr;
                ++token;
            }
        }

        for (auto *trj = a2; trj != nullptr; trj = trj->field_15C) {
            roll_back_rotation_and_rel_capsule_if_tunnelled(trj, token++);
        }

        scratchpad_stack::restore_state(allocator);

    } else {
        CDECL_CALL(0x00604A90, a2, a1);
    }
}

void resolve_collisions(intraframe_trajectory_t **a1, Float a2) {
    CDECL_CALL(0x00604E30, a1, a2);
}

void resolve_moving_pendulums(intraframe_trajectory_t *a1, Float a2) {
    CDECL_CALL(0x00605050, a1, a2);
}
