#include "info_node.h"

#include "base_ai_core.h"
#include "common.h"
#include "entity_base.h"
#include "func_wrapper.h"
#include "vtbl.h"

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

bool info_node::does_need_advance() const
{
    bool (__fastcall *func)(const void *) = CAST(func, get_vfunc(m_vtbl, 0x18));
    return func(this);
}

void info_node::frame_advance(Float a2)
{
    void (__fastcall *func)(void *, void *, Float) = CAST(func, get_vfunc(m_vtbl, 0x1C));
    func(this, nullptr, a2);
}

} // namespace ai
