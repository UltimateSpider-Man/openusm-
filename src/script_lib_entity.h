#pragma once

#include "script_library_class.h"

struct entity;
using vm_entity_t = entity *;

struct slc_entity_t : script_library_class {
    slc_entity_t(const char *n, int sz, const char *p = nullptr) : script_library_class(n, sz, p, false) { 
        m_vtbl = 0x0089A4C0;                                      
    }                                                       
};

extern slc_entity_t *slc_entity;

extern void register_entity_lib();

extern void script_lib_entity_patch();
