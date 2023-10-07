#pragma once

#include <list.hpp>

struct script_executable;
struct mString;

struct script_executable_allocated_stuff_record {
    void (*field_0)(script_executable *, _std::list<uint32_t> &, _std::list<mString> &);
    _std::list<uint32_t> field_4;
    _std::list<mString> field_10;

    script_executable_allocated_stuff_record() = default;
};
