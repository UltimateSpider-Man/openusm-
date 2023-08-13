#include "universal_soldier_inode.h"

#include "common.h"
#include "from_mash_in_place_constructor.h"
#include "func_wrapper.h"

namespace ai {

VALIDATE_SIZE(universal_soldier_inode, 0x78);

universal_soldier_inode::universal_soldier_inode(from_mash_in_place_constructor *a2) {
    THISCALL(0x006B58F0, this, a2);
}
} // namespace ai
