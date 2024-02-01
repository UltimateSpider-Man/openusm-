#include "traffic_path.h"

bool traffic_path_road::road_is_valid(const traffic_path_road *a1)
{
    return a1 != nullptr && a1->total_in_lanes <= 7u && a1->total_out_lanes <= 7u;
}
