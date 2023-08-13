#pragma once

struct terrain;
struct region;

struct region_lookup_cache {
    //0x00514290
    static void init(terrain *a1);

    //0x00523D50
    static region *lookup_by_district_id(int a1);
};
