/*************************************************************
Sakura Game Framework : SaViewport_Platform.h
Author: Darrell Blake

OpenGL/GLFW platform implementation for SaViewport.
*************************************************************/

#ifndef _SA_VIEWPORT_PLATFORM_H
#define _SA_VIEWPORT_PLATFORM_H

#include "../../../SaCore.h"

namespace Sakura
{
    class SaViewport;

    class SaViewport_Platform
    {
    public:
        SaViewport_Platform(SaViewport* pParent);

        void PreRender();

    private:
        SaViewport* m_pParent;
    };
}

#endif  //_SA_VIEWPORT_PLATFORM_H
