#pragma once

#include "variable.h"

struct damage_morph_memory_pool {
    int field_0;
    int *field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;

    //0x004C5550
    void *memalloc(int a2, int a3);
};

struct balanced_tree {
    struct tree_node {
        int field_0;
        int field_4;
        int field_8;
        tree_node *field_C;
        tree_node *field_10;
        tree_node *field_14;
        tree_node *field_18;
        int field_1C;
    };

    tree_node *field_0;
    tree_node *field_4;
    int field_8;

    bool retrieve(int a2, int *a3);

    bool remove(int a2);
};

struct actor;

struct damage_morphs {
    //0x004CE0E0
    static void init_memory_pools();

    //0x004C4D30
    static bool intercepting_allocations();

    //0x004F0E80
    static void *memalloc(int a1, int a2, bool a3);

    //0x004CE140
    static void memfree(void *a1);

    static bool is_subject_off_screen(actor *a1);

    //0x004D97C0
    static bool unregister_mesh_copy(int a1);

    static Var<int> allocations_intercept_reference_count;

    static Var<damage_morph_memory_pool> write_combine_pool;

    static Var<damage_morph_memory_pool> normal_pool;

    static Var<balanced_tree> registration_tree;
};
