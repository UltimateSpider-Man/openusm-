#pragma once

#include "entity.h"
#include "variable.h"

struct vector3d;

struct light_properties
{
    int field_0;
    float field_4;
    float field_8;
    float field_C;
    float field_10;
    float field_14;
    float field_18;
    float field_1C;
    float field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    float field_34;
    float field_38;
    float field_3C;
    float field_40;
    float field_44;
    float field_48;
    float field_4C;
    int field_50;
    int field_54;
    int field_58;
    int field_5C;
    int field_60;
    int field_64;

    //0x00515890
    light_properties();

    //0x005602C0
    light_properties(const light_properties &) = default;

    void sub_515BE0(const mString &a2);

    static constexpr auto default_contrast = 3.0f;
};

struct light_source : entity
{
    light_properties *properties;

    light_source(const string_hash &a2, unsigned int a3);

    light_source(const light_properties &a2,
                        entity *a3,
                        const string_hash &a4);

    //0x00515D50
    [[nodiscard]] vector3d get_dir(const vector3d &a3);

    void sub_41D050(const vector3d *a2, vector4d *a3, vector4d *a4);
};

struct USLightParam
{
    light_source *field_0;

    static inline Var<int> ID{0x009566C4};
};
