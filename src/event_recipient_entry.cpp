#include "event_recipient_entry.h"

#include "event.h"
#include "func_wrapper.h"
#include "vm.h"

event_recipient_entry::event_recipient_entry()
{

}

int event_recipient_entry::add_callback(void (*cb)(event *, entity_base_vhandle, void *),
                                        void *a3,
                                        bool a4) {
    return THISCALL(0x004D6260, this, cb, a3, a4);
}

int event_recipient_entry::add_callback(script_instance *a2,
                                        const vm_executable *a3,
                                        char *a4,
                                        bool a5) {
    return THISCALL(0x004C02A0, this, a2, a3, a4, a5);
}
