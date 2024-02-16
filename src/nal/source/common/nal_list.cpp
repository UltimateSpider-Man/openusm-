#include <nal_list.h>

#include <common.h>
#include <log.h>
#include <vtbl.h>

#include <nal_system.h>

VALIDATE_SIZE(nalInitListAnimType, 0x30);

Var<void *> nalInitList::head{0x00977154};

nalInitList::nalInitList() {
    this->field_4 = head();
    head() = this;
}

tlInstanceBank::Node *nalInitListAnimType::Register() {
    sp_log("0x%08X %s", field_8.m_hash, field_8.to_string());

    return nalTypeInstanceBank().Insert(this->field_8, this);
}

tlInstanceBank::Node *nalComponentInitList::Register() {
    tlFixedString v3{this->field_8};

    //sp_log("%d %s", v3.m_hash, v3.to_string());

    return nalComponentInstanceBank().Insert(v3, this->field_C);
}

void nalInitListInit() {
    nalInitList *v0 = static_cast<decltype(v0)>(nalInitList::head());
    while (v0 != nullptr) {
        void (__fastcall *Register)(void *) = CAST(Register, get_vfunc(v0->m_vtbl, 0x0));

        Register(v0);

        v0 = static_cast<decltype(v0)>(v0->field_4);
    }
}
