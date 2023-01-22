/*************************************************************
Sakura Game Framework : SaGame.cpp
Author: Darrell Blake
*************************************************************/

#include "SaGame.h"
#include "SaTime.h"
#include "SaEffect.h"
#include "SaDebugDraw.h"
#include <SakuraMaths/SaMatrix44.h>
#include "SaRenderState.h"
#include "SaResourceManager.h"
#include <cstdio>
#include "SaRender.h"
#include "SaInputManager.h"
#include PLATFORM_INCLUDE( SA_EFFECT_API_DIR/SaEffect_Platform.h )

using namespace Sakura;
using namespace SakuraMaths;
using namespace SakuraThread;

SaGame::SaGame() :
    m_bRunning(false),
    m_bError(false)
{
}

SaGame::SaGame(SaGameProperties& rProperties) :
    m_bRunning(false),
    m_bError(false),
    m_gameProperties(rProperties)
{
}

SaGame::~SaGame()
{
}

void SaGame::Run()
{
    SA_ASSERT(!m_bRunning, "Already running.");

    if (m_bRunning)
        return;

    Initialise();
    m_bRunning = true;

    uint32_t lastTime = SaTime::GetTimeMilliseconds();
    uint32_t deltaTime = 16;
    uint32_t timeAcc = 0;

    while (m_bRunning && !m_bError)
    {
        uint32_t newTime = SaTime::GetTimeMilliseconds();
        uint32_t frameTime = newTime - lastTime;
        lastTime = newTime;

        timeAcc += frameTime;

        uint32_t numUpdates = 0;

        //Run as many updates as is required to catch back up to the current time 
        //and then do one render. Lather, rinse, repeat.
        while (timeAcc >= deltaTime)
        {
            Update(deltaTime);
            PostUpdate();

            timeAcc -= deltaTime;

            //Protect against spiral of death. This breaks determinism, however.
            if (++numUpdates > 2)
            {
                SA_PRINTF("Dropping updates!\n");
                break;
            }
        }

        if (numUpdates > 0)
        {
            m_window.PreRender();

            for (uint32_t viewportIdx = 0; viewportIdx < m_window.GetNumViewports(); viewportIdx++)
            {
                if (viewportIdx > 0)
                {

                }

                m_window.GetViewport(viewportIdx).PreRender();

                SaRender::SetDepthTest(true);
                Render3D();
                SaDebugDraw::Render3D();

                SaRender::SetDepthTest(false);
                Render2D();
                SaDebugDraw::Render2D();
            }

            m_window.PostRender();

            SaRender::NextFrame();
        }
    }

    if (m_bError)
    {
        SA_PRINTF("Quitting because of error.\n");
    }

    Release();
}

void SaGame::Quit()
{
    m_bRunning = false;
}

void SaGame::Initialise()
{
    SaFile::Initialise();
    SaTime::Initialise();

    SaRender::Initialise();

    SaWindow::InitialiseSystem();
    WindowCreate();

    SaInputManager::Initialise();
    m_window.SetKeyboardInputHandler(&SaInputManager::GetKeyboard().GetInputHandler());

    SaResourceManager::InitParams params;
    params.TextureHashTableSize = m_gameProperties.m_textureHashTableSize;
    params.EffectHashTableSize = m_gameProperties.m_effectHashTableSize;
    params.ModelHashTableSize = m_gameProperties.m_modelHashTableSize;

    SaResourceManager::Initialise(params);

    SaEffect::Initialise();
    SaDebugDraw::Initialise();
}

void SaGame::Release()
{
    SaDebugDraw::Release();
    SaResourceManager::Release();

    SaInputManager::Release();

    SaWindow::TerminateSystem();

    SaRender::Release();
    SaFile::Release();
}

void SaGame::Update(uint32_t dt)
{
    SaWindow::UpdateSystem();

    //m_scene.Update(dt);   //Not using scene yet.
    m_window.Update(dt);
}

void SaGame::PostUpdate()
{
}

void SaGame::Render3D()
{
    //m_scene.Render(); //Not using scene yet.
}

void SaGame::Render2D()
{
}

void SaGame::WindowCreate()
{
    m_window.Initialise(m_gameProperties.m_name,
                        m_gameProperties.m_xResolution,
                        m_gameProperties.m_yResolution);

    SaMatrix44 mat2DProjection = SaMatrix44::CreateOrthographicProjection(0.0f, (float)m_gameProperties.m_xResolution,
                                                                          (float)m_gameProperties.m_yResolution, 0.0f,
                                                                          -1.0f, 1.0f);
    SaRenderState::Set2DProjectionMatrix(mat2DProjection);
}

const SaGameProperties& SaGame::GetGameProperties()
{
    return m_gameProperties;
}
