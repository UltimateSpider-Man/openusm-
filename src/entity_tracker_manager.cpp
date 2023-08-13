#include "entity_tracker_manager.h"

#include "entity_tracker.h"

entity_tracker *entity_tracker_manager::id_to_ptr(uint32_t a2) {
    slot_pool<entity_tracker*, unsigned int>::slot_t *v2;
    entity_tracker *result = nullptr;

    if (a2 && (v2 = &this->field_C.slots[a2 & this->field_C.field_0], a2 == v2->field_0)) {
        result = v2->field_4;
    }

    return result;
}

bool entity_tracker_manager::get_the_arrow_target_pos(vector3d *a2)
{
    return (bool) THISCALL(0x0062EE10, this, a2);
}
