#pragma once

struct mash_info_struct;

namespace als
{
    struct filter_data {
        int field_0;
        int field_4;
        int field_8;

        void unmash(mash_info_struct *, void *) {}
    };
}
