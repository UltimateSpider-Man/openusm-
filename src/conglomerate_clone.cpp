#include "conglomerate_clone.h"

#include "common.h"

VALIDATE_SIZE(conglomerate_clone, 0xD0);

conglomerate_clone::conglomerate_clone(string_hash const &a2, uint32_t a3) : actor(a2, a3) {}
