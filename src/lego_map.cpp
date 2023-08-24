#include "lego_map.h"

#include "func_wrapper.h"
#include "trace.h"

lego_map_root_node::lego_map_root_node() {}

void lego_map_root_node::un_mash(char *image, int *a3, region *reg)
{
    TRACE("lego_map_root_node::un_mash");

    THISCALL(0x0054E5A0, this, image, a3, reg);
}
