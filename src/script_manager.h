#pragma once

#include "float.hpp"
#include "variable.h"

#include <map.hpp>

struct mString;
struct script_var_container;
struct script_library_class;
struct resource_key;
struct script_executable_entry_key;
struct script_executable_entry;
struct script_executable;
struct script_executable_allocated_stuff_record;
struct vm_executable;

enum script_manager_callback_reason
{};

struct script_manager {
    //0x005A09B0
    static void *get_game_var_address(const mString &a1, bool *a2, script_library_class **a3);

    //0x0058F4C0
    static int save_game_var_buffer(char *a1);

    //0x005AFCE0
    static void init();

    //0x005A3620
    static void link();

    //0x005A0AC0
    static void run_callbacks(script_manager_callback_reason a1);

    static void run_callbacks(script_manager_callback_reason a1, script_executable *a2, const char *a3);

    //0x0058F480
    static int load_game_var_buffer(const char *a1);

    //0x005B0750
    static script_executable_entry *load(const resource_key &a1, uint32_t a2, void *a3, const resource_key &a4);

    //0x0059EE90
    static void init_game_var();

    //0x0059EE10
    static script_executable_entry *find_entry(const script_executable *a1);

    static bool using_chuck_old_fashioned();

    //0x0058F3A0
    static bool is_loadable(const resource_key &a1);

    //0x005A52F0
    static void destroy_game_var();

    //0x005B0640
    static void clear();

    //0x005AF9F0
    static void run(Float a1, bool a2);

    //0x0059ED70
    static vm_executable *find_function_by_address(const uint16_t *a1);

    static int get_total_loaded();
};


inline Var<script_var_container *> script_manager_game_var_container {0x00965EEC};

inline Var<script_var_container *> script_manager_shared_var_container {0x00965EF0};


extern Var<float> script_manager_time_inc;

extern Var<_std::map<script_executable_entry_key, script_executable_entry> *> script_manager_exec_map;

extern Var<_std::map<int, script_executable_allocated_stuff_record> *>
    script_manager_script_allocated_stuff_map;

extern void script_manager_patch();
