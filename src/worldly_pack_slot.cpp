#include "worldly_pack_slot.h"

#include "ai_interact_resource_handler.h"
#include "ai_state_graph_resource_handler.h"
#include "als_resource_handler.h"
#include "anim_resource_handler.h"
#include "base_ai_resource_handler.h"
#include "box_trigger_resource_handler.h"
#include "common.h"
#include "cut_scene_resource_handler.h"
#include "entity_resource_handler.h"
#include "func_wrapper.h"
#include "gab_database_resource_handler.h"
#include "glass_house_resource_handler.h"
#include "item_resource_handler.h"
#include "limited_timer.h"
#include "log.h"
#include "material_file_resource_handler.h"
#include "memory.h"
#include "mesh_file_resource_handler.h"
#include "morph_file_resource_handler.h"
#include "panel_resource_handler.h"
#include "path_resource_handler.h"
#include "patrol_def_resource_handler.h"
#include "resource_directory.h"
#include "resource_pack_directory.h"
#include "scene_anim_resource_handler.h"
#include "skeleton_resource_handler.h"
#include "sound_alias_database_resource_handler.h"
#include "texture_resource_handler.h"
#include "utility.h"
#include "variables.h"
#include "vtbl.h"
#include "wds.h"

#include <cassert>

VALIDATE_SIZE(worldly_pack_slot, 0xFC);

worldly_pack_slot::worldly_pack_slot() : resource_pack_slot() {
    if constexpr (1) {
        auto *mem = mem_alloc(sizeof(skeleton_resource_handler));
        this->m_handlers[0] = new (mem) skeleton_resource_handler{this};

        mem = mem_alloc(sizeof(anim_resource_handler));
        this->m_handlers[1] = new (mem) anim_resource_handler{this};

        mem = mem_alloc(sizeof(scene_anim_resource_handler));
        this->m_handlers[2] = new (mem) scene_anim_resource_handler{this};

        mem = mem_alloc(sizeof(als_resource_handler));
        this->m_handlers[3] = new (mem) als_resource_handler{this};

        mem = mem_alloc(sizeof(base_ai_resource_handler));
        this->m_handlers[4] = new (mem) base_ai_resource_handler{this};

        mem = mem_alloc(sizeof(ai_state_graph_resource_handler));
        this->m_handlers[5] = new (mem) ai_state_graph_resource_handler{this};

        mem = mem_alloc(sizeof(texture_resource_handler));
        this->m_handlers[6] = new (mem) texture_resource_handler{this};

        mem = mem_alloc(sizeof(mesh_file_resource_handler));
        this->m_handlers[7] = new (mem) mesh_file_resource_handler{this};

        mem = mem_alloc(sizeof(box_trigger_resource_handler));
        this->m_handlers[8] = (base_tl_resource_handler *) new (mem)
            box_trigger_resource_handler{this};

        mem = mem_alloc(sizeof(item_resource_handler));
        this->m_handlers[9] = (base_tl_resource_handler *) new (mem) item_resource_handler{this};

        mem = mem_alloc(sizeof(entity_resource_handler));
        this->m_handlers[10] = (base_tl_resource_handler *) new (mem) entity_resource_handler{this};

        mem = mem_alloc(sizeof(morph_file_resource_handler));
        this->m_handlers[11] = new (mem) morph_file_resource_handler{this};

        mem = mem_alloc(sizeof(material_file_resource_handler));
        this->m_handlers[12] = new (mem) material_file_resource_handler{this};

        mem = mem_alloc(sizeof(path_resource_handler));
        this->m_handlers[13] = new (mem) path_resource_handler{this};

        mem = mem_alloc(sizeof(patrol_def_resource_handler));
        this->m_handlers[14] = new (mem) patrol_def_resource_handler{this};

        mem = mem_alloc(sizeof(panel_resource_handler));
        this->m_handlers[15] = new (mem) panel_resource_handler{this};

        mem = mem_alloc(sizeof(cut_scene_resource_handler));
        this->m_handlers[16] = new (mem) cut_scene_resource_handler{this};

        mem = mem_alloc(sizeof(ai_interact_resource_handler));
        this->m_handlers[17] = new (mem) ai_interact_resource_handler{this};

        mem = mem_alloc(sizeof(gab_database_resource_handler));
        this->m_handlers[18] = new (mem) gab_database_resource_handler{this};

        mem = mem_alloc(sizeof(glass_house_resource_handler));
        this->m_handlers[19] = new (mem) glass_house_resource_handler{this};

        mem = mem_alloc(sizeof(sound_alias_database_resource_handler));
        this->m_handlers[20] = new (mem) sound_alias_database_resource_handler{this};

        this->clear_slot();
    } else {
        THISCALL(0x00532220, this);
    }
}

void worldly_pack_slot::clear_slot() {
    if constexpr (1) {
        resource_pack_slot::clear_slot();

        this->clear_pack();
    } else {
        THISCALL(0x0050ECE0, this);
    }
}

worldly_pack_slot::~worldly_pack_slot() {
    if constexpr (1) {
        this->clear_slot();
        this->clear_pack();
        for (auto &handler : m_handlers)
        {
            if (handler != nullptr) {
                delete handler;
            }
        }

    } else {
        THISCALL(0x005327E0, this);
    }
}

bool worldly_pack_slot::_on_load(limited_timer *a2)
{
    TRACE("worldly_pack_slot::on_load", this->get_name_key().get_platform_string(g_platform()).c_str());

    if constexpr (1)
    {
        if (a2 != nullptr) {
            if (a2->elapsed() >= a2->field_4) {
                return true;
            }
        }

        if (this->field_94.is_done())
        {
            return false;
        }

        if (!this->field_94.is_started()) {
            this->field_94.start();
        }

        for (auto &handler : this->m_handlers)
        {
            if (handler->handle(worldly_resource_handler::LOAD, a2)) {
                //sp_log("worldly_pack_slot::on_load(): end");
                return true;
            }
        }

        this->field_94.done();
        this->field_98.clear();

        this->clear_progress();

        return false;
    }
    else {
        return (bool) THISCALL(0x0050ED20, this, a2);
    }
}

_std::vector<item *> *worldly_pack_slot::get_item_instances() {
    assert(g_world_ptr() != nullptr);

    if (this->item_instances == nullptr) {
        auto *items = g_world_ptr()->ent_mgr.get_items();

        this->item_instances = items->sub_50A2B0();
    }

    auto *item_instances = this->item_instances;
    assert(g_world_ptr()->ent_mgr.get_items()->get_vector_index(item_instances) > 0);

    return this->item_instances;
}

_std::vector<entity *> *worldly_pack_slot::get_entity_instances() {
    assert(g_world_ptr() != nullptr);

    if (this->entity_instances == nullptr) {
        auto *entities = g_world_ptr()->ent_mgr.get_entities();

        this->entity_instances = entities->sub_50A230();
    }

    auto *entity_instances = this->entity_instances;
    assert(g_world_ptr()->ent_mgr.get_entities()->get_vector_index(entity_instances) > 0);

    return this->entity_instances;
}

void worldly_pack_slot::clear_progress()
{
    for (auto &handler : this->m_handlers) {
        handler->field_4.clear();
    }
}

bool worldly_pack_slot::_on_unload(limited_timer *a2)
{
    TRACE("worldly_pack_slot::on_unload");
    printf("%s\n", this->get_name_key().get_platform_string(3).c_str());

    if constexpr (0)
    {
        bool result;
        if (this->field_98.is_done())
        {
            byte_975468() = false;
            return false;
        }

        if (!this->field_98.is_started())
        {
            this->field_98.start();
        }

        for (int i = 20; i >= 0; --i) {
            auto *handler = this->m_handlers[i];

            if (handler->handle(worldly_resource_handler::UNLOAD, a2)) {
                byte_975468() = true;
                return true;
            }
        }

        if (resource_pack_slot::on_unload(a2)) {
            return true;
        }

        this->field_98.done();
        this->field_94.clear();

        this->clear_progress();

        byte_975468() = false;
        result = false;

        return result;
    } else {
        return (bool) THISCALL(0x0052AC90, this, a2);
    }
}

void worldly_pack_slot::clear_pack() {
    resource_pack_slot::clear_pack();

    this->field_94.clear();
    this->field_98.clear();

    this->clear_progress();

    this->entity_instances = nullptr;
    this->item_instances = nullptr;
    this->box_trigger_instances = nullptr;
}

_std::vector<box_trigger *> *worldly_pack_slot::get_box_trigger_instances()
{
    assert(g_world_ptr() != nullptr);
    if ( this->box_trigger_instances == nullptr )
    {
        auto *mem = mem_alloc(16u);
        this->box_trigger_instances = new (mem) _std::vector<box_trigger *> {};
    }

    return this->box_trigger_instances;
}

void worldly_pack_slot_patch() {
    {
        FUNC_ADDRESS(address, &worldly_pack_slot::_on_load);
        set_vfunc(0x008899D0, address);
    }

    {
        FUNC_ADDRESS(address, &worldly_pack_slot::_on_unload);
        set_vfunc(0x008899D4, address);
    }
}
