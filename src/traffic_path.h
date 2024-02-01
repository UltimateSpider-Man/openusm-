#pragma once

struct traffic_path_intersection;

struct traffic_path_road {

    int field_0;
    int total_in_lanes;
    int field_8;
    int total_out_lanes;
    int field_10;
    int field_14;
    traffic_path_intersection *field_18;
    traffic_path_intersection *field_1C;

    static bool road_is_valid(const traffic_path_road *a1);
};
