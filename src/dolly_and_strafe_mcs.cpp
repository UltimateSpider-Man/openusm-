#include "dolly_and_strafe_mcs.h"

#include "func_wrapper.h"
#include "mouselook_controller.h"

dolly_and_strafe_mcs::dolly_and_strafe_mcs() {}

void dolly_and_strafe_mcs::frame_advance([[maybe_unused]] Float a2) {
    if constexpr (1) {
        if (g_mouselook_controller() != nullptr) {
            if (g_mouselook_controller()->field_4) {
                this->do_dolly(this->field_C);
                this->do_strafe(this->field_10);
                this->do_lift(this->field_14);
                this->field_14 = 0.0;
                this->field_10 = 0.0;
                this->field_C = 0.0;
            }
        }
    } else {
        THISCALL(0x0052E6B0, this, a2);
    }
}

int dolly_and_strafe_mcs::do_dolly(Float a2) {
    return THISCALL(0x00526940, this, a2);
}

int dolly_and_strafe_mcs::do_strafe(Float a2) {
    return THISCALL(0x00526A30, this, a2);
}

int dolly_and_strafe_mcs::do_lift(Float a2) {
    return THISCALL(0x00526B20, this, a2);
}
