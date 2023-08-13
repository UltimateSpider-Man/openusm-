#pragma once

#include "resource_pack_streamer.h"

struct resource_pack_slot;
struct worldly_pack_slot;

enum resource_partition_enum {
    RESOURCE_PARTITION_START = 0,
    RESOURCE_PARTITION_HERO = 1,
    RESOURCE_PARTITION_MISSION = 3,
    RESOURCE_PARTITION_COMMON = 4,
    RESOURCE_PARTITION_STRIP = 5,
    RESOURCE_PARTITION_DISTRICT = 6,
    RESOURCE_PARTITION_END = 8,
};

struct resource_partition {
    int field_0;
    resource_partition_enum field_4;

    _std::vector<resource_pack_slot *> m_pack_slots;

    resource_pack_streamer streamer;

    uint8_t *field_A8;
    int partition_buffer_used;
    int partition_buffer_size;

    //0x005427C0
    resource_partition(resource_partition_enum a2);

    //0x0053DFD0
    ~resource_partition();

    //0x00556090
    void frame_advance(Float a1, limited_timer *a2);

    //0x0050E010
    bool has_room_for_slot(int a2);

    //0x00537B30
    void clear();

    //0x00542840
    void push_pack_slot(int memory_amount_to_reserve, void *a3);

    //0x00537BB0
    void pop_pack_slot();

    resource_pack_streamer *get_streamer() {
        return (&streamer);
    }

    auto &get_pack_slots() {
        return this->m_pack_slots;
    }
};

extern void resource_partition_patch();
