#pragma once

#include <variable.h>

#include <list.hpp>

#include <cstdint>

struct vm_stack;

#define NAME_FIELD 1

struct script_library_class {
    struct function {
        enum entry_t {
            FIRST_ENTRY,
            RECALL_ENTRY,
        };

        std::intptr_t m_vtbl;

#if NAME_FIELD
        const char *field_4;
#endif

        //0x0058EE30
        function(const char *name);

        //0x0058EDE0
        function(script_library_class *a2, const char *a3);

        //0x006794B0
        /* virtual */ bool operator()(vm_stack &a2,
                                      script_library_class::function::entry_t a3) const;

#if NAME_FIELD
        inline const char *get_name() {
            return this->field_4;
        }
#endif
    };

    std::intptr_t m_vtbl;
    char *name;
    int field_8;
    const char *field_C;
    script_library_class::function **funcs;
    int total_funcs;
    int next_func_slot;
    uint32_t field_1C;

    script_library_class() = default;

    //0x005AA860
    script_library_class(
        const char *a2,
        int a3,
        const char *a4,
        bool a5);

    bool operator<(const script_library_class &slc) const {
        return strcmp(this->get_name(), slc.get_name()) < 0;
    }

    void store_name(const char *a2);

    int get_size() const {
        return this->field_8;
    }

    const char *get_name() const;

    function *get_func(int index);

    bool are_funcs_from_mash() const
    {
        return (this->field_1C & 1) != 0;
    }

    void add_function(script_library_class::function *a2);
};

struct slc_str_t : script_library_class {};

struct slc_num_t : script_library_class {};

extern Var<script_library_class *> slc_global;

extern Var<slc_num_t *> slc_num;

extern Var<slc_str_t *> slc_str;

extern void script_library_class_patch();
