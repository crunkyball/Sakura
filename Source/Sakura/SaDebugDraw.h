/*************************************************************
Sakura Game Framework : SaDebugDraw.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_DEBUG_DRAW_H
#define _SA_DEBUG_DRAW_H

#include "SaCore.h"
#include "SaResource.h"
#include "SaEffect.h"

namespace SakuraMaths
{
    class SaVector2;
    class SaVector3;
    class SaMatrix44;
}

namespace Sakura
{
    class SaColour;

    class SaDebugDraw
    {
    public:
        static void Initialise();
        static void Release();

        static void Render3D();
        static void Render2D();

        static void DrawLine2D(const SakuraMaths::SaVector2& rPos1, const SakuraMaths::SaVector2& rPos2, const SaColour& rColour);
        static void DrawTriangle2D(const SakuraMaths::SaVector2& rPos1, const SakuraMaths::SaVector2& rPos2, const SakuraMaths::SaVector2& rPos3, const SaColour& rColour);
        static void DrawSquare2D(const SakuraMaths::SaVector2& rPos1, const SakuraMaths::SaVector2& rPos2, const SakuraMaths::SaVector2& rPos3, const SakuraMaths::SaVector2& rPos4, const SaColour& rColour);

        static void DrawLine3D(const SakuraMaths::SaVector3& rPos1, const SakuraMaths::SaVector3& rPos2, const SaColour& rColour);
        static void DrawTriangle3D(const SakuraMaths::SaVector3& rPos1, const SakuraMaths::SaVector3& rPos2, const SakuraMaths::SaVector3& rPos3, const SaColour& rColour);

    private:
        enum ShapeType
        {
            SHAPE_LINES = 0,
            SHAPE_TRIANGLES
        };

        struct DebugPrims
        {
            DebugPrims(uint32_t vertDimensions, uint32_t shapeVerts, uint32_t maxShapes, ShapeType shapeType ) :
                VERT_DIMENSIONS(vertDimensions),
                SHAPE_VERTS(shapeVerts),
                MAX_SHAPES(maxShapes),
                SHAPE_TYPE(shapeType),
                MAX_VERTS(SHAPE_VERTS*MAX_SHAPES),
                POS_SIZE_BYTES(VERT_DIMENSIONS * sizeof(float))
                {}

            const uint32_t  VERT_DIMENSIONS;
            const uint32_t  SHAPE_VERTS;
            const uint32_t  MAX_SHAPES;
            const uint32_t  MAX_VERTS;
            const ShapeType SHAPE_TYPE;
            const uint32_t  POS_SIZE_BYTES;

            uint32_t numVerts;
            uint32_t vao;
            uint32_t vbo[2];
        };

        enum EDebugPrimsType
        {
            PRIM_LINES_2D = 0,
            PRIM_TRIANGLES_2D,
            PRIM_LINES_3D,
            PRIM_TRIANGLES_3D,
            PRIM_MAX
        };

        static void RenderPrims(EDebugPrimsType primsType);

        static const uint32_t COL_SIZE_BYTES = 3 * sizeof(float);

        static DebugPrims ms_lineDebugPrims2D;
        static DebugPrims ms_triangleDebugPrims2D;
        static DebugPrims ms_lineDebugPrims3D;
        static DebugPrims ms_triangleDebugPrims3D;

        static DebugPrims* GetDebugPrims(EDebugPrimsType primsType);

        static SaResource<SaEffect>* ms_pDebugEffect2D;
        static SaResource<SaEffect>* ms_pDebugEffect3D;

        static void RenderThread_CreatePrimBuffers(const SaRenderJob* pJob);
        static void RenderThread_DeletePrimBuffers(const SaRenderJob* pJob);
        static void RenderThread_AddPrimLine2D(const SaRenderJob* pJob);
        static void RenderThread_AddPrimTri2D(const SaRenderJob* pJob);
        static void RenderThread_AddPrimSquare2D(const SaRenderJob* pJob);
        static void RenderThread_AddPrimLine3D(const SaRenderJob* pJob);
        static void RenderThread_AddPrimTri3D(const SaRenderJob* pJob);

        static void RenderThread_Render3DPrims(const SaRenderJob* pJob);
        static void RenderThread_Render2DPrims(const SaRenderJob* pJob);

        //These functions will need their own implementation per
        //platform in their relevant SaDebugDraw_Platform.cpp
        static void CreatePrimBuffer(DebugPrims* pPrims);
        static void DeletePrimBuffer(DebugPrims* pPrims);
        static void DrawPrims(DebugPrims* pPrims);
        static void AddPrim(DebugPrims* pPrims, const float* pColour, const float* pPos1, const float* pPos2, const float* pPos3 = NULL);
    };
}

#endif  //_SA_DEBUG_DRAW_H
