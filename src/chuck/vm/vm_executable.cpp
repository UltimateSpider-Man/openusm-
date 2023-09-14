#include "vm_executable.h"

#include "common.h"
#include "script_executable.h"

VALIDATE_SIZE(vm_executable, 0x24u);

constexpr auto VM_EXECUTABLE_FLAG_FROM_MASH = 4u;

void vm_executable::un_mash(
        generic_mash_header *,
        void *a3,
        void *,
        generic_mash_data_ptrs *)
{
    assert(!is_un_mashed());
    this->owner = CAST(owner, a3);
    assert((flags & VM_EXECUTABLE_FLAG_FROM_MASH ) != 0);

    auto *v6 = this->field_10;
    auto *v5 = this->owner->field_4;

    auto sub_6A171C = [](script_executable *a1, unsigned int offset) -> int16_t *
    {
        assert(a1->sx_exe_image != nullptr && "We should have loaded the executable code from the sxl or sxb file");

        assert(offset < (uint32_t) a1->sx_exe_image_size && "offset into exec code is out of bounds... bad juju man");

        return &a1->sx_exe_image[offset >> 1];
    };

    this->field_10 = sub_6A171C(v5, (unsigned int)v6);
    this->flags |= 8u;
}

