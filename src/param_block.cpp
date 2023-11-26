#include "param_block.h"

#include "common.h"
#include "func_wrapper.h"
#include "log.h"
#include "mash_info_struct.h"
#include "memory.h"
#include "trace.h"
#include "utility.h"

#include <cassert>

namespace ai {

VALIDATE_SIZE(param_block, 0xC);
VALIDATE_SIZE(param_block::param_data_array, 0x18);

param_block::param_block() {}

void param_block::unmash(mash_info_struct *a1, void *a3)
{
    TRACE("param_block::unmash");

    if constexpr (1)
    {
#ifdef TARGET_XBOX
        {
            uint8_t class_mashed = -1;
            class_mashed = *a1->read_from_buffer(mash::SHARED_BUFFER, 1, 1);
            assert(class_mashed == 0xAF || class_mashed == 0);
        }
#endif

        if ( this->param_array != nullptr )
        {
            a1->unmash_class(this->param_array, a3
#ifdef TARGET_XBOX
                    , mash::NORMAL_BUFFER
#endif
                    );
        }
    }
    else
    {
        THISCALL(0x006D56B0, this, a1, a3);
    }
}

const char *param_block::get_pb_fixedstring(string_hash a2) const {
    auto *v2 = bit_cast<param_data_array *>(this->param_array);
    if (v2 == nullptr) {
        return nullptr;
    }

    auto *v4 = v2->common_find_data(a2);
    if (v4 == nullptr) {
        a2.to_string();
    }

    return v4->m_union.str;
}

float param_block::get_pb_float(string_hash a2) {
    [[maybe_unused]] ai::param_block *v6 = this;
    auto *v2 = bit_cast<param_data_array*>(this->param_array);

    if (v2 == nullptr) {
        return 0.0f;
    }

    ai::param_block v5;
    v6 = &v5;
    param_data *v4 = v2->common_find_data(a2);

    if (v4 == nullptr) {
        const char *str = a2.to_string();
        sp_log("Could not find the parameter %s.", str);
        assert(0);
    }

    return v4->get_data_float();
}

string_hash param_block::param_data::get_data_hash() const {
    return this->m_union.hash;
}

void param_block::param_data::sub_6C8700(int a2) {
    if (a2 == 0 && this->m_union.i) {
        if (this->my_type == PT_FIXED_STRING) {
            operator delete[](this->m_union.str);
        } else if (this->my_type == PT_VECTOR_3D || this->my_type == PT_FLOAT_VARIANCE) {
            operator delete(this->m_union.vec3);
            this->m_union.vec3 = nullptr;
            return;
        }

        this->m_union.i = 0;
    }
}

void param_block::param_data::sub_436A70() {
    this->sub_6C8700(0);
}

void param_block::param_data::sub_6C8750() {
    this->field_8.destruct_mashed_class();
}

auto *param_block::param_data::set_data_float_variance(const variance_variable<float> &a2) {
    if (!this->get_data_float_variance()) {
        auto *v3 = new variance_variable<float>{};

        this->m_union.float_variance = v3;
    }

    auto &result = this->m_union.float_variance;

    *this->m_union.float_variance = a2;

    return result;
}

void param_block::param_data::set_data_vector3d(const vector3d &a2) {
    if (!this->get_data_vector3d()) {
        this->get_data_vector3d() = new vector3d{};
    }

    *this->get_data_vector3d() = a2;
}

string_hash param_block::get_pb_hash(string_hash a3) const
{
    ai::param_block v7{};
    auto *v3 = bit_cast<param_data_array *>(this->param_array);
    if (v3 != nullptr) {
        ai::param_block::param_data *v5 = v3->common_find_data(a3);
        if (v5 == nullptr) {
            const char *str = a3.to_string();
            sp_log("Could not find the parameter %s.", str);
            assert(0);
        }

        auto a2 = v5->get_data_hash();
        return a2;
    }

    return {};
}

variance_variable<float> *param_block::get_pb_float_variance(string_hash a2) {
    return (variance_variable<float> *) THISCALL(0x006CDDF0, this, a2);
}

vector3d *param_block::get_pb_vector3d(string_hash a2) {
    return (vector3d *) THISCALL(0x006CDD80, this, a2);
}

int param_block::get_pb_int(string_hash a2) {
    auto *v2 = bit_cast<param_data_array *>(this->param_array);
    if (v2 == nullptr) {
        return 0;
    }

    param_data *v4 = v2->common_find_data(a2);
    if (v4 == nullptr) {
        const char *v7 = a2.to_string();
        sp_log("Could not find the parameter %s.", v7);
        assert(0);
    }

    return v4->get_data_int();
}

float param_block::param_data::get_data_float() {
    assert(my_type == PT_FLOAT);

    return m_union.f;
}

int param_block::param_data::get_data_int() {
    assert(my_type == PT_INTEGER);
    return m_union.i;
}

int param_block::get_optional_pb_int(string_hash a2, const int &a3, bool *a4) const {
    if (a4 != nullptr) {
        *a4 = false;
    }

    auto *v4 = bit_cast<param_data_array*>(this->param_array);
    if (v4 == nullptr) {
        return a3;
    }

    float result;

    auto *curr_data = v4->common_find_data(a2);
    if (curr_data != nullptr) {
        assert((curr_data->get_data_type() == PT_INTEGER) && "Parameter is of the wrong type.");

        if (a4 != nullptr) {
            *a4 = true;
        }

        result = curr_data->get_data_int();
    } else {
        result = a3;
    }

    return result;
}

float param_block::get_optional_pb_float(string_hash a2, const Float &a3, bool *a4) const {
    if (a4 != nullptr) {
        *a4 = false;
    }

    auto *v4 = bit_cast<param_data_array *>(this->param_array);

    if (v4 == nullptr) {
        return a3;
    }

    float result;

    auto *curr_data = v4->common_find_data(a2);
    if (curr_data != nullptr) {
        assert((curr_data->get_data_type() == PT_FLOAT) && "Parameter is of the wrong type.");

        if (a4 != nullptr) {
            *a4 = true;
        }

        result = curr_data->get_data_float();
    } else {
        result = a3;
    }

    return result;
}

void param_block::param_data_array::unmash(mash_info_struct *a1, void *)
{
    a1->unmash_class_in_place(this->field_0, this); 
}

param_block::param_data *param_block::param_data_array::common_find_data(string_hash a2) {
    return (param_block::param_data *) THISCALL(0x006CD450, this, a2);
}

void param_block::param_data_array::sub_43F630() {
    this->field_14 = 0;
    this->sub_43E400();
}

void param_block::param_data_array::sub_43E400() {
    if (this->field_0.field_10) {
        for (auto i = 0; i < this->field_0.size(); ++i) {
            auto **v3 = this->field_0.m_data;
            auto *v4 = v3[i];
            auto **v5 = &v3[i];
            if ((int) v4 < (int) this || (int) v4 > (int) this + this->field_0.field_0) {
                if (v4) {
                    v3[i]->sub_436A70();
                    slab_allocator::deallocate(v4, nullptr);
                }
            } else {
                v3[i]->sub_6C8750();
            }

            *v5 = nullptr;
        }
    }

    auto v6 = this->field_0.m_data;
    if ((int) v6 < (int) this || (int) v6 > (int) this + this->field_0.field_0) {
        if ((unsigned int) (4 * this->field_0.field_C) > 0xB0) {
            operator delete(this->field_0.m_data);
            this->field_0 = {};
        }

        slab_allocator::deallocate(v6, nullptr);
    }

    this->field_0 = {};
}

bool param_block::does_parameter_exist(string_hash a2) const {
    auto *v2 = bit_cast<param_data_array *>(this->param_array);
    bool result = false;
    if (v2 != nullptr) {
        if (v2->common_find_data(a2) != nullptr) {
            result = true;
        }
    }

    return result;
}

bool param_block::does_parameter_match(const param_block::param_data *a2) const
{
    if ( this->param_array == nullptr ) {
        return false;
    }

    auto v5 = a2->field_8;
    auto *other = this->param_array->common_find_data(v5);
    assert(other != nullptr && "attempting to match a parameter that doesn't exist");
    return a2->deep_compare(other);
}

void param_block::sub_6D6EB0() {
    auto *v2 = bit_cast<param_data_array *>(this->param_array);
    if (v2 != nullptr && this->field_8) {
        v2->sub_43F630();

        mem_dealloc(v2, sizeof(*v2));

        this->param_array = nullptr;
    }

    auto *v3 = this->param_array;
    if (v3 != nullptr) {
        auto *v4 = bit_cast<param_data_array *>(this->param_array);
        v4->field_14 = 0;
        v4->sub_43E400();
        //v3->destruct_mashed_class();
        this->param_array = nullptr;
    }
}

void param_block::param_data::custom_unmash(mash_info_struct *a2, void *a3)
{
    THISCALL(0x006CC070, this, a2, a3);
}

bool param_block::param_data::deep_compare(const param_block::param_data *a2) const
{
    return (bool) THISCALL(0x006C4AE0, this, a2);
}

void param_block::param_data::unmash(mash_info_struct *a1, void *a3)
{
    a1->unmash_class_in_place(this->field_8, this);
    this->custom_unmash(a1, a3);
}

} // namespace ai

void param_block_patch() {
    {
        FUNC_ADDRESS(address, &ai::param_block::get_pb_float);

        REDIRECT(0x00694C33, address);
        REDIRECT(0x00694C56, address);
        REDIRECT(0x00694C79, address);
        REDIRECT(0x00694C9C, address);
        REDIRECT(0x00694CBA, address);
    }

    {
        FUNC_ADDRESS(address, &ai::param_block::get_optional_pb_float);

        REDIRECT(0x00694BBB, address);
        REDIRECT(0x00694BE0, address);
        REDIRECT(0x00694C05, address);
        REDIRECT(0x00694D48, address);
    }
}
