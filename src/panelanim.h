#pragma once

#include "mvector.h"

struct PanelQuad;
struct PanelAnimKeyframe;
struct PanelFile;

struct PanelAnim {
    mVector<PanelAnimKeyframe> field_0;

    PanelQuad *field_14;
    bool field_18;

    PanelAnim();

    void PostUnmashFixup(PanelFile *pf);
};
