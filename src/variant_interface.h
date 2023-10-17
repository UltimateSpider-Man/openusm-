#pragma once

#include "generic_interface.h"
#include "string_hash.h"

struct conglomerate;
struct variant_info;
struct nglMeshFile;

struct variant_interface : generic_interface {
    conglomerate *field_4;
    bool field_8;
    variant_info *field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    nglMeshFile *field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
    int field_54;

    variant_interface();

    variant_info *sub_4CAD00();

    void apply_variant(string_hash a2);

    void apply_variant(variant_info *info);

};

extern void variant_interface_patch();
