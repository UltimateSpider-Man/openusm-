#include "ngl_support.h"

#include "func_wrapper.h"
#include "ngl.h"
#include "ngl_dx_scene.h"
#include "ngl_scene.h"
#include "nglshader.h"
#include "oldmath_po.h"
#include "vtbl.h"

#include <cmath>


void FastListAddMesh(nglMesh *Mesh,
                     const math::MatClass<4, 3> &LocalToWorld,
                     nglMeshParams *MeshParams,
                     nglParamSet<nglShaderParamSet_Pool> *ShaderParams) {
    if constexpr (1) {
        assert(Mesh != nullptr && "NULL mesh passed to FastListAddMesh.\n");

        assert((Mesh->Flags & NGLMESH_PROCESSED) ||
               (Mesh->Flags & NGLMESH_SCRATCH_MESH) && "Mesh missing NGLMESH_PROCESSED flag.");

        assert(std::abs(AbsSquared(LocalToWorld.GetX()) - 1.0f) +
                       std::abs(AbsSquared(LocalToWorld.GetY()) - 1.0f) +
                       std::abs(AbsSquared(LocalToWorld.GetZ()) - 1.0f) <
                   0.01f &&
               "Invalid scale detected in local to world transform.  If scaling is desired, use "
               "MeshParams.\n");

        if (0) //(nglSyncDebug().field_12) {
        {
            nglDumpMesh(Mesh, LocalToWorld, MeshParams);
        }

        assert(MeshParams != nullptr && "NULL MeshParams in FastListAddMesh.\n");

        math::VecClass<3, 1> v18;

        if (Mesh->NLODs != 0) {
            float *v5;
            if ((MeshParams->Flags & 1) != 0) {
                v5 = Mesh->field_20.field_0;
            } else {
                v18 = sub_414360(Mesh->field_20, LocalToWorld);
                v5 = v18.field_0;
            }

            math::VecClass<3, 1> a2a;
            a2a.field_0[0] = v5[0];
            a2a.field_0[1] = v5[1];
            a2a.field_0[2] = v5[2];
            a2a.field_0[3] = v5[3];

            v18 = sub_414360(a2a, nglCurScene()->field_14C);
            auto v9 = Mesh->NLODs - 1;
            if (v9 >= 0) {
                auto *v10 = Mesh->LODs;
                auto *v11 = (float *) &v10[v9].field_4;
                while (v18.field_0[2] <= (double) *v11) {
                    --v9;
                    v11 -= 2;
                    if (v9 < 0) {
                        goto LABEL_11;
                    }
                }

                Mesh = v10[v9].field_0;
            }
        }

    LABEL_11:

        auto *v12 = static_cast<nglMeshNode *>(nglListAlloc(sizeof(nglMeshNode), 64));

        v12->field_88 = Mesh;
        std::memcpy(&v12->field_0, &LocalToWorld, sizeof(LocalToWorld));

        ptr_to_po a2a;
        a2a.m_rel_po = CAST(a2a.m_rel_po, &LocalToWorld);
        a2a.m_abs_po = CAST(a2a.m_abs_po, nglCurScene()->field_18C);

        matrix4x4 v19 = sub_507130(&a2a);
        v12->field_40 = v19;

        v12->field_84 = 0;
        v12->field_80 = 0;
        v12->field_94 = 1.0;

        assert(!(MeshParams->Flags & NGLP_SCALE) && "No scale allowed in FastListAddMesh.\n");

        //assert((MeshParams->Flags & NGLP_REFERENCED) && "MeshParams must be referenced in FastListAddMesh.\n");

        assert((MeshParams->Flags & NGLP_NO_CULLING) &&
               "Mesh must be pre-culled for FastListAddMesh.\n");

        assert(!(MeshParams->Flags & NGLP_FORCE_LOD) &&
               "Force LOD not supported by FastListAddMesh.\n");

        v12->field_90 = MeshParams;

        assert(ShaderParams != nullptr && "NULL ShaderParams in FastListAddMesh.\n");

        v12->field_8C = *ShaderParams;

        for (auto i = 0u; i < Mesh->NSections; ++i) {
            auto *MeshSection = Mesh->Sections[i].Section;

            nglPerfInfo().m_num_verts += MeshSection->NVertices;

            nglMaterialBase *v15 = sub_8EA2E0(&v12->field_8C, MeshSection->Material);

            auto &AddNode = get_vfunc(MeshSection->Material->field_4->m_vtbl, 0x8);
            AddNode(MeshSection->Material->field_4, v12, MeshSection, v15);
        }

        nglPerfInfo().m_num_polys += Mesh->field_3C;

        if (Mesh->File != nullptr) {
            Mesh->File->field_144 = nglFrame();
        }
    } else {
        CDECL_CALL(0x00507690, Mesh, LocalToWorld, MeshParams, ShaderParams);
    }
}
