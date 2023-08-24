#include "wds_entity_manager.h"

#include "box_trigger.h"
#include "camera.h"
#include "common.h"
#include "entity.h"
#include "func_wrapper.h"
#include "item.h"
#include "mstring.h"
#include "oldmath_po.h"
#include "trace.h"
#include "trigger_manager.h"
#include "utility.h"
#include "vtbl.h"
#include "multi_vector.h"

#include <list.hpp>

#include <cassert>

VALIDATE_SIZE(wds_entity_manager, 0x2C);

wds_entity_manager::wds_entity_manager() {
    THISCALL(0x005DF4C0, this);
}

template<typename T>
typename multi_vector<T>::iterator multi_vector_find(typename multi_vector<T>::iterator &begin, typename multi_vector<T>::iterator &end, T &a4)
{
    auto it = begin;
    while ( it != end )
    {
        auto v4 = *it.field_8;
        if ( v4 == a4 )
        {
            return it;
        }

        ++it;
    }

    return end;
}

bool wds_entity_manager::is_entity_valid(entity *a1)
{
    auto &v12 = this->entities;

    auto end = v12.end();
    auto begin = v12.begin();
    auto v11 = multi_vector_find<entity *>(begin, end, a1);

    auto v4 = v12.end();
    return v11 != v4;
}

bool wds_entity_manager::is_item_valid(item *a2)
{
    auto end = this->items.end();
    auto begin = this->items.begin();

    auto v11 = multi_vector_find<item *>(begin, end, a2);

    return v11 != this->items.end();
}

int wds_entity_manager::acquire_entity(string_hash a1, uint32_t a2) {
    TRACE("wds_entity_manager::acquire_entity");

    return THISCALL(0x005E0D40, this, a1, a2);
}

void wds_entity_manager::add_dynamic_instanced_entity(entity *a2) {
    TRACE("wds_entity_manager::add_dynamic_instanced_entity");

    THISCALL(0x005E0760, this, a2);
}

void wds_entity_manager::destroy_all_entities_and_items() {
    THISCALL(0x005D9060, this);
}

void wds_entity_manager::destroy_entity(entity *e) {
    assert(e != nullptr);

    if constexpr (1) {
        bool v4;

        auto v3 = e->get_flavor() - 9;
        if (v3 && v3 == 2) {
            v4 = this->remove_item((item *) e);
        } else {
            v4 = this->remove_entity(e);
        }

        if (v4) {
            if ((e->field_8 & 0x80000000) == 0) {
                e->release_mem();
            } else {
                e->~entity();
            }
        }
    } else {
        THISCALL(0x005D6F20, this, e);
    }
}

bool wds_entity_manager::remove_item(item *a2) {
    return (bool) THISCALL(0x005D5410, this, a2);
}

bool wds_entity_manager::remove_entity(entity *a2) {
    return (bool) THISCALL(0x005D5350, this, a2);
}

void wds_entity_manager::release_entity(entity *e) {
    this->destroy_entity(e);
}

void wds_entity_manager::remove_entity_from_misc_lists(entity *e) {
    assert(e != nullptr);
}

void wds_entity_manager::make_time_limited(entity *a1, Float a2) {
    THISCALL(0x005DBBC0, this, a1, a2);
}

item *wds_entity_manager::add_item(_std::vector<item *> *a2, item *a3) {
    TRACE("wds_entity_manager::add_item");

    return (item *) THISCALL(0x005DF7D0, this, a2, a3);
}

int wds_entity_manager::add_ent_to_lists(_std::vector<entity *> *a2,
                                         _std::vector<item *> *a3,
                                         entity *ent) {
    if constexpr (1) {
        auto result = 0;
        switch ((entity_flavor_t) ent->get_flavor()) {
        case ACTOR:
        case ENTITY:
        case MARKER:
        case PARKING_MARKER:
        case WATER_EXIT_MARKER:
        case LIGHT_SOURCE:
        case PFX:
        case CONGLOMERATE:
        case CONGLOMERATE_CLONE:
        case BEAM:
        case MANIP:
        case SWITCH:
        case LENSFLARE:
        case NEOLIGHT:
        case ANCHOR_MARKER:
        case LINE_ANCHOR:
        case AI_COVER_MARKER: {
            result = this->add_entity_internal(a2, ent);
            break;
        }
        case ITEM: {
            result = (int) this->add_item(a3, (item *) ent);
            break;
        }
        default:
            assert(0);
            break;
        }

        return result;
    } else {
        THISCALL(0x005E0970, this, a2, a3, ent);
    }
}

entity_base *wds_entity_manager::get_entity(string_hash a1) {
    return entity_handle_manager::find_entity(a1, entity_flavor_t::IGNORE_FLAVOR, true);
}

int wds_entity_manager::create_and_add_entity_or_subclass(string_hash a2,
                                                          string_hash a3,
                                                          const po &a4,
                                                          const mString &a5,
                                                          uint32_t a6,
                                                          const _std::list<region *> *a7) {
    TRACE("wds_entity_manager::create_and_add_entity_or_subclass");

    return THISCALL(0x005E0A10, this, a2, a3, &a4, &a5, a6, a7);
}

box_trigger *wds_entity_manager::create_and_add_box_trigger(
        string_hash a1,
        const vector3d &a3,
        const convex_box &a4)
{
    TRACE("wds_entity_manager::create_and_add_box_trigger");

    if constexpr (1) {
        auto *new_trigger = (box_trigger *) trigger_manager::instance()->new_box_trigger(a1, a3);
        new_trigger->set_box_info(a4);
        return new_trigger;
    } else {
        return (box_trigger *) THISCALL(0x005C2D80, this, a1, &a3, &a4);
    }
}

entity *wds_entity_manager::add_to_entities(_std::vector<entity *> *vec, entity *a3) {
    TRACE("wds_entity_manager::add_to_entities");

    return (entity *) THISCALL(0x005DFAB0, this, vec, a3);
}

int wds_entity_manager::add_entity_internal(_std::vector<entity *> *vec, entity *ent) {
    if constexpr (1) {
        this->add_to_entities(vec, ent);

        {
            FUNC_ADDRESS(address, &entity_base::get_entity_size);
            FUNC_ADDRESS(address1, &entity_base::is_alive);

            sp_log("0x%08X 0x%08X", (int) address, (int) address1);
        }

        auto result = ent->get_flavor() - 4;

        switch (result) {
        case 0:
        case 1:
        case 4:
        case 5:
        case 8:
        case 10:
        case 21:
        case 22: {
            ent->field_4 &= 0xFFFFDFFF;
            break;
        }
        default:
            break;
        }

        return result;
    } else {
        return THISCALL(0x005DFB10, this, vec, ent);
    }
}

void wds_entity_manager::add_camera(_std::vector<entity *> *vec, camera *a2) {
    TRACE("wds_entity_manager::add_camera");

    THISCALL(0x005DFC80, this, vec, a2);
}

void wds_entity_manager::process_time_limited_entities(Float a2) {
    TRACE("wds_entity_manager::process_time_limited_entities");

    THISCALL(0x005D92D0, this, a2);
}

void wds_entity_manager::check_water(Float) {}

void wds_entity_manager::frame_advance(Float a2) {
    this->process_time_limited_entities(a2);

    this->check_water(a2);
}

void wds_entity_manager_patch() {
    {
        FUNC_ADDRESS(address, &wds_entity_manager::add_entity_internal);
        //SET_JUMP(0x005DFB10, address);
    }

    if constexpr (0) {
        {
            FUNC_ADDRESS(address, &wds_entity_manager::acquire_entity);
            REDIRECT(0x00635795, address);
        }

        {
            FUNC_ADDRESS(address, &wds_entity_manager::add_camera);
            REDIRECT(0x0055B94E, address);
        }

        {
            FUNC_ADDRESS(address, &wds_entity_manager::add_ent_to_lists);
            REDIRECT(0x005E0B1C, address);
            REDIRECT(0x0055AC96, address);
        }
    }
}
