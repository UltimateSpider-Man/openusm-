#include "anchor_query_visitor.h"

#include "ai_find_best_swing_anchor.h"
#include "common.h"
#include "conglom.h"
#include "conglomerate_clone.h"
#include "func_wrapper.h"
#include "line_marker_base.h"
#include "local_collision.h"
#include "oldmath_po.h"
#include "utility.h"

VALIDATE_SIZE(anchor_query_visitor, 0x28);

anchor_query_visitor::anchor_query_visitor(fixed_vector<quick_anchor_info, 100> *a2,
                                           const vector3d &a1,
                                           const vector3d &a4,
                                           bool a5,
                                           Grid *a6) {
    this->m_vtbl = 0x0087E9A4;
    this->field_4 = a2;
    this->field_8 = a1;
    this->field_20 = a5;
    this->field_24 = a6;
    this->field_14 = a4;
}

int anchor_query_visitor::visit(subdivision_node *a2) {
    auto *v2 = (conglomerate *) a2;
    if (v2 == nullptr) {
        return 0;
    }

    if (v2->field_64 == entity::visit_key3()) {
        return 0;
    }

    v2->field_64 = entity::visit_key3();
    if (v2->is_flagged(0x800)) {
        return 0;
    }

    if ((v2->field_8 & 0x10000000) != 0) {
        v2->update_abs_po(true);
    }

    if (this->field_20 && v2->is_a_conglomerate_clone()) {
        return 0;
    }

    conglomerate *v4 = nullptr;
    if (v2->is_a_conglomerate_clone()) {
        vhandle_type<conglomerate> tmp;
        tmp.field_0 = CAST(tmp.field_0, v2->members.m_data);

        v4 = tmp.get_volatile_ptr();
    } else {
        if (!v2->is_a_conglomerate()) {
            goto LABEL_26;
        }

        v4 = v2;
    }

    bool v10;

    if (v4 == nullptr) {
    LABEL_26:
        if (this->field_20) {
            if (v2->is_a_line_marker_base() && (!v2->is_walkable())) {
                goto LABEL_33;
            }

            v10 = !v2->is_an_anchor_marker();
        } else {
            if (!v2->is_a_line_marker_base()) {
                return 0;
            }

            v10 = (!v2->is_walkable());
        }

        if (v10) {
            return 0;
        }

    LABEL_33:
        this->add_quick_anchor(v2, nullptr);
        return 0;
    }

    auto v5 = v4->members.begin();

    auto v11 = v4->members.end();
    auto v6 = v11;
    if (v5 == v11) {
        return 0;
    }

    int result;

    if (this->field_20) {
        do {
            if ((*v5)->get_flavor() == ANCHOR_MARKER ||
                (*v5)->get_flavor() == LINE_ANCHOR && (!(*v5)->is_walkable())) {
                auto v7 = v2->is_a_conglomerate_clone();
                this->add_quick_anchor(bit_cast<conglomerate *>(*v5),
                                       bit_cast<conglomerate_clone *>(v7 ? v2 : nullptr));
            }

            ++v5;
        } while (v5 != v6);

        result = 0;
    } else {
        do {
            if ((*v5)->get_flavor() == LINE_ANCHOR && (*v5)->is_walkable()) {
                auto v9 = v2->is_a_conglomerate_clone();
                this->add_quick_anchor(bit_cast<conglomerate *>(*v5),
                                       bit_cast<conglomerate_clone *>(v9 ? v2 : nullptr));
            }

            ++v5;
        } while (v5 != v6);

        result = 0;
    }

    return result;
}

void anchor_query_visitor::add_quick_anchor(conglomerate *anchor, conglomerate_clone *clone_ptr) {
    assert(clone_ptr == nullptr || clone_ptr->is_a_conglomerate_clone());

    if constexpr (1) {
        vector3d target;

        vector3d origin;

        auto *v3 = bit_cast<line_marker_base *>(anchor);

        sp_log("%u", anchor->get_flavor());

        if (anchor->get_flavor() == LINE_ANCHOR) {
            target = v3->get_target();

            origin = v3->get_origin();

            if (clone_ptr != nullptr) {
                vector3d v7 = clone_ptr->get_abs_po().slow_xform(target);

                target = v7;

                origin = clone_ptr->get_abs_po().slow_xform(origin);
            }
        } else if (v3->get_flavor() == ANCHOR_MARKER) {
            target = v3->get_abs_position();

            if (clone_ptr != nullptr) {
                target = clone_ptr->get_abs_po().slow_xform(target);
            }

            origin = target;
        }
#if 0
        else {
            assert(0 &&
                   "Entity in anchor_query_visitor::add_quick_anchor must be either an anchor "
                   "marker or a line anchor");
        }
#endif

        double v16;
        if (!this->field_20 || (v16 = this->field_14[1] + 5.0f, target[1] >= v16) ||
            origin[1] >= v16) {
            float tmp;
            closest_point_line_segment_point(target, origin, this->field_8, &tmp);

            vector3d v20 = (origin - target) * tmp + target;

            vector3d a5 = v20;
            auto v17 = v20[1] - this->field_8[1];
            auto v18 = v20[2] - this->field_8[2];
            auto a6 = (v18 * v18 + v17 * v17 +
                       (v20[0] - this->field_8[0]) * (v20[0] - this->field_8[0])) *
                0.25f;

            this->field_4->emplace_back(this->field_24, a5, YVEC, a5, a6, v3, clone_ptr);
        }

    } else {
        THISCALL(0x004901E0, this, anchor, clone_ptr);
    }
}

void anchor_query_visitor_patch() {
    {
        FUNC_ADDRESS(address, &anchor_query_visitor::visit);
        set_vfunc(0x0087E9A4, address);
    }

    {
        auto addr = &fixed_vector<quick_anchor_info, 100>::emplace_back;
        FUNC_ADDRESS(address, addr);
        REDIRECT(0x00486A2A, address);
        //REDIRECT(0x00490448, address);
    }
}
