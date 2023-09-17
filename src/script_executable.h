#pragma once

#include "fixedstring.h"
#include "string_hash.h"

#include <list.hpp>
#include <map.hpp>

struct script_executable_allocated_stuff_record;
struct mString;
struct generic_mash_header;
struct generic_mash_data_ptrs;
struct resource_key;
struct script_object;
struct vm_executable;

struct script_executable {
    fixedstring<8> field_0;
    uint16_t *sx_exe_image;
    int sx_exe_image_size;
    script_object **script_objects;
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
    struct {
        int field_0;
        int field_4;
        vm_executable *field_8;
        int field_C;
        int field_10;
        int field_14;
        int field_18;
    } *field_54;
    int field_58;

    script_executable();

    //0x005AFC50
    void constructor_common();

    //0x0059BBA0
    bool has_threads();

    uint16_t * get_exec_code(unsigned int offset);

    //0x005AFF90
    void quick_un_mash();

    script_object *find_object(int index) const;

    void sub_672318(script_object *a1, int a3);

    void load(const resource_key &a1);

    //0x0058F280
    vm_executable *find_function_by_address(const uint16_t *a2) const;

    //0x0058F310
    vm_executable *find_function_by_name(string_hash a2) const;

    void un_mash_start(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4, void *a5);

    void un_mash(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4);

    //0x005AF460
    void register_allocated_stuff_callback(int a1, void (*a2)(script_executable *, _std::list<uint32_t> &, _std::list<mString> &));
};

extern void script_executable_patch();
