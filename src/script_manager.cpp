#include "script_manager.h"

#include "func_wrapper.h"
#include "log.h"
#include "game.h"
#include "memory.h"
#include "mstring.h"
#include "parse_generic_mash.h"
#include "resource_manager.h"
#include "script_executable.h"
#include "script_executable_entry.h"
#include "script_executable_allocated_stuff_record.h"
#include "script_var_container.h"
#include "os_developer_options.h"
#include "trace.h"
#include "utility.h"
#include "variables.h"

#include <cassert>

Var<float> script_manager_time_inc{0x00961930};

Var<script_executable *> script_manager_master_script {0x00965EE8};

Var<_std::list<void (*)(script_manager_callback_reason, script_executable *, const char *)> *> script_manager_callbacks {0x00965F04};

Var<_std::map<script_executable_entry_key, script_executable_entry> *> script_manager_exec_map{
    0x00965EE4};

Var<_std::map<int, script_executable_allocated_stuff_record> *>
    script_manager_script_allocated_stuff_map{0x00965F00};

Var<script_var_container *> script_manager_game_var_container = {0x00965EEC};

Var<script_var_container *> script_manager_shared_var_container = {0x00965EF0};

Var<_std::list<script_executable_entry> *> script_manager_execs_pending_link_list {0x00965EF4};

void *script_manager::get_game_var_address(const mString &a1, bool *a2, script_library_class **a3) {
    TRACE("script_manager::get_game_var_address", a1.c_str());

    assert(script_manager_game_var_container() != nullptr);
    assert(script_manager_shared_var_container() != nullptr);

    auto result = script_manager_game_var_container()->get_script_var_address(a1.c_str(), a3);
    if (result != nullptr) {
        if (a2 != nullptr) {
            *a2 = true;
        }
    } else {
        result = script_manager_shared_var_container()->get_script_var_address(a1.c_str(), a3);
        if (a2 != nullptr) {
            *a2 = false;
        }
    }

    if (result == nullptr && a3 == nullptr) {
        mString v1{"unknown game/shared var "};
        v1 += a1;

        sp_log("%s", v1.c_str());
        assert(0);
    }

    return result;
}

bool script_manager::using_chuck_old_fashioned()
{
    return os_developer_options::instance()->get_flag(mString {"CHUCK_OLD_FASHIONED"});
}

int script_manager::get_total_loaded() {
    int result = 0;

    if (script_manager_exec_map() != nullptr) {
        result = script_manager_exec_map()->size();
    }

    return result;
}

void script_manager::init_game_var()
{
    TRACE("script_manager::init_game_var");

    if constexpr (1)
    {
        if ( script_manager_game_var_container() == nullptr )
        {
            resource_key a1 {string_hash {"master"}, RESOURCE_KEY_TYPE_SCRIPT_GV};
            auto *v0 = resource_manager::get_resource(a1, nullptr, nullptr);
            if ( v0 != nullptr )
            {
                auto allocated_mem = parse_generic_object_mash(script_manager_game_var_container(),
                    v0,
                    nullptr,
                    nullptr,
                    nullptr,
                    0,
                    0,
                    nullptr);

                assert(script_manager_game_var_container() != nullptr);

                assert(!allocated_mem);
            }
        }

        if ( script_manager_shared_var_container() == nullptr )
        {
            resource_key a1 {string_hash {"master"}, RESOURCE_KEY_TYPE_SCRIPT_SV};
            auto *v1 = resource_manager::get_resource(a1, nullptr, nullptr);
            if ( v1 != nullptr )
            {
                auto allocated_mem = parse_generic_object_mash(
                    script_manager_shared_var_container(),
                    v1,
                    nullptr,
                    nullptr,
                    nullptr,
                    0,
                    0,
                    nullptr);

                assert(script_manager_shared_var_container() != nullptr);
                assert(!allocated_mem);
            }
        }
    }
    else
    {
        CDECL_CALL(0x0059EE90);
    }
}

void script_manager::link() {
    TRACE("script_manager::link");

    CDECL_CALL(0x005A3620);
}

script_var_container *script_manager::load_game_var_buffer(const char *a1) {
    auto *result = script_manager_game_var_container();
    if (a1 != nullptr) {
        std::memcpy(script_manager_game_var_container()->field_4,
                    a1,
                    script_manager_game_var_container()->field_0);
    } else if (script_manager_game_var_container() == nullptr) {
        return result;
    }

    return (script_var_container *) result->field_0;
}

void script_manager::run_callbacks(script_manager_callback_reason a1)
{
    CDECL_CALL(0x005A0AC0, a1);
}

void script_manager::run_callbacks(script_manager_callback_reason a1, script_executable *a2, const char *a3)
{
    assert(script_manager_callbacks() != nullptr);

    for ( auto &cb : (*script_manager_callbacks()) )
    {
        cb(a1, a2, a3);
    }
}

bool script_manager::is_loadable(const resource_key &a1)
{
    TRACE("script_manager::is_loadable");

    resource_key a1a {a1.m_hash, RESOURCE_KEY_TYPE_SCRIPT};
    int mash_data_size = 0;
    return (resource_manager::get_resource(a1a, &mash_data_size, nullptr) != nullptr);
}

script_executable_entry *script_manager::load(const resource_key &a1, uint32_t a2, void *a3, const resource_key &a4)
{
    TRACE("script_manager::load", a1.get_platform_string(g_platform()).c_str());

    assert(script_manager_exec_map() != nullptr);

    if constexpr (1)
    {
        script_executable_entry_key key{};
        key.field_0 = a1;
        key.field_8 = a4;
        assert(script_manager_exec_map() != nullptr);

        using map_t = _std::map<script_executable_entry_key, script_executable_entry>;
        using iterator_t = map_t::iterator;

        iterator_t (__fastcall *find)(void *, int, const script_executable_entry_key *) 
            = CAST(find, 0x005B3360);
        auto v28 = find(script_manager_exec_map(), 0, &key);
        auto v4 = script_manager_exec_map()->end();
        script_executable_entry *result = nullptr;
        if ( v28 != v4 )
        {
            auto &v5 = *v28;
            auto *v27 = &v5.second;
            ++v5.second.field_4;
            result = v27;
        }
        else
        {
            script_executable_entry entry{};
            if ( g_is_the_packer() || using_chuck_old_fashioned() )
            {
                auto *v15 = mem_alloc(sizeof(script_executable));
                entry.exec = new (v15) script_executable {};
            }
            else
            {
                entry.exec = bit_cast<script_executable *>(resource_manager::get_resource(a1, nullptr, nullptr));
            }

            assert(entry.exec != nullptr);

            entry.field_4 = 1;
            entry.field_8 = bit_cast<int>(a3);
            if ( g_is_the_packer() || using_chuck_old_fashioned() )
            {
                entry.exec->load(a1);
            }
            else
            {
#ifdef TARGET_XBOX
                bool allocated_mem = false;
                {
                    auto *a1 = (generic_mash_header *) entry.exec;
                    generic_mash_data_ptrs a4;
                    entry.exec = (script_executable *) parse_generic_mash_init(a1, entry.exec, &allocated_mem, &a4, 0x60, nullptr, nullptr, 0, 0, nullptr);
                    entry.exec->un_mash_start(a1, entry.exec, &a4, nullptr);
                }
#else
                auto allocated_mem = parse_generic_object_mash(
                    entry.exec,
                    entry.exec,
                    nullptr,
                    nullptr,
                    nullptr,
                    0,
                    0,
                    nullptr);
                assert(entry.exec != nullptr);
                assert(!allocated_mem);
#endif

            }

            if ( (a2 & 1) != 0 )
            {
                if ( script_manager_master_script() != nullptr )
                {
                    script_manager::run_callbacks(
                        (script_manager_callback_reason)4,
                        nullptr,
                        "trying to load more than one master script!");
                }

                script_manager_master_script() = entry.exec;
            }

            assert(script_manager_execs_pending_link_list() != nullptr);

            script_manager_execs_pending_link_list()->push_back(entry);

            for ( auto &v23 : *script_manager_script_allocated_stuff_map() )
            {
                auto &v9 = v23.second;
                auto &v7 = v23.first;
                entry.exec->register_allocated_stuff_callback(v7, v9.field_0);
            }

            _std::pair<script_executable_entry_key, script_executable_entry> pair {key, entry};
            script_manager_exec_map()->insert(pair);
            auto v28 = script_manager_exec_map()->find(key);
            auto v8 = script_manager_exec_map()->end();
            if ( v28 != v8 )
            {
                result = &v28->second;
            }
            else
            {
                assert("Entry was not added to list" && 0);
                result = nullptr;
            }
        }

        return result;
    }
    else
    {
        return (script_executable_entry *) CDECL_CALL(0x005B0750, &a1, a2, a3, &a4);
    }
}

void script_manager::init() {
    CDECL_CALL(0x005AFCE0);
}

void script_manager::run(Float a1, bool a2) {
    TRACE("script_manager::run");

    CDECL_CALL(0x005AF9F0, a1, a2);
}

void script_manager::destroy_game_var() {
    CDECL_CALL(0x005A52F0);
}

void script_manager::clear() {
    TRACE("script_manager::clear");

    CDECL_CALL(0x005B0640);
}

vm_executable *script_manager::find_function_by_address(const uint16_t *a1)
{
    return (vm_executable *) CDECL_CALL(0x0059ED70, a1);
}

script_executable_entry *script_manager::find_entry(const script_executable *a1) {
    return (script_executable_entry *) CDECL_CALL(0x0059EE10, a1);
}

int script_manager::save_game_var_buffer(char *a1) {
    /*
    script_var_container *result; // eax

    result = script_manager_game_var_container;
    if (a1) {
        qmemcpy(a1,
                script_manager_game_var_container->field_4,
                script_manager_game_var_container->field_0);
    } else if (!script_manager_game_var_container) {
        return result;
    }
    return (script_var_container *) result->field_0;
    */

    return CDECL_CALL(0x0058F4C0, a1);
}

void *parse_generic_mash_init_hook(generic_mash_header *&header, void *a2, bool *allocated_mem, generic_mash_data_ptrs *a4, unsigned int struct_size, unsigned int *virtual_table_lookup, unsigned int *size_table_lookup, unsigned int num_table_entries, unsigned int base_class_size, void *a10)
{
#ifdef TARGET_XBOX
    struct_size = 0x60;
#endif

    return parse_generic_mash_init(header, a2, allocated_mem, a4, struct_size, virtual_table_lookup,
            size_table_lookup, num_table_entries, base_class_size, a10);
}

void script_manager_patch()
{
    {
        REDIRECT(0x005B07E9, resource_manager::get_resource);
    }

    {
        REDIRECT(0x005B0834, parse_generic_mash_init_hook);
    }

    {
        REDIRECT(0x0055C951, register_chuck_callbacks);
        REDIRECT(0x0055BEA7, register_chuck_callbacks);
    }

    {
        REDIRECT(0x0055C94C, script_manager::clear);
    }

    {
        REDIRECT(0x0055C93D, script_manager::link);
        REDIRECT(0x0055CC6B, script_manager::link);
    }

    {
        REDIRECT(0x0055C944, script_manager::run);
        REDIRECT(0x0055D28E, script_manager::run);
    }

    {
        REDIRECT(0x0055C8A6, script_manager::is_loadable);
    }

    {
        REDIRECT(0x0055C890, script_manager::init_game_var);
        REDIRECT(0x0057ED77, script_manager::init_game_var);
    }

    {
        REDIRECT(0x0055C8F3, script_manager::load);
        REDIRECT(0x0055C938, script_manager::load);
        REDIRECT(0x0055BF1A, script_manager::load);
    }
}
