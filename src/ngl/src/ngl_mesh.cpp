#include "ngl_mesh.h"

#include "common.h"
#include "debug_render.h"
#include "func_wrapper.h"
#include "matrix4x3.h"
#include "ngl.h"
#include "ngl_scene.h"
#include "nglshader.h"
#include "utility.h"
#include "vector3d.h"
#include "vtbl.h"

#include <ngl_dx_scene.h>

#include <cassert>

VALIDATE_SIZE(nglMeshParams, 0x20);

VALIDATE_SIZE(nglMesh, 0x40);

void nglMeshInit() {
    CDECL_CALL(0x0076F420);
}

vector4d sub_76EE90(const vector4d &a2, const float *a3) {
    auto v7 = a3[2];

    float v3;
    if (a2[3] <= v7) {
        v3 = v7;
    } else {
        v3 = a2[3];
    }

    float v4;
    if (a2[2] <= v7) {
        v4 = v7;
    } else {
        v4 = a2[2];
    }

    float v5;
    if (a2[1] <= v7) {
        v5 = v7;
    } else {
        v5 = a2[1];
    }

    float x;
    if (a2[0] <= (double) v7) {
        x = v7;
    } else {
        x = a2[0];
    }

    vector4d result;
    result[0] = x;
    result[1] = v5;
    result[2] = v4;
    result[3] = v3;
    return result;
}

matrix4x3 sub_771210(void *a2) {
    matrix4x3 result;
    CDECL_CALL(0x00771210, &result, a2);

    return result;
}

math::MatClass<4, 3> *nglListAddMesh_GetScaledMatrix(const math::MatClass<4, 3> &a1,
                                                     nglMeshParams *a2,
                                                     float *a3) {
    if constexpr (1) {
        auto v3 = a2->Scale.field_0[0];
        auto v4 = a2->Scale.field_0[1];
        auto v5 = a2->Scale.field_0[2];
        auto v6 = a2->Scale.field_0[3];

        vector4d v11;
        v11[0] = std::abs(v3);
        v11[1] = std::abs(v4);
        v11[2] = std::abs(v5);
        v11[3] = std::abs(v6);
        auto v12 = sub_76EE90(v11, &v11[0]);

        float v7;
        if (v12[1] <= v11[0]) {
            v7 = v11[0];
        } else {
            v7 = v12[1];
        }

        Var<BOOL> dword_9728F8{0x009728F8};
        bool v8 = dword_9728F8();
        *a3 = v7;
        if (v8) {
            dword_9728F8() |= 1u;
        }

        v12[2] = v5;
        v12[0] = v3;
        v12[1] = v4;
        v12[3] = v6;

        struct {
            vector4d *field_0;
            const math::MatClass<4, 3> *field_4;
        } v10 = {&v12, &a1};

        static matrix4x3 ScaledLocalToWorld;

        auto v13 = sub_771210(&v10);

        std::memcpy(&ScaledLocalToWorld, &v13, sizeof(v13));
        ScaledLocalToWorld[3] = a1[3];

        return (math::MatClass<4, 3> *) &ScaledLocalToWorld;

    } else {
        return (math::MatClass<4, 3> *) CDECL_CALL(0x00770230, &a1, a2, a3);
    }
}

nglMesh *nglListAddMesh_GetLOD(nglMesh *Mesh,
                               unsigned int a2,
                               nglMeshParams *a3,
                               math::VecClass<3, 1> a4) {
    if constexpr (1) {
        nglMesh *result;
        if ((a2 & 0x80u) == 0) {
            math::VecClass<3, 1> v10 = sub_414360(a4, {nglCurScene()->field_14C});
            auto v7 = Mesh->NLODs - 1;
            if (v7 < 0) {
            LABEL_11:
                result = Mesh;
            } else {
                auto *v8 = Mesh->LODs;
                auto *v9 = (float *) &v8[8 * v7 + 4];
                while (v10.field_0[2] <= (double) *v9) {
                    --v7;
                    v9 -= 2;
                    if (v7 < 0) {
                        goto LABEL_11;
                    }
                }

                result = *(nglMesh **) (v8 + 8 * v7);
            }
        } else {
            auto v4 = a3->field_C;
            if (v4) {
                auto v6 = Mesh->NLODs;
                if (v4 - 1 <= v6)
                    result = *(nglMesh **) &Mesh->LODs[8 * v4 - 8];
                else
                    result = *(nglMesh **) &Mesh->LODs[8 * v6 - 8];
            } else {
                result = Mesh;
            }
        }
        return result;

    } else {
        return (nglMesh *) CDECL_CALL(0x0, Mesh, a2, a3, a4);
    }
}

float *sub_507130(float *a1, void *arg4) {
    return (float *) CDECL_CALL(0x00507130, a1, arg4);
}

bool sub_755520(Float a1, Float a2, Float a3, Float, Float a5) {
    for (auto i = 0u; i < 6u; ++i) {
        auto &v = nglCurScene()->field_2AC[i];

        if (a3 * v[2] + a1 * v[0] + a2 * v[1] - v[3] + a5 < 0.0f) {
            return false;
        }
    }

    return true;
}

int sub_76F3E0(Float a1, Float a2, Float a3, Float a4, Float a5, char a6) {
    if constexpr (1) {
        if ((a6 & 0x40) != 0 || sub_755520(a1, a2, a3, a4, a5)) {
            return 0;
        }

        return -1;

    } else {
        return CDECL_CALL(0x0076F3E0, a1, a2, a3, a4, a5, a6);
    }
}

void nglListAddMesh(nglMesh *Mesh,
                    const math::MatClass<4, 3> &a2,
                    nglMeshParams *a3,
                    nglParamSet<nglShaderParamSet_Pool> *a4) {
    if (Mesh != nullptr) {
        assert(((Mesh->Flags & NGLMESH_PROCESSED) || (Mesh->Flags & NGLMESH_SCRATCH_MESH)) &&
               "Mesh missing NGLMESH_PROCESSED flag.");
    }

    if constexpr (0) {
        if (Mesh != nullptr) {
            int v20 = 0;
            if (a3 != nullptr) {
                v20 = a3->Flags;
            }

            auto *v5 = &a2;
            auto a5 = Mesh->SphereRadius;
            float v15 = 1.0;
            if ((v20 & 2) != 0) {
                v5 = nglListAddMesh_GetScaledMatrix(a2, a3, &v15);
                a5 *= v15;
            }

            math::VecClass<3, 1> v18 = sub_414360(Mesh->field_20, *v5);
            if (nglCurScene()->field_3E4) {
                nglCalculateMatrices(false);
            }

            if (Mesh->NLODs) {
                Mesh = nglListAddMesh_GetLOD(Mesh, v20, a3, v18);
            }

            auto *v6 = v5;
            auto v17 = nglListWorkPos();

            nglMeshNode *meshNode = static_cast<nglMeshNode *>(
                nglListAlloc(sizeof(nglMeshNode), 64));

            meshNode->field_88 = Mesh;
            meshNode->field_0 = {};

            struct {
                const void *field_0;
                void *field_4;
            } v14;

            v14.field_0 = v6;
            v14.field_4 = &nglCurScene()->field_18C;

            float v19[16];
            auto *v8 = sub_507130(v19, &v14);
            auto v9 = v15;

            std::memcpy(meshNode->field_40, v8, sizeof(meshNode->field_40));
            meshNode->field_84 = 0;
            meshNode->field_80 = 0;
            meshNode->field_94 = v9;
            if (a3 != nullptr) {
                if (v20 >= 0) {
                    meshNode->field_90 = static_cast<nglMeshParams *>(
                        nglListAlloc(sizeof(nglMeshParams), 16));

                    std::memcpy(meshNode->field_90, a3, sizeof(nglMeshParams));
                } else {
                    meshNode->field_90 = a3;
                }

            } else {
                static Var<nglMeshParams> nglEmptyMeshParams{0x00972820};
                meshNode->field_90 = &nglEmptyMeshParams();
            }

            if (a4 != nullptr) {
                meshNode->field_8C = *a4;
            } else {
                meshNode->field_8C = {0};
            }

            if (sub_76F3E0(v18.field_0[0], v18.field_0[1], v18.field_0[2], v18.field_0[3], a5, v20) ==
                -1) {
                nglListWorkPos() = v17;
            } else {
                for (auto i = 0u; i < Mesh->NSections; ++i)
                {
                    auto *MeshSection = Mesh->Sections[i].Section;
                    nglPerfInfo().field_7C += MeshSection->NVertices;

                    auto &AddNode = get_vfunc(MeshSection->Material->field_4->m_vtbl, 0x8);

                    AddNode(MeshSection->Material->field_4,
                            meshNode,
                            MeshSection,
                            MeshSection->Material);
                }

                nglPerfInfo().field_78 += Mesh->field_3C;
                auto *v13 = Mesh->File;
                if (v13 != nullptr) {
                    v13->field_144 = nglFrame();
                }
            }
        }
    } else {
        CDECL_CALL(0x00770360, Mesh, &a2, a3, a4);
    }
}

void sub_407F10(nglMesh *Mesh, int a2, int a3, Float a5, const math::MatClass<4, 3> &a6) {
    sp_log("sub_407F10:");

#if 0
    sub_4150E0(&a1, a2);
    sub_414360(&out, (const math::VecClass__3_1 *) a3, &a1);
    nglMeshSetSphere(out, a5);
    nglListAddMesh(Mesh, a2, 0, 0);
#else
    CDECL_CALL(0x00407F10, Mesh, a2, a3, a5, &a6);
#endif
}

void sub_407E90(nglMesh *Mesh,
                int a2,
                const math::VecClass<3, 1> &a3,
                Float a4,
                const math::MatClass<4, 3> &a5,
                nglMaterialBase *a6,
                nglParamSet<nglShaderParamSet_Pool> *a7) {
    //sp_log("sub_407E90: %f", a4.value);

#if 0    
    sub_4150E0(&a1, a2);
    sub_414360(&out, a3, &a1);
    nglMeshSetSphere(out, a4);
    a6->field_24 = arg4;
    nglListAddMesh(Mesh, a2, nullptr, a7);
#else
    CDECL_CALL(0x00407E90, Mesh, a2, &a3, a4, &a5, a6, a7);
#endif

    if constexpr (0) {
        matrix4x4 mat{};
        mat[0] = {1.0f, 0.0f, 0.0f, 0};
        mat[1] = {0, 1.0, 0, 0};
        mat[2] = {0, 0, 1.0, 0};
        mat[3] = {vector3d{a5[3]}, 1.0};

        //sp_log("%s", mat[3].to_string());

        //sp_log("NSections = %d, NBones = %d", Mesh->NSections, Mesh->NBones);

        nglListAddMesh(s_debug_box, {mat}, nullptr, a7);
    }
}

void render_debug_hemisphere(const vector3d &a2, float scale, color32 a4) {
    if (scale < 0.0049999999) {
        scale = 0.0049999999;
    }

    nglMeshParams meshParams;
    nglParamSet<nglShaderParamSet_Pool> paramSet{1};

    paramSet.set_color(a4);
    meshParams.Flags |= 2u;
    meshParams.Scale = math::VecClass<3, 1>{{scale, scale, scale, 1.f}};

    static constexpr vector3d LEFT{1.0, 0.0, 0.0};
    static constexpr vector3d UP{0.0, 1.0, 0.0};
    static constexpr vector3d FORWARD{0.0, 0.0, 1.0};

    math::MatClass<4, 3> v13 = {LEFT, UP, FORWARD, a2};

    nglListAddMesh(s_debug_hemisphere, v13, &meshParams, &paramSet);

    v13.arr[1] = -UP;
    v13.arr[2] = -FORWARD;

    nglListAddMesh(s_debug_hemisphere, v13, &meshParams, &paramSet);
}

tlHashString *nglMesh::get_string(nglMesh *Mesh) {
    return &Mesh->Name;
}

void nglMesh_patch() {
    {
        REDIRECT(0x00615F99, nglListAddMesh);
        REDIRECT(0x004F9BB3, nglListAddMesh);
    }

    REDIRECT(0x005A62C5, sub_407F10);

    {
        REDIRECT(0x005A6311, sub_407E90);
        //REDIRECT(0x005A648C, sub_407E90);
        //REDIRECT(0x005A6617, sub_407E90);
    }
}
