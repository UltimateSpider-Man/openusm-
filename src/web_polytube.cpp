#include "web_polytube.h"

#include "common.h"
#include "swinger.h"
#include "utility.h"
#include "vtbl.h"

VALIDATE_SIZE(web_polytube, 0x17C);

web_polytube::web_polytube(const string_hash &a2, uint32_t a3) : polytube(a2, a3) {}

void web_polytube::render(Float a2) {
    //sp_log("web_polytube::render:");

    if constexpr (1) {
        if (this->field_178 != nullptr) {
            this->rebuild_web();
        }

        polytube::render(a2);
    }
}

void web_polytube::rebuild_web() {
    if constexpr (1) {
        auto *swinger = this->field_178;

        sp_log("rebuild_web: visual_point = %s, ", swinger->m_visual_point.to_string().c_str());

        const auto &a2 = swinger->m_visual_point;
        auto &v38 = swinger->field_0;
        auto &v14 = swinger->field_40;
        auto &v1 = swinger->field_3C->get_abs_position();
        const auto v37 = v1 + v14;

        auto v2 = this->get_num_control_pts() - 1;
        this->set_abs_control_pt(v2, a2);
        this->set_abs_control_pt(0, v37);

        auto v13 = a2 * 2.0f;
        auto v4 = v37 * 3.0f + v13;
        auto v34 = v4 / 5.0f;
        auto v19 = v38.get_constraint();
        auto v5 = v38.get_pivot_abs_pos();
        auto v6 = v37 - v5;
        auto v18 = (v19 - v6.length() - 0.5f) / 2.0f;
        auto a3 = (v38.get_constraint() - 9.0f) / 9.0f + v18;
        if (a3 < LARGE_EPSILON) {
            a3 = 0.0f;
        }

        const auto v16 = YVEC * a3;

        auto v9 = (v37 + v34) / 2.0f - v16;
        this->set_abs_control_pt(1, v9);

        auto v12 = (a2 + v34) / 2.0f - v16;

        this->set_abs_control_pt(2, v12);
        this->rebuild_helper();

    } else {
        THISCALL(0x004775A0, this);
    }
}

void web_polytube_patch() {
    {
        FUNC_ADDRESS(address, &web_polytube::render);
        set_vfunc(0x0087E8E4, address);
    }
}
