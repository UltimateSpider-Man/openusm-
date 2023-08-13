#pragma once

struct matrix4x4;

struct quaternion {
    float arr[4];

    const float &operator[](int idx) const {
        return arr[idx];
    }

    auto &operator[](int idx) {
        return arr[idx];
    }

    quaternion() = default;

    //0x00588410
    quaternion(const matrix4x4 &matrix);

    quaternion(float x, float y, float z, float w) : arr{x, y, z, w} {}

    const quaternion operator-() const {
        quaternion quat{-arr[0], -arr[1], -arr[2], -arr[3]};

        return quat;
    }

    static float dot(const quaternion &quat0, const quaternion &quat1);

    //0x00588550
    void to_matrix(matrix4x4 &mat) const;

    //sub_588630
    static quaternion slerp(const quaternion &a2, const quaternion &a3, float lambda);
};
