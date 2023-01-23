/*************************************************************
Sakura Game Framework : SaWindow.cpp
Author: Darrell Blake
*************************************************************/

#include "SaWindow.h"
#include "SaDebug.h"
#include "SaScene.h"
#include "SaCamera.h"
#include "SaRenderState.h"
#include "SaRender.h"
#include <cstdio>
#include <cstring>

using namespace Sakura;

SaWindow::SaWindow() :
    m_platformWindow(this),
    m_state(STATE_UNITIALISED),
    m_width(0),
    m_height(0),
    m_clearColour(SaColour::SAKURA),
    m_pKeyboardInputHandler(NULL)
{
    strcpy_s(m_title, TITLE_LENGTH, "Sakura Game Framework");
}

void SaWindow::Initialise(const char* title, uint32_t width, uint32_t height, SaColour clearColour)
{
    const char* pAdd = "Sakura Game Framework";

    if (title && strlen(title) > 0)
    {
        sprintf_s(m_title, title, "%s - %s", title, pAdd);
    }

    m_width = width;
    m_height = height;
    m_clearColour = clearColour;

    m_numViewPorts = 1;
    m_viewports[0].Initialise(0, 0, m_width, m_height, clearColour);

    if (m_platformWindow.Initialise())
    {
        SaRenderJob job(BIND_MEMBER_FUNC(&SaWindow::RenderThread_Initialise, this));
        SaRender::AddRenderJob(job);
    }
    else
    {
        SA_FAIL("Error creating window!");
        m_state = STATE_ERROR;
    }
}

void SaWindow::Release()
{
    m_platformWindow.Release();
}

void SaWindow::Update(uint32_t dt)
{
    m_platformWindow.Update(dt);
}

void SaWindow::PreRender()
{
    SaRenderJob job(BIND_MEMBER_FUNC(&SaWindow::RenderThread_PreRender, this));
    SaRender::AddRenderFrameJob(job);
}

void SaWindow::PostRender()
{
    SaRenderJob job(BIND_MEMBER_FUNC(&SaWindow::RenderThread_PostRender, this));
    SaRender::AddRenderFrameJob(job);
}

void SaWindow::SetViewports(uint32_t numViewports, const ViewportConfig* configs)
{
    SA_ASSERT(numViewports > 0 && numViewports < MAX_VIEWPORTS, "Incorrect num of viewports.");

    if (numViewports > 0 && numViewports < MAX_VIEWPORTS)
    {
        m_numViewPorts = numViewports;

        for (uint32_t viewportIdx = 0; viewportIdx < numViewports; viewportIdx++)
        {
            const ViewportConfig& rConfig = configs[viewportIdx];
            m_viewports[viewportIdx].Initialise(rConfig.xPosition, rConfig.yPosition, rConfig.width, rConfig.height, m_clearColour);
        }
    }
}

void SaWindow::RenderThread_Initialise(const SaRenderJob* pJob)
{
    if (m_platformWindow.InitialiseRender())
    {
        m_state = STATE_INITIALISED;
    }
    else
    {
        SA_FAIL("Error creating window!");
        m_state = STATE_ERROR;
    }
}

void SaWindow::RenderThread_PreRender(const SaRenderJob* pJob)
{
    m_platformWindow.PreRender();
}

void SaWindow::RenderThread_PostRender(const SaRenderJob* pJob)
{
    m_platformWindow.PostRender();
}

void SaWindow::SetKeyboardInputHandler(const SaKeyboardInputHandler* pHandler)
{
    SA_WARNING(m_pKeyboardInputHandler == NULL, "Warning: Replacing keyboard input handler.");
    m_pKeyboardInputHandler = pHandler;
}
