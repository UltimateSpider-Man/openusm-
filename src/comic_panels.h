#pragma once

#include "entity_base_vhandle.h"
#include "fixed_vector.h"
#include "variable.h"
#include "vector2d.h"
#include "vector4d.h"
#include "camera.h"
#include "color.h"

struct cut_scene_player;
struct vector3d;
struct actor;
struct entity;
struct signaller;
struct nglTexture;

namespace comic_panels {

struct panel_component {
    struct render_info {};
};

struct panel_params_t {
    uint32_t field_0;
    int empty[51];
    uint8_t field_D0;
    uint8_t field_D1;
};

void set_default_bgcolor(const color &a1);

//0x0x00736A60
void init();

//0x0073EA70
void render();

bool render_panels();

struct panel {
    std::intptr_t m_vtbl;
    vector4d field_4[4];
    vector2d m_size;
    cut_scene_player *field_4C;
    float field_50;
    int field_54[4];
    char field_64;
    char field_65;
    char field_66;
    bool field_67;
    bool field_68;

    //0x007360B0
    void add_camera_component(const char *a2, bool a3, int a4);

    bool render();

    //0x007319C0
    void set_size(const vector2d &a2);

    //0x007319A0
    void set_loc(const vector3d &a2);
};

struct panel_component_camera {
    std::intptr_t m_vtbl;
    int field_4[12];

    vhandle_type<
        camera,
        vhandle_type<actor, vhandle_type<entity, vhandle_type<signaller, entity_base_vhandle>>>>
        field_34[4];
    nglTexture *field_44;
    bool field_48;

    //0x00733420
    void register_camera(uint32_t a2, const char *a3);

    //virtual
    void _render(panel_component::render_info *a2);
};

struct panel_component_base
{
    int m_vtbl;

    //virtual
    void _render(panel_component::render_info *a2);
};

//0x00738CB0
extern panel_params_t *get_panel_params();

//0x00731150
extern camera *get_current_view_camera(int);

//0x00733AD0
panel *acquire_panel(const char *a1);

extern Var<camera *> current_view_camera;

extern Var<panel *> game_play_panel;

extern Var<fixed_vector<panel *, 48>> panels;

inline Var<color> default_bgcol {0x009392EC};

} // namespace comic_panels

extern void comic_panels_patch();
