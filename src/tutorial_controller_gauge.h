#pragma once

struct PanelFile;
struct PanelAnimFile;
struct PanelQuad;

struct tutorial_controller_gauge {
    PanelFile *field_0;
    PanelAnimFile *field_4;
    PanelAnimFile *field_8;
    PanelQuad *field_C[4];
    PanelQuad *field_1C[12];
    float field_4C;
    float field_50;
    float field_54;
    float field_58;
    float field_5C;
    float field_60;
    float field_64;
    float field_68;
    float field_6C;
    float field_70;
    float field_74;
    float field_78;
    float field_7C;
    float field_80;
    PanelQuad *field_84;
    PanelQuad *field_88;
    int field_8C;
    int field_90;
    bool field_94;

    tutorial_controller_gauge();

    void Init();

    void Hide();

    void DeInit();
};
