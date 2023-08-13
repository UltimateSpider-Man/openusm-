#include "path_graph.h"

#include "common.h"
#include "func_wrapper.h"

VALIDATE_SIZE(path_graph, 0x34);
VALIDATE_ALIGNMENT(path_graph, 4);

path_graph::path_graph(from_mash_in_place_constructor *a2) {
    THISCALL(0x005DE080, this, a2);
}

int path_graph::destruct_mashed_class() {
    return THISCALL(0x005DC3A0, this);
}

int path_graph::unmash(mash_info_struct *a1, void *a3) {
    return THISCALL(0x005DC3E0, this, a1, a3);
}
