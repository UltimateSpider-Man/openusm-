#include "game_camera.h"

#include "common.h"
#include "func_wrapper.h"
#include "trace.h"

VALIDATE_SIZE(game_camera::_camera_shake_t, 0x1Cu);
VALIDATE_SIZE(game_camera, 0x1A0u);

void game_camera::_camera_shake_t::clear() {
    this->field_1A = 0;
    this->field_18 = -1;
    this->field_0 = 0;
    this->field_4 = 0;
    this->field_8 = 0;
    this->field_C = 0;
}

game_camera::_camera_shake_t::_camera_shake_t() {
    this->field_1A = 0;
    this->clear();
}

game_camera::game_camera(const string_hash &a2, [[maybe_unused]] entity *a3)
    : camera(nullptr, a2) {}

//FIXME 
entity *game_camera::get_target_entity()
{
    TRACE("game_camera::get_target_entity");

    if constexpr (0)
    {
        auto &v1 = this->field_118;
        auto *ent = v1.get_volatile_ptr();
        if (ent != nullptr)
        {
            ent = v1.get_volatile_ptr();
        }

        return ent;
    }
    else
    {
        return (entity *) THISCALL(0x0057A220, this);
    }

}

void game_camera::set_target_entity(entity *e) {
    if (e != nullptr) {
        this->field_118 = {e->get_my_handle()};
    } else {
        this->field_118 = {0};
    }
}
