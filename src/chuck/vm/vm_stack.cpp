#include "vm_stack.h"

#include <config.h>

#include <cstring>

void vm_stack::push(const char *a2, int a3) {
    std::memcpy(this->m_stack_pointer, a2, a3);
    this->m_stack_pointer += a3;
}

int vm_stack::pop_num() {
    auto v4 = this->m_stack_pointer - 4;
    this->m_stack_pointer = v4;
    return *bit_cast<int *>(v4);
}
