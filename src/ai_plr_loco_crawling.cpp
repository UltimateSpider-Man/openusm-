#include "ai_plr_loco_crawling.h"

#include "func_wrapper.h"
#include "trace.h"

line_info *check_interior_transition(
        actor *a1,
        ai::crawl_params_record &a2,
        ai::als_inode *a3,
        bool a4,
        bool a5,
        bool a6)
{
    TRACE("check_interior_transition");

    line_info * (*func)(actor *,
                    ai::crawl_params_record *a2,
                    ai::als_inode *a3,
                    bool a4,
                    bool a5,
                    bool a6) = CAST(func, 0x0047B1E0);
    return func(a1, &a2, a3, a4, a5, a6);
}

line_info *check_exterior_transition(
        actor *a1,
        ai::crawl_params_record &a2,
        ai::als_inode *a3,
        bool a4,
        bool a5,
        bool a6)
{
    TRACE("check_exterior_transition");

    line_info * (*func)(actor *,
                    ai::crawl_params_record *a2,
                    ai::als_inode *a3,
                    bool a4,
                    bool a5,
                    bool a6) = CAST(func, 0x0047BFF0);
    return func(a1, &a2, a3, a4, a5, a6);
}
