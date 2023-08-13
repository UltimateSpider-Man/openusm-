#pragma once

#include "float.hpp"
#include "vector3d.h"

struct zoom_map_ui {
    int field_0[144];
};

struct IGOZoomOutMap {
    struct internal {
        int field_0;
        int field_4[3];
        int field_10;
        int field_14;
        int field_18;

        internal() {
            auto *v2 = this->field_4;
            v2[0] = 0;
            v2[1] = 0;
            v2[2] = 0;
            this->field_0 = 0;
            this->field_14 = 5;
            this->field_18 = 3;
            this->field_10 = 0;
        }
    };

    internal field_0[50];
    vector3d field_578;

    int field_4[11];

    int field_5B0;
    int field_5B4;
    int field_5B8;
    char field_5BC;
    char field_5BD;
    char field_5BE;
    char field_5BF;
    char field_5C0;
    char field_5C1;
    char field_5C2;
    bool field_5C3;
    bool field_5C4;
    char field_5C5;
    char field_5C6;
    char field_5C7;
    float field_5C8;
    zoom_map_ui field_5CC;
    int field_80C;
    int field_810;
    int field_814;
    char field_818;
    int field_81C;
    int field_820;
    int field_824;
    int field_828;

    //0x006489A0
    IGOZoomOutMap();

    //0x0060C2D0
    void DoneZoomingBack();

    //0x0063A760
    void Update(Float a2);

    bool sub_55F320();

    void sub_638AD0(int a2, int a3, int a4);

    //0x00619550
    void SetZoomLevel(int a2);
};

extern void IGOZoomOutMap_patch();
