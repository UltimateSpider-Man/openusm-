#include "mashed_state.h"

#include "func_wrapper.h"
#include "common.h"
#include "trace.h"

namespace ai {

VALIDATE_SIZE(mashed_state, 0x18);

mashed_state::mashed_state() {
    THISCALL(0x006DD080, this);
}

void mashed_state::unmash(mash_info_struct *a1, void *)
{
    TRACE("mashed_state::unmash");

    a1->unmash_class_in_place(this->field_0, this);
    a1->unmash_class_in_place(this->field_C, this);
}

string_hash mashed_state::get_name() const {
    return this->field_C;
}

bool mashed_state::operator>(const mashed_state &state) {
    return (this->field_C > state.field_C);
}

bool mashed_state::operator<(const mashed_state &state) {
    return (this->field_C < state.field_C);
}

} // namespace ai
