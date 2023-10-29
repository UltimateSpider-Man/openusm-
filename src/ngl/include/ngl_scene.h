#pragma once

#include "float.hpp"
#include "matrix4x4.h"
#include "variable.h"

#include "ngl_params.h"

struct nglSceneCallbackType {
    int field_0;

    operator int() {
        return field_0;
    }
};

struct nglScene {
    int field_0;
    int empty3[82];
    matrix4x4 field_14C;
    float field_18C[16];
    int field_CC[56];

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
    int *field_334;
    int field_338;
    int field_33C;
    int field_340;
    int field_344;
    int OpaqueListCount;
    int TransListCount;
    int empty0[19];
    int field_39C;
    int field_3A0;
    float field_3A4[4];
    int field_3B4;
    bool field_3B8;
    bool field_3B9;
    bool field_3BA;

    int empty5[10];
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

extern Var<nglScene *> g_shadow_scene;

//0x0076B820
extern void nglSetPerspectiveMatrix(Float a1, Float nearz, Float farz);

extern void nglSetSceneCallBack(nglSceneCallbackType a1,
                                void (*Fn)(unsigned int *&, void *),
                                void *a3);
