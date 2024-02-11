#pragma once

#include "progress.h"
#include "resource_key.h"
#include "resource_pack_directory.h"
#include "resource_pack_token.h"

#include "float.hpp"

struct limited_timer;
struct resource_pack_streamer;
struct resource_directory;
struct resource_pack_header;
struct resource_partition;

enum slot_state_t {
    SLOT_STATE_EMPTY = 0,
    SLOT_STATE_STREAMING = 1,

    SLOT_STATE_READY = 4,
};

struct resource_pack_slot {
    enum callback_enum {
		CALLBACK_LOAD_STARTED = 0,
        CALLBACK_CONSTRUCT = 3,
        CALLBACK_PRE_DESTRUCT = 4,
        CALLBACK_DESTRUCT = 5,
    };

    int m_vtbl;

private:
    resource_key field_4;

public:
    
    slot_state_t m_slot_state;
    int slot_size;
    int pack_size;

private:
    uint8_t *header_mem_addr;

public:
    resource_pack_directory pack_directory;
    resource_pack_token field_78;
    progress field_80;
    int field_84;
    resource_partition *field_88;

    bool (*m_callback)(callback_enum,
                       resource_pack_streamer *,
                       resource_pack_slot *,
                       limited_timer *);
    bool field_90;

    //0x00531C70
    resource_pack_slot();

    auto &get_name_key() const
    {
        return field_4;
    }

	resource_pack_token &get_pack_token()
	{
		assert(m_slot_state != SLOT_STATE_EMPTY);
	  	return this->field_78;
	}

    auto *get_header_mem_addr()
    {
        return header_mem_addr;
    }

    inline bool is_pack_unloading() {
        return (m_slot_state == 3);
    }

    auto get_slot_size() const
    {
        return slot_size;
    }

    bool is_data_ready();

    inline bool is_pack_ready() {
        return (m_slot_state == 4);
    }

    resource_directory &get_resource_directory();

    void set_resource_directory(resource_directory *directory);

    void notify_unload_started();

    //0x0050E240
    void notify_load_started(const resource_key &a2,
                             uint32_t a3,
                             bool (*cb)(resource_pack_slot::callback_enum,
                                        resource_pack_streamer *,
                                        resource_pack_slot *,
                                        limited_timer *),
                             const resource_pack_token &a5);

    void notify_load_finished();

    void set_memory_area(uint8_t *starting_addr, uint32_t how_many_bytes, bool a4);

    //0x0050E210
    bool try_callback(callback_enum a2, limited_timer *a3);

    bool is_empty();

    uint8_t *get_resource(const resource_key &resource_id, int *a3, resource_pack_slot **a4);

    bool slot_allocators_empty();

    //0x005429F0
    void frame_advance(Float a2, limited_timer *a3);

    //0x0052A980
    static void *slot_allocate(unsigned int a1, unsigned int a2);

    static Var<resource_pack_slot *> current_alloc_slot;

    //0x0050E1B0
    //virtual
    bool on_load(limited_timer *a1);

    //0x0052A910
    //virtual
    bool on_unload(limited_timer *a2);

    //0x00531CF0
    //virtual
    ~resource_pack_slot();

    //0x0050E170
    //virtual
    void clear_slot();

    //0x0052A8B0
    //virtual
    void clear_pack();
};

struct ptr_to_resource_pack_slot {
    resource_pack_slot *field_0;
};

extern void resource_pack_slot_patch();
