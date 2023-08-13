#include "info_node.h"

#include "base_ai_core.h"
#include "common.h"
#include "entity_base.h"
#include "func_wrapper.h"

namespace ai {

VALIDATE_SIZE(info_node, 0x1C);

info_node::info_node() {
    this->field_4 = string_hash{};
    this->field_10.field_8 = 0;
    this->field_10.param_array = nullptr;
    this->field_10.field_0 = 0;
    this->field_10.field_8 = 0;
    this->field_8 = nullptr;
}

info_node::info_node(from_mash_in_place_constructor *a2) {
    THISCALL(0x006D9930, this, a2);
}

actor *info_node::get_actor() {
    return this->field_C;
}

} // namespace ai
