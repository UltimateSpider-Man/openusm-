#include "interaction.h"

#include "common.h"
#include "from_mash_in_place_constructor.h"
#include "func_wrapper.h"

VALIDATE_SIZE(interaction, 0x48);

interaction::interaction(from_mash_in_place_constructor *a2) {
    THISCALL(0x004D5A30, this, a2);
}

interaction::interaction(interaction_type_enum a2, string_hash a3) {
    THISCALL(0x004D5D10, this, a2, a3);
}

int interaction::get_approach() {
    return this->field_40;
}

void interaction::set_enabled(bool a2) {
    this->field_44 = a2;
    if (!a2) {
        this->field_38 = 0;
    }
}

int interaction::get_virtual_type_enum() {
    return 547;
}
