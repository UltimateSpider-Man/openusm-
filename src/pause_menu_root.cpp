#include "pause_menu_root.h"

#include "comic_panels.h"
#include "common.h"
#include "entity_base.h"
#include "fe_health_widget.h"
#include "fetext.h"
#include "femanager.h"
#include "femenusystem.h"
#include "igofrontend.h"
#include "mstring.h"
#include "panelquad.h"
#include "pausemenusystem.h"
#include "panelfile.h"
#include "utility.h"
#include "trace.h"
#include "vtbl.h"
#include "wds.h"

VALIDATE_SIZE(pause_menu_root, 0x100u);

pause_menu_root::pause_menu_root(FEMenuSystem *a2, int a3, int a4) : FEMenu(a2, 0, a3, a4, 8, 0) {
    this->field_AC = a2;

    this->field_9C = nullptr;
    this->field_B0 = 0;
    this->field_B4 = 0;
    this->field_30 = 0;
    this->field_2C = 0;
    this->field_2D = 0;
}

void pause_menu_root::_Load()
{
    TRACE("pause_menu_root::Load");

    if constexpr (0)
    {
        auto *v2 = bit_cast<PauseMenuSystem *>(this->field_AC)->field_2C;

        this->field_3C[0] = v2->GetPQ("pm_splash_back_01a");
        this->field_3C[1] = v2->GetPQ("pm_splash_back_01b");
        this->field_3C[2] = v2->GetPQ("pm_splash_back_02a");
        this->field_3C[3] = v2->GetPQ("pm_splash_back_02b");
        this->field_3C[4] = v2->GetPQ("pm_splash_back_03a");
        this->field_3C[5] = v2->GetPQ("pm_splash_back_03b");
        this->field_3C[6] = v2->GetPQ("pm_splash_back_stub_01");
        this->field_3C[7] = v2->GetPQ("pm_splash_back_stub_02");
        this->field_3C[8] = v2->GetPQ("pm_splash_icon");

        this->field_68 = v2->GetPQ("pm_splash_dialog_box_01");
        this->field_6C = v2->GetPQ("pm_splash_dialog_box_02");
        this->field_60 = v2->GetPQ("pm_splash_hilite_text");
        this->field_64 = v2->GetPQ("pm_splash_hilite_text_01");
        this->field_70 = v2->GetPQ("pm_splash_back_04");
        this->field_74 = v2->GetPQ("pm_splash_back_venom");

        this->field_78[0] = v2->GetTextPointer("pm_splash_text_01");
        this->field_78[1] = v2->GetTextPointer("pm_splash_text_02");
        this->field_78[2] = v2->GetTextPointer("pm_splash_text_03");
        this->field_78[3] = v2->GetTextPointer("pm_splash_text_04");
        this->field_78[4] = v2->GetTextPointer("pm_splash_text_05");
        this->field_78[5] = v2->GetTextPointer("pm_splash_text_06");
        this->field_78[6] = v2->GetTextPointer("pm_splash_text_07");
        this->field_78[7] = v2->GetTextPointer("pm_splash_text_08");
        this->field_78[8] = v2->GetTextPointer("pm_splash_text_09");

        this->field_9C = v2->GetTextPointer("pm_splash_text_GAMEPAUSED");
        this->field_A0 = v2->GetTextPointer("pm_splash_dialog_box_text_BODY");
        this->field_A4 = v2->GetTextPointer("pm_splash_dialog_box_text_NOWAY");

        this->field_A8 = v2->GetTextPointer("pm_splash_dialog_box_text_OKAY");
        for (auto i = 0u; i < 9u; ++i)
        {
            this->field_3C[i]->TurnOn(true);
        }

        this->field_78[0]->SetShown(true);
        this->field_78[0]->SetNoFlash(color32 {0xFFE6D03F});
        this->field_78[0]->SetScale(1.2, 1.2);

        for (auto i = 0u; i < 8u; ++i) 
        {
            auto *v6 = this->field_78[i + 1];
            v6->SetShown(true);
            v6->SetNoFlash(color32 {0xFFC87238});
        }

        this->field_68->TurnOn(1);
        this->field_6C->TurnOn(1);
        this->field_60->TurnOn(1);
        this->field_64->TurnOn(1);
        this->field_9C->SetShown(true);
        this->field_9C->SetText(static_cast<global_text_enum>(253));
        this->field_9C->SetNoFlash(color32 {0xFFC8C8C8});
        this->field_A0->SetShown(1);
        this->field_A0->SetText(static_cast<global_text_enum>(271));
        this->field_A0->SetNoFlash(color32 {0xFFC8C8C8});
        this->field_A4->SetShown(1);
        this->field_A4->SetText(static_cast<global_text_enum>(254));
        this->field_A4->SetNoFlash(color32 {0xFFC87238});
        this->field_A8->SetShown(1);
        this->field_A8->SetText(static_cast<global_text_enum>(255));
        this->field_A8->SetNoFlash(color32 {0xFFC87238});

        this->field_78[7]->SetText(static_cast<global_text_enum>(265));
        this->field_78[0]->SetText(static_cast<global_text_enum>(275));
        this->field_78[1]->SetText(static_cast<global_text_enum>(260));
        this->field_78[2]->SetText(static_cast<global_text_enum>(258));
        this->field_78[3]->SetText(static_cast<global_text_enum>(259));
        this->field_78[4]->SetText(static_cast<global_text_enum>(273));
        this->field_78[5]->SetText(static_cast<global_text_enum>(263));
        this->field_78[8]->SetText(static_cast<global_text_enum>(261));
        this->field_78[6]->SetText(static_cast<global_text_enum>(297));

        auto v8 = this->field_78[0]->GetX();
        auto v9 = this->field_78[0]->GetY();
        this->field_60->GetPos(this->field_B8, this->field_C8);
        this->field_64->GetPos(this->field_D8, this->field_E8);

        for (auto i = 0u; i < 4u; ++i)
        {
            this->field_B8[i] = this->field_B8[i] - v8;
            this->field_C8[i] = this->field_C8[i] - v9;
            this->field_D8[i] = this->field_D8[i] - v8;
            this->field_E8[i] = this->field_E8[i] - v9;
        }

        this->field_F8 = false;
    }
    else
    {
        THISCALL(0x0063B2E0, this);
    }
}

void pause_menu_root::OnUp(int a2) {
    sp_log("pause_menu_root::OnUp(): %d", a2);

    THISCALL(0x0061BD00, this, a2);
}

void pause_menu_root::OnDown(int a2) {
    THISCALL(0x0061BE10, this, a2);
}

void sub_648F40() {
    CDECL_CALL(0x00648F40);
}

void pause_menu_root::Update(Float a2) {
    if constexpr (1) {
        if (this->field_2D) {
            sub_648F40();
        }

        FEMenu::Update(a2);
        if (this->field_30) {
            this->update_switching_heroes();
        }

        if (this->field_2C) {
            if (!mission_stack_manager::s_inst->waiting_for_push_or_pop()) {
                auto *v3 = this->field_AC;
                this->field_2C = false;

                v3->MakeActive(8);

                comic_panels::game_play_panel()->field_67 = true;
            }
        }
    } else {
        THISCALL(0x006490A0, this, a2);
    }
}

void pause_menu_root::update_switching_heroes() {
    int v2 = this->field_30;
    if (v2 == 4) {
        g_world_ptr->remove_player(g_world_ptr->num_players - 1);
    } else if (v2 == 2) {
        int v3;
        if (this->field_34) {
            g_world_ptr->add_player(mString{"venom"});

            v3 = 4;
        } else {
            g_world_ptr->add_player(mString{"ultimate_spiderman"});

            v3 = 0;
        }

        auto *v4 = g_femanager.IGO->hero_health;
        if (v4->field_0[v3] != nullptr)
        {
            v4->field_30 = g_world_ptr->get_hero_ptr(0)->my_handle.field_0;
            v4->field_38 = v3;
            v4->UpdateMasking();
            v4->clear_bars();
        }

        v4->SetShown(this->field_38);
    }

    --this->field_30;
}

void pause_menu_root_patch() {

    {
        FUNC_ADDRESS(address, &pause_menu_root::_Load);
        set_vfunc(0x00893F48, address);
    }
    return;

    {
        FUNC_ADDRESS(address, &pause_menu_root::Update);
        set_vfunc(0x00893F58, address);
    }

    {
        FUNC_ADDRESS(address, &pause_menu_root::OnUp);
        //set_vfunc(0x00893F74, address);
    }
}
