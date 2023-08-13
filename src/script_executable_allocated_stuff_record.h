#pragma once

#include <list.hpp>

struct script_executable;
struct mString;

struct script_executable_allocated_stuff_record {
    void (*field_0)(script_executable *, _std::list<uint32_t> &, _std::list<mString> &);
    _std::list<void *> field_4;
    int field_10;
    int field_14;
    int field_18;

    script_executable_allocated_stuff_record();
};
