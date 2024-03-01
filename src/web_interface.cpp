#include "web_interface.h"

#include "func_wrapper.h"
#include "trace.h"
#include "utility.h"

web_interface::web_interface()
{

}

void web_interface::frame_advance_all_web_interfaces(Float a1)
{
    TRACE("web_interface::frame_advance_all_web_interfaces");

    CDECL_CALL(0x004F2AC0, a1);
}

void web_interface_patch()
{
    REDIRECT(0x0055850C, web_interface::frame_advance_all_web_interfaces);
}
