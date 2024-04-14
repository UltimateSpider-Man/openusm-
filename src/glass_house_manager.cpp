#include "glass_house_manager.h"

#include "func_wrapper.h"
#include "log.h"
#include "os_developer_options.h"
#include "utility.h"
#include "glass_house.h"

bool glass_house_manager::is_enabled() {
    bool result = enabled() && os_developer_options::instance()->get_flag(static_cast<os_developer_options::flags_t>(122));

    return result;
}

bool glass_house_manager::is_point_in_glass_house(const vector3d &a1) {
    return (bool) CDECL_CALL(0x00538570, &a1);
}

void glass_house_manager::show_glass_houses()
{
    for ( auto i = 0; i < 3; ++i )
    {
        auto &array = glass_houses()[i];
        for (auto &h : array)
        {
            h->render();
        }
    }
}

void glass_house_manager_patch() {
    REDIRECT(0x004645E6, glass_house_manager::is_enabled);
    REDIRECT(0x005BB673, glass_house_manager::is_enabled);
    REDIRECT(0x007421D2, glass_house_manager::is_enabled);
}
