#pragma once

struct mContainer_base {
    int field_0;
    int m_size;

    void clear();

    bool is_pointer_in_mash_image(void *a3) const;
};
