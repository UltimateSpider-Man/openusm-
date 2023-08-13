#pragma once

struct PanelFile;
struct PanelAnimFile;
struct PanelQuad;
struct FEText;

struct race_announcer {
    PanelFile *field_0;
    PanelAnimFile *field_4;
    PanelQuad *field_8;
    FEText *field_C;
    FEText *field_10;
    FEText *field_14;
    bool field_18;
    bool field_19;

    race_announcer();

    void Init();

    void DeInit();
};
