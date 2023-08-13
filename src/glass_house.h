#pragma once

#include "mvector.h"

struct subdivision_node_obb_base;

struct glass_house
{
    int field_0;
    mVector<subdivision_node_obb_base> obbs;
    void render();
};
