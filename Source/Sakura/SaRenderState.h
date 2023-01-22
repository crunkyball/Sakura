/*************************************************************
Sakura Game Framework : SaRenderState.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_RENDER_STATE_H
#define _SA_RENDER_STATE_H

#include "SaCore.h"
#include <SakuraMaths/SaMatrix44.h>

namespace Sakura
{
    //This class is static for now as I'm only having one render state for the back buffer.
    //When I implement render targets this may need to change as I might need a render state 
    //for each render target.
    class SaRenderState
    {
    public:
        static void SetViewMatrix(const SakuraMaths::SaMatrix44& rMatrix) { m_viewMatrix = rMatrix; }
        static void SetProjectionMatrix(const SakuraMaths::SaMatrix44& rMatrix) { m_projectionMatrix = rMatrix; }

        static const SakuraMaths::SaMatrix44& GetViewMatrix()  { return m_viewMatrix; }
        static const SakuraMaths::SaMatrix44& GetProjectionMatrix() { return m_projectionMatrix; }

        static void Set2DProjectionMatrix(const SakuraMaths::SaMatrix44& rMatrix) { m_2DprojectionMatrix = rMatrix; }
        static const SakuraMaths::SaMatrix44& Get2DProjectionMatrix() { return m_2DprojectionMatrix; }

    private:
        static SakuraMaths::SaMatrix44 m_viewMatrix;
        static SakuraMaths::SaMatrix44 m_projectionMatrix;

        static SakuraMaths::SaMatrix44 m_2DprojectionMatrix;
    };
}

#endif  //_SA_RENDER_STATE_H
