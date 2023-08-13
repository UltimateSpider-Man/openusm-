#include "polytube.h"

#include "common.h"
#include "func_wrapper.h"
#include "oldmath_po.h"
#include "pcuv_shadermaterial.h"
#include "slab_allocator.h"
#include "string_hash.h"
#include "trace.h"
#include "vtbl.h"

#include <cassert>

VALIDATE_SIZE(polytube, 0x178u);
VALIDATE_SIZE(polytube_pt_anim, 0x2C);

polytube::polytube(const string_hash &a2, uint32_t a3) : entity(a2, a3) {
    static Var<bool> g_generating_vtables = (0x0095A6F1);

    this->field_79 = 0;
    this->field_7A = 0;
    this->field_7B = 0;
    this->the_spline = spline{};
    this->field_11C = 0;
    this->field_120 = 0;
    this->field_128 = 0;
    this->field_144 = 0;
    this->field_148 = 0;
    this->field_14C = 0;
    if (!g_generating_vtables()) {
        this->field_68 = nullptr;
        this->field_6C = nullptr;
        this->init();
    }
}

int polytube::get_num_control_pts() {
    return this->the_spline.get_num_control_pts();
}

void polytube::build(int a1, spline::eSplineType a2) {
    this->the_spline.build(a1, a2);
}

void polytube::init_offsets() {
    assert(num_sides > 0);
    assert(tube_radius > 0);

    if constexpr (0) {
    } else {
        THISCALL(0x00B96220, this);
    }
}

void polytube::init() {
    this->field_D0 = nullptr;
    this->field_D8 = nullptr;
    this->field_D4 = nullptr;
    this->field_E4 = 0;
    this->num_sides = 2;
    this->tube_radius = 0.025f;
    this->tiles_per_meter = 1.0;
    this->field_79 = 1;
    this->field_7A = 0;
    this->max_length = -1.0;
    this->field_4 |= 0x100;
    this->field_7A = 0;
    this->field_104 = 0.0;
    this->field_100 = 0.0;
    this->field_128 = -1;
    this->field_DC = 0;
    this->field_E0 = 0;
    this->field_11C = 0;
    this->field_120 = 0;
    this->field_124 = 1.0;
    this->field_7B = 0;
    this->field_7C = 0;
    this->field_108 = 0;

    string_hash v5{"c_alpha"};
    this->set_material(v5);
    this->field_78 = 0;
    this->field_74 = nullptr;
    this->field_70 = nullptr;
    this->field_130 = 0;

    std::memset(this->field_15C, 0, sizeof(this->field_15C));

    this->field_8 = (this->field_8 & 0x8002041F) | 0xF;
    this->field_144 = 0;
    this->field_148 = 0;
    this->field_14C = 0;
    this->field_142 = 0;
    this->field_150 = 0;
    this->field_154 = 0;
    this->field_158 = 0;
    this->field_140 = -1;
}

void polytube::_render(Float a2)
{
    TRACE("polytube::render");
    
    THISCALL(0x005A5B10, this, a2);
}

void polytube::set_control_pt(int index, const vector3d &a2) {
    this->the_spline.set_control_pt(index, a2);
}

vector3d polytube::get_control_pt(int a3) {
    auto &v4 = this->the_spline.get_control_pt(a3);

    auto a2 = this->get_abs_po().slow_xform(v4);
    return a2;
}

void polytube::rebuild_helper() {
    if (this->the_spline.need_rebuild) {
        this->the_spline.rebuild_helper();
    }
}

void polytube::set_abs_control_pt(int index, const vector3d &a3) {
    auto &abs_po = this->get_abs_po();

    auto v4 = abs_po.inverse_xform(a3);
    this->set_control_pt(index, v4);
}

void polytube::set_max_length(Float a2) {
    this->max_length = a2;
}

void polytube::frame_advance_all_polytubes(Float a1) {
    CDECL_CALL(0x0059B490, a1);
}

void polytube::set_material(string_hash a2) {
    auto *v3 = this->field_D0;
    if (v3 != nullptr) {
        auto *vtbl = bit_cast<thiscall_call(*)[1]>(v3->m_vtbl);

        auto &func = (*vtbl)[0];
        func(v3, false);

        slab_allocator::deallocate(v3, nullptr);
        this->field_D0 = nullptr;
    }

    PCUV_ShaderMaterial *v4 = CAST(v4, slab_allocator::allocate(48, nullptr));
    if (v4 != nullptr) {
        nglTexture *v5 = nglGetTexture(a2.source_hash_code);
        *v4 = PCUV_ShaderMaterial(v5, {2}, 0, 72);
        v4->field_1C = &v5->field_60;
        v4->m_vtbl = 0x0087E698;
        this->field_D0 = v4;
    } else {
        this->field_D0 = nullptr;
    }
}

void polytube_patch()
{
    {
        FUNC_ADDRESS(address, &polytube::_render);
        set_vfunc(0x0088F46C, address);
    }
}
