#include "controller.h"

#include "memory.h"

controller::controller()
{

}

void * controller::operator new(size_t size)
{
    return mem_alloc(size);
}

void controller::kill() {
    this->field_4 = false;
}

void controller::resurrect() {
    this->field_4 = true;
}
