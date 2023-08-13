#pragma once

struct mash_info_struct;

namespace als
{
    struct post_kill_rule
    {
        int field_0;
        int field_4;

        void unmash(mash_info_struct *, void *);
    };
}
