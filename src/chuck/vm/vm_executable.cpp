#include "vm_executable.h"

#include "common.h"
#include "script_executable.h"
#include "script_object.h"
#include "trace.h"

VALIDATE_SIZE(vm_executable, 0x24u);

constexpr auto VM_EXECUTABLE_FLAG_FROM_MASH = 4u;

void vm_executable::un_mash(
        generic_mash_header *,
        void *a3,
        void *,
        generic_mash_data_ptrs *)
{
    TRACE("vm_executable::un_mash");

    assert(!is_un_mashed());
    this->owner = CAST(owner, a3);
    assert((flags & VM_EXECUTABLE_FLAG_FROM_MASH ) != 0);

    auto offset = bit_cast<uint32_t>(this->buffer);
    auto *v5 = this->owner->parent;

    this->buffer = v5->get_exec_code(offset);
    this->flags |= 8u;
}

