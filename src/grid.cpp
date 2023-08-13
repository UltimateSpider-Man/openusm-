#include "grid.h"

#include "func_wrapper.h"

Grid::Grid()
{

}

bool Grid::sub_48CEB0(const vector4d &a2) {
    if constexpr (1) {
        int minx, miny, minz, maxx, maxy, maxz;
        this->sub_48CD70(a2, minx, miny, minz, maxx, maxy, maxz);

        uint32_t v3 = (1 << maxz) | (1 << minz);

        assert(minz >= 0 && maxz >= 0 && minz < MAX_3DGRID_BITS && maxz < MAX_3DGRID_BITS);

        for (auto x = minx; x <= maxx; ++x) {
            auto v6 = MAX_3DGRID_BITS * x;

            for (auto y = miny; y <= maxy; ++y) {
                assert(x >= 0 && y >= 0 && x < MAX_3DGRID_BITS && y < MAX_3DGRID_BITS);

                auto index = y + v6;

                assert(index >= 0 && index < (MAX_3DGRID_BITS * MAX_3DGRID_BITS));

                if ((v3 & this->field_60[index]) != 0) {
                    return true;
                }

                this->field_60[index] |= v3;
            }
        }

        return false;

    } else {
        return (bool) THISCALL(0x0048CEB0, this, a2);
    }
}

void Grid::sub_48CD70(
    const vector4d &a2, int &minx, int &miny, int &minz, int &maxx, int &maxy, int &maxz) {
    if constexpr (1) {
        auto v8 = a2[0] - this->field_0[0];
        auto &max = this->field_40;
        auto v10 = a2[1] - this->field_0[1];
        auto &min = this->field_50;

        vector4d v27;
        v27[2] = a2[2] - this->field_0[2];
        v27[3] = a2[3] - this->field_0[3];

        vector4d v28;
        v28[0] = v8 * this->field_30[0];
        v27[0] = v28[0];
        v28[1] = v10 * this->field_30[1];
        v27[1] = v28[1];
        v28[2] = v27[2] * this->field_30[2];
        v27[2] = v28[2];
        v28[3] = v27[3] * this->field_30[3];
        v27[3] = v28[3];

        auto v12 = vector4d::floor(v27);
        v28 = vector4d::min(vector4d::max(v12, min), max);

        auto v14 = vector4d::ceil(v27);
        v27 = vector4d::min(vector4d::max(v14, min), max);

        minx = v28[0];

        miny = v28[1];

        minz = v28[2];

        maxx = v27[0];

        maxy = v27[1];

        maxz = v27[2];

        assert(minx >= 0 && minx < MAX_3DGRID_BITS);
        assert(miny >= 0 && miny < MAX_3DGRID_BITS);
        assert(minz >= 0 && minz < MAX_3DGRID_BITS);

    } else {
        THISCALL(0x0048CD70, this, &a2, &minx, &miny, &minz, &maxx, &maxy, &maxz);
    }
}
