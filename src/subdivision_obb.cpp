#include "subdivision_obb.h"

#include "common.h"
#include "osassert.h"
#include "subdivision_node_obb_base.h"

#include <cassert>

VALIDATE_SIZE(subdivision_node_large_aabb, 0x24);

VALIDATE_SIZE(subdivision_node_large_obb, 0x48);

void check_for_degeneracies(subdivision_node_obb_base *obb)
{
    vector3d a1[3] {};
    obb->unpack_axii(a1);

    for ( int i = 0; i < 3; ++i )
    {
        if ( dot(a1[i], a1[i]) <= 0.00019999999 )
        {
            auto func = [](subdivision_node_obb_base *self) -> vector3d
            {
                return self->field_4;
            };

            auto v3 = func(obb)[2];
            auto v2 = func(obb)[1];
            auto v1 = func(obb)[0];
            error("Data error: degenerate (thin) obb found at (%.2f, %.2f, %.2f).\n"
                "Please correct the obb in the MAX file corresponding to these coordinates.\n"
                "(This error can be ignored more or less safely)",
                v1,
                v2,
                v3);
        }
    }
}


bool subdivision_node_large_aabb::init(
        uint16_t a2,
        uint32_t terrain_type_info_arg,
        const vector3d &a4,
        const vector3d &a5)
{
    this->field_14 = a2;
    std::memset(&this->field_0[1], 0, 3);
    this->field_4 = ZEROVEC;
    this->field_0[0] = 5;
    this->field_4 = a4;
    this->field_18 = a5;

    assert(!( terrain_type_info_arg & 0xFF000000 ));

    std::memcpy(&this->field_0[1], &terrain_type_info_arg, 3);

    check_for_degeneracies(bit_cast<subdivision_node_obb_base *>(this));

    return true;
}

bool subdivision_node_large_obb::init(
        uint16_t a2,
        uint32_t terrain_type_info_arg,
        const vector3d &a4,
        const vector3d &a5,
        const vector3d &a6,
        const vector3d &a7)
{
    this->field_14 = a2;
    this->field_0[1] = 0;
    this->field_0[3] = 0;
    this->field_4 = ZEROVEC;
    this->field_0[0] = 7;
    this->field_4 = a4;
    this->field_18 = a5;
    this->field_24 = a6;
    this->field_30 = a7;

    this->x_length = this->field_18.length();
    this->y_length = this->field_24.length();
    this->z_length = this->field_30.length();

    assert(x_length > EPSILON && y_length > EPSILON && z_length > EPSILON);

    this->field_18 /= this->x_length;

    this->field_24 /= this->y_length;

    this->field_30 /= this->z_length;

    assert(!( terrain_type_info_arg & 0xFF000000 ));

    std::memcpy(&this->field_0[1], &terrain_type_info_arg, 3);

    check_for_degeneracies(bit_cast<subdivision_node_obb_base *>(this));

    return true;
}
