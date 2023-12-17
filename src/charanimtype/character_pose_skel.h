#pragma once

#include <nal_pose_comp.h>

namespace nalChar {

struct nalCharSkeleton;

struct nalCharPose : nalComp::nalCompPose {

    nalCharPose(const nalCharSkeleton *a2);

    void InitializePoseDataFromSkel();
};

struct nalCharSkeleton : nalComp::nalCompSkeleton {
    int field_7C;
    nalCharPose *m_theDefaultPose;

    struct vtbl {
        void *Dummy;
        void *finalize;

        using Process_t = void (nalCharSkeleton::*)();
        Process_t Process;

        void *Release;

        using CheckVersion_t = bool (nalCharSkeleton::*)();
        CheckVersion_t CheckVersion;
    };

    nalCharPose *GetDefaultPose();

    //virtual
    void Process();

    bool CheckVersion() {
        return this->Version == 0x10003;
    }

    static int vtbl_ptr;
};

} // nalChar

extern void nalChar_patch();
