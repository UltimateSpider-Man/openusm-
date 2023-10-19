#include "interactable_interface.h"

#include "common.h"
#include "func_wrapper.h"
#include "interaction.h"
#include "trace.h"
#include "utility.h"

VALIDATE_SIZE(interactable_interface, 0x1C);
VALIDATE_ALIGNMENT(interactable_interface, 4);

Var<_std::vector<interactable_interface *>> interactable_interface::all_ifcs {0x0095A998};

interactable_interface::interactable_interface(actor *act) {
    THISCALL(0x004ED630, this, act);
}

interactable_interface::interactable_interface(from_mash_in_place_constructor *a2) {
    THISCALL(0x004ED5C0, this, a2);
}

void interactable_interface::add_interface_to_list(interactable_interface *who_to_add)
{
    TRACE("interactable_interface::add_interface_to_list");

    assert(std::find(all_ifcs().begin(), all_ifcs().end(), who_to_add) == all_ifcs().end());

    all_ifcs().push_back(who_to_add);
}

void interactable_interface::frame_advance_all(Float a1) {
    TRACE("interactable_interface::frame_advance_all");

    CDECL_CALL(0x004D1C10, a1);
}

void interactable_interface::frame_advance(Float a2) {
    for (uint16_t i = 0; i < this->field_4.m_size; ++i) {
        auto *v3 = this->field_4.m_data[i];
        auto v4 = v3->field_38 - a2;
        v3->field_38 = v4;
        if (v4 < 0.0f) {
            v3->field_38 = 0.0;
        }
    }
}

void interactable_interface_patch() {

    SET_JUMP(0x004DAFB0, interactable_interface::add_interface_to_list);

    REDIRECT(0x00558451, interactable_interface::frame_advance_all);
}
