#include "game_button.h"

#include "common.h"
#include "func_wrapper.h"
#include "input_mgr.h"
#include "memory.h"
#include "slab_allocator.h"

#include <cassert>

VALIDATE_SIZE(game_button, 0x34u);

game_button::game_button() {
    if constexpr (0) {
        this->field_4 = input_mgr::instance()->field_58;
        this->field_C = nullptr;
        this->field_10 = nullptr;
        this->m_flags = 0;
        this->m_trigger_type = 4;
        this->field_2C = 0.0;
        this->set_control((game_control_t) 0);
        this->clear();
    } else {
        THISCALL(0x0048D9A0, this);
    }
}

void game_button::override(Float a2, Float a3, Float a4) {
    THISCALL(0x0050B640, this, a2, a3, a4);
}

double game_button::sub_55ED50() {
    double result = 0.0;

    if ((this->m_flags & 0x20) == 0) {
        result = this->field_14;
    }

    return result;
}

bool game_button::sub_48B290() {
    auto v1 = this->m_flags;

    bool result = false;

    if ((v1 & 0x20) == 0) {
        result = ((v1 & 2) != 0);
    }

    return result;
}

bool game_button::sub_48B270() {
    bool result = false;

    auto v1 = this->m_flags;
    if ((v1 & 0x20) == 0) {
        result = v1 & 1;
    }

    return result;
}

double game_button::sub_55ED30() {
    double result = 0.0;

    if ((this->m_flags & 0x20) == 0) {
        result = this->field_18;
    }

    return result;
}

void game_button::update(Float a2) {
    if constexpr (0) {
        auto *v3 = this->field_C;
        if (v3 == nullptr) {
            auto v37 = input_mgr::instance()->get_control_state(this->field_8,
                                                                this->field_4);
            auto v35 = input_mgr::instance()->get_control_delta(this->field_8,
                                                                this->field_4);
            this->override(a2, v37, v35);
            return;
        }

        v3->update(a2);
        auto *v6 = this->field_10;
        if (v6 != nullptr) {
            auto v8 = this->m_flags;
            if ((v8 & 8) != 0) {
                auto *v9 = this->field_C;
                if ((v9->m_flags & 0x20) == 0 && (v9->m_flags & 1) != 0) {
                    this->override(a2, 0.0, 0.0);
                    return;
                }

                this->m_flags = v8 & 0xFFF7;
            }

            v6->update(a2);

            float a2b;

            switch (this->m_trigger_type) {
            case 0: {
                auto *v10 = this->field_10;
                auto *v11 = this->field_C;
                auto a2c = v10->sub_55ED30();
                auto v12 = v11->sub_55ED30();
                auto *v13 = v10;
                if (v12 >= a2c) {
                    v13 = v11;
                }

                a2b = v13->sub_55ED30();
                if (!v11->sub_48B270() || !v10->sub_48B270()) {
                    a2b = 0.0;
                }

                goto LABEL_42;
            }
            case 1: {
                auto *v14 = this->field_10;
                auto *v15 = this->field_C;
                auto a2d = v14->sub_55ED30();
                auto v16 = v15->sub_55ED30();
                auto *v17 = v14;
                if (v16 >= a2d) {
                    v17 = v15;
                }

                a2b = v17->sub_55ED30();
                if (!v15->sub_48B270() && !v14->sub_48B270()) {
                    a2b = 0.0;
                }

                goto LABEL_42;
            }
            case 2: {
                auto *v18 = this->field_10;
                auto *v19 = this->field_C;
                auto a2e = v18->sub_55ED30();
                auto v20 = v19->sub_55ED30();
                auto *v21 = v18;
                if (v20 >= a2e) {
                    v21 = v19;
                }

                a2b = v21->sub_55ED30();
                if (v19->sub_48B270() && v18->sub_48B270() ||
                    !v19->sub_48B270() && !v18->sub_48B270()) {
                    a2b = 0.0;
                }

                goto LABEL_42;
            }
            case 3: {
                {
                    auto *v22 = this->field_10;
                    auto *v23 = this->field_C;
                    auto a2f = v22->sub_55ED30();
                    auto v24 = v23->sub_55ED30();
                    auto *v25 = v22;
                    if (v24 <= a2f) {
                        v25 = v23;
                    }

                    a2b = 0.f - v25->sub_55ED30();
                    if (v23->sub_48B270() || v22->sub_48B270()) {
                        a2b = 0.0;
                    }
                }

            LABEL_42:
                auto v31 = a2b - this->field_18;
                this->override(a2, a2b, v31);
                return;
            }
            case 4: {
                auto *v27 = this->field_10;
                if (!v27->sub_48B270()) {
                    goto LABEL_46;
                }

                game_button *v28;

                if (v27->sub_48B290() && (v28 = this->field_C, v28->sub_48B270()) &&
                    !v28->sub_48B290()) {
                    this->m_flags |= 8u;
                    this->override(a2, 0.0, 0.0);
                } else {
                    auto *v29 = this->field_C;
                    auto v34 = v29->sub_55ED50();
                    auto v30 = v29->sub_55ED30();
                    this->override(a2, v30, v34);
                }
                break;
            }
            case 5: {
                if (this->field_10->sub_48B270()) {
                LABEL_46:
                    auto v33 = -this->field_18;
                    this->override(a2, 0.0, v33);
                } else {
                    auto v26 = this->field_C->sub_55ED30();

                    auto v32 = v26 - this->field_18;
                    this->override(a2, v26, v32);
                }

                break;
            }
            default:
                assert(0 && "Invalid trigger type.");

                return;
            }
        } else {
            auto *v7 = this->field_C;

            float a2a = 0.0f;

            if ((v7->m_flags & 0x20) == 0) {
                a2a = v7->field_14;
            }

            float v36 = 0.0f;
            if ((v7->m_flags & 0x20) == 0) {
                v36 = v7->field_18;
            }

            this->override(a2, v36, a2a);
        }

    } else {
        THISCALL(0x0051D510, this, a2);
    }
}

game_button::~game_button() {
    game_button *v2 = this->field_C;
    if (v2 != nullptr) {
        this->field_C->~game_button();

        mem_dealloc(v2, sizeof(*v2));

        this->field_C = nullptr;
    }

    game_button *v3 = this->field_10;
    if (v3 != nullptr) {
        this->field_10->~game_button();

        mem_dealloc(v3, sizeof(*v3));

        this->field_10 = nullptr;
    }
}

void game_button::clear() {
    this->field_18 = 0.0;
    this->field_14 = 0.0;
    this->field_1C = 0.0;
    this->field_30 = 0;
    this->field_20 = 0.0;
    this->field_24 = 0.40000001f;
    this->field_28 = this->field_2C;
}

void game_button::sub_48C800(game_button *a2) {
    THISCALL(0x0048C800, this, a2);
}

void game_button::set_control(game_control_t a2) {
    game_button *v3 = this->field_C;
    if (v3 != nullptr) {
        this->field_C->~game_button();

        mem_dealloc(v3, sizeof(*v3));

        this->field_C = nullptr;
    }

    game_button *v4 = this->field_10;
    if (v4 != nullptr) {
        v4->~game_button();

        mem_dealloc(v4, sizeof(*v4));

        this->field_10 = nullptr;
    }

    this->field_8 = a2;
    this->clear();
}
