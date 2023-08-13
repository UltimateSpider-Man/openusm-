#pragma once

struct game_process {
    const char *field_0;
    int *field_4;
    int index;
    int num_states;
    int field_10;
    bool field_14;

    game_process(const char *a2, int *a3, int a4);

    void reset_index();

    void go_next_state();
};
