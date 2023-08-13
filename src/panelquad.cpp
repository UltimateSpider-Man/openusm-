#include "panelquad.h"

#include "common.h"
#include "from_mash_in_place_constructor.h"
#include "func_wrapper.h"
#include "mash_info_struct.h"
#include "panelquadsection.h"
#include "panelmeshsection.h"
#include "trace.h"
#include "vtbl.h"

VALIDATE_SIZE(PanelQuad, 0x4C);

PanelQuad::PanelQuad() {
    THISCALL(0x00637E80, this);
}

PanelQuad::PanelQuad(from_mash_in_place_constructor *a2) {
    THISCALL(0x00637F00, this, a2);
}

PanelQuad * __fastcall PanelQuad_constructor(PanelQuad *self, int, from_mash_in_place_constructor *a2)
{
    TRACE("PanelQuad::PanelQuad");
    return (PanelQuad*) THISCALL(0x00637F00, self, a2);
}

PanelQuad::~PanelQuad() {
    THISCALL(0x0043F7F0, this);
}

void PanelQuad::_destruct_mashed_class()
{
    TRACE("PanelQuad::_destruct_mashed_class");

    THISCALL(0x00633A30, this);
}

void PanelQuad::_unmash(mash_info_struct *a1, void *a3)
{
    TRACE("PanelQuad::unmash");
    if constexpr(1)
    {
        a1->unmash_class_in_place(this->field_1C, this);

        a1->unmash_class_in_place(this->field_3C, this);

#ifdef TARGET_XBOX
        uint8_t class_mashed = -1;
        [](mash_info_struct *a1, mash::buffer_type buffer, uint8_t &a3)
        {
            a3 = *a1->read_from_buffer(buffer, 1, 1);
        }(a1, mash::SHARED_BUFFER, class_mashed);
        assert(class_mashed == 0xAF || class_mashed == 0);
#endif

        if ( this->pmesh != nullptr )
        {
            this->pmesh =
                (PanelMeshSection *) a1->read_from_buffer(
#ifdef TARGET_XBOX
                    mash::NORMAL_BUFFER,
#endif 
                        sizeof(PanelMeshSection), 16);
        }
    }
    else
    {
        auto &func = get_vfunc(m_vtbl, 0x4);
        func(this, a1, a3);
    }
}

int PanelQuad::_get_mash_sizeof()
{
#ifdef TARGET_XBOX
    return 0x48;
#else
    return 0x4C;
#endif

}

vector2d PanelQuad::GetMax() {
    vector2d result;
    THISCALL(0x00616990, this, &result);

    return result;
}

vector2d PanelQuad::GetMin() {
    vector2d result;
    THISCALL(0x006168C0, this, &result);

    return result;
}

void PanelQuad::sub_616710(Float a2, Float a3) {
    THISCALL(0x00616710, this, a2, a3);
}

void PanelQuad::SetTexture(nglTexture *a2) {
    THISCALL(0x00616290, this, a2);
}

void PanelQuad::Draw() {
    auto &func = get_vfunc(m_vtbl, 0x58);

    func(this);
}

void PanelQuad::TurnOn(bool a2) {
    auto &func = get_vfunc(m_vtbl, 0x5C);

    func(this, a2);
}

void PanelQuad::SetColor(color32 a2) {
    auto &func = get_vfunc(m_vtbl, 0x7C);
    func(this, a2);
}

void PanelQuad::SetPos(float *a2, float *a3)
{
    void (__fastcall *func)(void *, int edx, float *, float *) = CAST(func, get_vfunc(m_vtbl, 0x94));
    func(this, 0, a2, a3);
}

void PanelQuad::SetPos(Float a2, Float a3, Float a4, Float a5) {
    auto &func = get_vfunc(m_vtbl, 0x90);
    func(this, a2, a3, a4, a5);
}

void PanelQuad::Init(vector2d *a2, color32 *a3, panel_layer a4, Float a5, const char *a6) {
    auto &func = get_vfunc(m_vtbl, 0x54);

    func(this, a2, a3, a4, a5, a6);
}

double PanelQuad::GetCenterX() {
    return this->field_14;
}

double PanelQuad::GetCenterY() {
    return this->field_18;
}

void PanelQuad::CopyFrom(const PanelQuad *a2) {
    THISCALL(0x0062E130, this, a2);
}

void PanelQuad::GetPos(float *a2, float *a3)
{
    TRACE("PanelQuad::GetPos");

    assert(pmesh == nullptr);

    for (auto i = 0u; i < 4u; ++i)
    {
        auto *quad_section = this->field_1C.at(0);
        auto &quad = quad_section->field_14;
        a2[i] = quad.field_0[i].pos.field_0;
        a3[i] = quad.field_0[i].pos.field_4;
    }
}

void PanelQuad_patch()
{
    {
        REDIRECT(0x00429C61, PanelQuad_constructor);
    }
    {
        FUNC_ADDRESS(address, &PanelQuad::_unmash);
        set_vfunc(0x0087B994, address);
    }

    {
        FUNC_ADDRESS(address, &PanelQuad::_destruct_mashed_class);
        set_vfunc(0x0087B990, address);
    }

    {
        FUNC_ADDRESS(address, &PanelQuad::GetPos);
        SET_JUMP(0x006166A0, address);
    }

    {
        FUNC_ADDRESS(address, &PanelQuad::_get_mash_sizeof);
        set_vfunc(0x0087B9DC, address);
    }
}
