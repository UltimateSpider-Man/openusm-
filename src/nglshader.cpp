#include "nglshader.h"

#include "common.h"
#include "fixedstring.h"
#include "log.h"
#include "vtbl.h"

#include "tl_instance_bank.h"
#include "tl_system.h"

VALIDATE_SIZE(nglShader, 0xC);

VALIDATE_SIZE(nglShaderNode, 0x14);

Var<int> nglShader::NextID{0x00972910};

nglShader::nglShader()
{

}

void nglShader::Register() {
    this->field_8 = nglShader::NextID()++;
    auto v4 = this->field_8;

    auto &GetName = get_vfunc(this->m_vtbl, 0x4);

    tlFixedString v1;
    GetName(this, &v1);

    auto *v2 = v1.to_string();
    sp_log("Registering shader %s, ID: %d\n", v2, v4);

    tlFixedString v3;
    GetName(this, &v3);
    nglShaderBank().Insert(v3, this);
}

tlFixedString nglShader::GetName() {
    auto &func = get_vfunc(m_vtbl, 0x4);

    tlFixedString result;
    func(this, &result);

    return result;
}

void nglShader::BindMaterial(nglMaterialBase *mat) {
    auto &func = get_vfunc(m_vtbl, 0xC);

    func(this, mat);
}

void nglShader::ReleaseMaterial(nglMaterialBase *mat) {
    auto &func = get_vfunc(m_vtbl, 0x10);

    func(this, mat);
}

void nglShader::RebaseMaterial(nglMaterialBase *Material, unsigned int a2) {
    void (__fastcall *func)(void *, int edx, nglMaterialBase *, uint32_t)
        = CAST(func, get_vfunc(m_vtbl, 0x14));

    if constexpr (1)
    {
        sp_log("0x%08X 0x%08X", m_vtbl, (int) func);
    }

    func(this, 0, Material, a2);
}

bool nglShader::CheckMaterialVersion(nglMaterialBase *mat) {
    if constexpr (1) {
        auto &func = get_vfunc(m_vtbl, 0x18);

        return (bool) func(this, mat);
    } else {
        return true;
    }
}

bool nglShader::CheckVertexDefVersion(nglMeshSection *Section) {
    if constexpr (1) {
        auto &func = get_vfunc(m_vtbl, 0x1C);

        return (bool) func(this, Section);
    } else {
        return true;
    }
}

void nglShader::BindSection(nglMeshSection *Section) {
    auto &func = get_vfunc(m_vtbl, 0x20);

    func(this, Section);
}

bool nglShader::IsSwitchable() {
    auto &func = get_vfunc(m_vtbl, 0x24);

    return (bool) func(this);
}

void nglShaderNode::Render() {
    auto *vtbl = get_vtbl(this);

    auto &func = get_vfunc((int) vtbl, 0x0);
    func(this);
}

void nglShaderNode::sub_413AF0() {
    THISCALL(0x00413AF0, this);
}
