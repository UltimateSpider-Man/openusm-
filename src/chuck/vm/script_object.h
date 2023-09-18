#pragma once

#include "string_hash.h"
#include "so_data_block.h"
#include "float.hpp"

#include <list.hpp>

struct vm_executable;
struct vm_thread;
struct script_instance;
struct script_executable;
struct generic_mash_header;
struct generic_mash_data_ptrs;

struct script_object {
    string_hash name;
    script_executable *parent;
    script_instance *global_instance;
    struct {
        string_hash field_0;
        _std::list<void *> field_4;
        _std::list<void *> field_10;
    } *debug_info;
    so_data_block data;
    int data_blocksize;
    vm_executable **funcs;
    int total_funcs;
    int field_28;
    _std::list<script_instance *> *instances;
    uint32_t field_30;

    script_object();

    auto *get_parent() {
        return parent;
    }

    auto &get_name() const {
        return name;
    }

    //0x005A0750
    void constructor_common();

    void sub_5AB420();

    //0x005AB350
    void un_mash(generic_mash_header *a2, void *a3, void *a4, generic_mash_data_ptrs *a5);

    //0x005AAEF0
    script_instance *create_auto_instance(Float arg0);

    vm_executable *get_func(int);

    //0x0058EF80
    int find_func(string_hash a2) const;
};

struct script_instance_callback_reason_t {
    int field_0;
};

struct script_instance
{
    int field_0;
    int field_4;
    int field_8;
    string_hash name;
    so_data_block data;
    _std::list<vm_thread *> threads;
    int field_28;
    script_object *parent;
    int field_30;

    auto &get_name() const {
        return name;
    }

    auto get_parent()
    {
        return this->parent;
    }

    char *get_buffer()
    {
        return this->data.get_buffer();
    }

    vm_thread *add_thread(const vm_executable *a2);

    vm_thread *add_thread(const vm_executable *a1, const char *a2);

    //0x005ADB80
    void massacre_threads(const vm_executable *a2, const vm_thread *a3);

    //0x005AD8D0
    void kill_thread(const vm_executable *a2, const vm_thread *a3);

    //0x005A33F0
    int *register_callback(
        void (*p_cb)(script_instance_callback_reason_t, script_instance *, vm_thread *, void *),
        void *a3);

};
