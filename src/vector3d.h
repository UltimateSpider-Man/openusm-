#pragma once

#include "config.h"

#include "float.hpp"
#include "log.h"
#include "mstring.h"
#include "variable.h"

inline constexpr auto LARGE_EPSILON = 0.0099999998;
inline constexpr auto EPSILON = 0.000099999997;
inline constexpr float SAMPLING_PERIOD = 0.033433333f - EPSILON;
inline constexpr float DURATION_EPSILON = 0.00050000002f;
inline constexpr auto MAX_ALLOWED_POSITION_LENGTH_SQUARED = 1.0e10;

struct euler_direction;
struct vector4d;

struct vector3d
{
    float x;
    float y;
    float z;

    vector3d() : x(0), y(0), z(0) {
    }

    constexpr vector3d(float a1, float a2, float a3) : x(a1), y(a2), z(a3) {}

    vector3d(const vector3d &v) : x(v[0]), y(v[1]), z(v[2]) {
    }

    vector3d(const vector4d &v);

    vector3d& operator=(const vector3d &v) = default;

    const float &operator[](int idx) const {
        return (&x)[idx];
    }

    float &operator[](int idx) {
        return (&x)[idx];
    }

    bool operator==(const vector3d &v) const;

    bool operator!=(const vector3d &a2) const {
        return not_equal(x, a2[0]) || not_equal(y, a2[1]) ||
            not_equal(z, a2[2]);
    }

    void operator+=(const vector3d &v) {
        *this = *this + v;
    }

    vector3d operator+(float f) const {
        vector3d result = (*this);
        result[0] = result[0] + f; 
        result[1] = result[1] + f; 
        result[2] = result[2] + f; 

        return result;
    }

    vector3d operator-(float f) const {
        vector3d result = (*this);
        result[0] = result[0] - f; 
        result[1] = result[1] - f; 
        result[2] = result[2] - f; 

        return result;
    }

    vector3d operator+(const vector3d &v) const {
        vector3d result;

        result[0] = x + v[0];
        result[1] = y + v[1];
        result[2] = z + v[2];

        return result;
    }

    vector3d operator-() const {
        return ((*this) * -1.f);
    }

    vector3d& operator-=(const vector3d &vec3) {
        x -= vec3[0];
        y -= vec3[1];
        z -= vec3[2];

        return (*this);
    }

    vector3d operator-(const vector3d &vec3) const {
        vector3d result;

        result[0] = x - vec3[0];
        result[1] = y - vec3[1];
        result[2] = z - vec3[2];

        return result;
    }

    vector3d operator*(float a1) const {
        vector3d result;
        result[0] = x * a1;
        result[1] = y * a1;
        result[2] = z * a1;

        return result;
    }

    friend vector3d operator*(float a1, const vector3d &a2) {
        vector3d result = a2 * a1;

        return result;
    }

    void operator*=(float a1) {
        x *= a1;
        y *= a1;
        z *= a1;
    }

    vector3d operator/(float a1) const {
        vector3d result;
        result[0] = x * (1.0 / a1);
        result[1] = y * (1.0 / a1);
        result[2] = z * (1.0 / a1);

        return result;
    }

    void operator/=(float a1) {
        auto v1 = (1.0 / a1);
        x *= v1;
        y *= v1;
        z *= v1;
    }

    mString to_string() const;

    //0x00501AB0
    bool is_valid() const;

    //0x004016C0
    void normalize();

    [[nodiscard]] vector3d normalized() const;

    //0x004ACE20
    bool is_normal() const;

    float xz_length2();

    Float length2() const;

    vector4d sub_48D010();

    //0x00401690
    float length() const;

    void sub_48BFB0(const float &a2);

    static float abs(Float a1);

    //0x00401870
    static vector3d cross(const vector3d &a2, const vector3d &a3);

    static vector3d sub_401870(const vector3d &a2, const vector3d &a3);

    //0x00495450
    static void reorient_vectors(vector3d a1,
                                 vector3d a4,
                                 vector3d a7,
                                 vector3d a10,
                                 vector3d &a13,
                                 vector3d &a14,
                                 float a15);

    //0x005BF0B0
    static bool is_colinear(vector3d a1, vector3d a4, Float epsilon = LARGE_EPSILON);
};

extern vector3d XVEC;

extern vector3d YVEC;

extern vector3d ZVEC;

extern vector3d ZEROVEC;

extern float dot(const vector3d &a1, const vector3d &a2);

extern float Abs(const vector3d &a1);

//0x00581AE0
[[nodiscard]] extern vector3d make_vector3d(const euler_direction &a2);

//0x0058FFE0
extern vector3d orthogonal_projection_onto_plane(
                                                  const vector3d &a2,
                                                  const vector3d &a3);

//0x005E1E90
extern float compute_angle_between_vectors(const vector3d &a1, const vector3d &a2);

//0x005B8FC0
extern bool collide_line_with_plane_infinite(
    const vector3d &a1, const vector3d &a2, Float a3, Float a4, Float a5, Float a6, vector3d &a7);

extern float sub_5B8DB0(const vector3d &a1, const vector3d &a2, const vector3d &a3);

extern vector3d sub_48B5B0(const vector3d &a2, const vector3d &a3, Float a4);
