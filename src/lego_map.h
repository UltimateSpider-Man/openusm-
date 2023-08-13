#pragma once

#include <cstdint>

struct nglMesh;
struct nglMaterialBase;
struct scene_entity;
struct proximity_map;

struct lego_map_root_node {
    nglMesh **field_0;
    nglMaterialBase **field_4;
    scene_entity *field_8;
    proximity_map *field_C;
    int field_10;
    int field_14;
    int field_18;
    uint16_t field_1C;

    lego_map_root_node();
};
