#pragma once

#include "variable.h"
#include "float.hpp"
#include "fixedstring.h"

#include "nslbank.h"

inline constexpr auto SB_TYPE_LEVEL_COMMON = 8;
inline constexpr auto SB_TYPE_HERO = 9;
inline constexpr auto SB_TYPE_MOVIE = 10;
inline constexpr auto SB_TYPE_MISSION = 11;

inline constexpr auto SB_STATE_EMPTY = 0;
inline constexpr auto SB_STATE_LOADING = 1;
inline constexpr auto SB_STATE_LOADED = 2;

struct sound_bank_slot {
    fixedstring<8> field_0;
    int m_state;
    int field_24;
    nslBankID nsl_voice_bank_id;
    nslBankID nsl_non_voice_bank_id;
    int field_30;
    int field_34;

    int get_state();

    //0x00520160
    void unload();

    //0x0054CC30
    void load(const char *a1, const char *a2, bool a4, int a5);

    //0x00520200
    void frame_advance(Float a2);
};

extern Var<sound_bank_slot[12]> s_sound_bank_slots;

extern void sound_bank_slot_patch();
