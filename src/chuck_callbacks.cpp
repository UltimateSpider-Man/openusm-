#include "chuck_callbacks.h"

#include "event_manager.h"
#include "resource_manager.h"
#include "script_controller.h"
#include "trace.h"
#include "utility.h"

void script_manager_callback(script_manager_callback_reason a1, script_executable *a2, const char *buffer)
{
    TRACE("script_manager_callback", std::to_string(int(a1)).c_str());

    switch ( a1 )
    {
    case 0:
    case 2:
    case 3:
    case 6:
    case 7:
        return;
    case 1:
        event_manager::clear_script_callbacks(script_pad()[0].my_handle, a2);
        event_manager::clear_script_callbacks(script_pad()[1].my_handle, a2);
        break;
    case 4:
        assert(buffer != nullptr);
        sp_log(buffer);
        assert(0);
        break;
    case 8:
    case 10:
        if ( buffer != nullptr ) {
            resource_manager::push_resource_context((resource_pack_slot *) buffer);
        }
        break;
    case 9:
    case 11:
        resource_manager::pop_resource_context();
        break;
    default:
        assert(0 && "unknown reason for script manager to call me:(");
        return;
    }
}

void chuck_callbacks_patch() {
    SET_JUMP(0x00660760, script_manager_callback);
}
