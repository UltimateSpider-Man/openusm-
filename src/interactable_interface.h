#pragma once

#include "float.hpp"
#include "mvector.h"

struct interaction;
struct actor;
struct from_mash_in_place_constructor;

struct interactable_interface {
    actor *field_0;
    mVector<interaction> field_4;
    bool field_18;

    //0x004ED630
    interactable_interface(actor *act);

    //0x004ED5C0
    interactable_interface(from_mash_in_place_constructor *a2);

    //0x004CAC60
    void frame_advance(Float a2);

    //0x004D1C10
    static void frame_advance_all(Float a1);
};
