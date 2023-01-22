/*************************************************************
Sakura Game Framework : SaDebugDraw.cpp
Author: Darrell Blake
*************************************************************/

#include "SaDebugDraw.h"
#include <SakuraMaths/SaVector2.h>
#include <SakuraMaths/SaVector3.h>
#include <SakuraMaths/SaMatrix44.h>
#include "SaColour.h"
#include "SaEffect.h"
#include "SaRenderState.h"
#include "SaResourceManager.h"
#include "SaRender.h"

using namespace Sakura;
using namespace SakuraMaths;

SaDebugDraw::DebugPrims SaDebugDraw::ms_lineDebugPrims2D(2, 2, 128, SHAPE_LINES);
SaDebugDraw::DebugPrims SaDebugDraw::ms_triangleDebugPrims2D(2, 3, 128, SHAPE_TRIANGLES);
SaDebugDraw::DebugPrims SaDebugDraw::ms_lineDebugPrims3D(3, 2, 4096, SHAPE_LINES);
SaDebugDraw::DebugPrims SaDebugDraw::ms_triangleDebugPrims3D(3, 3, 128, SHAPE_TRIANGLES);
SaResource<SaEffect>* SaDebugDraw::ms_pDebugEffect2D = NULL;
SaResource<SaEffect>* SaDebugDraw::ms_pDebugEffect3D = NULL;

void SaDebugDraw::Initialise()
{
    SaRenderJob job(BIND_FUNC(&RenderThread_CreatePrimBuffers));
    SaRender::AddRenderJob(job);

    ms_pDebugEffect2D = SaResourceManager::LoadEffect("SaDebugEffect");
    ms_pDebugEffect3D = SaResourceManager::LoadEffect("SaDebugEffect");
}

void SaDebugDraw::Release()
{
    if (ms_pDebugEffect2D)
        SaResourceManager::UnloadEffect(ms_pDebugEffect2D);
    if (ms_pDebugEffect3D)
        SaResourceManager::UnloadEffect(ms_pDebugEffect3D);

    SaRenderJob job(BIND_FUNC(&RenderThread_DeletePrimBuffers));
    SaRender::AddRenderJob(job);
}

void SaDebugDraw::Render3D()
{
    if (!ms_pDebugEffect3D)
        return;

    //Render 3D prims.
    ms_pDebugEffect3D->Get().Enable();

    ms_pDebugEffect3D->Get().SetMatrixParameter(VERTEX_SHADER, "viewMatrix", SaRenderState::GetViewMatrix());
    ms_pDebugEffect3D->Get().SetMatrixParameter(VERTEX_SHADER, "projectionMatrix", SaRenderState::GetProjectionMatrix());

    SaRenderJob job(BIND_FUNC(&RenderThread_Render3DPrims));
    SaRender::AddRenderFrameJob(job);

    ms_pDebugEffect3D->Get().Disable();
}

void SaDebugDraw::Render2D()
{
    if (!ms_pDebugEffect2D)
        return;

    //Render 2D prims.
    ms_pDebugEffect2D->Get().Enable();

    ms_pDebugEffect2D->Get().SetMatrixParameter(VERTEX_SHADER, "viewMatrix", SaMatrix44::IDENTITY);
    ms_pDebugEffect2D->Get().SetMatrixParameter(VERTEX_SHADER, "projectionMatrix", SaRenderState::Get2DProjectionMatrix());

    SaRenderJob job(BIND_FUNC(&RenderThread_Render2DPrims));
    SaRender::AddRenderFrameJob(job);

    ms_pDebugEffect2D->Get().Disable();
}

void SaDebugDraw::RenderPrims(EDebugPrimsType primsType)
{
    DebugPrims* pPrims = GetDebugPrims(primsType);

    if (pPrims)
    {
        DrawPrims(pPrims);

        pPrims->numVerts = 0;
    }
}

void SaDebugDraw::DrawLine2D(const SaVector2& rPos1, const SaVector2& rPos2, const SaColour& rColour)
{
    if (!ms_pDebugEffect2D)
        return;

    SaRenderJob job(BIND_FUNC(&RenderThread_AddPrimLine2D));
    job.SetVector2(rPos1, 0);
    job.SetVector2(rPos2, 1);
    job.SetColour(rColour);
    SaRender::AddRenderFrameJob(job);
}

void SaDebugDraw::DrawTriangle2D(const SaVector2& rPos1, const SaVector2& rPos2, const SaVector2& rPos3, const SaColour& rColour)
{
    if (!ms_pDebugEffect2D)
        return;

    SaRenderJob job(BIND_FUNC(&RenderThread_AddPrimTri2D));
    job.SetVector2(rPos1, 0);
    job.SetVector2(rPos2, 1);
    job.SetVector2(rPos3, 2);
    job.SetColour(rColour);
    SaRender::AddRenderFrameJob(job);
}

void SaDebugDraw::DrawSquare2D(const SakuraMaths::SaVector2& rPos1, const SakuraMaths::SaVector2& rPos2, const SakuraMaths::SaVector2& rPos3, const SakuraMaths::SaVector2& rPos4, const SaColour& rColour)
{
    if (!ms_pDebugEffect2D)
        return;

    SaRenderJob job(BIND_FUNC(&RenderThread_AddPrimSquare2D));
    job.SetVector2(rPos1, 0);
    job.SetVector2(rPos2, 1);
    job.SetVector2(rPos3, 2);
    job.SetVector2(rPos4, 3);
    job.SetColour(rColour);
    SaRender::AddRenderFrameJob(job);
}

void SaDebugDraw::DrawLine3D(const SaVector3& rPos1, const SaVector3& rPos2, const SaColour& rColour)
{
    if (!ms_pDebugEffect3D)
        return;

    SaRenderJob job(BIND_FUNC(&RenderThread_AddPrimLine3D));
    job.SetVector3(rPos1, 0);
    job.SetVector3(rPos2, 1);
    job.SetColour(rColour);
    SaRender::AddRenderFrameJob(job);
}

void SaDebugDraw::DrawTriangle3D(const SaVector3& rPos1, const SaVector3& rPos2, const SaVector3& rPos3, const SaColour& rColour)
{
    if (!ms_pDebugEffect3D)
        return;

    SaRenderJob job(BIND_FUNC(&RenderThread_AddPrimTri3D));
    job.SetVector3(rPos1, 0);
    job.SetVector3(rPos2, 1);
    job.SetVector3(rPos3, 2);
    job.SetColour(rColour);
    SaRender::AddRenderFrameJob(job);
}

SaDebugDraw::DebugPrims* SaDebugDraw::GetDebugPrims(EDebugPrimsType primsType)
{
    switch (primsType)
    {
        case PRIM_LINES_2D: return &ms_lineDebugPrims2D; break;
        case PRIM_TRIANGLES_2D: return &ms_triangleDebugPrims2D; break;
        case PRIM_LINES_3D: return &ms_lineDebugPrims3D; break;
        case PRIM_TRIANGLES_3D: return &ms_triangleDebugPrims3D; break;
        default:
            SA_FAIL("Unsupported prim type.");
    }

    return NULL;
}

void SaDebugDraw::RenderThread_CreatePrimBuffers(const SaRenderJob* pJob)
{
    for (uint32_t primsIdx = 0; primsIdx < PRIM_MAX; primsIdx++)
    {
        DebugPrims* pPrims = GetDebugPrims((EDebugPrimsType)primsIdx);

        if (pPrims)
        {
            CreatePrimBuffer(pPrims);
        }
    }
}

void SaDebugDraw::RenderThread_DeletePrimBuffers(const SaRenderJob* pJob)
{
    for (uint32_t primsIdx = 0; primsIdx < PRIM_MAX; primsIdx++)
    {
        DebugPrims* pPrims = GetDebugPrims((EDebugPrimsType)primsIdx);

        if (pPrims)
        {
            DeletePrimBuffer(pPrims);
        }
    }
}

void SaDebugDraw::RenderThread_AddPrimLine2D(const SaRenderJob* pJob)
{
    DebugPrims* pPrims = GetDebugPrims(PRIM_LINES_2D);

    if (pPrims)
    {
        SA_ASSERT(pPrims->numVerts + pPrims->SHAPE_VERTS <= pPrims->MAX_VERTS, "Too many prims of this type.");

        if (pPrims->numVerts + pPrims->SHAPE_VERTS <= pPrims->MAX_VERTS)
        {
            AddPrim(pPrims, (float*)&pJob->GetColour(), (float*)&pJob->GetVector2(0), (float*)&pJob->GetVector2(1));

            pPrims->numVerts += pPrims->SHAPE_VERTS;
        }
    }
}

void SaDebugDraw::RenderThread_AddPrimTri2D(const SaRenderJob* pJob)
{
    DebugPrims* pPrims = GetDebugPrims(PRIM_TRIANGLES_2D);

    if (pPrims)
    {
        SA_ASSERT(pPrims->numVerts + pPrims->SHAPE_VERTS <= pPrims->MAX_VERTS, "Too many prims of this type.");

        if (pPrims->numVerts + pPrims->SHAPE_VERTS <= pPrims->MAX_VERTS)
        {
            AddPrim(pPrims, (float*)&pJob->GetColour(), (float*)&pJob->GetVector2(0), (float*)&pJob->GetVector2(1), (float*)&pJob->GetVector2(2));

            pPrims->numVerts += pPrims->SHAPE_VERTS;
        }
    }
}

void SaDebugDraw::RenderThread_AddPrimSquare2D(const SaRenderJob* pJob)
{
    DebugPrims* pPrims = GetDebugPrims(PRIM_TRIANGLES_2D);

    if (pPrims)
    {
        SA_ASSERT(pPrims->numVerts + (pPrims->SHAPE_VERTS*2) <= pPrims->MAX_VERTS, "Too many prims of this type.");

        if (pPrims->numVerts + (pPrims->SHAPE_VERTS*2) <= pPrims->MAX_VERTS)
        {
            AddPrim(pPrims, (float*)&pJob->GetColour(), (float*)&pJob->GetVector2(0), (float*)&pJob->GetVector2(1), (float*)&pJob->GetVector2(2));
            pPrims->numVerts += (pPrims->SHAPE_VERTS);

            AddPrim(pPrims, (float*)&pJob->GetColour(), (float*)&pJob->GetVector2(2), (float*)&pJob->GetVector2(1), (float*)&pJob->GetVector2(3));
            pPrims->numVerts += (pPrims->SHAPE_VERTS);
        }
    }
}

void SaDebugDraw::RenderThread_AddPrimLine3D(const SaRenderJob* pJob)
{
    DebugPrims* pPrims = GetDebugPrims(PRIM_LINES_3D);

    if (pPrims)
    {
        SA_ASSERT(pPrims->numVerts + pPrims->SHAPE_VERTS <= pPrims->MAX_VERTS, "Too many prims of this type.");

        if (pPrims->numVerts + pPrims->SHAPE_VERTS <= pPrims->MAX_VERTS)
        {
            AddPrim(pPrims, (float*)&pJob->GetColour(), (float*)&pJob->GetVector3(0), (float*)&pJob->GetVector3(1));

            pPrims->numVerts += pPrims->SHAPE_VERTS;
        }
    }
}

void SaDebugDraw::RenderThread_AddPrimTri3D(const SaRenderJob* pJob)
{
    DebugPrims* pPrims = GetDebugPrims(PRIM_TRIANGLES_3D);

    if (pPrims)
    {
        SA_ASSERT(pPrims->numVerts + pPrims->SHAPE_VERTS <= pPrims->MAX_VERTS, "Too many prims of this type.");

        if (pPrims->numVerts + pPrims->SHAPE_VERTS <= pPrims->MAX_VERTS)
        {
            AddPrim(pPrims, (float*)&pJob->GetColour(), (float*)&pJob->GetVector3(0), (float*)&pJob->GetVector3(1), (float*)&pJob->GetVector3(2));

            pPrims->numVerts += pPrims->SHAPE_VERTS;
        }
    }
}

void SaDebugDraw::RenderThread_Render3DPrims(const SaRenderJob* pJob)
{
    RenderPrims(PRIM_LINES_3D);
    RenderPrims(PRIM_TRIANGLES_3D);
}

void SaDebugDraw::RenderThread_Render2DPrims(const SaRenderJob* pJob)
{
    RenderPrims(PRIM_LINES_2D);
    RenderPrims(PRIM_TRIANGLES_2D);
}
