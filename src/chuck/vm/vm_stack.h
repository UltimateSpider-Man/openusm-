#pragma once

struct vm_stack {
    int field_0[97];
    char *m_stack_pointer;
    int **field_188;

    //0x00502AC0
    void push(const char *a2, int a3);

    int pop_num();
};
