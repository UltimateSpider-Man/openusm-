#include "fe_mini_map_widget.h"

#include "common.h"
#include "entity.h"
#include "fe_mini_map_dot.h"
#include "func_wrapper.h"
#include "ngl.h"
#include "ngl_scene.h"
#include "oldmath_po.h"
#include "panel_layer.h"
#include "panelfile.h"
#include "region.h"
#include "terrain.h"
#include "trace.h"
#include "utility.h"
#include "vtbl.h"
#include "wds.h"

#include "resource_directory.h"

VALIDATE_SIZE(fe_mini_map_widget, 0x3B8u);

fe_mini_map_widget::fe_mini_map_widget() {
    THISCALL(0x006343C0, this);
}

void fe_mini_map_widget::Init() {
    TRACE("fe_mini_map_widget::Init");


    if constexpr (1) {
        assert(mini_map_icons == nullptr);

        this->mini_map_icons = PanelFile::UnmashPanelFile("mini_map_items", panel_layer{7});
        if (this->mini_map_icons != nullptr) {
            this->map_icon_spidey = this->mini_map_icons->GetPQ("map_icon_spidey");
            this->map_icon_others = this->mini_map_icons->GetPQ("map_icon_others");
            this->minimap_ring = this->mini_map_icons->GetPQ("minimap_ring");
        }

        assert(mini_map_frame == nullptr);

        this->mini_map_frame = PanelFile::UnmashPanelFile("mini_map_frame", panel_layer{7});

        if (this->mini_map_frame != nullptr) {
            this->map_frame_black = this->mini_map_frame->GetPQ("map_frame_black");
            this->map_frame_white = this->mini_map_frame->GetPQ("map_frame_white");
            this->map_frame_white_stub = this->mini_map_frame->GetPQ("map_frame_white_stub");
            this->compass_base = this->mini_map_frame->GetPQ("compass_base");
            this->compass_arrow = this->mini_map_frame->GetPQ("compass_arrow");
            this->map_frame_map_placeholder = this->mini_map_frame->GetPQ(
                "map_frame_map_placeholder");
            this->field_3A0 = this->mini_map_frame->GetAnimationPointer(0);
        }
    } else {
        THISCALL(0x006432F0, this);
    }
}

int fe_mini_map_widget::PrepareRegions() {
    return THISCALL(0x00619690, this);
}

void fe_mini_map_widget::RenderMeshes(matrix4x4 *a2, float &a4) {
    THISCALL(0x00638C30, this, a2, &a4);
}

void fe_mini_map_widget::UpdatePOIs(matrix4x4 *a2, Float a3, Float a4, Float a5, Float a6, Float a7) {
    THISCALL(0x0063AEC0, this, a2, a3, a4, a5, a6, a7);
}

void fe_mini_map_widget::Draw() {
    auto *v2 = this->field_3A0;
    auto v3 = v2 && v2->field_2D;
    if (this->field_3A8 || v3) {
        auto *hero_ptr = g_world_ptr()->get_hero_ptr(0);

        region *reg;

        if (hero_ptr == nullptr ||
            (reg = g_world_ptr()->the_terrain->find_outermost_region(hero_ptr->get_abs_position()),
             reg == nullptr) ||
            !reg->is_interior()) {
            if (v3) {
                auto &Draw = get_vfunc(this->map_frame_map_placeholder->m_vtbl, 0x58);

                Draw(this->map_frame_map_placeholder);
            } else {
                this->PrepareRegions();
                nglListBeginScene(nglSceneParamType{0});
                nglSetClearFlags(1u);
                nglCurScene()->field_3BA = true;
                nglCurScene()->m_farz = 10000.0;

                float local_vec0[4], local_vec1[4];

                auto &GetPos = get_vfunc(this->map_frame_map_placeholder->m_vtbl, 0xA4);
                GetPos(this->map_frame_map_placeholder, local_vec0, local_vec1);
                auto v10 = local_vec0[0];
                auto v13 = local_vec0[3];

                auto v14 = local_vec1[0];
                auto v12 = local_vec1[3];

                nglSetViewport(local_vec0[0], local_vec1[0], local_vec0[3], local_vec1[3]);

                Var<vector4d> stru_892F80{0x00892F80};

                char v9 = 0;
                matrix4x4 v19;
                v19.sub_415740(&v9);
                v19.arr[3] = stru_892F80();

                nglSetWorldToViewMatrix({v19});
                nglSetZTestEnable(false);

                matrix4x4 v20;
                float a4;
                this->RenderMeshes(&v20, a4);
                this->UpdatePOIs(&v20, a4, v10, v13, v14, v12);
                nglListEndScene();

                for (auto i = 0u; i < this->field_364.size(); ++i) {
                    this->field_364[i]->Draw();
                }

                auto &Draw = get_vfunc(this->compass_arrow->m_vtbl, 0x58);
                Draw(this->compass_arrow);
            }

            auto &Draw = get_vfunc(this->map_frame_black->m_vtbl, 0x58);
            Draw(this->map_frame_black);

            Draw = get_vfunc(this->map_frame_white->m_vtbl, 0x58);
            Draw(this->map_frame_white);

            Draw = get_vfunc(this->map_frame_white_stub->m_vtbl, 0x58);
            Draw(this->map_frame_white_stub);

            Draw = get_vfunc(this->compass_base->m_vtbl, 0x58);
            Draw(this->compass_base);
        }
    }
}

void fe_mini_map_widget::Update(Float a2) {
    THISCALL(0x00641810, this, a2);
}

void fe_mini_map_widget_patch() {
    {
        FUNC_ADDRESS(address, &fe_mini_map_widget::Init);
        set_vfunc(0x00895A04, address);
    }

    return;

    {
        FUNC_ADDRESS(address, &fe_mini_map_widget::Draw);
        set_vfunc(0x00895A08, address);
    }
}
