#include "base_ai_core.h"

#include "actor.h"
#include "base_ai_state_machine.h"
#include "colgeom_alter_sys.h"
#include "common.h"
#include "core_ai_resource.h"
#include "func_wrapper.h"
#include "ghetto_mash_file_header.h"
#include "info_node.h"
#include "memory.h"
#include "mstring.h"
#include "resource_manager.h"
#include "trace.h"
#include "utility.h"

namespace ai {

VALIDATE_SIZE(ai_core, 0x74u);

ai_core::ai_core(core_ai_resource *a3, const param_block *arg4, actor *a4) {
    THISCALL(0x006AEA90, this, a3, arg4, a4);
}

void sub_86AD60() {
    CDECL_CALL(0x0086AD60);
}

template<typename T>
bool binary_search_array_deref(T *a1, T **a2, int a3, int *index) {
    int v4 = a3;
    int v5 = 0;
    int v6 = a3;
    if (a3 <= 0) {
    LABEL_9:
        if (index) {
            if (v6 == v4 - 1 && a1->field_4.source_hash_code > a2[v6]->field_4.source_hash_code) {
                ++v6;
            }

            *index = v6;
        }

        return false;
    }

    auto v7 = a1->field_4.source_hash_code;
    int v8;
    uint32_t v9;
    while (1) {
        v8 = (v6 + v5) / 2;
        v9 = a2[v8]->field_4.source_hash_code;
        if (v7 >= v9) {
            break;
        }

        v6 = (v6 + v5) / 2;
    LABEL_7:
        if (v5 >= v6) {
            v4 = a3;
            goto LABEL_9;
        }
    }

    if (v7 > v9) {
        v5 = v8 + 1;
        goto LABEL_7;
    }

    if (index != nullptr) {
        *index = v8;
    }

    return true;
}

template<typename T>
bool binary_search_array_deref1(T *a1, T **a2, int a3, int *index) {
    bool result = false;
    int v7 = 0;
    int v6 = a3;
    while (v7 < v6) {
        auto v5 = (v6 + v7) / 2;
        if (a1->field_4.source_hash_code < a2[v5]->field_4.source_hash_code) {
            v6 = (v6 + v7) / 2;
        } else {
            if (!a1->field_4.source_hash_code < a2[v5]->field_4.source_hash_code) {
                result = true;
                if (index != nullptr) {
                    *index = v5;
                }

                break;
            }

            v7 = v5 + 1;
        }
    }

    if (!result && index != nullptr) {
        if (v6 == a3 - 1 && a1->field_4.source_hash_code < a2[v6]->field_4.source_hash_code) {
            ++v6;
        }

        *index = v6;
    }

    return result;
}

void ai_core::create_capsule_alter() {
    if constexpr (1) {
        if (this->field_70 == nullptr) {
            this->field_70 = new capsule_alter_sys{this->field_64};

            auto *my_actor = this->field_64;
            assert(my_actor->is_a_conglomerate());

            set_to_default_capsule_alter(this->field_70, bit_cast<conglomerate *>(my_actor));
        }
    } else {
        THISCALL(0x00687C50, this);
    }
}

void ai_core::post_entity_mash() {
    THISCALL(0x006A36E0, this);
}

void ai_core::frame_advance_all_core_ais(Float a2) {
    TRACE("ai_core::frame_advance_all_core_ais");

    CDECL_CALL(0x006B4AD0, a2);
}

void ai_core::frame_advance(Float a2) {
    THISCALL(0x006B48A0, this, a2);
}

bool ai_core::change_locomotion_machine(const string_hash &a2) {
    return (bool) THISCALL(0x006A34A0, this, &a2);
}

void ai_core::set_allow_facing(bool a2) {
    THISCALL(0x0068FC00, this, a2);
}

bool ai_core::stop_movement() {
    return (bool) THISCALL(0x006A3590, this);
}

void ai_core::do_machine_exit(ai_state_machine *a2) {
    THISCALL(0x0069B940, this, a2);
}

info_node *ai_core::get_info_node(string_hash the_info_node, bool a3) {
    //sp_log("ai_core::get_info_node(): %s", string_hash_dictionary::lookup_string(a2));

    if (this->field_60 != nullptr) {
        static info_node searcher{};

        searcher.field_4 = the_info_node;
        auto *v4 = this->field_60;
        auto v5 = v4->m_size;
        auto **v6 = v4->m_data;
        int index = -1;

        if (binary_search_array_deref(&searcher, v6, v5, &index)) {
            return this->field_60->m_data[static_cast<uint16_t>(index)];
        }
    }

    if (a3) {
        const char *v8 = this->field_64->field_10.to_string();
        const char *v9 = the_info_node.to_string();
        mString a1{0, "unknown ai info-node name %s, for entity %s", v9, v8};
        sp_log("%s", a1.c_str());
    }

    assert(0);

    return nullptr;
}

state_graph *ai_core::find_state_graph(resource_key a2) {
    auto *v2 = this->field_6C->field_3C;

    resource_manager::push_resource_context(v2);

    auto a1 = a2;
    a1.m_type = RESOURCE_KEY_TYPE_AI_STATE_GRAPH;

    auto *v3 = resource_manager::get_resource(a1, nullptr, nullptr);
    resource_manager::pop_resource_context();
    return (state_graph *) v3;
}

ai_state_machine *ai_core::find_machine(resource_key a2) {
    return (ai_state_machine *) THISCALL(0x0069B8F0, this, a2);
}

void ai_core::spawn_state_machine_internal(ai_state_machine *a2,
                                           resource_key graph_name,
                                           ai_state_machine **base_machine_ptr,
                                           string_hash a5) {
    auto v13 = graph_name;
    auto *v6 = this->find_state_graph(graph_name);
    if (v6 != nullptr) {
        if (this->find_machine(graph_name) == nullptr) {
            auto *mem = mem_alloc(sizeof(ai_state_machine));

            auto *new_state_machine = new (mem) ai_state_machine{this, v6, a5};

            if (a2 != nullptr) {
                a2->add_as_child(new_state_machine);
            } else {
                *base_machine_ptr = new_state_machine;
            }

            auto *v9 = this->my_machine_list.m_head;
            auto *v10 = v9->_Prev;
            auto *v11 = &this->my_machine_list;

            decltype(v9) __thiscall (
                *sub_5E3BE0)(void *, void *a1, void *a2, ai_state_machine **a3) = CAST(sub_5E3BE0,
                                                                                       0x005E3BE0);

            auto *v12 = sub_5E3BE0(v11, v9, v10, &new_state_machine);

            void __thiscall (*sub_6B76F0)(void *, unsigned int a2) = CAST(sub_6B76F0, 0x006B76F0);

            sub_6B76F0(v11, 1u);
            v9->_Prev = v12;
            v12->_Prev->_Next = v12;
        }
    }
}

} // namespace ai

void ai_core_patch() {
    {
        FUNC_ADDRESS(address, &ai::ai_core::get_info_node);
        REDIRECT(0x006A34BA, address);
    }

    {
        REDIRECT(0x00558442, ai::ai_core::frame_advance_all_core_ais);
    }
}
