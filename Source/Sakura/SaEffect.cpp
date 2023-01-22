/*************************************************************
Sakura Game Framework : SaEffect.cpp
Author: Darrell Blake
*************************************************************/

#include "SaEffect.h"
#include "SaDebug.h"
#include "SaFile.h"
#include "SaRender.h"

using namespace Sakura;

bool SaEffect::ms_locked = false;

SaEffect::SaEffect() :
    m_state(STATE_UNLOADED),
    m_platformEffect(this),
    m_enabled(false),
    m_loadFinishedCallback(NO_CALLBACK)
{
}

void SaEffect::Initialise()
{
    SaRenderJob job(BIND_FUNC(&RenderThread_Initialise, this));
    SaRender::AddRenderJob(job);
}

void SaEffect::Load(const uint8_t* pVertexShaderData, const uint8_t* pFragmentShaderData, SaCallback<bool> callback)
{
    m_loadFinishedCallback = callback;

    SaRenderJob job(BIND_MEMBER_FUNC(&SaEffect::RenderThread_Load, this));
    job.SetData(pVertexShaderData, 0);
    job.SetData(pFragmentShaderData, 1);
    SaRender::AddRenderJob(job);
}

void SaEffect::Unload(SaCallback<bool> callback)
{
    m_loadFinishedCallback = callback;

    SaRenderJob job(BIND_MEMBER_FUNC(&SaEffect::RenderThread_Unload, this));
    SaRender::AddRenderJob(job);
}

void SaEffect::SetIntParameter(SaShaderType shaderType, const char* pParameterName, const int32_t val)
{
    if (m_state == STATE_LOADED)
    {
        SaRenderJob job(BIND_MEMBER_FUNC(&SaEffect::RenderThread_SetIntParameter, this));
        job.SetShaderType(shaderType);
        job.SetName(pParameterName);
        job.SetInt(val);
        SaRender::AddRenderFrameJob(job);
    }
}

void SaEffect::SetFloatParameter(SaShaderType shaderType, const char* pParameterName, const float val)
{
    if (m_state == STATE_LOADED)
    {
        SaRenderJob job(BIND_MEMBER_FUNC(&SaEffect::RenderThread_SetFloatParameter, this));
        job.SetShaderType(shaderType);
        job.SetName(pParameterName);
        job.SetFloat(val);
        SaRender::AddRenderFrameJob(job);
    }
}

void SaEffect::SetVectorParameter(SaShaderType shaderType, const char* pParameterName, const SakuraMaths::SaVector3& rVector)
{
    if (m_state == STATE_LOADED)
    {
        SaRenderJob job(BIND_MEMBER_FUNC(&SaEffect::RenderThread_SetVectorParameter, this));
        job.SetShaderType(shaderType);
        job.SetName(pParameterName);
        job.SetVector3(rVector);
        SaRender::AddRenderFrameJob(job);
    }
}

void SaEffect::SetMatrixParameter(SaShaderType shaderType, const char* pParameterName, const SakuraMaths::SaMatrix44& rMatrix)
{
    if (m_state == STATE_LOADED)
    {
        SaRenderJob job(BIND_MEMBER_FUNC(&SaEffect::RenderThread_SetMatrixParameter, this));
        job.SetShaderType(shaderType);
        job.SetName(pParameterName);
        job.SetMatrix(rMatrix);
        SaRender::AddRenderFrameJob(job);
    }
}

void SaEffect::SetColourParameter(SaShaderType shaderType, const char* pParameterName, const SaColour& rColour)
{
    if (m_state == STATE_LOADED)
    {
        SaRenderJob job(BIND_MEMBER_FUNC(&SaEffect::RenderThread_SetColourParameter, this));
        job.SetShaderType(shaderType);
        job.SetName(pParameterName);
        job.SetColour(rColour);
        SaRender::AddRenderFrameJob(job);
    }
}

void SaEffect::SetTextureParameter(SaShaderType shaderType, const char* pParameterName, const SaTexture* pTexture)
{
    if (m_state == STATE_LOADED)
    {
        SaRenderJob job(BIND_MEMBER_FUNC(&SaEffect::RenderThread_SetTextureParameter, this));
        job.SetShaderType(shaderType);
        job.SetName(pParameterName);
        job.SetTexture(pTexture);
        SaRender::AddRenderFrameJob(job);
    }
}

void SaEffect::Enable()
{
    if (m_state == STATE_LOADED)
    {
        SaRenderJob job(BIND_MEMBER_FUNC(&SaEffect::RenderThread_Enable, this));
        SaRender::AddRenderFrameJob(job);
    }
}

void SaEffect::Disable()
{
    if (m_state == STATE_LOADED)
    {
        SaRenderJob job(BIND_MEMBER_FUNC(&SaEffect::RenderThread_Disable, this));
        SaRender::AddRenderFrameJob(job);
    }
}

void SaEffect::RenderThread_Initialise(const SaRenderJob* pJob)
{
    SaEffect_Platform::Initialise();
}

void SaEffect::RenderThread_Load(const SaRenderJob* pJob)
{
    const uint8_t* pVertexFileLoadData = pJob->GetData(0);
    const uint8_t* pFragmentFileLoadData = pJob->GetData(1);

    if (m_platformEffect.Load(pVertexFileLoadData, pFragmentFileLoadData))
    {
        m_state = STATE_LOADED;
    }
    else
    {
        m_state = STATE_ERROR;
    }

    m_loadFinishedCallback(m_state == STATE_LOADED);
}

void SaEffect::RenderThread_Unload(const SaRenderJob* pJob)
{
    SaRender::RenderThread_ClearCurrentFrameJobs();

    if (m_platformEffect.Unload())
    {
        m_state = STATE_UNLOADED;
    }
    else
    {
        m_state = STATE_ERROR;
    }

    m_loadFinishedCallback(m_state == STATE_UNLOADED);
}

void SaEffect::RenderThread_Enable(const SaRenderJob* pJob)
{
    SA_ASSERT(!m_enabled, "This effect is already enabled.");
    SA_ASSERT(!ms_locked, "Another effect is already enabled.");

    m_platformEffect.Enable();

    m_enabled = ms_locked = true;
}

void SaEffect::RenderThread_Disable(const SaRenderJob* pJob)
{
    SA_ASSERT(m_enabled && ms_locked, "This effect isn't enabled.");

    m_platformEffect.Disable();

    m_enabled = ms_locked = false;
}

void SaEffect::RenderThread_SetIntParameter(const SaRenderJob* pJob)
{
    SA_ASSERT(m_enabled, && ms_locked, "Effect isn't enabled.");
    m_platformEffect.SetIntParameter(pJob->GetShaderType(), pJob->GetName(), pJob->GetInt());
}

void SaEffect::RenderThread_SetFloatParameter(const SaRenderJob* pJob)
{
    SA_ASSERT(m_enabled, && ms_locked, "Effect isn't enabled.");
    m_platformEffect.SetFloatParameter(pJob->GetShaderType(), pJob->GetName(), pJob->GetFloat());
}

void SaEffect::RenderThread_SetVectorParameter(const SaRenderJob* pJob)
{
    SA_ASSERT(m_enabled && ms_locked, "Effect isn't enabled.");
    m_platformEffect.SetVectorParameter(pJob->GetShaderType(), pJob->GetName(), pJob->GetVector3());
}

void SaEffect::RenderThread_SetMatrixParameter(const SaRenderJob* pJob)
{
    SA_ASSERT(m_enabled && ms_locked, "Effect isn't enabled.");
    m_platformEffect.SetMatrixParameter(pJob->GetShaderType(), pJob->GetName(), pJob->GetMatrix());
}

void SaEffect::RenderThread_SetColourParameter(const SaRenderJob* pJob)
{
    SA_ASSERT(m_enabled && ms_locked, "Effect isn't enabled.");
    m_platformEffect.SetColourParameter(pJob->GetShaderType(), pJob->GetName(), pJob->GetColour());
}

void SaEffect::RenderThread_SetTextureParameter(const SaRenderJob* pJob)
{
    SA_ASSERT(m_enabled && ms_locked, "Effect isn't enabled.");
    m_platformEffect.SetTextureParameter(pJob->GetShaderType(), pJob->GetName(), pJob->GetTexture());
}
