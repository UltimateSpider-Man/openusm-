#pragma once

struct PanelFile;
struct FEText;
struct PanelAnimFile;

struct combo_words {
    PanelFile *field_0;
    PanelAnimFile *field_4;
    FEText *field_8[1];
    FEText *field_C;
    FEText *field_10;
    FEText *field_14;
    FEText *field_18;
    FEText *field_1C;
    FEText *field_20;
    int field_24;
    float field_28;

    combo_words();

    void Init();

    void DeInit();
};
