#include "light_source.h"

#include "func_wrapper.h"
#include "oldmath_po.h"
#include "vector3d.h"
#include "variables.h"
#include "common.h"

VALIDATE_SIZE(light_properties, 0x68);
VALIDATE_SIZE(light_source, 0x6C);

light_properties::light_properties()
{
    this->field_0 = 0;
    this->field_4 = 1.0;
    this->field_8 = 1.0;
    this->field_C = 1.0;
    this->field_10 = 1.0;
    this->field_14 = 1.0;
    this->field_18 = 1.0;
    this->field_1C = 1.0;
    this->field_20 = 1.0;
    this->field_34 = 1.0;
    this->field_38 = 16.0;
    this->field_40 = 1.0;
    this->field_44 = 1.0e10;
    this->field_5C = 1.0;
    this->field_60 = 1.0;
    this->field_64 = 1.0;
    this->field_24 = 0;
    this->field_28 = 0;
    this->field_2C = 0;
    this->field_30 = 0;
    
    auto v1 = this->field_38 - this->field_34;
    this->field_3C = ( v1 == 0.0f ? 1.0e10 : (1.f / v1) );

    auto v2 = this->field_44 - this->field_40;
    this->field_48 = ( v2 == 0.0f ? 1.0e10 : (1.f / v2) );

    this->field_50 = 1;
    this->field_54 = 0;
    this->field_58 = 0;
    this->field_4C = light_properties::default_contrast;
}

void light_properties::sub_515BE0(const mString &a2)
{
    this->field_50 = 0;
    
    auto v3 = a2.find("_CAT", 0);
    if ( v3 != -1 )
    {
        auto v4 = a2.c_str()[v3 + 4] - '0';
        switch ( v4 )
        {
          case 1:
            this->field_50 = 32;
            break;
          case 2:
            this->field_50 = 64;
            break;
          case 3:
            this->field_50 = 128;
            break;
          case 4:
            this->field_50 = 256;
            break;
        }
    }
}

light_source::light_source(const string_hash &a2, unsigned int a3) :
                        entity(a2, a3)
{

    this->m_vtbl = 0x00888C10;
    if ( !g_generating_vtables() )
    {
        this->properties = new light_properties{};

        auto *v6 = this->field_10.to_string();
        mString a2a {v6};
        this->properties->sub_515BE0(a2a);
    }
}

light_source::light_source(const light_properties &a2,
                        entity *a3,
                        const string_hash &a4) :
                        entity(a4, 0)
{
    this->m_vtbl = 0x00888C10;

    if ( !g_generating_vtables() )
    {
        this->properties = new light_properties(a2);

        auto *v7 = this->field_10.to_string();
        mString v10 {v7};
        this->properties->sub_515BE0(v10);
        if ( a3 != nullptr )
        {
            this->set_parent(a3);
        }
    }
}

void light_source::sub_41D050(const vector3d *a2, vector4d *a3, vector4d *a4) {
    THISCALL(0x0041D050, this, a2, a3, a4);
}

vector3d light_source::get_dir(const vector3d &a3) {
    vector3d v7;

    if (this->properties->field_0 == 2) {
        po &abs_po = this->get_abs_po();

        vector3d v5 = abs_po.m[1];

        v7 = -v5;

    } else {
        auto abs_pos = this->get_abs_position();

        v7 = a3 - abs_pos;
        v7.normalize();
    }

    return v7;
}
