#include "line_info.h"

#include "common.h"
#include "func_wrapper.h"
#include "utility.h"

#include <cassert>

VALIDATE_SIZE(line_info, 0x5C);

line_info::line_info() {
    this->field_48 = {0};
    this->field_58 = false;
    this->field_59 = false;
    this->field_5A = false;
    this->clear();
}

line_info::line_info(const vector3d &a2, const vector3d &a3) : line_info() {
    this->field_0 = a2;
    this->field_C = a3;
}

line_info::~line_info() {
    this->release_mem();
}

#ifndef TEST_CASE

int num_debug_line_info[2]{};

std::array<line_info[64], 2> debug_line_info{};
#endif

static constexpr auto MAX_RENDERABLE_LINE_INFOS = 64;

void line_info::render(int num, bool a3) {
    assert(num >= 0);

    assert(num < MAX_RENDERABLE_LINE_INFOS &&
           "If you need to render more line-info's edit line_info.cpp (Or reduce the usage!)");

    if (num < MAX_RENDERABLE_LINE_INFOS) {
        if (a3) {
            if (num > num_debug_line_info[0]) {
                num_debug_line_info[0] = num;
            }

            debug_line_info[0][num].copy(*this);

        } else {
            if (num > num_debug_line_info[1]) {
                num_debug_line_info[1] = num;
            }

            debug_line_info[1][num].copy(*this);
        }
    }
}

void line_info::clear() {
    if constexpr (1) {
        this->field_58 = false;
        this->field_59 = false;
        this->field_48.field_0.field_0 = 0;

        this->hit_norm = ZVEC;
        this->hit_pos = ZEROVEC;
        this->field_30 = ZEROVEC;
        this->field_3C = ZVEC;
        this->field_4C = nullptr;
        if (this->field_5A) { // line_info::remove_to_collision_check_queue()
            auto *a2 = this;

            queued_collision_checks().find(a2, 1);
            this->field_5A = false;
        }
    } else {
        THISCALL(0x0048C9D0, this);
    }
}

bool line_info::check_collision(const local_collision::entfilter_base &a2,
                                const local_collision::obbfilter_base &a3,
                                line_info_local_query *a4) {
    return (bool) THISCALL(0x0052EE20, this, &a2, &a3, a4);
}

bool line_info::remove_to_collision_check_queue() {
    if constexpr (1) {
        auto result = line_info::queued_collision_checks().find(this, 1);
        this->field_5A = false;
        return result;

    } else {
        return (bool) THISCALL(0x0052EE00, this);
    }
}

bool line_info::release_mem() {
    return this->remove_to_collision_check_queue();
}

void line_info::copy(const line_info &a2) {
    THISCALL(0x006B6E00, this, &a2);
}

bool is_noncrawlable_surface(line_info &a1) {
    return (bool) CDECL_CALL(0x0068A9D0, &a1);
}

void line_info::frame_advance(int a1) {
    CDECL_CALL(0x0052F120, a1);
}

void line_info_patch() {
    {
        FUNC_ADDRESS(address, &line_info::render);
        SET_JUMP(0x00519F00, address);
    }
}
