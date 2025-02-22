#include "message_board.h"

#include "common.h"
#include "func_wrapper.h"
#include "render_text.h"
#include "trace.h"
#include "utility.h"
#include "vector2di.h"

VALIDATE_SIZE(message_board, 0x10);

void message_board::post(string a1, Float a2, color32 a3)
{
    TRACE("message_board::post");

    if constexpr (1)
    {
        auto &v10 = this->field_0;

        uint32_t i;
        for (i = 0; i < v10.size() && v10.at(i).field_64 != 0.0; ++i) {
            ;
        }

        internal v1;

        strncpy(v1.field_0, a1.guts, 99);
        v1.field_64 = a2;
        v1.field_68 = a3;

        if (i == v10.size()) {
            v10.push_back(v1);
        } else {
            v10.at(i) = v1;
        }

    }
    else
    {
        THISCALL(0x00515EB0, this, a1, a2, a3);
    }
}

void message_board::frame_advance(float a2)
{
    TRACE("message_board::frame_advance");

    for ( uint32_t i = 0; i < this->field_0.size(); ++i )
    {
        auto &v3 = this->field_0[i].field_64;
        v3 = v3 - a2;
        if ( this->field_0[i].field_64 < 0.0 )
        {
            this->field_0[i].field_64 = 0.0;
        }
    }
}

void message_board::render()
{
    TRACE("message_board::render");
    auto &v15 = this->field_0;
    if constexpr (1)
    {
        int a3 = 390;
        for (auto i = 0u; i < v15.size(); ++i)
        {
            if (v15.at(i).field_64 > 0.0)
            {
                auto v12 = v15.at(i).field_68;

                auto v1 = v15.at(i).field_64 + 0.25;
                float v7 = (v1 >= 1.0 ? 1.0 : v1);

                uint8_t v2 = (v7 * 255.0);
                v12.set_alpha(v2);
                float v10 = 0.75;

                mString v9 {v15.at(i).field_0};

                auto v6 = v10;
                auto v5 = v12;
                vector2di v4 {32, a3};
                render_text(v9, v4, v5, 1.0, v6);
            }

            a3 -= 12;
        }
    }
}

void message_board_patch()
{
    {
        FUNC_ADDRESS(address, &message_board::post);
        SET_JUMP(0x00515EB0, address);
    }
}
