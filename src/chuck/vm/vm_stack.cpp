#include "vm_stack.h"

#include <trace.h>

#include <config.h>
#include <debugutil.h>

#include <cassert>
#include <cstring>
#include <string>

void vm_stack::push(const char *a2, int a3) {
    TRACE("vm_stack::push(const char *, int)", std::to_string(a3).c_str());

    std::memcpy(this->SP, a2, a3);
    this->SP += a3;
}

void vm_stack::push(vm_str_t a2)
{
    TRACE("vm_stack::push(vm_str_t)", a2);

    assert(size() + sizeof( vm_str_t ) <= capacity());
    *(vm_str_t *) this->SP = a2;
    this->move_SP(sizeof(vm_str_t));
}

void vm_stack::push(vm_num_t a2)
{
    TRACE("vm_stack::push(vm_num_t)", std::to_string(a2).c_str());

    assert(size() + sizeof( vm_num_t ) <= capacity());
    *(vm_num_t *)this->SP = a2;
    this->move_SP(sizeof(vm_num_t));
}

void vm_stack::push(int a2)
{
    TRACE("vm_stack::push(int)");
    printf("0x%08X\n", a2);

    assert(size() + sizeof( int ) <= capacity());
    *(int *)this->SP = a2;
    this->move_SP(sizeof(int));
}

vm_num_t vm_stack::pop_num() {
    this->pop(sizeof(vm_num_t));
    return *bit_cast<vm_num_t *>(SP);
}

void vm_stack::move_SP(int n)
{
    assert(!(n & 3));

    assert(!((unsigned) SP & 3));
    this->SP += n;

    auto my_size = this->size();

    assert(my_size >= 0 && "underflow -> VM stack corruption");
    if ( my_size > this->capacity() )
    {
        auto v2 = this->capacity();
        debug_print_va("capacity: %d", v2);
        assert(0 && "overflow -> bad scripter");
    }
}
