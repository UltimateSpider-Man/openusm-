#pragma once

#include "text_file.h"

inline constexpr auto CHUNK_FLAVOR_SIZE = 16u;

struct script_object;

struct chunk_flavor {
    char field_0[CHUNK_FLAVOR_SIZE];

    chunk_flavor() = default;

    chunk_flavor(const char *s);

    bool operator==(const chunk_flavor &a2) const;

    bool operator!=(const chunk_flavor &a2) const {
        return (!((*this) == a2));
    }
};

inline chunk_flavor CHUNK_END {"chunkend"};

inline chunk_flavor SCR_OBJ {"scrobj"};

struct chunk_file : text_file {

    void open(const mString &a1, int a3);

    void read(script_object *so);

    template<typename T>
    T read();
};

