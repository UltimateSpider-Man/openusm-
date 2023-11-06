#include "plr_loco_crawl_transition_state.h"

#include "func_wrapper.h"
#include "trace.h"
#include "utility.h"

plr_loco_crawl_transition_state::plr_loco_crawl_transition_state()
{

}

void plr_loco_crawl_transition_state::activate(
        ai::ai_state_machine *a2,
        const ai::mashed_state *a4,
        const ai::mashed_state *a5,
        const ai::param_block *a6,
        ai::base_state::activate_flag_e a7)
{
    TRACE("plr_loco_crawl_transition_state::activate");

    THISCALL(0x0046A340, this, a2, a4, a5, a6, a7);
}

void plr_loco_crawl_transition_state::deactivate(
        const ai::mashed_state *a1)
{
    TRACE("plr_loco_crawl_transition_state::deactivate");

    THISCALL(0x0046A9A0, this, a1);
}

void plr_loco_crawl_transition_state_patch()
{
    {
        FUNC_ADDRESS(address, &plr_loco_crawl_transition_state::activate);
        set_vfunc(0x00875E30, address);
    }

    {
        FUNC_ADDRESS(address, &plr_loco_crawl_transition_state::deactivate);
        set_vfunc(0x00875E34, address);
    }
}
