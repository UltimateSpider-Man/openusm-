#pragma once

#include "float.hpp"

struct resource_key;
struct token_def_list;

struct wds_token_manager {
    token_def_list *tokens;
    bool field_4;
    char field_5;
    float field_8;
    int field_C;
    int token_collected_array;
    char field_14;
    int field_18;
    int *field_1C;

    //0x005586A0
    void initialize(const resource_key &a2);

    //0x00555B50
    void frame_advance(Float a1);
};

extern void wds_token_manager_patch();
