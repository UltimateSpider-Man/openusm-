#pragma once

#include "variable.h"

struct PanelQuad;
struct FEMultiLineText;

struct fe_controller_disconnect {
    //0x00629E60
    static bool update();

    //0x0063A510
    static void draw();

    //0x0060BCD0
    static bool get_currently_plugged_in();

    static inline Var<bool> dialog_up{0x0096B434};

    static inline Var<bool> currently_plugged_in{0x00937764};

    static inline Var<PanelQuad *> back_ground_quad{0x0096B43C};

    static inline Var<FEMultiLineText *> text_box{0x0096B438};
};
