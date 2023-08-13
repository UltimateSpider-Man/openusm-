#include "nal_anim_controller.h"

#include "func_wrapper.h"
#include "nal_system.h"

nalAnimClass<nalAnyPose>::nalInstanceClass *nal_anim_controller::scene_anim_client::CreateInstance(
    nalAnimClass<nalAnyPose> *a2) {
    return (nalAnimClass<nalAnyPose>::nalInstanceClass *) THISCALL(0x00492890, this, a2);
}

int nal_anim_controller::scene_anim_client::Advance(
    nalAnimClass<nalAnyPose>::nalInstanceClass *a2, float a3, float a4, float a5, float a6) {
    return THISCALL(0x0049C090, this, a2, a3, a4, a5, a6);
}

nal_anim_controller::nal_anim_controller(actor *a2,
                                         nalBaseSkeleton *a3,
                                         unsigned int a4,
                                         const als::als_meta_anim_table_shared *a5) {
    THISCALL(0x0049BCF0, this, a2, a3, a4, a5);
}
