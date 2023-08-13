#include "trigger_manager.h"

#include "box_trigger.h"
#include "common.h"
#include "entity_trigger.h"
#include "func_wrapper.h"
#include "memory.h"
#include "point_trigger.h"
#include "vtbl.h"

VALIDATE_SIZE(trigger_manager, 8u);

Var<trigger_manager *> trigger_manager::instance{0x0095FF98};

trigger_manager::trigger_manager() : field_4(nullptr) {}

void trigger_manager::deinit() {
    purge();
}

void trigger_manager::purge() {
    THISCALL(0x0050CBA0, this);
}

void trigger_manager::update() {
    THISCALL(0x00541F30, this);
}

trigger *trigger_manager::sub_51E5B0(entity_base *a2) {
    return (trigger *) THISCALL(0x0051E5B0, this, a2);
}

void trigger_manager::delete_trigger(trigger *delete_me) {
    if constexpr (1) {
        assert(delete_me != nullptr);

        trigger **t = nullptr;
        for (t = &this->field_4; *t != delete_me && *t != nullptr; t = &(*t)->field_54) {
            ;
        }

        assert(*t != nullptr && "trigger_manager error: request to delete an unknown trigger");

        auto *v4 = *t;
        auto v5 = (*t == nullptr);
        *t = (*t)->field_54;
        if (!v5) {
            v4->~trigger();
        }

    } else {
        THISCALL(0x0051E560, this, delete_me);
    }
}

void trigger_manager::add_trigger(trigger *a2) {
    a2->field_54 = this->field_4;
    this->field_4 = a2;
}

trigger *trigger_manager::new_point_trigger(vector3d a2, Float a5) {
    auto *mem = mem_alloc(sizeof(point_trigger));

    auto *result = new (mem) point_trigger{ANONYMOUS, a2, a5};

    this->add_trigger(result);

    return result;
}

trigger *trigger_manager::new_entity_trigger(entity_base *a2, Float a3) {
    auto *mem = mem_alloc(sizeof(entity_trigger));

    auto *result = new (mem) entity_trigger{ANONYMOUS, a2, a3};

    this->add_trigger(result);

    return result;
}

trigger *trigger_manager::new_box_trigger(string_hash a2, const vector3d &a3) {
    auto *mem = mem_alloc(sizeof(box_trigger));

    auto *result = new (mem) box_trigger{a2, a3};

    this->add_trigger(result);

    return result;
}

trigger *trigger_manager::new_box_trigger(string_hash a2, entity_base *a3) {
    auto *mem = mem_alloc(sizeof(box_trigger));

    auto *result = new (mem) box_trigger{a2, a3};

    this->add_trigger(result);
    return result;
}
