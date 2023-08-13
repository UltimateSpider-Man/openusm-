#include "bitvector.h"

#include "common.h"

using bitvector_t = fixed_bitvector<unsigned, 2048>;
VALIDATE_SIZE(bitvector_t, 0x108);
