#pragma once

#include <cstdint>

struct PanelFile;
struct FEText;

struct fe_timer_widget {
    std::intptr_t m_vtbl;
    PanelFile *field_4;
    FEText *field_8;
    FEText *field_C;
    FEText *field_10;
    FEText *field_14;
    FEText *field_18;
    FEText *field_1C;
    char *field_20;
    float field_24;
    bool field_28;
    bool field_29;
    bool field_2A;
    float field_2C;

    //0x00615B50
    fe_timer_widget();

    /* virtual */ void SetShown(bool a2);
};
