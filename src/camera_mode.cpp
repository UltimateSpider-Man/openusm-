#include "camera_mode.h"

#include "vtbl.h"

camera_mode::camera_mode() {}

void camera_mode::request_recenter(Float a2, const camera_target_info &a3) {
    if constexpr (1) {
        auto &vtbl = get_vfunc(m_vtbl, 0x14);

        vtbl(this, a2, &a3);

    } else {
        auto *v3 = this->field_8;
        if (v3 != nullptr) {
            v3->request_recenter(a2, a3);
        }
    }
}
