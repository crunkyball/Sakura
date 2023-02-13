/*************************************************************
Sakura Game Framework : SaTexture.cpp
Author: Darrell Blake
*************************************************************/

#include "SaTexture.h"
#include "SaDebug.h"
#include "SaFile.h"
#include "SaRender.h"

using namespace Sakura;

extern "C" unsigned char *stbi_load_from_memory(unsigned char const *buffer, int len, int *x, int *y, int *comp, int req_comp);
extern "C" void stbi_image_free(void *retval_from_stbi_load);

SaTexture::SaTexture() :
    m_platformTexture(this),
    m_state(STATE_UNLOADED),
    m_width(0),
    m_height(0),
    m_bitDepth(0),
    m_loadFinishedCallback(NO_CALLBACK)
{
}

void SaTexture::Load(const uint8_t* pFileData, const uint32_t fileDataSize, SaCallback<bool> callback)
{
    m_loadFinishedCallback = callback;

    SaRenderJob job(BIND_MEMBER_FUNC(&SaTexture::RenderThread_Load, this));
    job.SetData(pFileData);
    job.SetDataSize(fileDataSize);
    SaRender::AddRenderJob(job);
}

void SaTexture::Unload(SaCallback<bool> callback)
{
    m_loadFinishedCallback = callback;

    SaRenderJob job(BIND_MEMBER_FUNC(&SaTexture::RenderThread_Unload, this));
    SaRender::AddRenderJob(job);
}

void SaTexture::GetDimensions(uint32_t& rWidth, uint32_t& rHeight) const
{
    rWidth = m_width;
    rHeight = m_height;
}

const SaTexture_Platform& SaTexture::GetPlatformTexture() const
{
    return m_platformTexture;
}

void SaTexture::RenderThread_Load(const SaRenderJob* pJob)
{
    int32_t width, height, bitDepth = 0;

    const uint8_t* pFileData = pJob->GetData();
    const uint32_t fileDataSize = pJob->GetDataSize();

    uint8_t* pFileLoadData = ::stbi_load_from_memory(pFileData, fileDataSize, &width, &height, &bitDepth, 0);

    if (pFileLoadData)
    {
        m_width = width;
        m_height = height;
        m_bitDepth = bitDepth;

        if (m_platformTexture.Load(pFileLoadData))
        {
            m_state = STATE_LOADED;
        }
        else
        {
            m_state = STATE_ERROR;
        }

        stbi_image_free(pFileLoadData);
    }
    else
    {
        m_state = STATE_ERROR;
    }

    m_loadFinishedCallback(m_state == STATE_LOADED);
}

void SaTexture::RenderThread_Unload(const SaRenderJob* pJob)
{
    SaRender::RenderThread_ClearCurrentFrameJobs();

    if (m_platformTexture.Unload())
    {
        m_state = STATE_UNLOADED;
    }
    else
    {
        m_state = STATE_ERROR;
    }

    m_loadFinishedCallback(m_state == STATE_UNLOADED);
}
