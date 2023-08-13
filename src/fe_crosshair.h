#pragma once

struct PanelFile;
struct PanelQuad;

struct fe_crosshair {
    int field_0;
    int field_4;
    int field_8;
    bool field_C;
    PanelFile *field_10;
    PanelQuad *field_14;

    fe_crosshair();

    void Init();

    void DeInit();
};
