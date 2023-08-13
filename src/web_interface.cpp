#include "web_interface.h"

#include "func_wrapper.h"

web_interface::web_interface()
{

}

void web_interface::frame_advance_all_web_interfaces(Float a1) {
    CDECL_CALL(0x004F2AC0, a1);
}
