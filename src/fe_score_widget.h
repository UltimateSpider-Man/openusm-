#pragma once

struct PanelFile;
struct PanelAnimFile;
struct FEText;

struct fe_score_widget {
    FEText *field_0;
    bool field_4;
    bool field_5;
    int field_8;
    int field_C;
    int field_10;
    PanelFile *field_14;
    PanelAnimFile *field_18;

    fe_score_widget();

    void Init();

    void DeInit();
};
