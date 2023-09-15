#include "text_file.h"

#include "func_wrapper.h"
#include "memory.h"

text_file::text_file()
    : os_file(),
#ifdef _STDEX_NATIVE_CPP11_SUPPORT
      field_34()
#endif
{
#ifndef _STDEX_NATIVE_CPP11_SUPPORT
    this->field_34 = mString();
#endif

    this->field_44 = arch_memalign(32u, 2048u);
    this->field_48 = 0;
    this->field_4C = 0;
    this->field_50 = 0;
    this->field_54 = -1;
}

bool text_file::is_open() {
    return this->opened || this->field_50;
}

void text_file::read(char *a2, int a3) {
    THISCALL(0x005D2DD0, this, a2, a3);
}

void text_file::read(int *a2)
{
    THISCALL(0x005D26C0, this, a2);
}

void text_file::read(mString *a1)
{
    THISCALL(0x005D5970, this, a1);
}
