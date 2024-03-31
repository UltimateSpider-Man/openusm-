#pragma once

#include <cstdint>

struct BaseComponent;

namespace nalComp {

struct nalCompSkeleton {
    std::intptr_t m_vtbl;
    int Version;
    char field_8[0x5C];

    uint32_t m_iNumComponents;
    int field_68;
    int field_6C;
    struct {
        int field_0;
        BaseComponent *field_4;
        int field_8;

        bool sub_671D5F(char a2) const
        {
            return ((1 << a2) & this->field_8) != 0;
        }
    } *field_70;
    char *field_74;
    char *field_78;

    uint32_t GetNumComponents() const
    {
        return this->m_iNumComponents;
    }

    int ConvertCompIxToPoseIx(uint32_t a2) const;

    int GetComponentPoseDataOffset(uint32_t a2) const;

    char * GetCompDefaultPoseData(uint32_t iCompIx) const;

    char * GetCompPerSkelDataInt(uint32_t iCompIx) const;

    void UnMash(void *a2, BaseComponent **a3, unsigned int iNumComponents);

    void ReMash(void *a2);
};

struct nalCompPose {
    std::intptr_t m_vtbl;
    const nalCompSkeleton *field_4;
    void *field_8;
    int field_C;

    nalCompPose(const nalCompSkeleton *);

    void * GetComponentPoseData(uint32_t a2);

    //virtual
    void * GetComponentPoseData(uint32_t a2) const;

    //virtual
    void FreePoseData();

    //virtual
    void ComponentFreePoseData();
};

} // namespace nalComp
