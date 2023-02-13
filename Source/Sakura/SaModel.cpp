/*************************************************************
Sakura Game Framework : SaModel.cpp
Author: Darrell Blake
*************************************************************/

#include "SaModel.h"
#include "SaDebug.h"
#include "SaFile.h"
#include <SakuraMaths/SaVector3.h>
#include "SaDebugDraw.h"
#include "SaDataReader.h"
#include "SaRender.h"

using namespace Sakura;
using namespace SakuraMaths;

SaModel::SaModel() :
    m_platformModel(this),
    m_state(STATE_UNLOADED),
    m_numVertices(0),
    m_numTriangles(0),
    m_pVertices(NULL),
    m_pTriangles(NULL),
    m_loadFinishedCallback(NO_CALLBACK)
{
}

void SaModel::Load(const uint8_t* pFileData, const uint32_t fileDataSize, SaCallback<bool> callback)
{
    m_loadFinishedCallback = callback;

    SaRenderJob job(BIND_MEMBER_FUNC(&SaModel::RenderThread_Load, this));
    job.SetData(pFileData);
    SaRender::AddRenderJob(job);
}

void SaModel::Unload(SaCallback<bool> callback)
{
    m_loadFinishedCallback = callback;

    SaRenderJob job(BIND_MEMBER_FUNC(&SaModel::RenderThread_Unload, this));
    SaRender::AddRenderJob(job);
}

void SaModel::Render()
{
    if (m_state == STATE_LOADED)
    {
        SaRenderJob job(BIND_MEMBER_FUNC(&SaModel::RenderThread_Render, this));
        SaRender::AddRenderFrameJob(job);
    }
}

#ifdef SA_BUILD_DEBUG
void SaModel::DebugDrawNormals()
{
    if (m_state == STATE_LOADED)
    {
        SA_ASSERT(m_pTriangles, "Not loaded!");

        if (m_pTriangles == NULL)
            return;

        for (uint32_t vertIdx = 0; vertIdx < m_numVertices; vertIdx++)
        {
            const Vertex& rVertex = m_pVertices[vertIdx];
            SaDebugDraw::DrawLine3D(rVertex.position, rVertex.position + rVertex.normal * 0.2f, SaColour::BLUE);        
        }
    }
}
#endif

const SaColour& SaModel::GetMaterialColour()
{
    return m_material.diffuseColour;
}

void SaModel::RenderThread_Load(const SaRenderJob* pJob)
{
    SA_ASSERT(m_pTriangles == NULL, "Model already loaded!?");

    const uint8_t* pFileData = pJob->GetData();

    SaDataReader dataReader(pFileData);

    uint32_t fileVersion = dataReader.Read32();
    SA_ASSERT(fileVersion == FILE_VERSION, "Incorrect file version!");

    if (!m_pTriangles && fileVersion == FILE_VERSION)
    {
        m_numVertices = dataReader.Read32();
        m_numTriangles = dataReader.Read32();

        m_pVertices = new Vertex[m_numVertices];
        m_pTriangles = new Triangle[m_numTriangles];

        for (uint32_t vertIdx = 0; vertIdx < m_numVertices; vertIdx++)
        {
            float x = dataReader.ReadFloat();
            float y = dataReader.ReadFloat();
            float z = dataReader.ReadFloat();
            m_pVertices[vertIdx].position.Set(x, y, z);

            x = dataReader.ReadFloat();
            y = dataReader.ReadFloat();
            z = dataReader.ReadFloat();
            m_pVertices[vertIdx].normal.Set(x, y, z);
        }

        for (uint32_t triIdx = 0; triIdx < m_numTriangles; triIdx++)
        {
            m_pTriangles[triIdx].vertIndices[0] = dataReader.Read32();
            m_pTriangles[triIdx].vertIndices[1] = dataReader.Read32();
            m_pTriangles[triIdx].vertIndices[2] = dataReader.Read32();
        }

        float r = dataReader.ReadFloat();
        float g = dataReader.ReadFloat();
        float b = dataReader.ReadFloat();
        m_material.diffuseColour.Set(r, g, b, 1.0f);

        if (m_platformModel.Load())
        {
            m_state = STATE_LOADED;
        }
        else
        {
            m_state = STATE_ERROR;
        }
    }
    else
    {
        m_state = STATE_ERROR;
    }

    m_loadFinishedCallback(m_state == STATE_LOADED);
}

void SaModel::RenderThread_Unload(const SaRenderJob* pJob)
{
    SA_ASSERT(m_pTriangles, "Not loaded!");

    SaRender::RenderThread_ClearCurrentFrameJobs();

    if (m_platformModel.Unload())
    {
        m_state = STATE_UNLOADED;
    }
    else
    {
        m_state = STATE_ERROR;
    }

    m_numVertices = 0;

    if (m_pVertices)
    {
        delete[] m_pVertices;
        m_pVertices = NULL;
    }

    m_numTriangles = 0;

    if (m_pTriangles)
    {
        delete[] m_pTriangles;
        m_pTriangles = NULL;
    }

    m_loadFinishedCallback(m_state == STATE_UNLOADED);
}

void SaModel::RenderThread_Render(const SaRenderJob* pJob)
{
    m_platformModel.Render();
}
