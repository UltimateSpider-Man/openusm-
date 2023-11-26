#pragma once

#include "float.hpp"
#include "string_hash.h"
#include "variance_variable.h"
#include "vector3d.h"
#include "mvector.h"

#include <variant>

namespace ai {

static constexpr auto PT_FLOAT = 0;
static constexpr auto PT_INTEGER = 1;
static constexpr auto PT_STRING_HASH = 2;
static constexpr auto PT_FIXED_STRING = 3;
static constexpr auto PT_VECTOR_3D = 4;
static constexpr auto PT_FLOAT_VARIANCE = 5;
static constexpr auto PT_ENTITY = 6;
static constexpr auto PT_POINTER = 7;

struct param_block {
    struct param_data {
        union U {
            int i;
            float f;
            string_hash hash;
            char *str;
            vector3d *vec3;
            variance_variable<float> *float_variance;
        } m_union;
        int my_type;
        string_hash field_8;

        void custom_unmash(mash_info_struct *a2, void *a3);

        void unmash(mash_info_struct *a1, void *a3);

        int get_data_int();

        auto &get_data_vector3d() {
            return m_union.vec3;
        }

        auto &get_data_float_variance() {
            return m_union.float_variance;
        }

        float get_data_float();

        inline int get_data_type() {
            return this->my_type;
        }

        //0x006C86C0
        auto *set_data_float_variance(const variance_variable<float> &a2);

        void set_data_vector3d(const vector3d &a2);

        //0x006BD200
        string_hash get_data_hash() const;

        void sub_436A70();

        void sub_6C8750();

        void sub_6C8700(int a2);

        bool deep_compare(const param_block::param_data *a2) const;
    };

    struct param_data_array {
        mVector<param_block::param_data> field_0;
        int field_14;

        //0x006CD450
        param_data *common_find_data(string_hash a2);

        void unmash(mash_info_struct *, void *);

        void sub_43F630();

        void sub_43E400();
    };

    int field_0;
    param_data_array *param_array;
    char field_8;
    char pad[3];

    param_block();

    //0x006D56B0
    void unmash(mash_info_struct *a1, void *a3);

    //0x006CE130
    bool does_parameter_exist(string_hash a2) const;

    bool does_parameter_match(const param_block::param_data *a2) const;

    void sub_6D6EB0();

    //0x006CDCE0
    string_hash get_pb_hash(string_hash a3) const;

    //0x006CDDF0
    variance_variable<float> *get_pb_float_variance(string_hash a2);

    //0x006CDD80
    vector3d *get_pb_vector3d(string_hash a2);

    //0x006CDD40
    const char *get_pb_fixedstring(string_hash a2) const;

    //0x006CDC60
    float get_pb_float(string_hash a2);

    //0x006CDCA0
    int get_pb_int(string_hash a2);

    //0x006CDF50
    int get_optional_pb_int(string_hash a2, const int &a3, bool *a4) const;

    //0x006CDF10
    float get_optional_pb_float(string_hash a2, const Float &a3, bool *a4) const;
};
} // namespace ai

extern void param_block_patch();
