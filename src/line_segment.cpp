#include "line_segment.h"

#include "common.h"

VALIDATE_SIZE(line_segment_t, 0x38);

line_segment_t::line_segment_t() {}

line_segment_t::line_segment_t(const vector3d &a2, const vector3d &a3) : field_0(a2), field_C(a3) {}
