#pragma once

#include "fixedstring.h"
#include "nglshader.h"
#include "vector4d.h"

#include <us_variant.h>

struct nglMaterialBase;
struct nglTexture;

namespace USPersonShaderSpace {

struct ParamStruct {
    vector4d field_0;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    float field_30;
    int field_34;
    bool field_38;
    int field_3C;
    bool field_40;
    bool field_41;
    int field_44;
    bool field_48;
    bool field_49;

    static inline constexpr auto OutlineThickness = 0.003f;
};

extern Var<ParamStruct> DefaultParams;

struct USPersonSolidShader : nglShader {
    void sub_41DEE0(nglMeshNode *a1, nglMeshSection *a2, nglMaterialBase *a3);

    void sub_41E0A0(nglMeshNode *a1, nglMeshSection *a2, nglMaterialBase *a3);

    void sub_41E290(nglMeshNode *a1, nglMeshSection *a2, nglMaterialBase *a3);

    //0x0041DBE0
    //virtual
    void AddNode(nglMeshNode *a1, nglMeshSection *a2, nglMaterialBase *a3);

    //virtual
    void _BindMaterial(nglMaterialBase *a1);

    void _RebaseMaterial(nglMaterialBase *a1, unsigned int a2);

    //virtual
    void Register();
};

struct USPersonShader : nglShader {
    tlFixedString field_C;

    USPersonShader();

    void sub_41BEF0(nglMeshNode *a1, nglMeshSection *a2, nglMaterialBase *a3);

    void sub_41C0B0(nglMeshNode *a2, nglMeshSection *a3, nglMaterialBase *a4);

    void sub_41C2A0(nglMeshNode *a1, nglMeshSection *a2, nglMaterialBase *a3);

    //0x0041BBC0
    //virtual
    void AddNode(nglMeshNode *a2, nglMeshSection *a3, nglMaterialBase *a4);

    //virtual
    void _BindMaterial(nglMaterialBase *);

    //virtual
    void _RebaseMaterial(nglMaterialBase *a1, unsigned int a2);

    //0x00411580
    //virtual
    void Register();

    //0x00410CC0
    //virtual
    tlFixedString GetName();
};

struct USPersonSolidNode : USVariantShaderNode {
    nglMaterialBase *field_18;
    nglTexture *field_1C;
    nglTexture *field_20;
    int field_24;

    //0x0041DCF0
    USPersonSolidNode(nglMeshNode *a2, nglMeshSection *a3, nglMaterialBase *a4);

    //0x0041E4B0
    /* virtual */ void Render() /* override */;

    /* virtual */ void GetSortInfo(nglSortInfo &sortInfo) /* override */;

    /* virtual */ ~USPersonSolidNode() = default;
};

struct USPersonNode : USVariantShaderNode {
    struct LightInfoStruct {
        vector4d field_0;
        vector4d field_10;
        vector4d field_20;
        float field_30;
        uint32_t field_34;
    };

    static Var<LightInfoStruct> DefaultLightInfo;

    nglMaterialBase *field_18;
    nglTexture *field_1C;
    nglTexture *field_20;
    int field_24;

    //0x0041BCD0
    USPersonNode(nglMeshNode *a2, nglMeshSection *a3, nglMaterialBase *a4);

    //0x0041CF70
    bool GetLightInfo(USPersonNode::LightInfoStruct &lightInfo);

    void sub_41D180();

    //0x0041C4C0
    /* virtual */ void Render() /* override */;

    //0x0041DD90
    /* virtual */ void GetSortInfo(nglSortInfo &sortInfo) /* override */;

    /* virtual */ ~USPersonNode() = default;
};

} // namespace USPersonShaderSpace

struct USPersonParam {
    USPersonShaderSpace::ParamStruct *field_0;

    static Var<int> ID;
};

extern void us_person_patch();
