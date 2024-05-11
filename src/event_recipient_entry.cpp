#include "event_recipient_entry.h"

#include "code_event_callback.h"
#include "common.h"
#include "event.h"
#include "func_wrapper.h"
#include "memory.h"
#include "vm.h"

VALIDATE_SIZE(event_recipient_entry, 0x28u);

event_recipient_entry::event_recipient_entry(
        entity_base_vhandle a2,
        bool )
{
    this->field_0 = a2;
    this->field_20 = 0;
    this->field_24 = 0;
}

void * event_recipient_entry::operator new(size_t size)
{
    return mem_alloc(size);
}

int event_recipient_entry::add_callback(void (*cb)(event *, entity_base_vhandle, void *),
                                        void *a3,
                                        bool a4)
{
    if constexpr (0)
    {
        auto *new_callback = new code_event_callback {cb, a3, a4};
        assert(new_callback != nullptr && "probably out of memory");

        this->field_4.push_back(new_callback);
        return new_callback->id;
    }
    else
    {
        return THISCALL(0x004D6260, this, cb, a3, a4);
    }
}

int event_recipient_entry::add_callback(script_instance *a2,
                                        const vm_executable *a3,
                                        char *a4,
                                        bool a5)
{
    if constexpr (0)
    {}
    else
    {
        return THISCALL(0x004C02A0, this, a2, a3, a4, a5);
    }
}

bool event_recipient_entry::callback_exists(int a2) const
{
    if ( a2 == 0 ) {
        return false;
    }

    for ( auto &v3 : this->field_4 )
    {
        if ( v3->id == a2 ) {
            return true;
        }
    }

    return false;
}
