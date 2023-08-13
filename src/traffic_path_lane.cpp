#include "traffic_path_lane.h"

#include "vector3d.h"

#include "func_wrapper.h"

vector3d traffic_path_lane::sub_5E2040() {
    auto result = this->field_0[this->field_C - 1];
    return result;
}

vector3d traffic_path_lane::sub_5E2000(int a3) {
    auto v3 = a3;
    if (a3 >= 0) {
        auto v4 = this->field_C;
        if (a3 >= v4) {
            v3 = v4 - 1;
        }

    } else {
        v3 = 0;
    }

    auto v5 = this->field_0[v3];

    return v5;
}

vector3d traffic_path_lane::get_node_before_point(const vector3d &a3, int *a4) {
    vector3d result;
    THISCALL(0x005C85F0, this, &result, &a3, a4);

    return result;
}
