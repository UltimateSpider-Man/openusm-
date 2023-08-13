#include "camera_frame.h"

bool camera_frame::is_valid() const
{
    return this->field_0.is_valid()
      && this->field_C.is_valid()
      && this->field_C.is_normal();
}
