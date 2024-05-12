#include "devopt.h"

#include "os_developer_options.h"

game_option_t *get_option(int idx)
{
    constexpr auto NUM_OPTIONS = 150;

    assert(idx >= 0);
    assert(idx < NUM_OPTIONS);

    static game_option_t option{};

    auto &name = flag_names[idx];
    BOOL *flag = &flag_defaults[idx];

    option.m_name = name;
    option.m_type = game_option_t::INT_OPTION;
    option.m_value.p_bval = flag;

    return &option;
}
