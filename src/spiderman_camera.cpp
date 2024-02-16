#include "spiderman_camera.h"

#include "camera_mode.h"
#include "camera_target_info.h"
#include "common.h"
#include "func_wrapper.h"
#include "game.h"
#include "geometry_manager.h"
#include "oldmath_po.h"
#include "trace.h"
#include "vtbl.h"

VALIDATE_SIZE(spiderman_camera, 0x204u);
VALIDATE_OFFSET(spiderman_camera, field_1A0, 0x1A0);

Var<spiderman_camera *> g_spiderman_camera_ptr{0x00959A70};

spiderman_camera::spiderman_camera(const string_hash &a2, entity *a3) : game_camera(a2, a3) {
    THISCALL(0x004B78E0, this, &a2, a3);
}

void spiderman_camera::adjust_geometry_pipe(bool a1) {
    if constexpr (1) {
        auto *abs_po = &this->get_abs_po();
        auto &pos = abs_po->get_position();

        auto &v2 = abs_po->get_z_facing();
        auto eye = v2 + pos;

        auto &up = abs_po->get_y_facing();
        if (a1) {
            assert(!is_externally_controlled());

            auto *v7 = entity_handle_manager::find_entity(string_hash{"SCENE_ANALYZER_CAM"},
                                                          entity_flavor_t::CAMERA,
                                                          false);

            this->set_abs_po(v7->get_abs_po());

            auto &pos = abs_po->get_position();

            geometry_manager::set_view(pos, eye, up);
        } else if (g_game_ptr() != nullptr && !g_game_ptr()->m_user_camera_enabled) {
            auto &pos = abs_po->get_position();
            geometry_manager::set_view(pos, eye, up);
        }

    } else {
        THISCALL(0x004B6480, this, a1);
    }
}

void spiderman_camera::autocorrect(Float a2)
{
    void (__fastcall *func)(void *, void *, Float) = CAST(func, get_vfunc(m_vtbl, 0x2D0));
    func(this, nullptr, a2);
}

void spiderman_camera::_autocorrect(Float a2)
{
    TRACE("spiderman_camera::autocorrect");

    if constexpr (1)
    {
        auto &v3 = this->field_1B0;

        auto &v4 = this->field_1A4;

        auto *target = this->get_target_entity();

        camera_target_info v13{target, 0.033333335f, v4, v3};

        //sp_log("0x%08X", this->field_1A0->m_vtbl);
        this->field_1A0->request_recenter(a2, v13);
        if (equal(a2.value, 0.0f))
        {
            v4 = v13.pos;

            v3 = v13.up;
        }

    } else {
        THISCALL(0x004B63F0, this, a2);
    }
}

void spiderman_camera::set_target_entity(entity *e) {
    assert(e->has_physical_ifc());

    assert(e->is_a_conglomerate());

    game_camera::set_target_entity(e);
}

void spiderman_camera_patch()
{
    {
        FUNC_ADDRESS(address, &spiderman_camera::_autocorrect);
        set_vfunc(0x008823B0, address);
    }
}
