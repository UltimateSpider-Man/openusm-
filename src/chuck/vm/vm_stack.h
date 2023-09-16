#pragma once

using vm_num_t = float;
typedef const char * vm_str_t;

struct vm_stack {
    int field_0[96];
    char *buffer;
    char *SP;
    int **field_188;

    int capacity() const {
        return 384;
    }

    int size() const {
        return this->SP - this->buffer;
    }

    vm_num_t& top_num() {
        return *(vm_num_t *)(SP - sizeof(vm_num_t));
    }

    vm_str_t& top_str() {
        return *(vm_str_t*)(SP - sizeof(vm_str_t));
    }

    //0x00502AC0
    void push(const char *a2, int a3);

    void push(vm_str_t);

    void push(vm_num_t a2);

    void push(int);

    char *get_SP() const
    {
        return this->SP;
    }

    void set_SP(char *sp) {
        SP = sp;
    }

    void move_SP(int n);

    void pop(int n)
    {
        this->move_SP(-n);
    }

    void* pop_addr()
    {
        this->pop(sizeof(void *));
        return *(void**)SP;
    }

    vm_str_t pop_str()
    {
        this->pop(sizeof(vm_str_t));
        return *(vm_str_t *)SP;
    }

    vm_num_t pop_num();
};
