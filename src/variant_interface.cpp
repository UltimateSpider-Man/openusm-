#include "variant_interface.h"

#include "common.h"
#include "func_wrapper.h"
#include "trace.h"

VALIDATE_SIZE(variant_interface, 0x58);

variant_interface::variant_interface()
{

}

variant_info *variant_interface::sub_4CAD00()
{
    return (variant_info *) THISCALL(0x004CAD00, this);
}

void variant_interface::apply_variant(variant_info *info)
{
    TRACE("variant_interface::apply_variant");
    THISCALL(0x004DB110, this, info);
}
