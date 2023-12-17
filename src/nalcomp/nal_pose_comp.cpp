#include "nal_pose_comp.h"

#include "common.h"
#include "trace.h"
#include <vtbl.h>

#include <nal_skeleton.h>
#include <nal_system.h>

namespace nalComp {

VALIDATE_SIZE(nalCompSkeleton, 0x7C);

void nalCompSkeleton::UnMash(void *a2, BaseComponent **a3, unsigned int iNumComponents)
{
    TRACE("nalCompSkeleton::UnMash");

    if constexpr (0) {
        auto v5 = (int) this->field_70;
        auto v6 = (int) this->field_74;
        auto v7 = this->field_6C;
        int v8 = 0;
        this->field_70 = (char *) a2 + v5;
        this->field_74 = (char *) a2 + v6;
        if (v7) {
            this->field_78 += (int) a2;
        } else {
            this->field_78 = 0;
        }

        int v14;
        uint32_t v15;

        for (auto a2a = 0u; a2a < this->m_iNumComponents; ++a2a) {
            auto *v9 = this->field_70;
            auto v10 = *(int32_t *) &v9[v8 + 4];
            int v11 = 0;
            int v23 = *(int32_t *) &v9[v8];
            if (iNumComponents != 0) {
                while (a3[v11]->GetType() != v10) {
                    if (++v11 >= iNumComponents) {
                        goto LABEL_28;
                    }
                }

                *(int32_t *) &this->field_70[v8 + 4] = (int32_t) a3[v11];
                auto *v12 = this->field_70;
                auto v13 = *(int32_t *) &v12[v8 + 8];
                if ((v13 & 1) != 0) {
                    goto LABEL_17;
                }

                v14 = -1;
                v15 = 0u;
                if (this->m_iNumComponents == 0) {
                    goto LABEL_17;
                }

                {
                    char *v16 = v12 + 8;
                    do {
                        if ((*v16 & 1) == 0) {
                            ++v14;
                        }

                        if (v15 == a2a) {
                            break;
                        }

                        ++v15;
                        v16 += 12;
                    } while (v15 < this->m_iNumComponents);
                }

                int v17;
                if (v14 == -1) {
                LABEL_17:
                    v17 = 0;
                } else {
                    v17 = this->field_78 + *(uint32_t *) (this->field_78 + 4 * v14 + 4);
                }

                char *v18;

                if ((v13 & 4) != 0) {
                    int v19 = 0;
                    if (v8) {
                        auto v20 = a2a;
                        auto *v21 = this->field_70 + 8;
                        do {
                            if ((*v21 & 4) != 0) {
                                ++v19;
                            }

                            v21 += 12;
                            --v20;
                        } while (v20);
                    }

                    v18 = &this->field_74[*(uint32_t *) &this->field_74[4 * v19 + 4]];
                } else {
                    v18 = 0;
                }

                assert(0);

                auto *v22 = *(char **) &this->field_70[v8 + 4];

                struct {
                    std::intptr_t m_vtbl;
                } *tmp = CAST(tmp, v22);

                auto &func3C = get_vfunc(tmp->m_vtbl, 0x3c);

                func3C(v22, v23, v18, v17);
            }
        LABEL_28:
            v8 += 12;
        }
    } else {
        THISCALL(0x007378A0, this, a2, a3, iNumComponents);

        auto *v22 = *(char **) &this->field_70[4];
        struct {
            std::intptr_t m_vtbl;
        } *tmp = CAST(tmp, v22);

        sp_log("0x%08X", tmp->m_vtbl);
    }
}

nalCompPose::nalCompPose(const nalComp::nalCompSkeleton *a2) {
    m_vtbl = 0x008AA1E4;
    field_4 = a2;
    field_8 = nullptr;
}
} // namespace nalComp
