#include "region_lookup_cache.h"

#include "func_wrapper.h"
#include "region.h"
#include "terrain.h"

void region_lookup_cache::init(terrain *a1) {
    CDECL_CALL(0x00514290, a1);
}

region *region_lookup_cache::lookup_by_district_id(int a1) {
    return (region *) CDECL_CALL(0x00523D50, a1);
}
