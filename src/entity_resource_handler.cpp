#include "entity_resource_handler.h"

#include "common.h"
#include "entity.h"
#include "func_wrapper.h"
#include "utility.h"
#include "vtbl.h"
#include "wds.h"
#include "worldly_pack_slot.h"

#include <cassert>

VALIDATE_SIZE(entity_resource_handler, 0x10);

entity_resource_handler::entity_resource_handler(worldly_pack_slot *a2) {
    this->my_slot = a2;
}

int entity_resource_handler::get_num_resources() {
    return this->my_slot->entity_instances->size();
}

bool entity_resource_handler::handle_resource(worldly_resource_handler::eBehavior behavior) {
    if constexpr (1) {
        assert(behavior == UNLOAD);

        bool result;

        auto *entity_instances = this->my_slot->entity_instances;
        auto *entities = g_world_ptr()->ent_mgr.get_entities();

        if (entities->get_vector_index(entity_instances) > 0) {
            assert(my_slot->entity_instances != nullptr);

            auto *v4 = this->my_slot->entity_instances->at(this->field_C);
            if (v4 != nullptr) {
                if (!v4->is_conglom_member()) {
                    g_world_ptr()->ent_mgr.remove_entity_from_misc_lists(v4);
                    entity_handle_manager::check_world_lists() = false;
                    if (!v4->is_dynamic()) {
                        v4->release_mem();

                    } else {
                        v4->~entity();
                    }

                    v4 = nullptr;
                    entity_handle_manager::check_world_lists() = true;
                }
            }

            ++this->field_C;
            result = false;
        } else {
            this->field_C = this->get_num_resources();
            result = true;
        }
        return result;
    } else {
        return (bool) THISCALL(0x0056BFA0, this, behavior);
    }
}

void entity_resource_handler::post_handle_resources(worldly_resource_handler::eBehavior) {
    if (this->my_slot->entity_instances != nullptr) {
        g_world_ptr()->ent_mgr.entities.sub_572FB0(this->my_slot->entity_instances);
        this->my_slot->entity_instances = nullptr;
    }
}

void entity_resource_handler_patch() {
    {
        FUNC_ADDRESS(address, &entity_resource_handler::handle_resource);
        set_vfunc(0x00888A7C, address);
    }
}
