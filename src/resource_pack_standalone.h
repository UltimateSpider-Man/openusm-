#pragma once

#include "nfl_system.h"
#include "resource_pack_header.h"

struct mString;
struct resource_directory;
struct resource_location;

struct resource_pack_standalone {
    std::intptr_t m_vtbl;
    resource_pack_header m_header;
    nflFileID m_filedID;
    resource_directory *res_dir;
    void *res_dir_mash;

    int base_offset;
    resource_key name;

    //0x0052AB30
    resource_pack_standalone();

    //0x0050E430
    nflFileID get_nfl_file_handle();

    //0x0051F8B0
    //virtual
    bool get_unloaded_resource_location(const resource_key &a1, resource_location *location_struct);

    //0x0052ABB0
    //virtual
    void unload();

    //0x0053E380
    //virtual
    bool load(const mString &str);
};

extern void sub_732D60(bool a1);

extern void resource_pack_standalone_patch();
