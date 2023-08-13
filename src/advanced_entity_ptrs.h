#pragma once

#include "oldmath_po.h"
#include "vector3d.h"

struct script_instance;
struct generic_mash_header;
struct actor;
struct generic_mash_data_ptrs;

struct movement_info {
    po field_0;
    vector3d field_30;
    int field_3C;
    float field_40;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
    bool field_54;
};

struct advanced_entity_ptrs {
    int *field_0;
    int *field_4;
    void *field_8;
    movement_info *field_C;
    script_instance *my_script;

    advanced_entity_ptrs();

    ~advanced_entity_ptrs();

    //0x004CFCE0
    void un_mash(generic_mash_header *header, actor *arg4, void *a4, generic_mash_data_ptrs *a5);
};
