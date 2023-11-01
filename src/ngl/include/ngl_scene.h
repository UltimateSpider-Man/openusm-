#pragma once

#include "float.hpp"
#include "matrix4x4.h"
#include "variable.h"
#include "vector3d.h"

#include "ngl_params.h"

struct nglTexture;
struct nglLightContext;

enum nglSceneCallbackType {};

struct nglScene {
    int field_0;
    int field_4;
    int field_8;
    matrix4x4 field_C;
    float field_4C[16];
    float field_8C[16];
    float field_CC[16];
    float field_10C[16];
    matrix4x4 field_14C;
    float field_18C[16];
    float field_1CC[16];
    float field_20C;
    float field_210;
    float field_214;
    float field_218;
    float field_21C;
    float field_220;
    float field_224;
    float field_228;
    float field_22C;
    float field_230;
    float field_234;
    float field_238;
    float field_23C;
    float field_240;
    float field_244;
    float field_248;
    float field_24C[16];
    vector3d field_28C;
    int field_298;
    int field_29C;
    int field_2A0;
    int field_2A4;
    int field_2A8;
    vector4d field_2AC[1];
    int empty[20];

    nglScene *field_30C;
    nglScene *field_310;
    nglScene *field_314;
    nglScene *field_318;
    void (*field_31C)(unsigned int *&, void *);
    void *field_320;
    void (*field_324)(unsigned int *&, void *);
    void *field_328;
    void (*field_32C)(unsigned int *&, void *);
    void *field_330;
    nglTexture *field_334;
    nglTexture *field_338;
    int field_33C;
    int field_340;
    int field_344;
    int OpaqueListCount;
    int TransListCount;
    nglLightContext *field_350;
    int empty0[18];
    int field_39C;
    int field_3A0;
    float field_3A4[4];
    int field_3B4;
    bool field_3B8;
    bool field_3B9;
    bool field_3BA;

    int empty5[8];
    bool field_3DC;
    int field_3E0;
    bool field_3E4;
    float field_3E8;
    float field_3EC;
    float m_nearz;
    float m_farz;
    float field_3F8;
    float field_3FC;
    int field_400;
    nglParamSet<nglSceneParamSet_Pool> field_404;
    bool field_408;
    int empty2[12];
    int field_43C;
};

//0x0076C700
extern void nglSetupScene(nglScene *a1, nglSceneParamType a2);

extern void nglSceneDumpStart();

extern Var<nglScene *> nglCurScene;
extern Var<nglScene *> nglRootScene;

extern Var<nglScene *> nglCurScene;

extern Var<nglScene *> g_shadow_scene;

//0x0076B820
extern void nglSetPerspectiveMatrix(Float a1, Float nearz, Float farz);

extern void nglSetSceneCallBack(nglSceneCallbackType a1,
                                void (*Fn)(unsigned int *&, void *),
                                void *a3);
