/*************************************************************
Sakura Game Framework : SaViewport.cpp
Author: Darrell Blake
*************************************************************/

#include "SaViewport.h"
#include "SaCamera.h"
#include "SaRenderState.h"
#include "SaRender.h"

using namespace Sakura;

SaViewport::SaViewport() :
    m_platformViewport(this),
    m_xPosition(0),
    m_yPosition(0),
    m_width(0),
    m_height(0),
    m_clearColour(SaColour::SAKURA),
    m_pCamera(NULL)
{
}

void SaViewport::Initialise(uint32_t xPosition, uint32_t yPosition, uint32_t width, uint32_t height, SaColour clearColour)
{
    m_xPosition = xPosition;
    m_yPosition = yPosition;
    m_width = width;
    m_height = height;
    m_clearColour = clearColour;
}

void SaViewport::Release()
{
}

void SaViewport::PreRender()
{
    SaRenderJob job(BIND_MEMBER_FUNC(&SaViewport::RenderThread_PreRender, this));
    SaRender::AddRenderFrameJob(job);

    if (m_pCamera)
    {
        SaRenderState::SetProjectionMatrix(m_pCamera->GetProjectionMatrix());
        SaRenderState::SetViewMatrix(m_pCamera->GetViewMatrix());
    }
}

void SaViewport::AttachCamera(const SaCamera* pCamera)
{
    m_pCamera = pCamera;
}

void SaViewport::RenderThread_PreRender(const SaRenderJob* pJob)
{
    m_platformViewport.PreRender();
}
