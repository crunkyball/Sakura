/*************************************************************
Sakura Game Framework : SaViewport.h
Author: Darrell Blake
*************************************************************/

#ifndef _SA_VIEWPORT_H
#define _SA_VIEWPORT_H

#include "SaCore.h"
#include "SaColour.h"
#include PLATFORM_INCLUDE( SA_WINDOW_API_DIR/SaViewport_Platform.h )

namespace Sakura
{
    class SaCamera;
    class SaRenderJob;

    class SaViewport    
    {
        friend class SaViewport_Platform;

    public:
        SaViewport();

        void Initialise(uint32_t xPosition, uint32_t yPosition, uint32_t width, uint32_t height, SaColour clearColour);
        void Release();

        void PreRender();

        void AttachCamera(const SaCamera* pCamera);

    private:
        void RenderThread_PreRender(const SaRenderJob* pJob);

        SaViewport_Platform m_platformViewport;

        uint32_t m_xPosition;
        uint32_t m_yPosition;
        uint32_t m_width;
        uint32_t m_height;
        SaColour m_clearColour;

        const SaCamera* m_pCamera;
    };
}

#endif  //_SA_VIEWPORT_H
