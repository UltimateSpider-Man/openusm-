#include "comic_panels.h"

#include "common.h"
#include "entity_base.h"
#include "func_wrapper.h"
#include "ngl_scene.h"
#include "utility.h"
#include "trace.h"
#include "vector3d.h"
#include "wds.h"

VALIDATE_SIZE(comic_panels::panel_component_camera, 0x4C);

VALIDATE_OFFSET(comic_panels::panel, field_64, 0x64u);

namespace comic_panels {

Var<camera *> current_view_camera{0x0096F7B4};

Var<panel *> game_play_panel{0x0096F7D4};

Var<fixed_vector<panel *, 48>> panels{0x0096F9F8};

void set_default_bgcolor(const color &a1)
{
    default_bgcol() = a1;
}

void sub_7315A0()
{
    TRACE("sub_7315A0");

    CDECL_CALL(0x007315A0);
}

void init()
{
    TRACE("comic_panels::init");

    CDECL_CALL(0x00736A60);
}

void render()
{
    TRACE("comic_panels::render");
    
    CDECL_CALL(0x0073EA70);
}

bool render_panels()
{
    TRACE("comic_panels::render_panels");
    return (bool) CDECL_CALL(0x0073E710);
}

panel *acquire_panel(const char *a1) {
    return (comic_panels::panel *) CDECL_CALL(0x00733AD0, a1);
}

panel_params_t *get_panel_params()
{
    if constexpr (0)
    {
        if ( nglCurScene() == nullptr ) {
            return nullptr;
        }

        if ( !nglCurScene()->field_404.IsSetParam<SMPanelParams>() ) {
            return nullptr;
        }

        SMPanelParams v1 {};
        return nglCurScene()->field_404.GetOrDefault<SMPanelParams>(v1)->field_0;
    }
    else
    {
        return (panel_params_t *) CDECL_CALL(0x00738CB0);
    }
}

camera *get_current_view_camera(int) {
    return current_view_camera();
}

void panel::add_camera_component(const char *a2, bool a3, int a4) {
    if constexpr (1) {
    } else {
        THISCALL(0x007360B0, this, a2, a3, a4);
    }
}

bool panel::render()
{
    TRACE("comic_panels::panel::render");

    return (bool) THISCALL(0x00738B50, this);
}

void panel::set_size(const vector2d &a2) {
    this->m_size = a2;
}

void panel::set_loc(const vector3d &a2) {
    this->field_4[3] = a2;
}

void panel_component_camera::register_camera(uint32_t a2, const char *a3) {
    if (a3 != nullptr && a3[0] != '\0') {
        auto *v4 = g_world_ptr()->ent_mgr.get_entity(string_hash{a3});
        if (v4 != nullptr) {
            this->field_34[a2].field_0 = v4->get_my_handle();
        } else {
            this->field_34[a2].field_0 = {0};
        }

    } else {
        this->field_34[a2].field_0 = {0};
    }
}

void panel_component_camera::_render(comic_panels::panel_component::render_info *a2)
{
    TRACE("comic_panels::panel_component_camera::render");

    THISCALL(0x007419C0, this, a2);
}

void panel_component_base::_render(panel_component::render_info *a2)
{
    TRACE("comic_panels::panel_component_base::render");

    THISCALL(0x0073AF90, this, a2);
}

    

} // namespace comic_panels


void __fastcall sub_742C50(void *self, int, comic_panels::panel_component_base *a2)
{
    sp_log("0x%08X", a2->m_vtbl);

    THISCALL(0x00742C50, self, a2);
}

void comic_panels_patch()
{
    FUNC_ADDRESS(address, &comic_panels::panel::add_camera_component);
    REDIRECT(0x006424BB, address);

    {
        FUNC_ADDRESS(address, &comic_panels::panel::render);
        REDIRECT(0x0073E84C, address);
        REDIRECT(0x0073EA2E, address);
    }

    REDIRECT(0x00736AE5, comic_panels::sub_7315A0);

    {
        REDIRECT(0x005D7112, comic_panels::render);
    }

    REDIRECT(0x0073EB04, comic_panels::render_panels);

    {
        FUNC_ADDRESS(address, &comic_panels::panel_component_camera::_render);
        set_vfunc(0x008AA340, address);
    }

    {
        FUNC_ADDRESS(address, &comic_panels::panel_component_base::_render);
        set_vfunc(0x008A9E04, address);
    }

    REDIRECT(0x00743453, sub_742C50);
}
