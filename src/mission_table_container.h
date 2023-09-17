#pragma once

#include "mashable_vector.h"
#include "variable.h"

#include <vector.hpp>

struct region;

struct mission_condition_instance
{
    char field_0[0x18];
    const char *script_data_name;
    char field_1C[0x38];
    unsigned int field_54;

    bool is_flag_set(unsigned int a2)
    {
        return (a2 & this->field_54) != 0;
    }

    const char *get_script_data_name();
};

struct mission_condition
{
    int field_0;
    int field_4;
    mashable_vector<mission_condition_instance> instances;
    mashable_vector<int> field_10;
    const char *field_18;
    const char *field_1C;
    unsigned char field_20;
    int field_24;
    unsigned int field_28;
    const char *field_2C;
    const char *field_30;

    bool is_flag_set(unsigned int a2) const
    {
        return (a2 & this->field_28) != 0;
    }

    bool applies_to_current_hero();
};


struct mission_table_container
{
    char field_0[0x38];
    mashable_vector<mission_condition> field_38;
    int field_40;
    region *field_44;

    struct script_info {
        const char *field_0;
        mission_condition_instance *field_4;
        int field_8;
    };

    region *get_region()
    {
        return this->field_44;
    }

    bool append_script_info(_std::vector<mission_table_container::script_info> *info);

    //0x005C6010
    void un_mash(generic_mash_header *a2, void *a3, void *a4, generic_mash_data_ptrs *a5);
};

inline Var<mission_table_container*> s_current_un_mashing_mission_table_container {0x00968524};

