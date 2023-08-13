#pragma once

#include <fixedstring.h>
#include <variable.h>

#include <tl_instance_bank.h>

struct nalInitList {
    std::intptr_t m_vtbl;
    void *field_4;

    nalInitList();

    static Var<void *> head;

    /* virtual */ tlInstanceBank::Node *Register() /* = 0 */;
};

struct nalInitListAnimType : nalInitList {
    tlFixedString field_8;
    std::intptr_t anim_vtbl_ptr;
    std::intptr_t skel_vtbl_ptr;

    nalInitListAnimType(const char *str,
                        std::intptr_t anim_vtbl_ptr_arg,
                        std::intptr_t skel_vtbl_ptr_arg)
        : nalInitList(), field_8(str), anim_vtbl_ptr(anim_vtbl_ptr_arg),
          skel_vtbl_ptr(skel_vtbl_ptr_arg) {}

    /* virtual */ tlInstanceBank::Node *Register() /* override */;
};

struct nalComponentInitList : nalInitList {
    const char *field_8;
    void *field_C;

    nalComponentInitList(const char *str, void *a3) : nalInitList(), field_8(str), field_C(a3) {}

    /* virtual */ tlInstanceBank::Node *Register() /* override */;
};

//0x0078AE10
extern void nalInitListInit();
