#pragma once

#include "string_hash.h"

struct script_object;

namespace script {

//0x0064E4F0
extern int find_function(string_hash a1, const script_object *a2, bool a3);

} // namespace script

extern void script_patch();
