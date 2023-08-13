#pragma once

struct region;

struct region_audio_box_set {
    int field_0[8];

    region_audio_box_set();

    //0x00520600
    int un_mash(char *a2, int *a3, region *a4);
};
