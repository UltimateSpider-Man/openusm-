#include "district_graph_container.h"

#include "common.h"
#include "func_wrapper.h"
#include "terrain.h"
#include "trace.h"

VALIDATE_SIZE(dsg_box_container, 0x34);

VALIDATE_SIZE(district_graph_container, 0x14);

void district_graph_container::setup_terrain(terrain *the_terrain) {
    TRACE("district_graph_container::setup_terrain");

    THISCALL(0x00556640, this, the_terrain);
}

void dsg_region_container::un_mash(generic_mash_header *a2,
                                   [[maybe_unused]] void *a3,
                                   generic_mash_data_ptrs *a4)
{
    if constexpr (1)
    {
        uint32_t v4 = 4 - ((uint32_t) a4->field_0 & 3);
        if (v4 < 4) {
            a4->field_0 += v4;
        }

        auto v5 = *(uint32_t *) a4->field_0;
        auto *v6 = (uint8_t *) ((uint32_t) a4->field_0 + 4);
        a4->field_0 = v6;
        this->field_0 = (char *) v6;
        a4->field_0 += v5;
        this->field_48.custom_un_mash(a2, &this->field_48, a4, nullptr);
    }
    else
    {
        assert(0);
    }
}


void district_graph_container::un_mash_start(generic_mash_header *a2,
                                       void *a3,
                                       generic_mash_data_ptrs *a4,
                                       [[maybe_unused]] void *a5)
{
    this->un_mash(a2, a3, a4);
}

void district_graph_container::un_mash(generic_mash_header *a2,
                                       [[maybe_unused]] void *a3,
                                       generic_mash_data_ptrs *a4)
{
    TRACE("district_graph_container::un_mash");

    if constexpr (0)
    {
        this->field_0.custom_un_mash(a2, &this->field_0, a4, nullptr);
        this->field_8.custom_un_mash(a2, &this->field_8, a4, nullptr);
    }
    else
    {
        THISCALL(0x00520C90, this, a2, a3, a4);
    }
}

void dsg_box_container::un_mash([[maybe_unused]] generic_mash_header *a2,
                                [[maybe_unused]] void *a3,
                                [[maybe_unused]] generic_mash_data_ptrs *a4) {
    ;
}
