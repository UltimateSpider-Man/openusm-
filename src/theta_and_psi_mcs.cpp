#include "theta_and_psi_mcs.h"

#include "camera.h"
#include "common.h"
#include "custom_math.h"
#include "func_wrapper.h"
#include "oldmath_po.h"

#include <cmath>

VALIDATE_SIZE(theta_and_psi_mcs, 0x1Cu);

void theta_and_psi_mcs::reset_angles() {
    if constexpr (1) {
        auto &z_facing = this->field_8->get_abs_po().get_z_facing();

        auto cross = vector3d::cross(z_facing, YVEC);

        this->field_10 = std::atan2(z_facing[1], z_facing[2] / cross[0]);
        this->field_C = std::atan2(cross[2], cross[0]);

        float v5;
        if (this->field_10 >= -half_PI) {
            if (this->field_10 <= half_PI) {
                return;
            }

            v5 = PI;
        } else {
            v5 = -PI;
        }

        this->field_10 = v5 - this->field_10;
        this->field_C += PI;
    } else {
        THISCALL(0x005196E0, this);
    }
}

void theta_and_psi_mcs::frame_advance(Float dt) {
    THISCALL(0x0053B260, this, dt);
}
