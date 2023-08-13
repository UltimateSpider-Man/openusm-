#include "panel_pose_skel.h"

#include "common.h"

#include <nal_list.h>
#include <nal_system.h>

namespace nalPanel {
VALIDATE_SIZE(nalPanelSkeleton, 0x84);

VALIDATE_SIZE(nalPanelPose, 0x10);

static nalPanelSkeleton::vtbl g_skel_vtbl{nullptr,
                                          nullptr,
                                          &nalPanelSkeleton::Process,
                                          nullptr,
                                          &nalPanelSkeleton::CheckVersion};

int nalPanelSkeleton::vtbl_ptr{(int) &g_skel_vtbl};

static nalInitListAnimType InitListAnimType_nalPanelAnim{"Panel",
                                                         nalPanel::nalPanelAnim::vtbl_ptr,
                                                         nalPanel::nalPanelSkeleton::vtbl_ptr};

nalPanelPose::nalPanelPose(const nalPanelSkeleton *a2) : nalCompPose(a2) {
    field_C = 0;
}

void nalPanelSkeleton::Process() {
    auto *v1 = PanelComponentMgr::comp_list();
    int num;
    for (num = 0; v1 != nullptr; ++num) {
        v1 = (int *) v1[1];
    }

    auto *v4 = (BaseComponent **) tlMemAlloc(4 * num, 8, 0);
    int v5 = 0;

    decltype(v4) j;
    for (j = v4; v5 < num; ++v5) {
        auto *v7 = PanelComponentMgr::comp_list();
        for (auto k = v5; k; v7 = (int *) v7[1]) {
            if (v7 == nullptr) {
                break;
            }

            --k;
        }

        j[v5] = (BaseComponent *) v7;
    }

    this->UnMash(this, j, num);
    tlMemFree(j);
    auto *mem = tlMemAlloc(sizeof(nalPanel::nalPanelPose), 8, 0);

    this->field_80 = new (mem) nalPanel::nalPanelPose{this};
}
} // namespace nalPanel
