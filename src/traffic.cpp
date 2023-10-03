#include "traffic.h"

#include "actor.h"
#include "common.h"
#include "func_wrapper.h"
#include "region.h"
#include "terrain.h"
#include "trace.h"
#include "traffic_path_graph.h"
#include "traffic_path_lane.h"
#include "wds.h"

VALIDATE_SIZE(traffic, 0x22Cu);

void traffic::sub_6DA3B0(Float a2, Float a3, Float a4) {
    auto &v4 = this->field_14C;
    v4[0] = a2;
    v4[1] = a3;
    v4[2] = a4;
}

void traffic::enable_traffic(bool a1, bool a2) {
    TRACE("traffic::enable_traffic");

    CDECL_CALL(0x006D33C0, a1, a2);
}

void traffic::get_closest_point_on_lane_with_facing(vector3d *a1, vector3d *a2, bool a3) {
    if constexpr (1) {
        auto *v3 = g_world_ptr()->the_terrain->sub_6DC8A0(*a1);
        if (v3 != nullptr) {
            auto it = v3->begin();
            auto end = v3->end();
            if (it != end) {
                traffic_path_lane *v8 = nullptr;

                vector3d a5;
                while (1) {
                    auto *v5 = *it;
                    auto *v6 = v5->get_traffic_path_graph();
                    auto v7 = v5->flags;
                    if ((v7 & 0x100) == 0 && (v7 & 0x40000) == 0) {
                        if (v6 != nullptr) {
                            v8 = v6->get_closest_or_farthest_lane(true,
                                                                  *a1,
                                                                  ZEROVEC,
                                                                  &a5,
                                                                  traffic_path_lane::eLaneType{
                                                                      static_cast<int>(!a3)},
                                                                  false,
                                                                  nullptr);
                            if (v8 != nullptr) {
                                break;
                            }
                        }
                    }

                    if (++it == end) {
                        return;
                    }
                }

                int tmp = 0;

                auto v26 = v8->get_node_before_point(a5, &tmp);
                auto v9 = tmp;
                vector3d node1;
                if (tmp < 1 || tmp < v8->field_C - 2) {
                    node1 = v8->sub_5E2000(tmp);
                    ++v9;
                } else {
                    node1 = v8->sub_5E2000(tmp - 1);
                }

                auto node2 = v8->sub_5E2000(v9);

                assert((node2 - node1).xz_length2() > EPSILON);

                v26 = node2 - node1;

                auto v17 = v26.normalized();

                *a2 = v17;

                *a1 = a5;
            }
        }
    } else {
        CDECL_CALL(0x006D0910, a1, a2, a3);
    }
}

bool traffic::is_unanimated_car(actor *a1) {
    if constexpr (1) {

        bool result = false;
        if ((a1->field_4 & 0x800) != 0) {
            auto *v1 = traffic::get_traffic_from_entity({a1->my_handle});
            if (v1 == nullptr || !v1->field_202) {
                result = true;
            }
        }

        return result;
    } else {
        return (bool) CDECL_CALL(0x004ADE20, a1);
    }
}

traffic *traffic::get_traffic_from_entity(vhandle_type<entity> a1) {
    return (traffic *) CDECL_CALL(0x006C3510, a1);
}

void traffic_patch() {
    REDIRECT(0x006779EB, traffic::enable_traffic);
    REDIRECT(0x006779FF, traffic::enable_traffic);
}
