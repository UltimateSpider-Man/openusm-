#include "wds_camera_manager.h"

#include "common.h"
#include "controller.h"
#include "func_wrapper.h"
#include "motion_control_system.h"

#include <cassert>

VALIDATE_SIZE(wds_camera_manager, 0x4C);

wds_camera_manager::wds_camera_manager() {
    this->field_0 = {};
    this->field_10 = {};
    this->field_20 = nullptr;
    this->field_30 = 0;
    this->field_24 = 0;
    this->field_28 = 0;
    this->field_2C = 0;
    this->field_34 = 0;
    this->field_38 = 0;
    this->field_3C = 0;
    this->field_40 = 0;
    this->field_44 = nullptr;
    this->field_48 = false;
}

void wds_camera_manager::frame_advance(Float a2) {
    if constexpr (1) {
        struct Vtbl {
            int field_0;
            bool __thiscall (*is_active)(void *);
            int field_8;
            void __thiscall (*frame_advance)(void *, Float);
        };

        for (auto &mcs : this->field_0) {
            Vtbl *vtbl = CAST(vtbl, mcs->m_vtbl);

            if (vtbl->is_active(mcs)) {
                vtbl->frame_advance(mcs, a2);
            }
        }
    } else {
        THISCALL(0x00530A30, this, a2);
    }
}

int wds_camera_manager::add_controller(controller *a2) {
    return THISCALL(0x00542630, this, a2);
}

int wds_camera_manager::add_mcs(motion_control_system *a2) {
    return THISCALL(0x005426A0, this, a2);
}

void wds_camera_manager::advance_controllers(Float a2) {
    if constexpr (0) {
        for (auto &cntrl : this->field_10) {
            if (cntrl->field_4) {
                struct Vtbl {
                    int field_0;
                    void __thiscall (*frame_advance)(void *, Float);
                };

                Vtbl *vtbl = CAST(vtbl, cntrl->m_vtbl);
                vtbl->frame_advance(cntrl, a2);
            }
        }
    } else {
        THISCALL(0x00530A70, this, a2);
    }
}

void wds_camera_manager::setup_cameras() {
    THISCALL(0x0054B8A0, this);
}

void wds_camera_manager::usercam_frame_advance(Float a2) {
    THISCALL(0x0050D480, this, a2);
}

void wds_camera_manager::scene_analyzer_frame_advance(Float a2) {
    THISCALL(0x0051EA10, this, a2);
}

void wds_camera_manager::enable_marky_cam(bool a2, Float a3) {
    assert(this->field_44 != nullptr);

    THISCALL(0x0050D4C0, this, a2, a3);
}
