#pragma once

#include <list.hpp>
#include <map.hpp>

struct script_executable_allocated_stuff_record;
struct mString;
struct generic_mash_header;
struct generic_mash_data_ptrs;
struct script_object;

struct script_executable {
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    script_object **field_28;
    script_object **script_objects_by_name;
    int total_script_objects;
    script_object *global_script_object;
    char **permanent_string_table;
    int permanent_string_table_size;
    char **system_string_table;
    int system_string_table_size;
    void *script_object_dummy_list;
    _std::map<int, script_executable_allocated_stuff_record> *script_allocated_stuff_map;
    uint32_t flags;
    int field_54;
    int field_58;

    script_executable();

    //0x005AFC50
    void constructor_common();

    //0x0059BBA0
    bool has_threads();

    //0x005AFF90
    void quick_un_mash();

    void un_mash_start(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4, void *a5);

    void un_mash(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4);

    //0x005AF460
    void register_allocated_stuff_callback(int a1, void (*a2)(script_executable *, _std::list<uint32_t> &, _std::list<mString> &));
};

extern void script_executable_patch();
