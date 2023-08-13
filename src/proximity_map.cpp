#include "proximity_map.h"

#include "func_wrapper.h"
#include "sector2d.h"
#include "vector3d.h"

#include <cassert>

int proximity_map::traverse_point(const vector3d &a2, subdivision_visitor &a3) {
    return THISCALL(0x005115E0, this, &a2, &a3);
}

void proximity_map::traverse_sector_raster(const sector2d &sec,
                                           Float sector_radius,
                                           subdivision_visitor &visitor) {
    assert(sector_radius > EPSILON);
    assert(is_initialized());

    THISCALL(0x00522680, this, &sec, sector_radius, &visitor);
}

bool proximity_map::is_initialized() {
    return this->initialized;
}

void dynamic_proximity_map::init(dynamic_proximity_map_stack *alloc, fixed_pool *a3, int number_of_cells_arg, const vector3d &a5, const vector3d &a6, subdivision_node::type_t cell_node_type)
{
    assert(cell_node_type == subdivision_node::DYNAMIC_ENTITY_LIST_NODE || cell_node_type == subdivision_node::DYNAMIC_LEAF_LIST_NODE);
    assert(alloc != nullptr);
    assert(number_of_cells == number_of_cells_arg);

    assert(map_type == DYNAMIC);

    THISCALL(0x00522500, this, alloc, a3, number_of_cells_arg, &a5, &a6, cell_node_type);
}
