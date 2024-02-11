#pragma once

#include <cstdint>

#include "float.hpp"

struct fe_health_widget;
struct entity_tracker_manager;
struct IGOZoomOutMap;
struct fe_mini_map_widget;
struct fe_track_and_field;
struct fe_distance_chase;
struct fe_distance_race;
struct fe_mission_text;
struct combo_words;
struct fe_hotpursuit_indicator;
struct fe_score_widget;
struct threat_assessment_meters;
struct thug_health;
struct targeting_reticle;
struct tutorial_controller_gauge;
struct medal_award_ui;
struct race_announcer;
struct fe_crosshair;
struct fe_game_credits;
struct fe_timer_widget;

struct IGOFrontEnd {
    fe_timer_widget *field_0;
    fe_mini_map_widget *field_4;
    fe_health_widget *boss_health;
    fe_health_widget *hero_health;
    fe_health_widget *third_party_health;
    fe_track_and_field *field_14;
    fe_distance_chase *field_18;
    fe_distance_race *field_1C;
    fe_mission_text *field_20;
    threat_assessment_meters *field_24;
    thug_health *field_28;
    targeting_reticle *field_2C;
    tutorial_controller_gauge *field_30;
    medal_award_ui *field_34;
    race_announcer *field_38;
    fe_crosshair *field_3C;
    fe_game_credits *field_40;
    IGOZoomOutMap *field_44;
    combo_words *field_48;
    fe_hotpursuit_indicator *field_4C;
    fe_score_widget *field_50;
    entity_tracker_manager *field_54;

    //0x00648B40
    IGOFrontEnd();

    void UpdateInScene();

    //0x00647DE0
    void Init();

    //0x006358F0
    void Draw();

    //0x00629F80
    void CheckPauseUnpause();

    //0x00641600
    void Update(Float a2);
};

extern void IGOFrontEnd_patch();
